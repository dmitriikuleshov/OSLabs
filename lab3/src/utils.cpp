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

void HandleProcessWork(char *shared_memory, void (*StringOperation)(char *)) {
    StringOperation(shared_memory); // Apply the operation to the string
}
