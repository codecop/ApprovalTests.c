/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <assert.h>
#include <stdarg.h>
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

static size_t string_count_joined(size_t count, ...)
{
    va_list strings;
    size_t length = 0;

    va_start(strings, count);
    size_t i;
    for (i = 0; i < count; i++) {
        const char* s = va_arg(strings, char*);
        length += strlen(s);
    }
    va_end(strings);

    return length;
}

const char* string_create_joined(size_t count, ...)
{
    va_list strings;
    va_start(strings, count);

    size_t total_length = string_count_joined(count, strings) + 1; /* \0 */
    char* s = (char*)malloc(total_length);
    char* offset = s;

    size_t i;
    for (i = 0; i < count; i++) {
        const char* string_i = va_arg(strings, char*);
        strcpy(offset, string_i);
        offset += strlen(string_i);
    }
    va_end(strings);

    *offset = '\0';

    return s;
}
