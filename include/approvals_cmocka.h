/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */

/*
#include <cmocka.h>
#include <stdlib.h>
*/

extern const char* __approvals_verify(const char* received,
                                      const char* full_file_name,
                                      const char* test_name,
                                      const char* extension_no_dot);

extern const char* __approvals_xml_format(const char* xml);

#define verify_xml(xml)                                                            \
    const char* __got = __approvals_xml_format(xml);                               \
    const char* __approved = __approvals_verify(__got, __FILE__, __func__, "xml"); \
    assert_string_equal(__approved, __got);                                        \
    free((void*)__got);                                                            \
    free((void*)__approved);

#define verify_txt(txt)                                                            \
    const char* __got = (txt);                                                     \
    const char* __approved = __approvals_verify(__got, __FILE__, __func__, "txt"); \
    assert_string_equal(__approved, __got);                                        \
    free((void*)__approved);
