/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
extern void use_reporter(void (*reporter)(const char* approved, const char* received));

extern void approval_report_failure(const char* approved, const char* received);
