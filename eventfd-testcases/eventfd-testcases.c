#include "eventfd-testcases.h"

int main()
{
    testcase_create_eventfd();

    testcase_read_with_efd_semaphore_set();
    testcase_read_with_efd_semaphore_not_set();
    testcase_read_with_efd_nonblock_set();

    testcase_write_with_efd_nonblock_set();
    testcase_write_multiple_values_with_efd_nonblock_set();
    testcase_write_u64_max_value();
    testcase_write_allowed_max_value_with_efd_nonblock_set();
    testcase_write_allowed_max_value_plus_one_with_efd_nonblock_set();

    testcase_block_read();
    testcase_block_write();

    testcase_select_read_eventfd();

    testcase_check_o_rdwr_status();
    testcase_check_o_nonblock_status();
    testcase_check_o_cloexec_status();
}
