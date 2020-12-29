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

#include "../include/approvals.h"

static void test_approvals_approve(void** state)
{
    (void)state; /* unused */

    __approvals_approve("abc123", __FILE__, __func__, __LINE__, "txt");
}

static void show_approvals_fail(void** state)
{
    (void)state; /* unused */

    /*
    __approvals_approve("missing", __FILE__, __func__, __LINE__, "txt");
    */
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_approvals_approve), /* */
        cmocka_unit_test(show_approvals_fail),    /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
