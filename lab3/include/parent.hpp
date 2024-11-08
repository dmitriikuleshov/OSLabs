#ifndef PARENT_HPP
#define PARENT_HPP

#include <csignal> // kill, SIGUSR1, SIGUSR2
#include <fcntl.h> // O_CREAT, O_RDWR
#include <iostream>
#include <sys/mman.h>  // mmap, munmap, shm_open
#include <sys/types.h> // pid_t
#include <sys/wait.h>  // waitpid
#include <unistd.h>    // ftruncate, fork

void StartChildProcess(const char *pathToChild);
void Parent(const char *pathToChild1, const char *pathToChild2);

#endif // PARENT_HPP
