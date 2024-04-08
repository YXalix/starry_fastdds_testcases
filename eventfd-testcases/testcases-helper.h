#ifndef TESTCASES_HELPER
#define TESTCASES_HELPER

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <sys/eventfd.h>
#include <sys/select.h>

// print test pass result and close eventfd
int pass(int efd, char *name)
{
    close(efd);
    printf("[√] %s (passed)\n", name);
    return 0;
}

// print test failure result and close eventfd
int fail(int efd, char *name)
{
    close(efd);
    fprintf(stderr, "[x] %s (failed)\n", name);
    return -1;
}

// print test failure result
int fail2(char *name)
{
    fprintf(stderr, "[x] %s (failed)\n", name);
    return -1;
}

// a simple wrapper on read
int read_efd(int efd, uint64_t *value)
{
    return read(efd, value, sizeof(uint64_t));
}

// a simple wrapper on write
int write_efd(int efd, uint64_t value)
{
    return write(efd, &value, sizeof(uint64_t));
}

#endif /* TESTCASES_HELPER */
