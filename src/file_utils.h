/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
extern const char* approvals_load_text_file(const char* filename);
extern void approvals_save_text_file(const char* filename, const char* data);
extern void approvals_delete_file(const char* filename);
