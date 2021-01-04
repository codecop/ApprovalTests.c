/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <setjmp.h> /* used by cmocka */
#include <stdarg.h> /* used by cmocka */
#include <stddef.h> /* used by cmocka */

#include <cmocka.h> /* see https://cmocka.org/ */

#include <approvals_cmocka.h> /* see https://github.com/codecop/ApprovalTests.c */
#include <approvals_reporters.h>

static void test_with_quiet_reporter(void** state)
{
    (void)state; /* unused */

    approvals_use_reporter(approval_report_failure_quiet);

    verify_txt("text");
}

static void test_with_diff_reporters(void** state)
{
    (void)state; /* unused */

    /* specific reporter
    approvals_use_reporter(approval_report_failure_generic_diff(&WINDOWS_DIFFS.KDIFF3));
    */
    /* or first working */
    approvals_use_reporter(approval_report_failure_generic_diff(approval_first_working_mac_diff()));
    approvals_use_reporter(approval_report_failure_generic_diff(approval_first_working_linux_diff()));
    approvals_use_reporter(approval_report_failure_generic_diff(approval_first_working_windows_diff()));

    verify_txt("text");
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_with_quiet_reporter), /* */
        cmocka_unit_test(test_with_diff_reporters), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
