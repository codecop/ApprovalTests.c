#include <setjmp.h> /* used by cmocka */
#include <stdarg.h> /* used by cmocka */
#include <stddef.h> /* used by cmocka */

#include <cmocka.h> /* see https://cmocka.org/ */

#include <approvals_cmocka.h> /* see https://github.com/codecop/ApprovalTests.c */
#include <stdlib.h>           /* used by approvals */

static void test_some_text(void** state)
{
    (void)state; /* unused */

    verify_txt("text");
}

static void test_some_xml(void** state)
{
    (void)state; /* unused */

    verify_xml("<xml />");
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_some_text), /* */
        cmocka_unit_test(test_some_xml),  /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
