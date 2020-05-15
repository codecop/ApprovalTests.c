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
    struct StringBuilder* sb = make_sb();
    sb_ensure_size(sb, strlen(xml));

    unsigned int intent = 0;
    char prev = '\0', current = '\0', next = '\0';
    const size_t len = strlen(xml);
    bool newline = true;
    for (size_t i = 0; i < len; i++) {
        current = *(xml + i);
        next = *(xml + i + 1); /* \0 at end */

        /*
         * TODO ignore whitespace outside of tags, after > and before <, ignore \n
         */

        switch (current) {
        /*
        newline before opening tag (unless last was newline)
        newline before closing tag, remove intent, (unless last was newline)
        */
        case '<':              /* opening or closing tag */
            if (next == '/') { /* closing tag */
                intent -= 1;
            }
            if (!newline) {
                xml_newline(sb, intent);
            }
            break;
        default:
            break;
        }

        // printf("%d: %s %d - %d\n", i, (xml + i), current, intent);
        sb_append_len(sb, xml + i, 1);
        newline = false;
        switch (current) {
        /*
        newline after opening tag, increase intent
        newline after closing tag
        */
        case '<':
            if (next != '/') {
                intent += 1;
            }
            break;
        case '>':
            if (prev == '/') {
                intent -= 1;
            }
            if (next != '<') {
                /* if there is a next tag, it will do what is necessary */
                xml_newline(sb, intent);
                newline = true;
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
