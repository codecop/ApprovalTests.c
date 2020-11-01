/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
extern void approval_report_failure(const char* approved_file_name, const char* received_file_name);

extern void use_reporter(void (*reporter)(const char* approved_file_name, const char* received_file_name));

/*
 * Available reporters.
 */
extern void approval_report_failure_quiet(const char* approved_file_name, const char* received_file_name);
