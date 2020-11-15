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

    int result = approvals_create_if_needed(test_file);
    long size = approvals_file_size(test_file);

    assert_true(approvals_file_exists(test_file));
    assert_int_equal(1, result);
    assert_int_equal(0, size);

    approvals_delete_file(test_file);
    assert_false(approvals_file_exists(test_file));
}

static void leave_alone_if_exists(void** state)
{
    (void)state; /* unused */

    const char* test_file = "tests/ApprovalsTest.test_verify_txt.approved.txt";

    int result = approvals_create_if_needed(test_file);

    assert_int_equal(0, result);
}

static void size_of_non_empty_file(void** state)
{
    (void)state; /* unused */

    const char* test_file = "tests/ApprovalsTest.test_verify_txt.approved.txt";

    long result = approvals_file_size(test_file);

    assert_int_equal(23, result);
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(create_if_needed),       /* */
        cmocka_unit_test(leave_alone_if_exists),  /* */
        cmocka_unit_test(size_of_non_empty_file), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
