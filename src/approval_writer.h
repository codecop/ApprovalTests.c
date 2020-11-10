/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
struct ApprovalFileName {
    // TODO rename to ApprovalBaseName
    const char* base_name;
    const char* extension_no_dot;
};

extern void approval_writer_write_received_file(struct ApprovalFileName name, const char* received);
extern const char* approval_writer_create_received_file_name(struct ApprovalFileName name);
extern const char* approval_writer_create_approved_file_name(struct ApprovalFileName name);
extern void approval_writer_delete_received_file(struct ApprovalFileName name);
