/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
extern void approvals_use_reporter(void (*reporter)(const char* approved_file_name,
                                                    const char* received_file_name));
extern void approvals_clear_reporters();

/*
 * Available reporters.
 */
extern void approval_report_failure_quiet(const char* approved_file_name, const char* received_file_name);
