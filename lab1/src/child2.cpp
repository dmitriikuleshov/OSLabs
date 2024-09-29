#include "utils.hpp"
#include <cstring> // strlen
#include <iostream>
#include <unistd.h> // read, write

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Not enough arguments!" << std::endl;
        return 1;
    }

    int read_fd = atoi(argv[1]);
    int write_fd = atoi(argv[2]);

    char input[256];
    if (read(read_fd, input, sizeof(input)) == -1) {
        perror("Error when reading from pipe");
        return 1;
    };

    ReplaceSpacesWithUnderscore(input);

    if (write(write_fd, input, strlen(input) + 1) == -1) {
        perror("Error when writing to pipe");
        return 1;
    };

    close(read_fd);
    close(write_fd);

    return 0;
}