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

const char* string_make_2(const char* s1, const char* s2)
{
    size_t length = 0;
    length += strlen(s1);
    length += strlen(s2);
    length += 1; /* \0 */
    char* s = (char*)malloc(length);

    char* offset = s;
    strcpy(offset, s1);
    offset += strlen(s1);
    strcpy(offset, s2); /* includes \0 */
    offset += strlen(s2);

    return s;
}
