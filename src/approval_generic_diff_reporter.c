/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/approvals_reporters.h"
#include "asserts.h"
#include "exec_utils.h"
#include "file_utils.h"

static void assert_diff_info(const struct DiffInfo diff)
{
    assert_str_not_empty(diff.diff_program);
    assert_str_not_empty(diff.parameters);
}

static void assert_approval_file_names(const struct ApprovalFileNames file_names)
{
    assert_str_not_empty(file_names.approved);
    assert_str_not_empty(file_names.received);
}

FailureReporterResult approval_open_diff_tool(const struct DiffInfo diff,
                                              const struct ApprovalFileNames file_names)
{
    assert_diff_info(diff);
    assert_approval_file_names(file_names);

    const char* diff_program = approval_create_resolved_path(diff.diff_program);
    if (diff_program == NULL) {
        /* This tool is not available. */
        return FailureReport_tool_missing;
        /* TODO test case for that FailureReport_tool_missing */
    }

    approval_create_if_needed(file_names.approved);

    const char* command_line = approval_create_command_line(
        diff_program, diff.parameters, file_names.received, file_names.approved);
    if (command_line == NULL) {
        free((void*)diff_program);
        return FailureReport_error; /* error */
    }

    int result = system(command_line);
    /* TODO result is unused */

    free((void*)command_line);
    free((void*)diff_program);
    return FailureReport_continue;
}

#define MAX_DIFF_REPORTERS 10
static struct DiffInfo used_diffs[MAX_DIFF_REPORTERS];

#define open_diff_tool_name_for(i) open_diff_tool_##i
#define open_diff_tool_for(i)                                                      \
    static FailureReporterResult open_diff_tool_name_for(i) (                      \
        const struct ApprovalFileNames file_names,                                 \
        const struct ApprovalData data,                                            \
        const struct ApprovalVerifyLine verify_line)                               \
    {                                                                              \
        (void)data;        /* unused */                                            \
        (void)verify_line; /* unused */                                            \
        return approval_open_diff_tool(used_diffs[i], file_names);                 \
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

FailureReporter approval_report_failure_generic_diff(const struct DiffInfo* diff)
{
    if (diff == NULL || diff->diff_program == NULL) {
        /* no suitable diff was found */
        return NULL;
    }

    unsigned int i = 0;
    while (used_diffs[i].diff_program && i < (MAX_DIFF_REPORTERS - 1)) {
        i += 1;
        /* TODO test cases for more than one diff */
    }
    used_diffs[i] = *diff;
    return diffs_reporters[i];
}

static bool diff_is_working_in_this_environment(const struct DiffInfo* diff)
{
    assert_not_null(diff);
    assert_diff_info(*diff);

    const char* diff_program = approval_create_resolved_path(diff->diff_program);
    if (diff_program == NULL) {
        return false;
    }
    free((void*)diff_program);
    return true;
}

const struct DiffInfo* approval_first_working_diff(const struct DiffInfo* diffInfos)
{
    const struct DiffInfo* diff = diffInfos;
    while (diff && diff->diff_program) {
        if (diff_is_working_in_this_environment(diff)) {
            return diff;
        }
        diff += 1;
    }
    return NULL;
}

const struct DiffInfo* approval_first_working_mac_diff(void)
{
    const struct MacDiffInfos* diffInfos = &MAC_DIFFS;
    return approval_first_working_diff((const struct DiffInfo*)diffInfos);
}

const struct DiffInfo* approval_first_working_windows_diff(void)
{
    const struct WindowsDiffInfos* diffInfos = &WINDOWS_DIFFS;
    return approval_first_working_diff((const struct DiffInfo*)diffInfos);
}

const struct DiffInfo* approval_first_working_linux_diff(void)
{
    const struct LinuxDiffInfos* diffInfos = &LINUX_DIFFS;
    return approval_first_working_diff((const struct DiffInfo*)diffInfos);
}
