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

static void test_approvals_verify(void** state)
{
    (void)state; /* unused */

    __approvals_approve("abc123", __FILE__, __func__, 42, "txt");
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_approvals_verify), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
