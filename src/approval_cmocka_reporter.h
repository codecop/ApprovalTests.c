/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include "../include/approvals_reporters.h"

extern FailureReporterResult approval_report_failure_cmocka(struct ApprovalFileNames file_names,
                                                            struct ApprovalData data,
                                                            struct ApprovalVerifyLine verify_line);
