#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstring> // strlen
#include <iostream>
#include <string>
#include <unistd.h> // write, getpid

void ToLowerCase(char *str);
void ReplaceSpacesWithUnderscore(char *str);
void HandleProcessWork(char *shared_memory, void (*StringOperation)(char *));

#endif // UTILS_HPP
