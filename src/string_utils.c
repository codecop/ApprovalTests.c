/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "asserts.h"

#define TERM '\0'

bool string_starts_with(const char* s, const char* prefix)
{
    assert_not_null(s);
    assert_not_null(prefix);

    const char* si = s;
    const char* pi = prefix;
    while (*si != TERM && *pi != TERM && *si == *pi) {
        si += 1;
        pi += 1;
    }
    return *pi == TERM;
}

const char* string_create_substring(const char* s, size_t start, size_t length)
{
    assert_not_null(s);
    assert(start + length <= strlen(s));

    char* substring = (char*)malloc(length + 1);
    if (substring == NULL) {
        return NULL; /* error */
    }
    strncpy(substring, s + start, length);
    substring[length] = TERM;
    return substring;
}

static size_t vstring_count_joined(size_t count, va_list strings)
{
    size_t length = 0;

    size_t i;
    for (i = 0; i < count; i++) {
        const char* string_i = va_arg(strings, char*);
        length += strlen(string_i);
    }

    return length;
}

size_t string_count_joined(size_t count, ...)
{
    va_list strings;

    va_start(strings, count);
    size_t total_length = vstring_count_joined(count, strings) + 1; /* \0 */
    va_end(strings);

    return total_length;
}

const char* string_create_joined(size_t count, ...)
{
    va_list strings;

    va_start(strings, count);
    size_t total_length = vstring_count_joined(count, strings) + 1; /* \0 */
    va_end(strings);

    char* s = (char*)malloc(total_length);
    if (s == NULL) {
        return NULL; /* error */
    }
    char* offset = s;

    va_start(strings, count);
    size_t i;
    for (i = 0; i < count; i++) {
        const char* string_i = va_arg(strings, char*);
        strcpy(offset, string_i);
        offset += strlen(string_i);
    }
    va_end(strings);

    *offset = TERM;

    return s;
}
