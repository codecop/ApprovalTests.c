#include <setjmp.h> /* jmp_buf for mocka */
#include <stdarg.h> /* va_start for mocka */
#include <stddef.h> /* size_t for mocka */

#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/string_utils.h"

static void string_starts_with_other_string(void** state)
{
    (void)state; /* unused */

    assert_true(string_starts_with("", ""));
    assert_true(string_starts_with("foo", ""));
    assert_true(string_starts_with("foo", "f"));
    assert_true(string_starts_with("foo", "fo"));
    assert_true(string_starts_with("foo", "foo"));
}

static void string_does_not_starts_with_other_string(void** state)
{
    (void)state; /* unused */

    assert_false(string_starts_with("", "a"));
    assert_false(string_starts_with("foo", "o"));
}

static void string_with_different_substrings(void** state)
{
    (void)state; /* unused */

    const char* s = string_substring("", 0, 0);
    assert_string_equal("", s);
    free((void*)s);

    s = string_substring("abc", 0, 0);
    assert_string_equal("", s);
    free((void*)s);

    s = string_substring("abc", 0, 1);
    assert_string_equal("a", s);
    free((void*)s);

    s = string_substring("abc", 1, 1);
    assert_string_equal("b", s);
    free((void*)s);

    s = string_substring("abc", 0, 3);
    assert_string_equal("abc", s);
    free((void*)s);
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(string_starts_with_other_string),          /* */
        cmocka_unit_test(string_does_not_starts_with_other_string), /* */
        cmocka_unit_test(string_with_different_substrings),         /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
