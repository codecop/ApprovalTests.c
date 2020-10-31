/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdlib.h>
#include <string.h>

#include "approval_writer.h"
#include "file_utils.h"

static const char* approvals_read_approved(struct ApprovalName name)
{
    const char* approved_name = approvals_get_approved_file_name(name);
    const char* approved = approvals_load_text_file(approved_name);
    free((void*)approved_name);

    return approved;
}

static int approvals_approve_text(const char* approved, const char* received)
{
    return strcmp(approved, received) == 0;
}

const char* __approvals_approve(const char* received,
                                const char* full_file_name,
                                const char* test_name,
                                const char* extension_no_dot)
{
    const struct ApprovalName name = {full_file_name, test_name, extension_no_dot};
    const char* approved = approvals_read_approved(name);

    approvals_write_received_file(name, received);
    if (approvals_approve_text(approved, received)) {
        /* OK */
        approvals_delete_received_file(name);
    }

    return approved;
}
