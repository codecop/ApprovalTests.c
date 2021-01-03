/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include "cmocka_utils.h"
#include <stdlib.h>

#include "cmocka_assume_file.c"

#include "../src/exec_utils.h"
#include "../src/system_utils.h"

/* My local installations */
const char* tortoiseHg = "C:\\Program Files\\TortoiseHg\\bin\\kdiff3.exe";
const char* kdiff3 = "C:\\Program Files (x86)\\KDiff3\\kdiff3.exe";
const char* linux_kdiff3 = "/usr/bin/kdiff3";

static void test_resolve_existing_file(void** state)
{
    (void)state; /* unused */
    assume_has_file(tortoiseHg);

    const char* diff_program = "C:\\Program Files\\TortoiseHg\\bin\\kdiff3.exe";
    const char* resolved = approval_create_resolved_path(diff_program);

    assert_non_null(resolved);
    assert_string_equal(tortoiseHg, resolved);

    if (resolved) {
        free((void*)resolved);
    }
}

static void test_not_resolve_missing_file(void** state)
{
    (void)state; /* unused */

    const char* diff_program = "/this_does_not_exist.exe";
    const char* resolved = approval_create_resolved_path(diff_program);

    assert_null(resolved);
}

static void test_resolve_windows_program_files(void** state)
{
    (void)state; /* unused */
    assume_has_file(tortoiseHg);

    const char* diff_program = "{ProgramFiles}TortoiseHg\\bin\\kdiff3.exe";
    const char* resolved = approval_create_resolved_path(diff_program);

    assert_non_null(resolved);
    assert_string_equal(tortoiseHg, resolved);

    if (resolved) {
        free((void*)resolved);
    }
}

static void test_resolve_windows_x86_program_files(void** state)
{
    (void)state; /* unused */
    assume_has_file(kdiff3);

    const char* diff_program = "{ProgramFiles}KDiff3\\kdiff3.exe";
    const char* resolved = approval_create_resolved_path(diff_program);

    assert_non_null(resolved);
    assert_string_equal(kdiff3, resolved);

    if (resolved) {
        free((void*)resolved);
    }
}

static void test_resolve_linux_program_files(void** state)
{
    (void)state; /* unused */
    assume_has_file(linux_kdiff3);

    const char* diff_program = "{ProgramFiles}kdiff3";
    const char* resolved = approval_create_resolved_path(diff_program);

    assert_non_null(resolved);
    assert_string_equal(linux_kdiff3, resolved);

    if (resolved) {
        free((void*)resolved);
    }
}

static void test_not_resolve_missing_windows_file(void** state)
{
    (void)state; /* unused */

    const char* diff_program = "{ProgramFiles}this_does_not_exist.exe";
    const char* resolved = approval_create_resolved_path(diff_program);

    assert_null(resolved);
}

static void test_create_command_line(void** state)
{
    (void)state; /* unused */

    const char* command_line = approval_create_command_line(
        "kdiff3.exe", "%s %s", "received.file", "approved_file");

    assert_non_null(command_line);
#ifdef OS_WINDOWS
    assert_string_equal("\"kdiff3.exe\" received.file approved_file", command_line);
#else
    assert_string_equal("kdiff3.exe received.file approved_file", command_line);
#endif

    if (command_line) {
        free((void*)command_line);
    }
}

int main(void)
{
    cmocka_print_test_suite;

    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_resolve_existing_file),             /* */
        cmocka_unit_test(test_not_resolve_missing_file),          /* */
        cmocka_unit_test(test_resolve_windows_program_files),     /* */
        cmocka_unit_test(test_resolve_windows_x86_program_files), /* */
        cmocka_unit_test(test_resolve_linux_program_files),       /* */
        cmocka_unit_test(test_not_resolve_missing_windows_file),  /* */
        cmocka_unit_test(test_create_command_line),               /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
