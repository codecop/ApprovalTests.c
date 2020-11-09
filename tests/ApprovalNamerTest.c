#include <setjmp.h> /* used by cmocka */
#include <stdarg.h> /* used by cmocka */
#include <stddef.h> /* used by cmocka */

#include <cmocka.h>
#include <stdlib.h>

#include "../src/approval_namer.h"
#include "../src/system_utils.h"

static void test_create_approval_name(void** state)
{
    (void)state; /* unused */

    const char* s = approval_namer_create_approval_name(__FILE__, __func__);

    assert_string_equal("tests" OS_SLASH "ApprovalNamerTest.test_create_approval_name", s);

    free((void*)s);
}

int main(void)
{
    const struct CMUnitTest test_suite[] = {
        cmocka_unit_test(test_create_approval_name), /* */
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
