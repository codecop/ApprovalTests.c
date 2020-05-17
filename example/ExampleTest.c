#include <setjmp.h> /* used by cmocka */
#include <stdarg.h> /* used by cmocka */
#include <stddef.h> /* used by cmocka */

#include <approvals_cmocka.h> /* see https://github.com/codecop/ApprovalTests.c */
#include <cmocka.h>           /* see https://cmocka.org/ */
#include <stdlib.h>           /* used by approvals */

static void test_some_xml(void** state)
{
    (void)state; /* unused */

    verify_xml("<nope />");
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_some_xml), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
