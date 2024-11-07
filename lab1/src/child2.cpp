#include "utils.hpp"
#include <cstring> // strlen
#include <iostream>
#include <unistd.h> // read, write

int main(int argc, char *argv[]) {
    HandleProcessWork(argc, argv, ReplaceSpacesWithUnderscore);
    return 0;
}