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

typedef struct {
    char* xml;
    char* expected_xml;
} FormatterTestCase;

FormatterTestCase test_cases[] = {
    {"<nope />", "<nope />\n"},                                   /* empty */
    {"<a>foo</a>", "<a>\n  foo\n</a>\n"},                         /* intent */
    {"<a><b>foo</b></a>", "<a>\n  <b>\n    foo\n  </b>\n</a>\n"}, /* nested */
};

static void test_format_xml(void** state)
{
    FormatterTestCase test_case = **(FormatterTestCase**)state;

    const char* xml = test_case.xml;
    const char* formatted = __approvals_xml_format(xml);

    assert_string_equal(test_case.expected_xml, formatted);
    free((void*)formatted);
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

static void test_format_multi_intent(void** state)
{
    (void)state; /* unused */

    const char* xml = "<a><b>foo</b></a>";
    const char* formatted = __approvals_xml_format(xml);

    assert_string_equal("<a>\n  <b>\n    foo\n  </b>\n</a>\n", formatted);
    free((void*)formatted);
}

static void test_format_sibling_intent(void** state)
{
    (void)state; /* unused */

    const char* xml = "<r><a>bar</a><b>foo</b></r>";
    const char* formatted = __approvals_xml_format(xml);

    assert_string_equal("<r>\n  <a>\n    bar\n  </a>\n  <b>\n    foo\n  </b>\n</r>\n", formatted);
    free((void*)formatted);
}

static void test_format_sibling_text(void** state)
{
    (void)state; /* unused */

    const char* xml = "<r><a>bar</a>foo</r>";
    const char* formatted = __approvals_xml_format(xml);

    assert_string_equal("<r>\n  <a>\n    bar\n  </a>\n  foo\n</r>\n", formatted);
    free((void*)formatted);
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_verify_xml),                          /* */
        cmocka_unit_test_prestate(test_format_xml, &test_cases[0]), /* */
        cmocka_unit_test(test_format_xml_null),                     /* */
        cmocka_unit_test(test_format_single_intent),                /* */
        cmocka_unit_test(test_format_multi_intent),                 /* */
        cmocka_unit_test(test_format_sibling_intent),               /* */
        cmocka_unit_test(test_format_sibling_text),                 /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
