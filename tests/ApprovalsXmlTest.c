#include <setjmp.h> /* used by cmocka */
#include <stdarg.h> /* used by cmocka */
#include <stddef.h> /* used by cmocka */

#include <cmocka.h>
#include <stdlib.h>

#include "../include/approvals_cmocka.h"

static void test_verify_xml(void** state)
{
    (void)state; /* unused */

    verify_xml("<nope />", "test_verify_xml");
}

static void test_format_xml_null(void** state)
{
    (void)state; /* unused */

    const char* xml = "<nope />";
    const char* formatted = __approvals_xml_format(xml);

    assert_string_equal("<nope />\n", formatted);
    free((void*)formatted);
}

static void test_format_single_intent(void** state)
{
    (void)state; /* unused */

    const char* xml = "<a>foo</a>";
    const char* formatted = __approvals_xml_format(xml);

    assert_string_equal("<a>\n  foo\n</a>\n", formatted);
    free((void*)formatted);
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_verify_xml),           /* */
        cmocka_unit_test(test_format_xml_null),      /* */
        cmocka_unit_test(test_format_single_intent), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
