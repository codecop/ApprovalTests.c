/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdio.h>
#include <stdlib.h>

#include "approval_failure_reporter.h"
#include "system_utils.h"

#define MAX_REPORTERS 10

static FailureReporter used_reporter[MAX_REPORTERS + 1];

void approvals_use_reporter(FailureReporter reporter)
{
    unsigned int i = 0;
    while (used_reporter[i] && i < (MAX_REPORTERS - 1)) {
        i += 1;
    }
    used_reporter[i] = reporter;
}

void approvals_clear_reporters()
{
    unsigned int i = 0;
    while (used_reporter[i] && i < MAX_REPORTERS) {
        used_reporter[i] = NULL;
        i += 1;
    }
}

void approval_report_failure(const char* approved_file_name, const char* received_file_name)
{
    unsigned int i = 0;
    while (used_reporter[i] && i < MAX_REPORTERS) {
        int result = (*used_reporter[i])(approved_file_name, received_file_name);
        i += 1;
        if (result == FailureReporterResult_stop) {
            break;
        }
    }
}

/*
 * A reporter which creates the command to accept the received file as the approve file.
 */
int approval_report_failure_quiet(const char* approved_file_name, const char* received_file_name)
{
#ifdef OS_WINDOWS
    fprintf(stdout, "move /Y \"%s\" \"%s\"\n", received_file_name, approved_file_name);
#else
    fprintf(stdout, "mv %s %s\n", received_file_name, approved_file_name);
#endif
    return FailureReporterResult_continue;
}
