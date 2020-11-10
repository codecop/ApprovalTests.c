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

static FailureReporterResult approval_report_failure_diff(struct DiffInfo diff,
                                                          const char* approved_file_name,
                                                          const char* received_file_name)
{
    fprintf(stdout, diff.parameters, received_file_name, approved_file_name);
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

static FailureReporterResult approval_report_failure_diff_0(const char* approved_file_name,
                                                            const char* received_file_name)
{
    return approval_report_failure_diff(used_diffs[0], approved_file_name, received_file_name);
}
static FailureReporterResult approval_report_failure_diff_1(const char* approved_file_name,
                                                            const char* received_file_name)
{
    return approval_report_failure_diff(used_diffs[1], approved_file_name, received_file_name);
}
static FailureReporterResult approval_report_failure_diff_2(const char* approved_file_name,
                                                            const char* received_file_name)
{
    return approval_report_failure_diff(used_diffs[2], approved_file_name, received_file_name);
}
static FailureReporterResult approval_report_failure_diff_3(const char* approved_file_name,
                                                            const char* received_file_name)
{
    return approval_report_failure_diff(used_diffs[3], approved_file_name, received_file_name);
}
static FailureReporterResult approval_report_failure_diff_4(const char* approved_file_name,
                                                            const char* received_file_name)
{
    return approval_report_failure_diff(used_diffs[4], approved_file_name, received_file_name);
}
static FailureReporterResult approval_report_failure_diff_5(const char* approved_file_name,
                                                            const char* received_file_name)
{
    return approval_report_failure_diff(used_diffs[5], approved_file_name, received_file_name);
}
static FailureReporterResult approval_report_failure_diff_6(const char* approved_file_name,
                                                            const char* received_file_name)
{
    return approval_report_failure_diff(used_diffs[6], approved_file_name, received_file_name);
}
static FailureReporterResult approval_report_failure_diff_7(const char* approved_file_name,
                                                            const char* received_file_name)
{
    return approval_report_failure_diff(used_diffs[7], approved_file_name, received_file_name);
}
static FailureReporterResult approval_report_failure_diff_8(const char* approved_file_name,
                                                            const char* received_file_name)
{
    return approval_report_failure_diff(used_diffs[8], approved_file_name, received_file_name);
}
static FailureReporterResult approval_report_failure_diff_9(const char* approved_file_name,
                                                            const char* received_file_name)
{
    return approval_report_failure_diff(used_diffs[9], approved_file_name, received_file_name);
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
