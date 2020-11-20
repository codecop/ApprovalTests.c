/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdio.h>
#include <stdlib.h>

#include "../include/approvals_reporters.h"
#include "asserts.h"
#include "exec_utils.h"
#include "file_utils.h"

static void assert_diff_info(struct DiffInfo diff)
{
    assert_str_not_empty(diff.diff_program);
    assert_str_not_empty(diff.parameters);
}

FailureReporterResult approval_open_diff_tool(struct DiffInfo diff, struct ApprovalFileNames file_names)
{
    assert_diff_info(diff);

    const char* diff_program = aprovals_create_resolved_path(diff.diff_program);
    if (diff_program == 0) {
        /* This tool is not available. */
        return FailureReport_tool_missing;
    }

    approvals_create_if_needed(file_names.approved);

    const char* command_line = approvals_create_command_line(
        diff_program, diff.parameters, file_names.received, file_names.approved);

    int result = system(command_line);
    /* TODO result is unused */

    free((void*)command_line);
    free((void*)diff_program);
    return FailureReport_continue;
}

#define MAX_DIFF_REPORTERS 10
static struct DiffInfo used_diffs[MAX_DIFF_REPORTERS];

#define open_diff_tool_name_for(i) open_diff_tool_##i
#define open_diff_tool_for(i)                                                                    \
    static FailureReporterResult open_diff_tool_name_for(i)(struct ApprovalFileNames file_names) \
    {                                                                                            \
        return approval_open_diff_tool(used_diffs[i], file_names);                               \
    }

open_diff_tool_for(0)
open_diff_tool_for(1)
open_diff_tool_for(2)
open_diff_tool_for(3)
open_diff_tool_for(4)
open_diff_tool_for(5)
open_diff_tool_for(6)
open_diff_tool_for(7)
open_diff_tool_for(8)
open_diff_tool_for(9)

static FailureReporter diffs_reporters[MAX_DIFF_REPORTERS] = {
    open_diff_tool_name_for(0), /* */
    open_diff_tool_name_for(1), /* */
    open_diff_tool_name_for(2), /* */
    open_diff_tool_name_for(3), /* */
    open_diff_tool_name_for(4), /* */
    open_diff_tool_name_for(5), /* */
    open_diff_tool_name_for(6), /* */
    open_diff_tool_name_for(7), /* */
    open_diff_tool_name_for(8), /* */
    open_diff_tool_name_for(9), /* */
};

FailureReporter approval_report_failure_generic_diff(struct DiffInfo diff)
{
    assert_diff_info(diff);

    unsigned int i = 0;
    while (used_diffs[i].diff_program && i < (MAX_DIFF_REPORTERS - 1)) {
        i += 1;
    }
    used_diffs[i] = diff;
    return diffs_reporters[i];
}
