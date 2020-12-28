/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */

/*
 * These headers or their equivalents MUST be included prior to including
 * this header file.
 * @code
 * #include <cmocka.h>
 * @endcode
 */
#ifndef Approvals_Cmocka_H_
#define Approvals_Cmocka_H_

#include "approvals_reporters.h"

extern FailureReporterResult __approval_report_failure_cmocka(struct ApprovalFileNames file_names,
                                                              struct ApprovalData data,
                                                              struct ApprovalVerifyLine verify_line);

#define __approvals_final_reporter \
    __approvals_set_final_reporter(__approval_report_failure_cmocka)

#include "approvals.h"

#endif
