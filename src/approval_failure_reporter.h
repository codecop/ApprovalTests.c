/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include "../include/approvals_reporters.h"

typedef enum FailureReporterResult {
    FailureReporterResult_continue, /* */
    FailureReporterResult_stop      /* */
} FailureReporterResult;

typedef int (*FailureReporter)(const char* approved_file_name, const char* received_file_name);

extern void approval_report_failure(const char* approved_file_name, const char* received_file_name);
