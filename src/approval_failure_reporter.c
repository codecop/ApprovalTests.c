/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdio.h>
#include <stdlib.h>

#include "../include/approvals_reporters.h"
#include "asserts.h"
#include "system_utils.h"

#define MAX_REPORTERS 10
static FailureReporter used_reporter[MAX_REPORTERS];

void approvals_use_reporter(FailureReporter reporter)
{
    assert_not_null(reporter);
    /* TODO allow NULL for using the first_working_... which can be null */

    unsigned int i = 0;
    while (used_reporter[i] && i < (MAX_REPORTERS - 1)) {
        i += 1;
    }
    used_reporter[i] = reporter;
}

void approvals_clear_reporters(void)
{
    unsigned int i = 0;
    while (i < MAX_REPORTERS) {
        used_reporter[i] = NULL;
        i += 1;
    }
}

static void assert_approval_file_names(struct ApprovalFileNames file_names)
{
    assert_str_not_empty(file_names.approved);
    assert_str_not_empty(file_names.received);
}

void approval_report_failure(struct ApprovalFileNames file_names)
{
    assert_approval_file_names(file_names);

    unsigned int i = 0;
    while (used_reporter[i] && i < MAX_REPORTERS) {
        FailureReporterResult result = (*used_reporter[i])(file_names);
        i += 1;
        if (result == FailureReport_abort) {
            break;
        }
    }
}

FailureReporterResult approval_report_failure_quiet(struct ApprovalFileNames file_names)
{
    assert_approval_file_names(file_names);

#ifdef OS_WINDOWS
    fprintf(stdout, "move /Y \"%s\" \"%s\"\n", file_names.received, file_names.approved);
#else
    fprintf(stdout, "mv %s %s\n", file_names.received, file_names.approved);
#endif
    return FailureReport_continue;
}
