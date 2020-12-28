/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */

/*
 * These headers or their equivalents MUST be included prior to including
 * this header file.
 * @code
 * #include <stdlib.h>
 * @endcode
 */
extern void __approvals_approve(const char* received,
                                const char* full_file_name,
                                const char* test_name,
                                int line,
                                const char* extension_no_dot);

extern const char* __approvals_xml_format(const char* xml);

#ifndef __approvals_final_reporter
#define __approvals_final_reporter __approvals_set_final_reporter(0)
#endif

/* TODO 3. do formatting of XML inside based on extension, no need to expose __approvals_xml_format */

#define verify_xml(xml)                                              \
    __approvals_final_reporter;                                      \
    const char* __got = __approvals_xml_format(xml);                 \
    __approvals_approve(__got, __FILE__, __func__, __LINE__, "xml"); \
    free((void*)__got);

#define verify_txt(__got)       \
    __approvals_final_reporter; \
    __approvals_approve((__got), __FILE__, __func__, __LINE__, "txt");
