#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstring> // strlen
#include <iostream>
#include <string>
#include <unistd.h> // read, write

void ToLowerCase(char *str);
void ReplaceSpacesWithUnderscore(char *str);
void HandleProcessWork(int argc, char *argv[], void (*StringOperation)(char *));

#endif // UTILS_HPP