/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#ifndef Approval_Asserts_H_
#define Approval_Asserts_H_

#include <assert.h>

#define assert_not_null(p) assert((p) != NULL);

#define assert_str_not_empty(s) assert_not_null(s) assert(*(s) != '\0');

#define assert_str_longer_than(s, len) assert_not_null(s) assert(strlen((s)) > (len));

#endif