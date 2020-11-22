/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */

/*
 * These headers or their equivalents MUST be included prior to including
 * this header file.
 * @code
 * #include <cmocka.h>
 * @endcode
*/
#ifndef __approval_assert_equals

#define __approval_assert_equals(__approved, __got) \
    assert_string_equal((__approved), (__got));

#endif
#include "approvals.h"
