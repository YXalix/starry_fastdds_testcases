#include <stdio.h>
#include <stdlib.h>
#include <sys/eventfd.h>
#include <pthread.h>
#include <unistd.h>

int main()
{
    int efd = eventfd(0, 0);
    if (efd == -1) {
        fprintf(stderr, "error: eventfd create\n");
        return -1;
    }

    uint64_t u;
    ssize_t n;

    u = 1;
    n = write(efd, &u, sizeof(uint64_t));
    if (n !=8) {
        fprintf(stderr, "error: eventfd write n:%d\n", n);
        goto error;
    }

    u = 2;
    n = write(efd, &u, sizeof(uint64_t));

    u = 3;
    n = write(efd, &u, sizeof(uint64_t));

    n = read(efd, &u, sizeof(uint64_t));
    if (u != 6 || n !=8) {
        fprintf(stderr, "error: eventfd read u:%d, n:%d\n", u, n);
        goto error;
    }

    close(efd);
    printf("^_^ eventfd test passed\n");
    return 0;


error:
    close(efd);
    return -1;
}
