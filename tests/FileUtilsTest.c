#include <setjmp.h> /* jmp_buf for mocka */
#include <stdarg.h> /* va_start for mocka */
#include <stddef.h> /* size_t for mocka */

#include <cmocka.h>

#include "../src/file_utils.h"

static void create_if_needed(void** state)
{
    (void)state; /* unused */

    const char* test_file = "empty_temp_file_will_be_deleted";
    if (approvals_file_exists(test_file)) {
        approvals_delete_file(test_file);
    }
    assert_false(approvals_file_exists(test_file));

    approvals_create_if_needed(test_file);

    assert_true(approvals_file_exists(test_file));

    approvals_delete_file(test_file);
    assert_false(approvals_file_exists(test_file));
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(create_if_needed), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
