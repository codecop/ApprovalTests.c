#include <setjmp.h> /* used by cmocka */
#include <stdarg.h> /* used by cmocka */
#include <stddef.h> /* used by cmocka */

#include <cmocka.h>
#include <stdlib.h>

#include "../include/approvals_cmocka.h"

static void test_verify_xml_macro(void** state)
{
    (void)state; /* unused */

    verify_xml("<nope />", "test_verify_xml");
}

typedef struct {
    char* xml;
    char* expected_xml;
} FormatterTestCase;

FormatterTestCase test_cases[] = {
    {"<a />",                                /* format */
     "<a />\n"},                             /* - null case */
    {"<a>foo</a>",                           /* format */
     "<a>\n  foo\n</a>\n"},                  /* - a single element */
    {"<a><b>foo</b></a>",                    /* format */
     "<a>\n  <b>\n    foo\n  </b>\n</a>\n"}, /* - multi elements */
    {"<a><b>bar</b><b>foo</b></a>",          /* format */
     "<a>\n  <b>\n    bar\n  </b>\n  <b>\n    foo\n  </b>\n</a>\n"}, /* - siblings */
    {"<a><b>bar</b>foo</a>",                                         /* format */
     "<a>\n  <b>\n    bar\n  </b>\n  foo\n</a>\n"},                  /* - text */
};

/* TODO test list
 * <?xml version="1.0" encoding="UTF-8"?>
 * ignore whitespace (' ', \n) outside of tags, after > and before <
 * ignore additional whitespace in attributes
 * CDATA
 * Comments <!-- -->
 */

static void test_format_xml(void** state)
{
    FormatterTestCase test_case = **(FormatterTestCase**)state;

    const char* xml = test_case.xml;
    const char* formatted = __approvals_xml_format(xml);

    assert_string_equal(test_case.expected_xml, formatted);
    free((void*)formatted);
}

static void test_complex_complete_xml(void** state)
{
    (void)state; /* unused */

    verify_xml(
        "<orders><order id='1234'><product id='EVENT02' stylist='Celeste "
        "Pulchritudo'><price "
        "currency='USD'>149.99</price>Makeover</product></order><order "
        "id='1235'><product id='LIPSTICK01' weight='30'><price "
        "currency='USD'>14.99</price>Cherry Bloom</product></order></orders>",
        "test_orders_xml");
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_verify_xml_macro),                    /* */
        cmocka_unit_test_prestate(test_format_xml, &test_cases[0]), /* */
        cmocka_unit_test_prestate(test_format_xml, &test_cases[1]), /* */
        cmocka_unit_test_prestate(test_format_xml, &test_cases[2]), /* */
        cmocka_unit_test_prestate(test_format_xml, &test_cases[3]), /* */
        cmocka_unit_test_prestate(test_format_xml, &test_cases[4]), /* */
        cmocka_unit_test(test_complex_complete_xml),                /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
