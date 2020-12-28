/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <setjmp.h> /* used by cmocka */
#include <stdarg.h> /* used by cmocka */
#include <stddef.h> /* used by cmocka */

#include <cmocka.h>

#include "../include/approvals_reporters.h"

FailureReporterResult approval_report_failure_cmocka(struct ApprovalFileNames file_names,
                                                     struct ApprovalData data,
                                                     struct ApprovalVerifyLine verify_line)
{
    (void)file_names; /* unused */

    _assert_string_equal(data.approved, data.received, verify_line.file, verify_line.line);

    return FailureReport_abort;
}
