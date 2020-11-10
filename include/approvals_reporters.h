/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#ifndef ApprovalsFailureReporters
#define ApprovalsFailureReporters

typedef int (*FailureReporter)(const char* approved_file_name, const char* received_file_name);

extern void approvals_use_reporter(FailureReporter reporter);
extern void approvals_clear_reporters();

/*
 * Available reporters.
 */

/*
 * A reporter which creates the command to accept the received file as the approve file.
 */
extern int approval_report_failure_quiet(const char* approved_file_name, const char* received_file_name);
/*
struct DiffInfo {
    const char* diff_program;
    const char* parameters;
};
*/
/* Windows */
/*
static struct DiffInfo WINDOWS_KDIFF3 = {"{ProgramFiles}KDiff3\\kdiff3.exe", "%s %s"};
static struct DiffInfo WINDOWS_VISUAL_STUDIO_CODE = {
    "{ProgramFiles}Microsoft VS Code\\Code.exe", "-d %s %s"};
*/
#endif
