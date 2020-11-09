#include <setjmp.h> /* used by cmocka */
#include <stdarg.h> /* used by cmocka */
#include <stddef.h> /* used by cmocka */

#include <cmocka.h>

#include "../include/approvals_cmocka.h"
#include "../include/approvals_reporters.h"
#include "../src/approval_failure_reporter.h"

static void show_quiet_reporter(void** state)
{
    (void)state; /* unused */

    approvals_use_reporter(approval_report_failure_quiet);
    /* verify_txt("text"); */
    approval_report_failure("approved", "received");
}

static int reset_reporters(void** state)
{
    (void)state; /* unused */
    approvals_clear_reporters();
    return 0;
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test_teardown(show_quiet_reporter, reset_reporters), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
