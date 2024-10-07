/* anon_mmap.c

   Demonstrate how to share a region of mapped memory between a parent and
   child process without having to create a mapped file, either through the
   creation of an anonymous memory mapping or through the mapping of /dev/zero.
*/
#ifdef USE_MAP_ANON
#define _BSD_SOURCE /* Get MAP_ANONYMOUS definition */
#endif
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int *addr; /* Pointer to shared memory region */

    /* Parent creates mapped region prior to calling fork() */

#ifdef USE_MAP_ANON /* Use MAP_ANONYMOUS */
    addr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
                MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED)
        exit(-1);

#else /* Map /dev/zero */
    int fd;

    fd = open("/dev/zero", O_RDWR);
    if (fd == -1)
        exit(-1);

    addr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED)
        exit(-1);

    if (close(fd) == -1) /* No longer needed */
        exit(-1);
#endif
    *addr = 1; /* Initialize integer in mapped region */

    switch (fork()) { /* Parent and child share mapping */
    case -1:
        exit(-1);

    case 0: /* Child: increment shared integer and exit */
        printf("Child started, value = %d\n", *addr);
        (*addr)++;
        if (munmap(addr, sizeof(int)) == -1)
            exit(-1);
        exit(EXIT_SUCCESS);

    default: /* Parent: wait for child to terminate */
        if (wait(NULL) == -1)
            exit(-1);
        printf("In parent, value = %d\n", *addr);
        if (munmap(addr, sizeof(int)) == -1)
            exit(-1);
        exit(EXIT_SUCCESS);
    }
}
