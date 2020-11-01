/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdio.h>
#include <stdlib.h>

#include "system_utils.h"

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
 * TODO also need AND reporter or chain of reporters
 */

/*
 * A reporter which creates the command to accept the received file as the approve file.
 */
void approval_report_failure_quiet(const char* approved_file_name, const char* received_file_name)
{
#ifdef OS_WINDOWS
    fprintf(stdout, "move /Y \"%s\" \"%s\"\n", received_file_name, approved_file_name);
#else
    fprintf(stdout, "mv %s %s\n", received_file_name, approved_file_name);
#endif
}
