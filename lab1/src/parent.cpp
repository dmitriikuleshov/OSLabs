#include "../include/parent.hpp"
#include "../include/utils.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void CreateChildProcess(const char *pathToChild, int readFd[2],
                        int writeFd[2]) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("Error creating the process");
        exit(1);
    }

    if (pid == 0) { // Child process
        close(readFd[1]);
        close(writeFd[0]);
        std::string readFdStr = std::to_string(readFd[0]);
        std::string writeFdStr = std::to_string(writeFd[1]);
        char *args[] = {const_cast<char *>(pathToChild),
                        const_cast<char *>(readFdStr.c_str()),
                        const_cast<char *>(writeFdStr.c_str()), nullptr};

        if (execvp(args[0], args) == -1) {
            perror("Error when starting a child program");
            exit(1);
        }

        _exit(0);
    }
}

void Parent(const char *pathToChild1, const char *pathToChild2) {
    int pipe_to_child1[2], pipe_between_child1_child2[2], pipe_from_child2[2];

    pid_t child1_pid, child2_pid;

    // Create pipes
    if (pipe(pipe_to_child1) == -1 || pipe(pipe_between_child1_child2) == -1 ||
        pipe(pipe_from_child2) == -1) {
        std::cerr << "Ошибка при создании pipe" << std::endl;
        exit(-1);
    }

    // User input
    char input[256];
    std::cout << "Enter your text: ";
    std::cin.getline(input, sizeof(input));

    write(pipe_to_child1[1], input, sizeof(input));
    close(pipe_to_child1[1]);

    CreateChildProcess(pathToChild1, pipe_to_child1,
                       pipe_between_child1_child2);

    close(pipe_to_child1[0]);
    close(pipe_between_child1_child2[1]);

    CreateChildProcess(pathToChild2, pipe_between_child1_child2,
                       pipe_from_child2);

    close(pipe_between_child1_child2[0]);
    close(pipe_from_child2[1]);

    read(pipe_from_child2[0], input, sizeof(input));
    std::cout << input << std::endl;
    close(pipe_from_child2[0]);

    waitpid(child1_pid, nullptr, 0);
    waitpid(child2_pid, nullptr, 0);
}
