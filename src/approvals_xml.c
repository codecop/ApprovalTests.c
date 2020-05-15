/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include "StringBuilder.h"
#include <stdlib.h>
#include <string.h>

const char* __approvals_xml_format(const char* xml)
{
    struct StringBuilder* sb = make_sb();
    sb_ensure_size(sb, strlen(xml));

    for (size_t i = 0; i < strlen(xml); i++) {
        sb_append_len(sb, xml + i, 1);
        if (*(xml + i) == '>') {
            sb_append(sb, "\n");
        }
    }

    const char* s = sb_string(sb);
    return s;
}
