#include <setjmp.h> /* used by cmocka */
#include <stdarg.h> /* used by cmocka */
#include <stddef.h> /* used by cmocka */

#include <cmocka.h>
#include <stdbool.h>
#include <stdio.h>

#include "../src/approval_failure_reporter.h"
#include "../src/approval_generic_diff_reporter.h"
#include "../src/file_utils.h"

/* My local installations */
const char* kdiff3 = "C:\\Program Files (x86)\\KDiff3\\kdiff3.exe";

static bool has_file(const char* file, const char* test)
{
    if (approvals_file_exists(file)) {
        return true;
    }

    fprintf(stderr, "Ignoring test %s, test file %s missing.\n", test, file);
    return false;
    /* TODO duplication, extract test helper to include directly */
}

/* show is not testing - check test output */
static void show_windows_diff_reporter(void** state)
{
    (void)state; /* unused */

    approvals_use_reporter(approval_report_failure_generic_diff(WINDOWS_DIFFS.KDIFF3));

    approval_report_failure(
        (struct ApprovalFileNames){"tests/ApprovalGenericDiffReporterTest_approved.txt",
                                   "tests/ApprovalGenericDiffReporterTest_received.txt"});
}

static void test_find_no_working_reporter(void** state)
{
    (void)state; /* unused */

    struct DiffInfo* all_diffs = (struct DiffInfo*)&MAC_DIFFS;
    struct DiffInfo* diff = approval_first_working_diff(all_diffs);

    assert_null(diff);
}

static void test_find_first_working_reporter(void** state)
{
    (void)state; /* unused */
    if (!has_file(kdiff3, __func__)) {
        return;
    }

    struct DiffInfo* all_diffs = (struct DiffInfo*)&WINDOWS_DIFFS;
    struct DiffInfo* diff = approval_first_working_diff(all_diffs);

    assert_string_equal(WINDOWS_DIFFS.KDIFF3.diff_program, diff->diff_program);
}

static int reset_reporters(void** state)
{
    (void)state; /* unused */
    approvals_clear_reporters();
    return 0;
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test_teardown(show_windows_diff_reporter, reset_reporters), /* */
        cmocka_unit_test(test_find_no_working_reporter),                        /* */
        cmocka_unit_test(test_find_first_working_reporter),                     /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
