/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdlib.h>
#include <string.h>

/* not C99, only POSIX */
char* strdup(const char* src)
{
    char* dst = malloc(strlen(src) + 1);
    if (dst == NULL) {
        return NULL;
    }
    strcpy(dst, src);
    return dst;
}

const char* __approvals_xml_format(const char* xml)
{
    return strdup(xml);
}
