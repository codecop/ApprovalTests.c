/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdlib.h>
#include <string.h>

#include "asserts.h"
#include "system_utils.h"

static void to_path(char* path)
{
    assert_not_null(path);

#ifdef OS_WINDOWS
    char* slash = strrchr(path, '/');
    while (slash) {
        *slash = '\\';
        slash = strrchr(path, '/');
    }
#endif
}

const char* approval_namer_create_approval_name(const char* full_file_name, const char* test_name)
{
    assert_str_not_empty(full_file_name);
    assert_str_not_empty(test_name);

    const char* last_dot = strrchr(full_file_name, '.');
    size_t length_file_name = 0;
    if (last_dot) {
        length_file_name = last_dot - full_file_name;
    }
    else {
        length_file_name = strlen(full_file_name);
        /* TODO test case no dot in full file name */
    }

    size_t length = 0;
    length += length_file_name;
    length += 1; /* . */
    length += strlen(test_name);
    length += 1; /* \0 */
    char* s = (char*)malloc(length);

    char* offset = s;
    strcpy(offset, full_file_name);
    offset += length_file_name;
    strcpy(offset, ".");
    offset += 1;
    strcpy(offset, test_name);
    offset += strlen(test_name); /* includes \0 */

    to_path(s);

    return s;
}
