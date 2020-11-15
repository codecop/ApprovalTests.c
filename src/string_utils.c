/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int string_starts_with(const char* s, const char* prefix)
{
    assert(s != 0);
    assert(prefix != 0);

    const char* si = s;
    const char* pi = prefix;
    while (*si != '\0' && *pi != '\0' && *si == *pi) {
        si += 1;
        pi += 1;
    }
    return *pi == '\0';
}

const char* string_create_substring(const char* s, int start, size_t length)
{
    assert(s != 0);
    assert(start >= 0);
    assert(start + length <= strlen(s));

    char* substring = (char*)malloc(length + 1);
    strncpy(substring, s + start, length);
    substring[length] = '\0';
    return substring;
}
