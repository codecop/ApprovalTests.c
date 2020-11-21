/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <setjmp.h> /* used by cmocka */
#include <stdarg.h> /* used by cmocka */
#include <stddef.h> /* used by cmocka */

#include <cmocka.h>
#include <stdlib.h>

#include "../src/approval_writer.h"
#include "../src/file_utils.h"

static void test_create_approved_file_name(void** state)
{
    (void)state; /* unused */

    const struct ApprovalBaseName name = {
        "tests/ApprovalWriterTest.test_create_approved_file_name", "txt"};

    const char* file_name = approval_writer_create_approved_file_name(name);

    assert_string_equal(
        "tests/ApprovalWriterTest.test_create_approved_file_name.approved.txt", file_name);

    free((void*)file_name);
}

static void test_create_received_file_name(void** state)
{
    (void)state; /* unused */

    const struct ApprovalBaseName name = {
        "tests/ApprovalWriterTest.test_create_received_file_name", "txt"};

    const char* file_name = approval_writer_create_received_file_name(name);

    assert_string_equal(
        "tests/ApprovalWriterTest.test_create_received_file_name.received.txt", file_name);

    free((void*)file_name);
}

static void test_write_received_file(void** state)
{
    (void)state; /* unused */

    const struct ApprovalBaseName name = {
        "tests/ApprovalWriterTest.test_write_received_file", "txt"};

    const char* text = "abc123";
    approval_writer_write_received_file(name, text);

    const char* file_name =
        "tests/ApprovalWriterTest.test_write_received_file.received.txt";
    bool exists; /* type hack to accept bool */
    assert_true(exists = approvals_file_exists(file_name));
    const char* read = approvals_load_text_file(file_name);
    assert_string_equal(text, read);
    approval_writer_delete_received_file(name);
    assert_false(exists = approvals_file_exists(file_name));

    free((void*)read);
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_create_approved_file_name), /* */
        cmocka_unit_test(test_create_received_file_name), /* */
        cmocka_unit_test(test_write_received_file),       /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
