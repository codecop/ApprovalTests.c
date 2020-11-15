/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdlib.h>
#include <string.h>

#include "approval_writer.h"
#include "file_utils.h"
#include "string_utils.h"

static const char* create_approvals_file_name_for(struct ApprovalBaseName name, const char* suffix)
{
    return string_create_joined(5, name.base_name, /* */
                                ".",               /* */
                                suffix,            /* "approved" or "received" */
                                ".",               /* */
                                name.extension_no_dot);
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
