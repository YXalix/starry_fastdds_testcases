#ifndef TESTCASES_HELPER
#define TESTCASES_HELPER

#include <stdio.h>
#include <stdlib.h>
#include <sys/eventfd.h>
#include <pthread.h>
#include <unistd.h>

void pass(int efd, char* name) {
    close(efd);
    printf("[√] %s\n", name);
}

void fail(char* name) {
    fprintf(stderr, "[x] %s\n", name);
}

#endif /* TESTCASES_HELPER */

