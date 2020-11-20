/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
struct ApprovalBaseName {
    const char* base_name;
    const char* extension_no_dot;
};

extern void approval_writer_write_received_file(struct ApprovalBaseName name, const char* received);
extern const char* approval_writer_create_received_file_name(struct ApprovalBaseName name);
extern const char* approval_writer_create_approved_file_name(struct ApprovalBaseName name);
extern void approval_writer_delete_received_file(struct ApprovalBaseName name);
