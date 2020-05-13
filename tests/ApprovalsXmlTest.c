#include <setjmp.h> /* used by cmocka */
#include <stdarg.h> /* used by cmocka */
#include <stddef.h> /* used by cmocka */

#include <cmocka.h>
#include <stdlib.h>

#include "../include/approvals_cmocka.h"

static void test_format_xml_null(void** state)
{
    (void)state; /* unused */

    const char* xml = "<nope />";
    const char* formatted = __approvals_xml_format(xml);

    assert_string_equal("<nope />", formatted);
    free((void*)formatted);
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_format_xml_null), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
