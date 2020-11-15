#include <setjmp.h> /* used by cmocka */
#include <stdarg.h> /* used by cmocka */
#include <stddef.h> /* used by cmocka */

#include <cmocka.h>

#include "../src/approval_failure_reporter.h"
#include "../src/approval_generic_diff_reporter.h"

static void show_windows_diff_reporter(void** state)
{
    (void)state; /* unused */

    approvals_use_reporter(approval_report_failure_generic_diff(WINDOWS_KDIFF3));

    approval_report_failure((struct ApprovalFileNames){"approved", "received"});
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
