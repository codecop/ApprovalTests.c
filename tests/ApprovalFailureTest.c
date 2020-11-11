#include <setjmp.h> /* used by cmocka */
#include <stdarg.h> /* used by cmocka */
#include <stddef.h> /* used by cmocka */

#include <cmocka.h>

#include "../include/approvals_cmocka.h"
#include "../include/approvals_reporters.h"
#include "../src/approval_failure_reporter.h"

static void show_quiet_reporter(void** state)
{
    (void)state; /* unused */

    approvals_use_reporter(approval_report_failure_quiet);
    /* verify_txt("text"); */
    approval_report_failure((struct ApprovalFileNames){"approved", "received"});
}

static int reporters_called[3];

FailureReporterResult fakeReportA(struct ApprovalFileNames file_names)
{
    (void)file_names; /* unused */
    reporters_called[0] = 1;
    return 0;
}

FailureReporterResult fakeReportB(struct ApprovalFileNames file_names)
{
    (void)file_names; /* unused */
    reporters_called[1] = 1;
    return 1;
}

FailureReporterResult fakeReportC(struct ApprovalFileNames file_names)
{
    (void)file_names; /* unused */
    reporters_called[2] = 1;
    return 0;
}

static void test_report_sequence_of_reporters(void** state)
{
    (void)state; /* unused */

    approvals_use_reporter(fakeReportA);
    approvals_use_reporter(fakeReportB);
    approvals_use_reporter(fakeReportC);
    reporters_called[0] = 0;
    reporters_called[1] = 0;
    reporters_called[2] = 0;

    approval_report_failure((struct ApprovalFileNames){"approved", "received"});

    assert_int_equal(1, reporters_called[0]);
    assert_int_equal(1, reporters_called[1]);
    assert_int_equal(0, reporters_called[2]);
}

static void show_windows_kdiff_reporter(void** state)
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
        cmocka_unit_test_teardown(show_quiet_reporter, reset_reporters), /* */
        cmocka_unit_test_teardown(test_report_sequence_of_reporters, reset_reporters), /* */
        cmocka_unit_test_teardown(show_windows_kdiff_reporter, reset_reporters), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
