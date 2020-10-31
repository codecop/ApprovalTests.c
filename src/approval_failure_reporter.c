/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
typedef void (*FailureReporter)(const char* approved, const char* received);

static FailureReporter reporter;

void use_reporter(FailureReporter r)
{
    reporter = r;
}

void approval_report_failure(const char* approved, const char* received)
{
    if (reporter) {
        (*reporter)(approved, received);
    }
}

/*
 * reporter needs file names
 * also need AND reporter or chain of reporters
 */
