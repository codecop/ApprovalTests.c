/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
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
const char* windows_kdiff3 = "C:\\Program Files (x86)\\KDiff3\\kdiff3.exe";
const char* linux_kdiff3 = "/usr/bin/kdiff3";

static bool has_file(const char* file, const char* test)
{
    if (approvals_file_exists(file)) {
        return true;
    }

    fprintf(stderr, "Ignoring test %s, test file %s missing.\n", test, file);
    return false;
    /* TODO duplication, extract test helper to include directly */
}

#define assume_has_file(needed_file)                         \
    {                                                        \
        _assume_has_file((needed_file), __FILE__, __LINE__); \
    }

static void _assume_has_file(const char* needed_file, const char* file, const int line)
{
    if (approvals_file_exists(needed_file)) {
        return;
    }

    fprintf(stderr, "[          ] - test file %s missing.\n", needed_file);
    _skip(file, line);
}

/* show is not testing - check test output */
static void show_windows_diff_reporter(void** state)
{
    (void)state; /* unused */

    approvals_use_reporter(approval_report_failure_generic_diff(WINDOWS_DIFFS.KDIFF3));

    approval_report_failure(
        (struct ApprovalFileNames){"tests/ApprovalGenericDiffReporterTest_approved.txt",
                                   "tests/ApprovalGenericDiffReporterTest_received.txt"},
        (struct ApprovalData){"ignored", "ignored"},
        (struct ApprovalVerifyLine){"tests/ApprovalGenericDiffReporterTest.c", 58});
}

static void test_find_no_working_reporter(void** state)
{
    (void)state; /* unused */

    struct DiffInfo* diff = approval_first_working_mac_diff(&MAC_DIFFS);

    assert_null(diff);
}

static void test_find_first_working_windows_reporter(void** state)
{
    (void)state; /* unused */
    if (!has_file(windows_kdiff3, __func__)) {
        skip();
        return;
    }

    struct DiffInfo* diff = approval_first_working_windows_diff(&WINDOWS_DIFFS);

    assert_string_equal(WINDOWS_DIFFS.KDIFF3.diff_program, diff->diff_program);
}

static void test_find_first_working_linux_reporter(void** state)
{
    (void)state; /* unused */
    assume_has_file(linux_kdiff3);

    struct DiffInfo* diff = approval_first_working_linux_diff(&LINUX_DIFFS);

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
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test_teardown(show_windows_diff_reporter, reset_reporters), /* */
        cmocka_unit_test(test_find_no_working_reporter),                        /* */
        cmocka_unit_test(test_find_first_working_windows_reporter),             /* */
        cmocka_unit_test(test_find_first_working_linux_reporter),               /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
