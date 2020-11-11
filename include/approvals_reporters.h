/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#ifndef ApprovalsFailureReporters
#define ApprovalsFailureReporters

/*
 * Definition of failure reporters.
 */

typedef enum FailureReporterResult {
    FailureReport_continue = 0, /* */
    FailureReport_abort = 1     /* */
} FailureReporterResult;

struct ApprovalFileNames {
    const char* approved;
    const char* received;
};

typedef FailureReporterResult (*FailureReporter)(struct ApprovalFileNames file_names);

extern void approvals_use_reporter(FailureReporter reporter);
extern void approvals_clear_reporters();

/*
 * Available reporters.
 */

/*
 * A reporter which creates the command to accept the received file as the approve file.
 */
extern FailureReporterResult approval_report_failure_quiet(struct ApprovalFileNames file_names);

struct DiffInfo {
    const char* diff_program;
    const char* parameters;
};

static struct DiffInfo WINDOWS_KDIFF3 = {"{ProgramFiles}KDiff3\\kdiff3.exe", "%s %s"};
static struct DiffInfo WINDOWS_VISUAL_STUDIO_CODE = {
    "{ProgramFiles}Microsoft VS Code\\Code.exe", "-d %s %s"};

/*
 * A reporter which opens the diff between the received file as the approve file.
 */
extern FailureReporter approval_report_failure_generic_diff(struct DiffInfo diff);

#endif
