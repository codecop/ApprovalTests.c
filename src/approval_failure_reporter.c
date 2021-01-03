/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/approvals_reporters.h"
#include "asserts.h"
#include "system_utils.h"

#define MAX_REPORTERS 10
static FailureReporter used_reporter[MAX_REPORTERS];
static FailureReporter final_reporter = approval_report_failure_assert;

void approvals_use_reporter(FailureReporter reporter)
{
    if (reporter == NULL) {
        /* ignore NULL reporters, maybe no matching diff */
        return;
    }

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

static void assert_approval_file_names(const struct ApprovalFileNames file_names)
{
    assert_str_not_empty(file_names.approved);
    assert_str_not_empty(file_names.received);
}

static void assert_approval_data(const struct ApprovalData data)
{
    assert_not_null(data.approved);
    assert_not_null(data.received);
}

static void assert_approval_verify_line(const struct ApprovalVerifyLine verify_line)
{
    assert_str_not_empty(verify_line.file);
    assert(verify_line.line > 0);
}

static void run_final_reporter(const struct ApprovalFileNames file_names,
                               const struct ApprovalData data,
                               const struct ApprovalVerifyLine verify_line)
{
    (*final_reporter)(file_names, data, verify_line);
}

void approval_report_failure(const struct ApprovalFileNames file_names,
                             const struct ApprovalData data,
                             const struct ApprovalVerifyLine verify_line)
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

FailureReporterResult approval_report_failure_quiet(const struct ApprovalFileNames file_names,
                                                    const struct ApprovalData data,
                                                    const struct ApprovalVerifyLine verify_line)
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

FailureReporterResult approval_report_failure_assert(const struct ApprovalFileNames file_names,
                                                     const struct ApprovalData data,
                                                     const struct ApprovalVerifyLine verify_line)
{
    (void)file_names;  /* unused */
    (void)verify_line; /* unused */
    assert(strcmp(data.approved, data.received) == 0);
    return FailureReport_abort;
}
