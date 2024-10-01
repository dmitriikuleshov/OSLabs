#ifndef PARENT_HPP
#define PARENT_HPP

#include <iostream>
#include <stdlib.h>
#include <sys/types.h> // pid_t
#include <sys/wait.h>  // waitpid, pipe
#include <unistd.h>    // pipe

void StartChildProcess(const char *pathToChild, int readFd[2], int writeFd[2]);
void Parent(const char *pathToChild1, const char *pathToChild2);

#endif // PARENT_HPP