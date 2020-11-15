/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdlib.h>

extern int string_starts_with(const char* s, const char* prefix);
extern const char* string_create_substring(const char* s, int start, size_t length);
extern const char* string_make_2(const char* s1, const char* s2);
extern const char* string_make_3(const char* s1, const char* s2, const char* s3);
