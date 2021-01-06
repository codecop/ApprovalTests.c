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

static void test_one(void** state)
{
    (void)state; /* unused */

    verify_txt("text");
}

static void test_two(void** state)
{
    (void)state; /* unused */

    verify_txt("text");
}

int main(void)
{
    /* first quiet reporter */
    approvals_use_reporter(approval_report_failure_quiet);
    /* then a specific reporter
    approvals_use_reporter(approval_report_failure_generic_diff(&WINDOWS_DIFFS.KDIFF3));
    */
    /* or first working one */
    approvals_use_reporter(approval_report_failure_generic_diff(approval_first_working_mac_diff()));
    approvals_use_reporter(approval_report_failure_generic_diff(approval_first_working_linux_diff()));
    approvals_use_reporter(approval_report_failure_generic_diff(approval_first_working_windows_diff()));

    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_one), /* */
        cmocka_unit_test(test_two), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
