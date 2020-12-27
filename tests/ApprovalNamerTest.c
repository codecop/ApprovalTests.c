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

#include "../src/approval_namer.h"
#include "../src/system_utils.h"

static void test_create_approval_base_name(void** state)
{
    (void)state; /* unused */

    const char* base_name = approval_namer_create_approval_name(__FILE__, __func__);

    assert_string_equal("tests" OS_SLASH
                        "ApprovalNamerTest"
                        "."
                        "test_create_approval_base_name",
                        base_name);

    free((void*)base_name);
}

static void test_create_approval_base_name_no_dot(void** state)
{
    (void)state; /* unused */

    const char* base_name = approval_namer_create_approval_name("file_no_dot", "method");

    assert_string_equal(
        "file_no_dot"
        "."
        "method",
        base_name);

    free((void*)base_name);
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_create_approval_base_name),        /* */
        cmocka_unit_test(test_create_approval_base_name_no_dot), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
