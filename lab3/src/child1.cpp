#include "utils.hpp"
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define SHM_NAME "/shared_memory"
#define SHM_SIZE 256

int main() {
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("Error opening shared memory");
        return 1;
    }

    char *shared_memory = (char *)mmap(
        nullptr, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_memory == MAP_FAILED) {
        perror("Error mapping shared memory");
        return 1;
    }

    HandleProcessWork(shared_memory, ToLowerCase);

    munmap(shared_memory, SHM_SIZE);
    close(shm_fd);
    return 0;
}
