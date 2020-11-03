/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */

/*
 * Need to include cmocka before including this macro.
#include <cmocka.h>
*/
#ifndef __approval_assert_equals

#define __approval_assert_equals(__approved, __got) \
    assert_string_equal((__approved), (__got));

#endif
#include "approvals.h"
