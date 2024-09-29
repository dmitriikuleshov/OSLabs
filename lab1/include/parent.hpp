#ifndef PARENT_HPP
#define PARENT_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void Parent(const char *pathToChild1, const char *pathToChild2);
void StartChildProcess(const char *pathToChild, int readFd[2], int writeFd[2]);
#endif // PARENT_HPP