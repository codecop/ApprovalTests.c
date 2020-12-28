/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */

extern void __approvals_approve(const char* received,
                                const char* full_file_name,
                                const char* test_name,
                                int line,
                                const char* extension_no_dot);

#ifndef __approvals_final_reporter
#define __approvals_final_reporter __approvals_set_final_reporter(0)
#endif

#define verify(__got, __extension) \
    __approvals_final_reporter;    \
    __approvals_approve((__got), __FILE__, __func__, __LINE__, (__extension));

#define verify_xml(__got) verify(__got, "xml");

#define verify_txt(__got) verify(__got, "txt");
