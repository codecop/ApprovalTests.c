/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#ifndef Asserts
#define Asserts

#include <assert.h>

#define assert_not_null(p) assert((p) != 0);

#define assert_str_not_empty(s) \
    assert((s) != 0);           \
    assert(*(s) != '\0');

#define assert_str_longer_than(s, len) \
    assert((s) != 0);                  \
    assert(strlen((s)) > (len));

#endif