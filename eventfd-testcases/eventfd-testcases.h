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

int testcase_write_with_efd_nonblock_set()
{
    char *name = "write with EFD_NONBLOCK set";
    int efd = eventfd(0, EFD_NONBLOCK);
    int n = write_efd(efd, 42);
    if (n != 8)
    {
        return fail(efd, name);
    }

    uint64_t counter;
    read_efd(efd, &counter);
    if (counter != 42)
    {
        return fail(efd, name);
    }

    return pass(efd, name);
}

int testcase_write_multiple_values_with_efd_nonblock_set()
{
    char *name = "write multiple values with EFD_NONBLOCK set";
    int efd = eventfd(0, EFD_NONBLOCK);
    write_efd(efd, 1);
    write_efd(efd, 2);
    write_efd(efd, 3);

    uint64_t counter;
    read_efd(efd, &counter);
    if (counter != 6)
    {
        return fail(efd, name);
    }

    return pass(efd, name);
}

int testcase_write_u64_max_value()
{
    char *name = "write max u64 value(0xffffffffffffffff)";
    int efd = eventfd(1, 0);
    int n = write_efd(efd, 0xffffffffffffffff);
    if (errno != EINVAL)
    {
        return fail(efd, name);
    }

    errno = 0;
    return pass(efd, name);
}

int testcase_write_allowed_max_value_with_efd_nonblock_set()
{
    char *name = "write allowed max(0xfffffffffffffffe) value with EFD_NONBLOCK set";
    int efd = eventfd(0, EFD_NONBLOCK);
    int n = write_efd(efd, 0xfffffffffffffffe);

    uint64_t counter;
    read_efd(efd, &counter);
    if (counter != 0xfffffffffffffffe)
    {
        return fail(efd, name);
    }

    return pass(efd, name);
}

int testcase_write_allowed_max_value_plus_one_with_efd_nonblock_set()
{
    char *name = "write allowed max value(0xfffffffffffffffe) plus one with EFD_NONBLOCK set";
    int efd = eventfd(1, EFD_NONBLOCK);
    int n = write_efd(efd, 0xfffffffffffffffe);
    if (errno != EAGAIN)
    {
        return fail(efd, name);
    }

    errno = 0;
    return pass(efd, name);
}

int testcase_block_read()
{
    char *name = "block read: read zero (with EFD_NONBLOCK not set)";
    int efd = eventfd(0, EFD_NONBLOCK ^ EFD_NONBLOCK);
    uint64_t counter;

    switch (fork())
    {
    case 0:                      // child
        read_efd(efd, &counter); // should block
        pass(efd, name);
        exit(EXIT_SUCCESS);
    default: // parent
        sleep(1);
        write_efd(efd, 1); // unblock the read
        close(efd);
        return 0;
    }

    return fail(efd, name);
}

int testcase_block_write()
{
    char *name = "block write: write 1 to max value (with EFD_NONBLOCK not set)";
    int efd = eventfd(1, EFD_NONBLOCK ^ EFD_NONBLOCK);
    uint64_t counter;

    switch (fork())
    {
    case 0:                                 // child
        write_efd(efd, 0xfffffffffffffffe); // should block
        pass(efd, name);
        exit(EXIT_SUCCESS);
    default:
        sleep(1);
        read_efd(efd, &counter); // unblock the write
        close(efd);
        return 0;
    }

    return fail(efd, name);
}

int testcase_select_read_eventfd()
{
    char *name = "select read eventfd";
    int efd = eventfd(0, 0);
    int value_to_write = 42;
    uint64_t counter;
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(efd, &rfds);

    switch (fork())
    {
    case 0:                             // child
        write_efd(efd, value_to_write); // unblock select
        exit(EXIT_SUCCESS);
    }

    int retval = select(efd + 1, &rfds, NULL, NULL, NULL);
    if (retval > 0)
    {
        read_efd(efd, &counter);
        if (counter != value_to_write)
        {
            return fail(efd, name);
        }
        else
        {
            return pass(efd, name);
        }
    }

    return fail(efd, name);
}

int testcase_check_o_rdwr_status() {
    char *name = "check status O_RDWR";
    int efd = eventfd(0, 0);
    if (fcntl(efd, F_GETFD, O_RDWR) < 0) {
        return fail(efd, name);
    }

    pass(efd, name);
}

int testcase_check_o_nonblock_status() {
    char *name = "check status NONBLOCK";

    int efd = eventfd(0, 0);
    if (fcntl(efd, F_GETFD, O_NONBLOCK) > 0) {
        return fail(efd, name);
    }
    close(efd);

    efd = eventfd(0, EFD_NONBLOCK);
    if (fcntl(efd, F_GETFD, O_NONBLOCK) < 0) {
        return fail(efd, name);
    }

    pass(efd, name);
}

int testcase_check_o_cloexec_status() {
    char *name = "check status O_CLOEXEC";

    int efd = eventfd(0, 0);
    // use __O_CLOEXEC in Linux
    if (fcntl(efd, F_GETFD, O_CLOEXEC) > 0) {
        return fail(efd, name);
    }
    close(efd);

    efd = eventfd(0, EFD_CLOEXEC);
    // use __O_CLOEXEC in Linux
    if (fcntl(efd, F_GETFD, O_CLOEXEC) < 0) {
        return fail(efd, name);
    }

    pass(efd, name);
}

#endif /* EVENTFD_TESTCASES */
