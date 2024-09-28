#include "../include/utils.hpp"
#include <cstring>
#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Недостаточно аргументов!" << std::endl;
        return 1;
    }

    int read_fd = atoi(argv[1]);
    int write_fd = atoi(argv[2]);

    char input[256];
    read(read_fd, input, sizeof(input));

    ToLowerCase(input);

    write(write_fd, input, strlen(input) + 1);

    close(read_fd);
    close(write_fd);

    return 0;
}
