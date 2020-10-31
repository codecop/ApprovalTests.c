/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <assert.h>

/*
 * Failure reporter signature
 *
 * extern void approval_report_failure(const char* __approved, const char* __got);
 *
 * implemented as macro
 */
#ifndef approval_report_failure

#define approval_report_failure(__approved, __got) assert(0);

#endif
