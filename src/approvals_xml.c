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

static void xml_newline(struct StringBuilder* sb, unsigned int intent)
{
    sb_append(sb, "\n");
    for (unsigned int i = 0; i < intent; i++) {
        sb_append(sb, "  ");
    }
}

const char* __approvals_xml_format(const char* xml)
{
    struct StringBuilder* sb = make_sb_sized(strlen(xml));
    if (sb == NULL) {
        /* error, do not format */
        return xml;
    }

    unsigned int intent = 0;
    char prev = '\0', current = '\0', next = '\0';
    bool newline = true;
    bool comment = false;

    for (const char* c = xml; *c; c++) {
        current = *c;
        next = *(c + 1); /* \0 at end */

        if (prev == '<' && current == '!' && next == '-') {
            /* before comment */
            comment = true;
        }

        if (comment) {
            bool comment_ends = (comment && prev == '-' && current == '>');

            if (!comment_ends) {
                sb_append_len(sb, c, 1);
                goto end_loop;
            }

            comment = comment ^ comment_ends;
        }

        if (current == '<') {
            if (next == '/') {
                /* before closing tag */
                intent -= 1;
            }

            /* before opening or closing tag, processing or comment */
            if (!newline) {
                xml_newline(sb, intent);
            }
        }

        sb_append_len(sb, c, 1);
        newline = false;

        if (current == '<' && (next != '/' && next != '?' && next != '!')) {
            /* after opening tag (not closing, not processing, not comment) */
            intent += 1;
        }

        if (current == '>') {
            if (prev == '/') {
                /* self closed tag */
                intent -= 1;
            }

            /* after any tag */
            if (next != '<') {
                xml_newline(sb, intent);
                newline = true;
            }
        }

    end_loop:
        prev = current;
    }

    const char* s = sb_string(sb);
    return s;
}
