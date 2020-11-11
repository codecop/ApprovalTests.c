/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdio.h>
#include <stdlib.h>

#include "../include/approvals_reporters.h"
#include "system_utils.h"

static FailureReporterResult approval_report_failure_diff(struct DiffInfo diff,
                                                          struct ApprovalFileNames file_names)
{
    fprintf(stdout, diff.parameters, file_names.received, file_names.approved);
    /*
  public boolean checkFileExists()
  {
    boolean exists = new File(diffProgram).exists();
    if (REPORT_MISSING_FILES && !exists)
    {
      System.out.println(String.format("%s can't find '%s'", this.getClass().getSimpleName(), diffProgram));
    }
    return exists;
  }

    FileUtils.createIfNeeded(approved);
    launch(received, approved);

    String full = String.format(arguments, "{received}", "{approved}");
    List<String> argsSplitOnSpace = Arrays.stream(full.split(" "))
        .map(t -> t.replace("{received}", received).replace("{approved}", approved)).collect(Collectors.toList());
    ArrayList<String> commands = new ArrayList<String>();
    commands.add(diffProgram);
    commands.addAll(argsSplitOnSpace);
    System.out.println(commands);
    return commands.toArray(new String[0]);

      ProcessBuilder builder = new ProcessBuilder(getCommandLine(received, approved));
      preventProcessFromClosing(builder);
      builder.start();

    */
    return FailureReport_continue;
}

#define MAX_DIFF_REPORTERS 10
static struct DiffInfo used_diffs[MAX_DIFF_REPORTERS];

static FailureReporterResult approval_report_failure_diff_0(struct ApprovalFileNames file_names)
{
    return approval_report_failure_diff(used_diffs[0], file_names);
}
static FailureReporterResult approval_report_failure_diff_1(struct ApprovalFileNames file_names)
{
    return approval_report_failure_diff(used_diffs[1], file_names);
}
static FailureReporterResult approval_report_failure_diff_2(struct ApprovalFileNames file_names)
{
    return approval_report_failure_diff(used_diffs[2], file_names);
}
static FailureReporterResult approval_report_failure_diff_3(struct ApprovalFileNames file_names)
{
    return approval_report_failure_diff(used_diffs[3], file_names);
}
static FailureReporterResult approval_report_failure_diff_4(struct ApprovalFileNames file_names)
{
    return approval_report_failure_diff(used_diffs[4], file_names);
}
static FailureReporterResult approval_report_failure_diff_5(struct ApprovalFileNames file_names)
{
    return approval_report_failure_diff(used_diffs[5], file_names);
}
static FailureReporterResult approval_report_failure_diff_6(struct ApprovalFileNames file_names)
{
    return approval_report_failure_diff(used_diffs[6], file_names);
}
static FailureReporterResult approval_report_failure_diff_7(struct ApprovalFileNames file_names)
{
    return approval_report_failure_diff(used_diffs[7], file_names);
}
static FailureReporterResult approval_report_failure_diff_8(struct ApprovalFileNames file_names)
{
    return approval_report_failure_diff(used_diffs[8], file_names);
}
static FailureReporterResult approval_report_failure_diff_9(struct ApprovalFileNames file_names)
{
    return approval_report_failure_diff(used_diffs[9], file_names);
}

static FailureReporter diffs_reporters[MAX_DIFF_REPORTERS] = {
    approval_report_failure_diff_0, /* */
    approval_report_failure_diff_1, /* */
    approval_report_failure_diff_2, /* */
    approval_report_failure_diff_3, /* */
    approval_report_failure_diff_4, /* */
    approval_report_failure_diff_5, /* */
    approval_report_failure_diff_6, /* */
    approval_report_failure_diff_7, /* */
    approval_report_failure_diff_8, /* */
    approval_report_failure_diff_9, /* */
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
