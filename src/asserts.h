/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#ifndef Asserts_H_
#define Asserts_H_

#include <assert.h>

#define assert_not_null(p) assert((p) != NULL);

#define assert_str_not_empty(s) \
    assert((s) != NULL);           \
    assert(*(s) != '\0');

#define assert_str_longer_than(s, len) \
    assert((s) != NULL);                  \
    assert(strlen((s)) > (len));

#endif