#include <setjmp.h> /* jmp_buf for mocka */
#include <stdarg.h> /* va_start for mocka */
#include <stddef.h> /* size_t for mocka */

#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/exec_utils.h"
#include "../src/file_utils.h"
#include "../src/system_utils.h"

/* My local installations */
const char* tortoiseHg = "C:\\Program Files\\TortoiseHg\\bin\\kdiff3.exe";
const char* kdiff3 = "C:\\Program Files (x86)\\KDiff3\\kdiff3.exe";

static int has_file(const char* file, const char* test)
{
    if (!approvals_file_exists(file)) {
        fprintf(stderr, "Ignoring test %s, test file %s missing.\n", test, file);
        return 1;
    }
    return 0;
}

static int has_tortoise_kdiff(const char* test)
{
    return has_file(tortoiseHg, test);
}

static void resolve_existing_file(void** state)
{
    (void)state; /* unused */
    if (!has_tortoise_kdiff(__func__)) {
        return;
    }

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
