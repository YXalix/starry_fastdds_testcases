#ifndef TESTCASES_HELPER
#define TESTCASES_HELPER

#include <stdio.h>
#include <stdlib.h>
#include <sys/eventfd.h>
#include <pthread.h>
#include <unistd.h>

// print test pass result and close eventfd
void pass(int efd, char* name) {
    close(efd);
    printf("[√] %s (passed)\n", name);
}

// print test failure result
void fail(char* name) {
    fprintf(stderr, "[x] %s (failed)\n", name);
}

// print test failure result and close eventfd
void fail2(int efd, char* name) {
    close(efd);
    fprintf(stderr, "[x] %s (failed)\n", name);
}

#endif /* TESTCASES_HELPER */
