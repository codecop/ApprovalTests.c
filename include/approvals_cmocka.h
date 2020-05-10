/***********************************************************************
 * Approvals.c - micro Approvals for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */

extern const char* __approvals_verify(const char* received,
                                      const char* full_file_name,
                                      const char* test_name,
                                      const char* extension_no_dot);

#define verify_xml(xml, testName)                                                \
    const char* __approved = __approvals_verify((xml), __FILE__, testName, "xml"); \
    assert_string_equal(__approved, (xml));
