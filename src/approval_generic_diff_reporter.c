/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdio.h>
#include <stdlib.h>

#include "../include/approvals_reporters.h"
#include "exec_utils.h"
#include "file_utils.h"

FailureReporterResult approval_open_diff_tool(struct DiffInfo diff, struct ApprovalFileNames file_names)
{
    const char* diff_program = aprovals_create_resolved_path(diff.diff_program);
    if (diff_program == 0) {
        /* This tool is not available. */
        return FailureReport_tool_missing;
    }

    approvals_create_if_needed(file_names.approved);

    fprintf(stdout, diff.parameters, file_names.received, file_names.approved);
    /* TODO implement diff report using exec_utils. */

    /*

    String full = String.format(arguments, "{received}", "{approved}");
    List<String> argsSplitOnSpace = Arrays.stream(full.split(" "))
        .map(t -> t.replace("{received}", received).replace("{approved}", approved)).collect(Collectors.toList());
    ArrayList<String> commands = new ArrayList<String>();
    commands.add(diffProgram);
    commands.addAll(argsSplitOnSpace);
    System.out.println(commands);
    return commands.toArray(new String[0]);

    launch(received, approved);

      ProcessBuilder builder = new ProcessBuilder(getCommandLine(received, approved));
      preventProcessFromClosing(builder);
      builder.start();
    */
    return FailureReport_continue;
}

#define MAX_DIFF_REPORTERS 10
static struct DiffInfo used_diffs[MAX_DIFF_REPORTERS];

#define open_diff_tool_name_for(i) open_diff_tool_##i
#define open_diff_tool_for(i)                                                                    \
    static FailureReporterResult open_diff_tool_name_for(i)(struct ApprovalFileNames file_names) \
    {                                                                                            \
        return approval_open_diff_tool(used_diffs[i], file_names);                                        \
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
    unsigned int i = 0;
    while (used_diffs[i].diff_program && i < (MAX_DIFF_REPORTERS - 1)) {
        i += 1;
    }
    used_diffs[i] = diff;
    return diffs_reporters[i];
}
