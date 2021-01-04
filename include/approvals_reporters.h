/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#ifndef Approvals_FailureReporters_H_
#define Approvals_FailureReporters_H_

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

typedef FailureReporterResult (*FailureReporter)(const struct ApprovalFileNames file_names,
                                                 const struct ApprovalData data,
                                                 const struct ApprovalVerifyLine verify_line);

extern void approvals_use_reporter(const FailureReporter reporter);
extern void approvals_clear_reporters(void);
extern void __approvals_set_final_reporter(const FailureReporter reporter);

/*
 * Available reporters.
 */

/*
 * A reporter which creates the command to accept the received file as the approve file.
 */
extern FailureReporterResult approval_report_failure_quiet(const struct ApprovalFileNames file_names,
                                                           const struct ApprovalData data,
                                                           const struct ApprovalVerifyLine verify_line);

/*
 * A reporter which uses `assert` to compare the approvals. Stops execution on failure.
 * This is the default final reporter.
 */
extern FailureReporterResult approval_report_failure_assert(const struct ApprovalFileNames file_names,
                                                            const struct ApprovalData data,
                                                            const struct ApprovalVerifyLine verify_line);

struct DiffInfo {
    const char* diff_program;
    const char* parameters;
};

/*
 * Diff tools to use with `approval_report_failure_generic_diff`.
 * Copied from `DiffPrograms.java`, https://github.com/approvals/ApprovalTests.Java
 */
static const struct MacDiffInfos {
    const struct DiffInfo BEYOND_COMPARE;
    const struct DiffInfo DIFF_MERGE;
    const struct DiffInfo KALEIDOSCOPE;
    const struct DiffInfo KDIFF3;
    const struct DiffInfo TK_DIFF;
    const struct DiffInfo VISUAL_STUDIO_CODE;
    const struct DiffInfo _NULL_TERMINATED;
} MAC_DIFFS = {
    {"/Applications/Beyond Compare.app/Contents/MacOS/bcomp", "%s %s"},
    {"/Applications/DiffMerge.app/Contents/MacOS/DiffMerge", "--nosplash %s %s"},
    {"/Applications/Kaleidoscope.app/Contents/MacOS/ksdiff", "%s %s"},
    {"/Applications/kdiff3.app/Contents/MacOS/kdiff3", "%s %s -m"},
    {"/Applications/TkDiff.app/Contents/MacOS/tkdiff", "%s %s"},
    {"/Applications/Visual Studio Code.app/Contents/Resources/app/bin/code", "-d %s %s"},
    {NULL, NULL},
};

static const struct WindowsDiffInfos {
    const struct DiffInfo ARAXIS_MERGE;
    const struct DiffInfo BEYOND_COMPARE_3;
    const struct DiffInfo BEYOND_COMPARE_4;
    const struct DiffInfo CODE_COMPARE;
    const struct DiffInfo KDIFF3;
    const struct DiffInfo TORTOISE_KDIFF3;
    const struct DiffInfo TORTOISE_TEXT_DIFF;
    const struct DiffInfo VISUAL_STUDIO_CODE;
    const struct DiffInfo WIN_DIFF;
    const struct DiffInfo WIN_MERGE;
    const struct DiffInfo _NULL_TERMINATED;
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

static const struct LinuxDiffInfos {
    const struct DiffInfo DIFF_MERGE;
    const struct DiffInfo MELD_MERGE;
    const struct DiffInfo KDIFF3;
    const struct DiffInfo _NULL_TERMINATED;
} LINUX_DIFFS = {
    {"/usr/bin/diffmerge", "--nosplash %s %s"},
    {"/usr/bin/meld", "%s %s"},
    {"{ProgramFiles}kdiff3", "%s %s"},
    {NULL, NULL},
};

/*
 * A reporter which opens the diff between the received file as the approve file.
 */
extern FailureReporter approval_report_failure_generic_diff(const struct DiffInfo* diff);

extern const struct DiffInfo* approval_first_working_diff(const struct DiffInfo* diffInfos);
extern const struct DiffInfo* approval_first_working_mac_diff(void);
extern const struct DiffInfo* approval_first_working_windows_diff(void);
extern const struct DiffInfo* approval_first_working_linux_diff(void);

#endif
