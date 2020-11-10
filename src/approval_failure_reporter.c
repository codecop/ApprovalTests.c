/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdio.h>
#include <stdlib.h>

#include "../include/approvals_reporters.h"
#include "system_utils.h"

#define MAX_REPORTERS 10

static FailureReporter used_reporter[MAX_REPORTERS];

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
        FailureReporterResult result = (*used_reporter[i])(approved_file_name, received_file_name);
        i += 1;
        if (result == FailureReport_abort) {
            break;
        }
    }
}

FailureReporterResult approval_report_failure_quiet(const char* approved_file_name,
                                                    const char* received_file_name)
{
#ifdef OS_WINDOWS
    fprintf(stdout, "move /Y \"%s\" \"%s\"\n", received_file_name, approved_file_name);
#else
    fprintf(stdout, "mv %s %s\n", received_file_name, approved_file_name);
#endif
    return FailureReport_continue;
}

/* TODO move to generic diff reporter */

#define MAX_DIFF_REPORTERS 10
static struct DiffInfo used_diffs[MAX_DIFF_REPORTERS];

static FailureReporterResult approval_report_failure_diff(struct DiffInfo diff,
                                                          const char* approved_file_name,
                                                          const char* received_file_name)
{
    fprintf(stdout, "DIFF \"%s\" \"%s\"\n", received_file_name, approved_file_name);
    return FailureReport_continue;
}

// TODO macro for defining methods for each i in 0...MAX_DIFF_REPORTERS
// and put into array
static FailureReporterResult approval_report_failure_diff_0(const char* approved_file_name,
                                                            const char* received_file_name)
{
    return approval_report_failure_diff(used_diffs[0], approved_file_name, received_file_name);
}

static FailureReporter diffs_reporters[MAX_DIFF_REPORTERS] = {
    approval_report_failure_diff_0, /* */
    approval_report_failure_diff_0, /* */
    approval_report_failure_diff_0, /* */
    approval_report_failure_diff_0, /* */
    approval_report_failure_diff_0, /* */
    approval_report_failure_diff_0, /* */
    approval_report_failure_diff_0, /* */
    approval_report_failure_diff_0, /* */
    approval_report_failure_diff_0, /* */
    approval_report_failure_diff_0, /* */
};

FailureReporter approval_report_failure_generic_diff(struct DiffInfo diff)
{
    unsigned int i = 0;
    while (used_diffs[i].diff_program && i < (MAX_DIFF_REPORTERS - 1)) {
        i += 1;
    }
    used_diffs[i] = diff;

    return diffs_reporters[i];
}