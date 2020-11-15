#include <setjmp.h> /* used by cmocka */
#include <stdarg.h> /* used by cmocka */
#include <stddef.h> /* used by cmocka */

#include <cmocka.h>
#include <stdio.h>

#include "../src/approval_failure_reporter.h"
#include "../src/approval_generic_diff_reporter.h"
#include "../src/file_utils.h"

static int has_file(const char* file, const char* test)
{
    if (approvals_file_exists(file)) {
        return 1;
    }

    fprintf(stderr, "Ignoring test %s, test file %s missing.\n", test, file);
    return 0;
}

static void show_windows_diff_reporter(void** state)
{
    (void)state; /* unused */
    if (!has_file(WINDOWS_KDIFF3.parameters, __func__)) {
        return;
    }

    approvals_use_reporter(approval_report_failure_generic_diff(WINDOWS_KDIFF3));

    approval_report_failure(
        (struct ApprovalFileNames){"tests/ApprovalGenericDiffReporterTest_approved.txt",
                                   "tests/ApprovalGenericDiffReporterTest_received.txt"});
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
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
