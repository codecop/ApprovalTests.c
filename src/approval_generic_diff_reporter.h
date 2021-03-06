/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include "../include/approvals_reporters.h"
/*
 * in public include
extern FailureReporter approval_report_failure_generic_diff(const struct DiffInfo diff);
*/

extern FailureReporterResult approval_open_diff_tool(const struct DiffInfo diff,
                                                     const struct ApprovalFileNames file_names);
