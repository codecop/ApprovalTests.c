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
static FailureReporter final_reporter = approval_report_failure_assert;

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

void __approvals_set_final_reporter(FailureReporter reporter)
{
    if (reporter) {
        final_reporter = reporter;
    }
    else {
        final_reporter = approval_report_failure_assert;
    }
}

static void assert_approval_file_names(struct ApprovalFileNames file_names)
{
    assert_str_not_empty(file_names.approved);
    assert_str_not_empty(file_names.received);
}

static void assert_approval_data(struct ApprovalData data)
{
    assert_str_not_empty(data.approved);
    assert_str_not_empty(data.received);
}

static void assert_approval_verify_line(struct ApprovalVerifyLine verify_line)
{
    assert_str_not_empty(verify_line.file);
    assert(verify_line.line > 0);
}

static void run_final_reporter(struct ApprovalFileNames file_names,
                               struct ApprovalData data,
                               struct ApprovalVerifyLine verify_line)
{
    (*final_reporter)(file_names, data, verify_line);
}

void approval_report_failure(struct ApprovalFileNames file_names,
                             struct ApprovalData data,
                             struct ApprovalVerifyLine verify_line)
{
    assert_approval_file_names(file_names);
    assert_approval_data(data);
    assert_approval_verify_line(verify_line);

    unsigned int i = 0;
    while (used_reporter[i] && i < MAX_REPORTERS) {
        FailureReporterResult result = (*used_reporter[i])(file_names, data, verify_line);
        i += 1;
        if (result == FailureReport_abort) {
            break;
        }
    }

    run_final_reporter(file_names, data, verify_line);
}

FailureReporterResult approval_report_failure_quiet(struct ApprovalFileNames file_names,
                                                    struct ApprovalData data,
                                                    struct ApprovalVerifyLine verify_line)
{
    assert_approval_file_names(file_names);
    (void)data;        /* unused */
    (void)verify_line; /* unused */

#ifdef OS_WINDOWS
    fprintf(stdout, "move /Y \"%s\" \"%s\"\n", file_names.received, file_names.approved);
#else
    fprintf(stdout, "mv %s %s\n", file_names.received, file_names.approved);
#endif
    return FailureReport_continue;
}

FailureReporterResult approval_report_failure_assert(struct ApprovalFileNames file_names,
                                                     struct ApprovalData data,
                                                     struct ApprovalVerifyLine verify_line)
{
    (void)file_names;  /* unused */
    (void)data;        /* unused */
    (void)verify_line; /* unused */

    /* TODO implement */

    return FailureReport_abort;
}
