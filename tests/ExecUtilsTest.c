#include <setjmp.h> /* jmp_buf for mocka */
#include <stdarg.h> /* va_start for mocka */
#include <stddef.h> /* size_t for mocka */

#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/exec_utils.h"
#include "../src/file_utils.h"

/* My local installations */
const char* tortoiseHg = "C:\\Program Files\\TortoiseHg\\bin\\kdiff3.exe";
const char* kdiff3 = "C:\\Program Files (x86)\\KDiff3\\kdiff3.exe";

static int has_file(const char* file, const char* test)
{
    if (approvals_file_exists(file)) {
        return 1;
    }

    fprintf(stderr, "Ignoring test %s, test file %s missing.\n", test, file);
    return 0;
}

static void resolve_existing_file(void** state)
{
    (void)state; /* unused */
    if (!has_file(tortoiseHg, __func__)) {
        return;
    }

    const char* diff_program = "C:\\Program Files\\TortoiseHg\\bin\\kdiff3.exe";
    const char* resolved = aprovals_resolve_program_path(diff_program);

    assert_non_null(resolved);
    assert_string_equal(tortoiseHg, resolved);

    if (resolved) {
        free((void*)resolved);
    }
}

static void not_resolve_missing_file(void** state)
{
    (void)state; /* unused */

    const char* diff_program = "/this_does_not_exist.exe";
    const char* resolved = aprovals_resolve_program_path(diff_program);

    assert_null(resolved);
}

static void resolve_windows_program_files(void** state)
{
    (void)state; /* unused */
    if (!has_file(tortoiseHg, __func__)) {
        return;
    }

    const char* diff_program = "{ProgramFiles}TortoiseHg\\bin\\kdiff3.exe";
    const char* resolved = aprovals_resolve_program_path(diff_program);

    assert_non_null(resolved);
    assert_string_equal(tortoiseHg, resolved);

    if (resolved) {
        free((void*)resolved);
    }
}

static void resolve_windows_x86_program_files(void** state)
{
    (void)state; /* unused */
    if (!has_file(kdiff3, __func__)) {
        return;
    }

    const char* diff_program = "{ProgramFiles}KDiff3\\kdiff3.exe";
    const char* resolved = aprovals_resolve_program_path(diff_program);

    assert_non_null(resolved);
    assert_string_equal(kdiff3, resolved);

    if (resolved) {
        free((void*)resolved);
    }
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(resolve_existing_file),             /* */
        cmocka_unit_test(not_resolve_missing_file),          /* */
        cmocka_unit_test(resolve_windows_program_files),     /* */
        cmocka_unit_test(resolve_windows_x86_program_files), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
