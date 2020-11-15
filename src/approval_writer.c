/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdlib.h>
#include <string.h>

#include "approval_writer.h"
#include "file_utils.h"

static const char* create_approvals_file_name_for(struct ApprovalBaseName name, const char* suffix)
{
    /* TODO create string_make with varargs all strings and do this code here */
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

const char* approval_writer_create_approved_file_name(struct ApprovalBaseName name)
{
    return create_approvals_file_name_for(name, "approved");
}

const char* approval_writer_create_received_file_name(struct ApprovalBaseName name)
{
    return create_approvals_file_name_for(name, "received");
}

void approval_writer_write_received_file(struct ApprovalBaseName name, const char* received)
{
    const char* received_name = approval_writer_create_received_file_name(name);

    approvals_save_text_file(received_name, received);

    free((void*)received_name);
}

void approval_writer_delete_received_file(struct ApprovalBaseName name)
{
    const char* received_name = approval_writer_create_received_file_name(name);
    approvals_delete_file(received_name);
    free((void*)received_name);
}
