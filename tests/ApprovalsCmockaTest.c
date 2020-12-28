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

#include "../include/approvals_cmocka.h"

static void test_verify_txt(void** state)
{
    (void)state; /* unused */

    verify_txt("Some text.\nNew line.\n");
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_verify_txt), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
