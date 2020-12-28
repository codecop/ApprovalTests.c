/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#ifndef ApprovalsFailureReporters_H_
#define ApprovalsFailureReporters_H_

/*
 * Definition of failure reporters.
 */

typedef enum FailureReporterResult {
    FailureReport_continue = 0,     /* */
    FailureReport_abort = 1,        /* */
    FailureReport_tool_missing = 2, /* */
    FailureReport_error = 3,        /* */
} FailureReporterResult;

struct ApprovalFileNames {
    const char* approved;
    const char* received;
};

struct ApprovalData {
    const char* approved;
    const char* received;
};

struct ApprovalVerifyLine {
    const char* file;
    const int line;
};

typedef FailureReporterResult (*FailureReporter)(struct ApprovalFileNames file_names,
                                                 struct ApprovalData data,
                                                 struct ApprovalVerifyLine verify_line);

extern void approvals_use_reporter(FailureReporter reporter);
extern void approvals_clear_reporters(void);

/*
 * Available reporters.
 */

/*
 * A reporter which creates the command to accept the received file as the approve file.
 */
extern FailureReporterResult approval_report_failure_quiet(struct ApprovalFileNames file_names,
                                                           struct ApprovalData data,
                                                           struct ApprovalVerifyLine verify_line);

struct DiffInfo {
    const char* diff_program;
    const char* parameters;
};

/*
 * Diff tools to use with `approval_report_failure_generic_diff`.
 * Copied from `DiffPrograms.java`, https://github.com/approvals/ApprovalTests.Java
 */
static struct MacDiffInfos {
    struct DiffInfo BEYOND_COMPARE;
    struct DiffInfo DIFF_MERGE;
    struct DiffInfo KALEIDOSCOPE;
    struct DiffInfo KDIFF3;
    struct DiffInfo TK_DIFF;
    struct DiffInfo VISUAL_STUDIO_CODE;
    struct DiffInfo _NULL_TERMINATED;
} MAC_DIFFS = {
    {"/Applications/Beyond Compare.app/Contents/MacOS/bcomp", "%s %s"},
    {"/Applications/DiffMerge.app/Contents/MacOS/DiffMerge", "--nosplash %s %s"},
    {"/Applications/Kaleidoscope.app/Contents/MacOS/ksdiff", "%s %s"},
    {"/Applications/kdiff3.app/Contents/MacOS/kdiff3", "%s %s -m"},
    {"/Applications/TkDiff.app/Contents/MacOS/tkdiff", "%s %s"},
    {"/Applications/Visual Studio Code.app/Contents/Resources/app/bin/code", "-d %s %s"},
    {NULL, NULL},
};

static struct WindowsDiffInfos {
    struct DiffInfo ARAXIS_MERGE;
    struct DiffInfo BEYOND_COMPARE_3;
    struct DiffInfo BEYOND_COMPARE_4;
    struct DiffInfo CODE_COMPARE;
    struct DiffInfo KDIFF3;
    struct DiffInfo TORTOISE_KDIFF3;
    struct DiffInfo TORTOISE_TEXT_DIFF;
    struct DiffInfo VISUAL_STUDIO_CODE;
    struct DiffInfo WIN_DIFF;
    struct DiffInfo WIN_MERGE;
    struct DiffInfo _NULL_TERMINATED;
} WINDOWS_DIFFS = {
    {"{ProgramFiles}Araxis\\Araxis Merge\\Compare.exe", "%s %s"},
    {"{ProgramFiles}Beyond Compare 3\\BCompare.exe", "%s %s"},
    {"{ProgramFiles}Beyond Compare 4\\BCompare.exe", "%s %s"},
    {"{ProgramFiles}Devart\\Code Compare\\CodeCompare.exe", "%s %s"},
    {"{ProgramFiles}KDiff3\\kdiff3.exe", "%s %s"},
    {"{ProgramFiles}TortoiseHg\\bin\\kdiff3.exe", "%s %s"},
    {"{ProgramFiles}TortoiseSVN\\bin\\TortoiseMerge.exe", "%s %s"},
    {"{ProgramFiles}Microsoft VS Code\\Code.exe", "-d %s %s"},
    {"{ProgramFiles}Microsoft SDKs\\Windows\\v7.1\\Bin\x64\\WinDiff.exe", "%s %s"},
    {"{ProgramFiles}WinMerge\\WinMergeU.exe", "%s %s"},
    {NULL, NULL},
};

static struct LinuxDiffInfos {
    struct DiffInfo DIFF_MERGE;
    struct DiffInfo MELD_MERGE;
    struct DiffInfo KDIFF3;
    struct DiffInfo _NULL_TERMINATED;
} LINUX_DIFFS = {
    {"/usr/bin/diffmerge", "--nosplash %s %s"},
    {"/usr/bin/meld", "%s %s"},
    {"{ProgramFiles}kdiff3", "%s %s"},
    {NULL, NULL},
};

/*
 * A reporter which opens the diff between the received file as the approve file.
 */
extern FailureReporter approval_report_failure_generic_diff(struct DiffInfo diff);

extern struct DiffInfo* approval_first_working_diff(struct DiffInfo* diffInfos);
extern struct DiffInfo* approval_first_working_mac_diff(struct MacDiffInfos* diffInfos);
extern struct DiffInfo* approval_first_working_windows_diff(struct WindowsDiffInfos* diffInfos);
extern struct DiffInfo* approval_first_working_linux_diff(struct LinuxDiffInfos* diffInfos);

#endif
