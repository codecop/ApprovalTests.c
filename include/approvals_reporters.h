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

/* Diff tools copied from DiffPrograms.java, https://github.com/approvals/ApprovalTests.Java */
static struct DiffInfo MAC_DIFF_MERGE = {
    "/Applications/DiffMerge.app/Contents/MacOS/DiffMerge", "--nosplash %s %s "};
static struct DiffInfo MAC_BEYOND_COMPARE = {
    "/Applications/Beyond Compare.app/Contents/MacOS/bcomp", "%s %s"};
static struct DiffInfo MAC_KALEIDOSCOPE = {
    "/Applications/Kaleidoscope.app/Contents/MacOS/ksdiff", "%s %s"};
static struct DiffInfo MAC_KDIFF3 = {
    "/Applications/kdiff3.app/Contents/MacOS/kdiff3", "%s %s -m"};
static struct DiffInfo MAC_TK_DIFF = {
    "/Applications/TkDiff.app/Contents/MacOS/tkdiff", "%s %s"};
static struct DiffInfo MAC_VISUAL_STUDIO_CODE = {
    "/Applications/Visual Studio Code.app/Contents/Resources/app/bin/code", "-d %s %s"};

static struct DiffInfo WINDOWS_BEYOND_COMPARE_3 = {
    "{ProgramFiles}Beyond Compare 3\\BCompare.exe", "%s %s"};
static struct DiffInfo WINDOWS_BEYOND_COMPARE_4 = {
    "{ProgramFiles}Beyond Compare 4\\BCompare.exe", "%s %s"};
static struct DiffInfo WINDOWS_TORTOISE_TEXT_DIFF = {
    "{ProgramFiles}TortoiseSVN\\bin\\TortoiseMerge.exe", "%s %s"};
static struct DiffInfo WINDOWS_WIN_MERGE_REPORTER = {
    "{ProgramFiles}WinMerge\\WinMergeU.exe", "%s %s"};
static struct DiffInfo WINDOWS_ARAXIS_MERGE = {
    "{ProgramFiles}Araxis\\Araxis Merge\\Compare.exe", "%s %s"};
static struct DiffInfo WINDOWS_CODE_COMPARE = {
    "{ProgramFiles}Devart\\Code Compare\\CodeCompare.exe", "%s %s"};
static struct DiffInfo WINDOWS_KDIFF3 = {
    "{ProgramFiles}KDiff3\\kdiff3.exe", "%s %s"};
static struct DiffInfo WINDOWS_VISUAL_STUDIO_CODE = {
    "{ProgramFiles}Microsoft VS Code\\Code.exe", "-d %s %s"};

static struct DiffInfo LINUX_DIFF_MERGE = {"/usr/bin/diffmerge", "--nosplash %s %s "};
static struct DiffInfo LINUX_MELD_MERGE = {"/usr/bin/meld", "%s %s "};

/*
 * A reporter which opens the diff between the received file as the approve file.
 */
extern FailureReporter approval_report_failure_generic_diff(struct DiffInfo diff);

#endif
