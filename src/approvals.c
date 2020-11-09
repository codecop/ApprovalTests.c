/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdlib.h>
#include <string.h>

#include "approval_failure_reporter.h"
#include "approval_namer.h"
#include "approval_writer.h"
#include "file_utils.h"

static const char* approvals_read_approved(struct ApprovalFileName name)
{
    const char* approved_name = approval_writer_create_approved_file_name(name);
    const char* approved = approvals_load_text_file(approved_name);
    free((void*)approved_name);

    return approved;
}

static int approvals_approve_text(const char* approved, const char* received)
{
    return strcmp(approved, received) == 0;
}

static void approvals_report(struct ApprovalFileName name)
{
    const char* approved_name = approval_writer_create_approved_file_name(name);
    const char* received_name = approval_writer_create_received_file_name(name);
    approval_report_failure(approved_name, received_name);
    free((void*)received_name);
    free((void*)approved_name);
}

const char* __approvals_approve(const char* received,
                                const char* full_file_name,
                                const char* test_name,
                                const char* extension_no_dot)
{
    const char* base_name = approval_namer_create_approval_name(full_file_name, test_name);
    const struct ApprovalFileName name = {base_name, extension_no_dot};
    /* TODO use basename here, drop struct ApprovalName */
    const char* approved = approvals_read_approved(name);

    approval_writer_write_received_file(name, received);
    if (approvals_approve_text(approved, received)) {
        /* OK */
        approval_writer_delete_received_file(name);
    }
    else {
        /* FAIL */
        approvals_report(name);
    }
    free((void*)base_name);
    return approved;
}
