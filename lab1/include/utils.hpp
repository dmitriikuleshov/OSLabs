#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstring> // for strlen()
#include <iostream>
#include <string>
#include <unistd.h> // for pipe(), fork(), execvp(), read(), write()

void ToLowerCase(char *str);
void ReplaceSpacesWithUnderscore(char *str);
#endif // UTILS_HPP