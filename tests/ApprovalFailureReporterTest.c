#include <setjmp.h> /* used by cmocka */
#include <stdarg.h> /* used by cmocka */
#include <stddef.h> /* used by cmocka */

#include <cmocka.h>
#include <stdio.h>

#include "../src/approval_failure_reporter.h"

/* show is not testing - check test output */
static void show_quiet_reporter_prints_copy_command(void** state)
{
    (void)state; /* unused */

    approvals_use_reporter(approval_report_failure_quiet);

    printf("On Windows system expect output of\n%s\n",
           ">>>>>move /Y \"received_file.txt\" \"approved_file.txt\"<<<<<");
    approval_report_failure(
        (struct ApprovalFileNames){"approved_file.txt", "received_file.txt"});
}

static int reporters_called[3];

FailureReporterResult fakeReportA(struct ApprovalFileNames file_names)
{
    (void)file_names; /* unused */
    reporters_called[0] = 1;
    return FailureReport_continue;
}

FailureReporterResult fakeReportB(struct ApprovalFileNames file_names)
{
    (void)file_names; /* unused */
    reporters_called[1] = 1;
    return FailureReport_abort;
}

FailureReporterResult fakeReportC(struct ApprovalFileNames file_names)
{
    (void)file_names; /* unused */
    reporters_called[2] = 1;
    return FailureReport_continue;
}

static void test_abort_sequence_of_reporters(void** state)
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

static int reset_reporters(void** state)
{
    (void)state; /* unused */
    approvals_clear_reporters();
    return 0;
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test_teardown(show_quiet_reporter_prints_copy_command, reset_reporters), /* */
        cmocka_unit_test_teardown(test_abort_sequence_of_reporters, reset_reporters), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
