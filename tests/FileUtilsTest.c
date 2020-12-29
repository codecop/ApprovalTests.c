/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <setjmp.h> /* jmp_buf for mocka */
#include <stdarg.h> /* va_start for mocka */
#include <stddef.h> /* size_t for mocka */

#include <cmocka.h>
#include <stdbool.h>

#include "../src/file_utils.h"

static void test_create_file_if_needed(void** state)
{
    (void)state; /* unused */

    const char* test_file = "empty_temp_file_will_be_deleted";
    if (approval_file_exists(test_file)) {
        approval_delete_file(test_file);
    }
    bool exists; /* type hack to accept bool */
    assert_false(exists = approval_file_exists(test_file));

    bool result = approval_create_if_needed(test_file);
    long size = approval_file_size(test_file);

    assert_true(exists = approval_file_exists(test_file));
    assert_true(result);
    assert_int_equal(0, size);

    approval_delete_file(test_file);
    exists = approval_file_exists(test_file);
    assert_false(exists);
}

static void test_leave_file_alone_if_exists(void** state)
{
    (void)state; /* unused */

    const char* test_file = "tests/FileUtilsTest.existing_file.txt";

    bool result = approval_create_if_needed(test_file);

    assert_false(result);
}

static void test_size_of_non_empty_file(void** state)
{
    (void)state; /* unused */

    const char* test_file = "tests/FileUtilsTest.existing_file.txt";

    long result = approval_file_size(test_file);

    assert_int_equal(82, result);
}

static void test_size_of_missing_file(void** state)
{
    (void)state; /* unused */

    const char* test_file = "tests/FileUtilsTest.non_existing_file.txt";

    long result = approval_file_size(test_file);

    assert_int_equal(0, result);
}

static void test_remove_of_missing_file(void** state)
{
    (void)state; /* unused */

    const char* test_file = "tests/FileUtilsTest.non_existing_file.txt";

    bool result = approval_delete_file(test_file);

    assert_false(result);
}

static void test_load_of_missing_file(void** state)
{
    (void)state; /* unused */

    const char* test_file = "tests/FileUtilsTest.non_existing_file.txt";

    const char* result = approval_load_text_file(test_file);

    assert_string_equal("", result);
}

static void test_save_empty_string(void** state)
{
    (void)state; /* unused */

    const char* test_file = "empty_temp_file_will_be_deleted";
    bool exists = approval_file_exists(test_file);
    if (exists) {
        approval_delete_file(test_file);
    }

    approval_save_text_file(test_file, "");

    exists = approval_file_exists(test_file);
    assert_true(exists);

    approval_delete_file(test_file);
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_create_file_if_needed),      /* */
        cmocka_unit_test(test_leave_file_alone_if_exists), /* */
        cmocka_unit_test(test_size_of_non_empty_file),     /* */
        cmocka_unit_test(test_size_of_missing_file),       /* */
        cmocka_unit_test(test_remove_of_missing_file),     /* */
        cmocka_unit_test(test_load_of_missing_file),       /* */
        cmocka_unit_test(test_save_empty_string),          /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
