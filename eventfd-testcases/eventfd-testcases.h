#ifndef EVENTFD_TESTCASES
#define EVENTFD_TESTCASES

#include "testcases-helper.h"

int testcase_create_eventfd()
{
    char *name = "create eventfd";
    int efd = eventfd(42, 0);
    if (efd == -1)
    {
        return fail2(name);
    }
    else
    {
        return pass(efd, name);
    }
}

int testcase_read_with_efd_semaphore_set()
{
    char *name = "read with EFD_SEMAPHORE set";
    int efd = eventfd(2, EFD_SEMAPHORE);

    uint64_t counter;
    int n = read_efd(efd, &counter);
    // printf("%ld\n", counter);
    if (n != 8 || counter != 1)
    {
        return fail(efd, name);
    }

    // read again
    read_efd(efd, &counter);
    // printf("%ld\n", counter);
    if (counter != 1)
    {
        return fail(efd, name);
    }

    // if call read_efd(efd, &counter) one more time, the thread would block
    return pass(efd, name);
}

int testcase_read_with_efd_semaphore_not_set()
{
    char *name = "read with EFD_SEMAPHORE not set";
    int efd = eventfd(42, EFD_SEMAPHORE ^ EFD_SEMAPHORE);

    uint64_t counter;
    int n = read_efd(efd, &counter);
    // printf("%ld\n", counter);
    if (n != 8 || counter != 42)
    {
        return fail(efd, name);
    }

    // if call read_efd(efd, &counter) one more time, the thread would block since the counter has reset to zero
    return pass(efd, name);
}

int testcase_read_with_efd_nonblock_set()
{
    char *name = "read with EFD_NONBLOCK set";
    int efd = eventfd(0, EFD_NONBLOCK);

    uint64_t counter;
    // read would return directly without blocking
    read_efd(efd, &counter);
    if (errno != EAGAIN)
    {
        return fail(efd, name);
    }

    return pass(efd, name);
}

#endif /* EVENTFD_TESTCASES */
