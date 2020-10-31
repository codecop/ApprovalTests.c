#include <setjmp.h> /* used by cmocka */
#include <stdarg.h> /* used by cmocka */
#include <stddef.h> /* used by cmocka */

#include <cmocka.h>

#include "../src/approval_writer.h"
#include "../src/file_utils.h"

static void test_get_approved_file_name(void** state)
{
    (void)state; /* unused */

    assert_string_equal(
        "tests/ApprovalWriterTest.test_get_approved_file_name.approved.txt",
        approvals_get_approved_file_name(__FILE__, __func__, "txt"));
}

static void test_write_received_file(void** state)
{
    (void)state; /* unused */

    const char* s = "abc123";
    approvals_write_received_file(__FILE__, __func__, "txt", s);
    const char* r = approvals_load_text_file(
        "tests/ApprovalWriterTest.test_write_received_file.received.txt");
    assert_string_equal(s, r);
    approvals_delete_received_file(__FILE__, __func__, "txt");
    /* TODO assert file is gone */
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_get_approved_file_name), /* */
        cmocka_unit_test(test_write_received_file),    /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
