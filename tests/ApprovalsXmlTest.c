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
    {"<nope />", /* empty */
     "<nope />\n"},
    {"<a>foo</a>", /* intent */
     "<a>\n  foo\n</a>\n"},
    {"<a><b>foo</b></a>", /* multi */
     "<a>\n  <b>\n    foo\n  </b>\n</a>\n"},
    {"<r><a>bar</a><b>foo</b></r>", /* sibling */
     "<r>\n  <a>\n    bar\n  </a>\n  <b>\n    foo\n  </b>\n</r>\n"},
    {"<r><a>bar</a>foo</r>", /* text */
     "<r>\n  <a>\n    bar\n  </a>\n  foo\n</r>\n"},
};

static void test_format_xml(void** state)
{
    FormatterTestCase test_case = **(FormatterTestCase**)state;

    const char* xml = test_case.xml;
    const char* formatted = __approvals_xml_format(xml);

    assert_string_equal(test_case.expected_xml, formatted);
    free((void*)formatted);
}

/* TODO <?xml version="1.0" encoding="UTF-8"?> */

static void test_orders_xml(void** state)
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
        cmocka_unit_test(test_verify_xml),                          /* */
        cmocka_unit_test_prestate(test_format_xml, &test_cases[0]), /* */
        cmocka_unit_test_prestate(test_format_xml, &test_cases[1]), /* */
        cmocka_unit_test_prestate(test_format_xml, &test_cases[2]), /* */
        cmocka_unit_test_prestate(test_format_xml, &test_cases[3]), /* */
        cmocka_unit_test_prestate(test_format_xml, &test_cases[4]), /* */
        cmocka_unit_test(test_orders_xml),                          /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
