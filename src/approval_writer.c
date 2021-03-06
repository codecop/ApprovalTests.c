/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdlib.h>

#include "approval_writer.h"
#include "asserts.h"
#include "file_utils.h"
#include "string_utils.h"

#define APPROVED "approved"
#define RECEIVED "received"

static void assert_approval_base_name(const struct ApprovalBaseName name)
{
    assert_str_not_empty(name.base_name);
    assert_not_null(name.extension_no_dot);
}

static const char* create_approvals_file_name_for(const struct ApprovalBaseName name, const char* suffix)
{
    assert_approval_base_name(name);
    assert_str_not_empty(suffix);

    return string_create_joined(5, name.base_name, /* */
                                ".",               /* */
                                suffix,            /* "approved" or "received" */
                                ".",               /* */
                                name.extension_no_dot);
}

const char* approval_writer_create_approved_file_name(const struct ApprovalBaseName name)
{
    return create_approvals_file_name_for(name, APPROVED);
}

const char* approval_writer_create_received_file_name(const struct ApprovalBaseName name)
{
    return create_approvals_file_name_for(name, RECEIVED);
}

void approval_writer_write_received_file(const struct ApprovalBaseName name, const char* received)
{
    assert_approval_base_name(name);
    assert_not_null(received);

    const char* received_name = approval_writer_create_received_file_name(name);
    approval_save_text_file(received_name, received);
    free((void*)received_name);
}

void approval_writer_delete_received_file(const struct ApprovalBaseName name)
{
    assert_approval_base_name(name);

    const char* received_name = approval_writer_create_received_file_name(name);
    approval_delete_file(received_name);
    free((void*)received_name);
}
