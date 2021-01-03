/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdbool.h>
#include <stdlib.h>

extern bool string_starts_with(const char* s, const char* prefix);
extern const char* string_create_substring(const char* s, const size_t start, const size_t length);
extern size_t string_count_joined(const size_t count, ...);
extern const char* string_create_joined(const size_t count, ...);
extern const char* string_create_empty(void);
extern unsigned int string_count(const char* s, const char needle);
