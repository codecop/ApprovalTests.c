/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <setjmp.h> /* used by cmocka */
#include <stdarg.h> /* used by cmocka */
#include <stddef.h> /* used by cmocka */

#include <cmocka.h>

#include "../include/approvals_cmocka.h"

static void test_verify_txt(void** state)
{
    (void)state; /* unused */

    verify_txt("Some text.\nNew line.\n");
}

static void test_verify_empty_no_file(void** state)
{
    (void)state; /* unused */

    verify_txt("");
}

static void test_verify_xml(void** state)
{
    (void)state; /* unused */

    verify_xml("<nope />");
}

static void test_complex_complete_xml(void** state)
{
    (void)state; /* unused */

    verify_xml(
        "<orders><order id='1234'><product id='EVENT02' stylist='Celeste "
        "Pulchritudo'><price "
        "currency='USD'>149.99</price>Makeover</product></order><order "
        "id='1235'><product id='LIPSTICK01' weight='30'><price "
        "currency='USD'>14.99</price>Cherry Bloom</product></order></orders>");
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_verify_txt),           /* */
        cmocka_unit_test(test_verify_empty_no_file), /* */
        cmocka_unit_test(test_verify_xml),           /* */
        cmocka_unit_test(test_complex_complete_xml), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
