#include <setjmp.h> /* used by cmocka */
#include <stdarg.h> /* used by cmocka */
#include <stddef.h> /* used by cmocka */

#include <cmocka.h>
#include <stdlib.h>

#include "../include/approvals_cmocka.h"
#include "../src/approval_failure_reporter.h"

static void test_quiet_reporter(void** state)
{
    (void)state; /* unused */
    use_reporter(approval_report_failure_quiet);

    verify_txt("text");
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_quiet_reporter), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
