/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include "StringBuilder.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

const char* __approvals_xml_format(const char* xml)
{
    struct StringBuilder* sb = make_sb();
    sb_ensure_size(sb, strlen(xml));

    int intent = 0;
    char prev = '\0';
    const size_t len = strlen(xml);
    for (size_t i = 0; i < len; i++) {
        char current = *(xml + i);
        char next = *(xml + i + 1); /* \0 at end */

        switch (current) {
        case '<':
            if (next == '/') {
                intent -= 1;
            }
            if (prev != '\0') {
                sb_append(sb, "\n");
                if (intent > 0) {
                    sb_append(sb, "  ");
                }
            }
            break;
        default:
            break;
        }

        // bool is_opening = (current = '<' && next != '/');
        // printf("%d: %s %d - %d\n", i, (xml + i), current, intent);
        sb_append_len(sb, xml + i, 1);
        /*
         * TODO ignore whitespace outside of tags, after > and before <, ignore \n
         */
        switch (current) {
        case '<':
            if (next != '/') {
                intent += 1;
            }
            else {
                intent -= 1;
            }
            break;
        case '>':
            if (prev == '/') {
                intent -= 1;
            }
            sb_append(sb, "\n");
            if (intent > 0) {
                sb_append(sb, "  ");
            }
            break;
        default:
            break;
        }
        prev = current;
    }

    const char* s = sb_string(sb);
    return s;
}
