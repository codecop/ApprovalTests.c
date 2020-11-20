/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdbool.h>

extern bool approvals_file_exists(const char* filename);
extern const char* approvals_load_text_file(const char* filename);
extern long approvals_file_size(const char* filename);
extern void approvals_save_text_file(const char* filename, const char* data);
extern void approvals_delete_file(const char* filename);
extern bool approvals_create_if_needed(const char* filename);
