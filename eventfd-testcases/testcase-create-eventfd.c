#include "testcases-helper.h"

void testcase_create_eventfd() {
    char* name = "create eventfd";
    int efd = eventfd(42, 0);
    if (efd == -1) {
        fail(name);
    } else {
        pass(efd, name);
    }
}
