#include "utils.hpp"

void ToLowerCase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = std::tolower(static_cast<unsigned char>(str[i]));
    }
}

void ReplaceSpacesWithUnderscore(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            str[i] = '_';
        }
    }
}

void HandleProcessWork(int argc, char *argv[],
                       void (*StringOperation)(char *)) {
    if (argc < 3) {
        std::cerr << "Not enough arguments!" << std::endl;
        exit(EXIT_FAILURE);
    }

    int read_fd = atoi(argv[1]);
    int write_fd = atoi(argv[2]);

    char input[256];
    if (read(read_fd, input, sizeof(input)) == -1) {
        perror("Error when reading from pipe");
        exit(EXIT_FAILURE);
    }

    StringOperation(input);

    if (write(write_fd, input, strlen(input) + 1) == -1) {
        perror("Error when writing to pipe");
        exit(EXIT_FAILURE);
    }

    close(read_fd);
    close(write_fd);
}