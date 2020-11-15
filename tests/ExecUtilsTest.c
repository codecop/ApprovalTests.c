#include <setjmp.h> /* jmp_buf for mocka */
#include <stdarg.h> /* va_start for mocka */
#include <stddef.h> /* size_t for mocka */

#include "../src/exec_utils.h"
#include <cmocka.h>
#include <stdlib.h>

static void resolve_existing_file(void** state)
{
    (void)state; /* unused */

    /* my TortoiseHg installation */
    const char* diff_program = "C:\\Program Files\\TortoiseHg\\bin\\kdiff3.exe";

    const char* resolved = aprovals_resolve_program_path(diff_program);

    assert_string_equal(diff_program, resolved);

    if (resolved) {
        free((void*)resolved);
    }
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(resolve_existing_file), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
