/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdlib.h>
#include <string.h>

#include "approval_writer.h"
#include "file_utils.h"
#include "system_utils.h"

static const char* approvals_file_name_for(struct ApprovalName name, const char* suffix)
{
    size_t length = 0;
    length += strlen(name.base_name);
    length += 1;              /* . */
    length += strlen(suffix); /* "approved" or "received" */
    length += 1;              /* . */
    length += strlen(name.extension_no_dot);
    length += 1; /* \0 */
    char* s = (char*)malloc(length);

    char* offset = s;
    strcpy(offset, name.base_name);
    offset += strlen(name.base_name);
    strcpy(offset, ".");
    offset += 1;
    strcpy(offset, suffix);
    offset += 8;
    strcpy(offset, ".");
    offset += 1;
    strcpy(offset, name.extension_no_dot); /* includes \0 */

    return s;
}

const char* approvals_get_approved_file_name(struct ApprovalName name)
{
    return approvals_file_name_for(name, "approved");
}

const char* approvals_get_received_file_name(struct ApprovalName name)
{
    return approvals_file_name_for(name, "received");
}

void approvals_write_received_file(struct ApprovalName name, const char* received)
{
    const char* received_name = approvals_get_received_file_name(name);

    approvals_save_text_file(received_name, received);

    free((void*)received_name);
}

void approvals_delete_received_file(struct ApprovalName name)
{
    const char* received_name = approvals_get_received_file_name(name);
    approvals_delete_file(received_name);
    free((void*)received_name);
}
