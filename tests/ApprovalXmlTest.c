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

#include "../src/approval_xml.h"

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
    {"<?xml version=\"1.0\" encoding=\"UTF-8\"?><a>foo</a>",         /* format */
     "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<a>\n  foo\n</a>\n"}, /* - processing instruction */
    {"<!-- a --><a>foo<!-- f --></a>",                                  /* format */
     "<!-- a -->\n<a>\n  foo\n  <!-- f -->\n</a>\n"},                   /* - comments */
    {"<!-- <a>foo</a> -->",                                             /* (not) format */
     "<!-- <a>foo</a> -->\n"},      /* - commented tags */
    {"<![CDATA[ <a>foo</a> ]]>",    /* (not) format */
     "<![CDATA[ <a>foo</a> ]]>\n"}, /* - CDATA */
};

/* TODO test list
 *
 * ignore whitespace (' ', \n) outside of tags, after > and before <
 * ignore additional whitespace in attributes
 */

static void test_format_xml(void** state)
{
    FormatterTestCase test_case = **(FormatterTestCase**)state;

    const char* xml = test_case.xml;
    const char* formatted = approvals_xml_format(xml);

    assert_string_equal(test_case.expected_xml, formatted);
    free((void*)formatted);
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test_prestate(test_format_xml, &test_cases[0]), /* */
        cmocka_unit_test_prestate(test_format_xml, &test_cases[1]), /* */
        cmocka_unit_test_prestate(test_format_xml, &test_cases[2]), /* */
        cmocka_unit_test_prestate(test_format_xml, &test_cases[3]), /* */
        cmocka_unit_test_prestate(test_format_xml, &test_cases[4]), /* */
        cmocka_unit_test_prestate(test_format_xml, &test_cases[5]), /* */
        cmocka_unit_test_prestate(test_format_xml, &test_cases[6]), /* */
        cmocka_unit_test_prestate(test_format_xml, &test_cases[7]), /* */
        cmocka_unit_test_prestate(test_format_xml, &test_cases[8]), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
