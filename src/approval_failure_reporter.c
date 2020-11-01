/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
typedef void (*FailureReporter)(const char* approved_file_name, const char* received_file_name);

static FailureReporter used_reporter;

void use_reporter(FailureReporter reporter)
{
    used_reporter = reporter;
}

void approval_report_failure(const char* approved_file_name, const char* received_file_name)
{
    if (used_reporter) {
        (*used_reporter)(approved_file_name, received_file_name);
    }
}

/*
 * also need AND reporter or chain of reporters
 */
