/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include "cmocka_utils.h"

#include "../src/approval_failure_reporter.h"

/* show is not testing - check test output */
static void show_quiet_reporter_prints_copy_command(void** state)
{
    (void)state; /* unused */

    approvals_use_reporter(approval_report_failure_quiet);

    print_message("On Windows system expect output of\n%s\n",
                  ">>>>>move /Y \"received_file.txt\" \"approved_file.txt\"<<<<<");
    approval_report_failure(
        (struct ApprovalFileNames){"approved_file.txt", "received_file.txt"},
        (struct ApprovalData){"ignored", "ignored"},
        (struct ApprovalVerifyLine){"ApprovalFailureReporterTest.c", 26});
}

static int reporters_called[3];

FailureReporterResult fakeReportA(struct ApprovalFileNames file_names,
                                  struct ApprovalData data,
                                  struct ApprovalVerifyLine verify_line)
{
    (void)file_names;  /* unused */
    (void)data;        /* unused */
    (void)verify_line; /* unused */
    reporters_called[0] += 1;
    return FailureReport_continue;
}

FailureReporterResult fakeReportB(struct ApprovalFileNames file_names,
                                  struct ApprovalData data,
                                  struct ApprovalVerifyLine verify_line)
{
    (void)file_names;  /* unused */
    (void)data;        /* unused */
    (void)verify_line; /* unused */
    reporters_called[1] += 1;
    return FailureReport_abort;
}

FailureReporterResult fakeReportC(struct ApprovalFileNames file_names,
                                  struct ApprovalData data,
                                  struct ApprovalVerifyLine verify_line)
{
    (void)file_names;  /* unused */
    (void)data;        /* unused */
    (void)verify_line; /* unused */
    reporters_called[2] += 1;
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

    approval_report_failure((struct ApprovalFileNames){"approved", "received"},
                            (struct ApprovalData){"ignored", "ignored"},
                            (struct ApprovalVerifyLine){"ApprovalFailureReporterTest.c", 65});

    assert_int_equal(1, reporters_called[0]);
    assert_int_equal(1, reporters_called[1]);
    assert_int_equal(0, reporters_called[2]);
}

FailureReporterResult mockReport(struct ApprovalFileNames file_names,
                                 struct ApprovalData data,
                                 struct ApprovalVerifyLine verify_line)
{
    assert_string_equal("approvedFileName", file_names.approved);
    assert_string_equal("receivedFileName", file_names.received);
    assert_string_equal("approved", data.approved);
    assert_string_equal("received", data.received);
    assert_string_equal("ApprovalFailureReporterTest.c", verify_line.file);
    assert_int_equal(91, verify_line.line);
    reporters_called[0] += 1;
    return FailureReport_continue;
}

static void test_pass_data_to_reporter(void** state)
{
    (void)state; /* unused */

    __approvals_set_final_reporter(fakeReportA); /* ignore final reporter */
    approvals_use_reporter(mockReport);
    reporters_called[0] = 0;

    approval_report_failure(
        (struct ApprovalFileNames){"approvedFileName", "receivedFileName"},
        (struct ApprovalData){"approved", "received"},
        (struct ApprovalVerifyLine){"ApprovalFailureReporterTest.c", 91});

    assert_int_equal(2, reporters_called[0]);
}

static void test_pass_data_to_final_reporter(void** state)
{
    (void)state; /* unused */

    __approvals_set_final_reporter(mockReport);
    reporters_called[0] = 0;

    approval_report_failure(
        (struct ApprovalFileNames){"approvedFileName", "receivedFileName"},
        (struct ApprovalData){"approved", "received"},
        (struct ApprovalVerifyLine){"ApprovalFailureReporterTest.c", 91});

    assert_int_equal(1, reporters_called[0]);
}

static void test_ignore_null_reporters(void** state)
{
    (void)state; /* unused */

    approvals_use_reporter(NULL);
    approvals_use_reporter(fakeReportA);
    reporters_called[0] = 0;

    approval_report_failure((struct ApprovalFileNames){"approved", "received"},
                            (struct ApprovalData){"ignored", "ignored"},
                            (struct ApprovalVerifyLine){"ApprovalFailureReporterTest.c", 65});

    assert_int_equal(1, reporters_called[0]);
}

static int reset_reporters(void** state)
{
    (void)state; /* unused */
    __approvals_set_final_reporter(NULL);
    approvals_clear_reporters();
    return 0;
}

int main(void)
{
    cmocka_print_test_suite;

    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test_teardown(show_quiet_reporter_prints_copy_command, reset_reporters), /* */
        cmocka_unit_test_teardown(test_abort_sequence_of_reporters, reset_reporters), /* */
        cmocka_unit_test_teardown(test_pass_data_to_reporter, reset_reporters), /* */
        cmocka_unit_test_teardown(test_pass_data_to_final_reporter, reset_reporters), /* */
        cmocka_unit_test_teardown(test_ignore_null_reporters, reset_reporters), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
