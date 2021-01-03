/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include "cmocka_utils.h"

#include "cmocka_assume_file.c"

#include "../src/approval_failure_reporter.h"
#include "../src/approval_generic_diff_reporter.h"

/* My local installations */
const char* windows_kdiff3 = "C:\\Program Files (x86)\\KDiff3\\kdiff3.exe";
const char* linux_kdiff3 = "/usr/bin/kdiff3";

/* show is not testing - check test output */
static void show_windows_diff_reporter(void** state)
{
    (void)state; /* unused */

    approvals_use_reporter(approval_report_failure_generic_diff(WINDOWS_DIFFS.KDIFF3));

    approval_report_failure(
        (const struct ApprovalFileNames){"tests/ApprovalGenericDiffReporterTest_approved.txt",
                                   "tests/ApprovalGenericDiffReporterTest_received.txt"},
        (const struct ApprovalData){"ignored", "ignored"},
        (const struct ApprovalVerifyLine){"tests/ApprovalGenericDiffReporterTest.c", 58});
}

static void test_find_no_working_reporter(void** state)
{
    (void)state; /* unused */

    const struct DiffInfo* diff = approval_first_working_mac_diff(&MAC_DIFFS);

    assert_null(diff);
}

static void test_find_first_working_windows_reporter(void** state)
{
    (void)state; /* unused */
    assume_has_file(windows_kdiff3);

    const struct DiffInfo* diff = approval_first_working_windows_diff(&WINDOWS_DIFFS);

    assert_string_equal(WINDOWS_DIFFS.KDIFF3.diff_program, diff->diff_program);
}

static void test_find_first_working_linux_reporter(void** state)
{
    (void)state; /* unused */
    assume_has_file(linux_kdiff3);

    const struct DiffInfo* diff = approval_first_working_linux_diff(&LINUX_DIFFS);

    assert_string_equal(LINUX_DIFFS.KDIFF3.diff_program, diff->diff_program);
}

static int reset_reporters(void** state)
{
    (void)state; /* unused */
    approvals_clear_reporters();
    return 0;
}

int main(void)
{
    cmocka_print_test_suite;

    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test_teardown(show_windows_diff_reporter, reset_reporters), /* */
        cmocka_unit_test(test_find_no_working_reporter),                        /* */
        cmocka_unit_test(test_find_first_working_windows_reporter),             /* */
        cmocka_unit_test(test_find_first_working_linux_reporter),               /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
