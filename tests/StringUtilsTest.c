#include <setjmp.h> /* jmp_buf for mocka */
#include <stdarg.h> /* va_start for mocka */
#include <stddef.h> /* size_t for mocka */

#include <cmocka.h>
#include <stdlib.h>

#include "../src/string_utils.h"

static void test_string_starts_with_other_string(void** state)
{
    (void)state; /* unused */

    bool starts; /* type hack to accept bool */
    assert_true(starts = string_starts_with("", ""));
    assert_true(starts = string_starts_with("foo", ""));
    assert_true(starts = string_starts_with("foo", "f"));
    assert_true(starts = string_starts_with("foo", "fo"));
    assert_true(starts = string_starts_with("foo", "foo"));
}

static void test_string_not_starting_with_string(void** state)
{
    (void)state; /* unused */

    bool starts; /* type hack to accept bool */
    assert_false(starts = string_starts_with("", "a"));
    assert_false(starts = string_starts_with("foo", "o"));
}

static void test_string_with_different_substrings(void** state)
{
    (void)state; /* unused */

    const char* s = string_create_substring("", 0, 0);
    assert_string_equal("", s);
    free((void*)s);

    s = string_create_substring("abc", 0, 0);
    assert_string_equal("", s);
    free((void*)s);

    s = string_create_substring("abc", 0, 1);
    assert_string_equal("a", s);
    free((void*)s);

    s = string_create_substring("abc", 1, 1);
    assert_string_equal("b", s);
    free((void*)s);

    s = string_create_substring("abc", 0, 3);
    assert_string_equal("abc", s);
    free((void*)s);
}

static void test_string_joining_none(void** state)
{
    (void)state; /* unused */

    const char* s = string_create_joined(0);

    assert_string_equal("", s);
    free((void*)s);
}

static void test_string_joining_single(void** state)
{
    (void)state; /* unused */

    const char* s = string_create_joined(1, "abcd");

    assert_string_equal("abcd", s);
    free((void*)s);
}

static void test_string_joining_two(void** state)
{
    (void)state; /* unused */

    const char* s = string_create_joined(2, "ab", "cd");

    assert_string_equal("abcd", s);
    free((void*)s);
}

static void test_string_joining_multiple(void** state)
{
    (void)state; /* unused */

    const char* s = string_create_joined(8, "a", "b", "c", "d", "a", "b", "c", "d");

    assert_string_equal("abcdabcd", s);
    free((void*)s);
}

static void test_string_joining(void** state)
{
    (void)state; /* unused */

    const char* s =
        string_create_joined(5, "tests/ApprovalWriterTest.test_create_approved_file_name",
                             ".", "approved", ".", "txt");
    assert_string_equal(
        "tests/ApprovalWriterTest.test_create_approved_file_name.approved.txt", s);
    free((void*)s);
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_string_starts_with_other_string),  /* */
        cmocka_unit_test(test_string_not_starting_with_string),  /* */
        cmocka_unit_test(test_string_with_different_substrings), /* */
        cmocka_unit_test(test_string_joining_none),              /* */
        cmocka_unit_test(test_string_joining_single),            /* */
        cmocka_unit_test(test_string_joining_two),               /* */
        cmocka_unit_test(test_string_joining_multiple),          /* */
        cmocka_unit_test(test_string_joining),                   /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
