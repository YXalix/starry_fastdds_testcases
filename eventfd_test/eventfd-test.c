#include <stdio.h>
#include <stdlib.h>
#include <sys/eventfd.h>
#include <pthread.h>
#include <unistd.h>

int test_count()
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
    printf("case 1: ^_^ eventfd count test passed\n");
    return 0;

error:
    close(efd);
    printf("case 1: eventfd count test failed\n");
    return -1;
}

int test_multiprocess()
{
    int efd;
    uint64_t u;
    ssize_t s;

    efd = eventfd(0, 0);

    switch(fork()) {
        case -1:
            fprintf(stderr, "error: fork");

        case 0: // 子进程
            for (int j = 1; j <= 3; j++) {
                printf("Child writing %d to efd\n", j);
                u = j;
                // 向eventfd内部写一个8字节大小的数据
                s = write(efd, &u, sizeof(uint64_t));
            }

            printf("Child completed write loop\n");

            exit(EXIT_SUCCESS);

        default: // 父进程
            sleep(1); // 先休眠1秒, 等待子进程写完数据

            //从eventfd中读取数据
            s = read(efd, &u, sizeof(uint64_t));

            printf("Parent read %d from efd\n", u);
            if (u == 6) {
                printf("case 2: ^_^ eventfd multi process test passed\n");
            } else {
                printf("case 2: eventfd multi process test failed\n");
            }
            exit(EXIT_SUCCESS);
    }
}

int main()
{
    test_count();
    test_multiprocess();
}

