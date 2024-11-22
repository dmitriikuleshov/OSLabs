#include "parent.hpp"

#define SHM_NAME "/shared_memory"
#define SHM_SIZE 256

void StartChildProcess(const char *pathToChild) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("Error creating the process");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        char *args[] = {const_cast<char *>(pathToChild), nullptr};
        if (execvp(args[0], args) == -1) {
            perror("Error when starting a child program");
            exit(EXIT_FAILURE);
        }
    }
}

void Parent(const char *pathToChild1, const char *pathToChild2) {
    // Create a shared memory file
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("Error creating shared memory");
        exit(EXIT_FAILURE);
    }
    ftruncate(shm_fd, SHM_SIZE); // Set size

    // Map the file into memory
    // nullptr - pointer to address where the process is going to map object to
    // into memory MAP_SHARED or MAP_PRIVATE 0 - shift
    char *shared_memory = (char *)mmap(
        nullptr, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    if (shared_memory == MAP_FAILED) {
        perror("Error mapping shared memory");
        exit(EXIT_FAILURE);
    }

    // User input
    std::cout << "Enter your text: ";
    std::cin.getline(shared_memory, SHM_SIZE);

    // Start the first child process
    StartChildProcess(pathToChild1);
    wait(nullptr); // Wait for child1 to finish

    // Start the second child process
    StartChildProcess(pathToChild2);
    wait(nullptr); // Wait for child2 to finish

    // Output the result
    std::cout << shared_memory << std::endl;

    // Cleanup
    munmap(shared_memory, SHM_SIZE);
    close(shm_fd);
    shm_unlink(SHM_NAME);
}
