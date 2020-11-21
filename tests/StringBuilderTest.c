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

#include "../src/string_builder.h"

static void test_string_builder_empty(void** state)
{
    (void)state; /* unused */

    struct StringBuilder* sb = make_sb();
    const char* actual = sb_string(sb);

    assert_string_equal("", actual);
    free((void*)actual);
}

static void test_string_append_empty(void** state)
{
    (void)state; /* unused */

    struct StringBuilder* sb = make_sb();
    int error = sb_append(sb, "");
    const char* actual = sb_string(sb);

    assert_int_equal(0, error);
    assert_string_equal("", actual);
    free((void*)actual);
}

static void test_string_append(void** state)
{
    (void)state; /* unused */

    struct StringBuilder* sb = make_sb();
    sb_append(sb, "foo");
    sb_append(sb, " ");
    sb_append(sb, "bar");
    const char* actual = sb_string(sb);

    assert_string_equal("foo bar", actual);
    free((void*)actual);
}

static void test_string_builder_grow(void** state)
{
    (void)state; /* unused */

    struct StringBuilder* sb = make_sb();
    sb_append(sb, "a");
    sb_append(sb,
              "1234567890ABCDEF"
              "1234567890abcdef"
              "1234567890ABCDEF"
              "1234567890ABCDEF");
    const char* actual = sb_string(sb);

    assert_string_equal(
        "a"
        "1234567890ABCDEF"
        "1234567890abcdef"
        "1234567890ABCDEF"
        "1234567890ABCDEF",
        actual);
    free((void*)actual);
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_string_builder_empty), /* */
        cmocka_unit_test(test_string_append_empty),  /* */
        cmocka_unit_test(test_string_append),        /* */
        cmocka_unit_test(test_string_builder_grow),  /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
