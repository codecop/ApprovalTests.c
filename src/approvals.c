/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "asserts.h"
#include "approval_failure_reporter.h"
#include "approval_namer.h"
#include "approval_writer.h"
#include "file_utils.h"

static const char* read_approved(struct ApprovalBaseName name)
{
    const char* approved_name = approval_writer_create_approved_file_name(name);
    const char* approved = approvals_load_text_file(approved_name);
    free((void*)approved_name);

    return approved;
}

static bool text_is_approved(const char* approved, const char* received)
{
    assert_not_null(approved);
    assert_not_null(received);

    return strcmp(approved, received) == 0;
}

static void report_failure(struct ApprovalBaseName name)
{
    /* TODO not tested */
    const char* approved_name = approval_writer_create_approved_file_name(name);
    const char* received_name = approval_writer_create_received_file_name(name);
    struct ApprovalFileNames file_names = {approved_name, received_name};
    approval_report_failure(file_names);
    free((void*)received_name);
    free((void*)approved_name);
}

const char* __approvals_approve(const char* received,
                                const char* full_file_name,
                                const char* test_name,
                                const char* extension_no_dot)
{
    assert_not_null(received);
    assert_str_not_empty(full_file_name)
    assert_str_not_empty(test_name)
    assert_str_not_empty(extension_no_dot)

    const char* base_name = approval_namer_create_approval_name(full_file_name, test_name);
    const struct ApprovalBaseName name = {base_name, extension_no_dot};
    const char* approved = read_approved(name);

    approval_writer_write_received_file(name, received);
    if (text_is_approved(approved, received)) {
        /* OK */
        approval_writer_delete_received_file(name);
    }
    else {
        /* FAIL */
        report_failure(name);
        /* TODO not tested */
    }

    free((void*)base_name);
    return approved;
}
