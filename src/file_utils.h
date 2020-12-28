/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdbool.h>

extern bool approval_file_exists(const char* filename);
extern const char* approval_load_text_file(const char* filename);
extern long approval_file_size(const char* filename);
extern void approval_save_text_file(const char* filename, const char* data);
extern bool approval_delete_file(const char* filename);
extern bool approval_create_if_needed(const char* filename);
