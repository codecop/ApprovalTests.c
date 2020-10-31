/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include "approvals_writer.h"

extern const char* approvals_load(const char* filename);
extern void approvals_save(const char* filename, const char* data);
extern void approvals_delete(const char* filename);
