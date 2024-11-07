#include "parent.hpp"

void StartChildProcess(const char *pathToChild, int readFd[2], int writeFd[2]) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("Error creating the process");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        close(readFd[1]);
        close(writeFd[0]);
        std::string readFdStr = std::to_string(readFd[0]);
        std::string writeFdStr = std::to_string(writeFd[1]);
        char *args[] = {const_cast<char *>(pathToChild), readFdStr.data(),
                        writeFdStr.data(), nullptr};
        if (execvp(args[0], args) == -1) {
            perror("Error when starting a child program");
            exit(EXIT_FAILURE);
        }
    }
}

void Parent(const char *pathToChild1, const char *pathToChild2) {
    int pipe_to_child1[2], pipe_between_child1_child2[2], pipe_from_child2[2];

    // Create pipes
    if (pipe(pipe_to_child1) == -1 || pipe(pipe_between_child1_child2) == -1 ||
        pipe(pipe_from_child2) == -1) {
        std::cerr << "Error when creating pipe" << std::endl;
        exit(EXIT_FAILURE);
    }

    // User input
    char input[256];
    std::cout << "Enter your text: ";
    std::cin.getline(input, sizeof(input));

    if (write(pipe_to_child1[1], input, sizeof(input)) == -1) {
        perror("Error when writing to pipe");
        exit(EXIT_FAILURE);
    };

    // Close after writing
    close(pipe_to_child1[1]);

    StartChildProcess(pathToChild1, pipe_to_child1, pipe_between_child1_child2);
    // Close after child1 worked
    close(pipe_to_child1[0]);
    // Close unused (by parent process) side
    close(pipe_between_child1_child2[1]);

    StartChildProcess(pathToChild2, pipe_between_child1_child2,
                      pipe_from_child2);
    // Close after child2 worked
    close(pipe_between_child1_child2[0]);
    // Close unused (by parent process) side
    close(pipe_from_child2[1]);

    if (read(pipe_from_child2[0], input, sizeof(input)) == -1) {
        perror("Error when reading from pipe");
        exit(EXIT_FAILURE);
    };
    close(pipe_from_child2[0]);
    std::cout << input << std::endl;
}
