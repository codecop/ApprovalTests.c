/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdbool.h>

extern const char* approvals_file_name_for(const char* full_file_name,
                                           const char* test_name,
                                           bool is_approved,
                                           const char* extension_no_dot);

extern const const char* approvals_load(const char* filename);
extern void approvals_save(const char* filename, const char* data);
extern void approvals_delete(const char* filename);
