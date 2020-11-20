/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include "../include/approvals_reporters.h"
/*
 * in public include
extern void approvals_use_reporter(FailureReporter reporter);
extern void approvals_clear_reporters();
extern FailureReporterResult approval_report_failure_quiet(struct ApprovalFileNames file_names);
*/

extern void approval_report_failure(struct ApprovalFileNames file_names);
