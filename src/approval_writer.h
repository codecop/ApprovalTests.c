/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
struct ApprovalName {
    const char* full_file_name;
    const char* test_name;
    const char* extension_no_dot;
};

extern void approvals_write_received_file(struct ApprovalName name, const char* received);
extern const char* approvals_get_received_file_name(struct ApprovalName name);
extern const char* approvals_get_approved_file_name(struct ApprovalName name);
extern void approvals_delete_received_file(struct ApprovalName name);
