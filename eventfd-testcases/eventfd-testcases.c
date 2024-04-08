#include "eventfd-testcases.h"

int main()
{
    testcase_create_eventfd();
    testcase_read_with_efd_semaphore_set();
    testcase_read_with_efd_semaphore_not_set();
    testcase_read_with_efd_nonblock_set();
    testcase_write_with_efd_nonblock_set();
    testcase_write_multiple_values_with_efd_nonblock_set();
    testcase_write_max_value_with_efd_nonblock_set();
    testcase_write_max_value_plus_one_with_efd_nonblock_set();
}
