/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */

/*
#include <cmocka.h>
*/
#ifndef __approval_report_failure

#define __approval_report_failure(__approved, __got) \
    assert_string_equal((__approved), (__got));

#endif
#include "approvals.h"
