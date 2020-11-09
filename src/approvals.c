/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdlib.h>
#include <string.h>

#include "approval_failure_reporter.h"
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

static const char* get_approval_name(const char* full_file_name,
                                     const char* test_name)
{
    const char* last_dot = strrchr(full_file_name, '.');
    size_t length_file_name = 0;
    if (last_dot) {
        length_file_name = last_dot - full_file_name;
    }
    else {
        length_file_name = strlen(full_file_name);
    }

    size_t length = 0;
    length += length_file_name;
    length += 1; /* . */
    length += strlen(test_name);
    length += 1; /* \0 */
    char* s = (char*)malloc(length);

    char* offset = s;
    strcpy(offset, full_file_name);
    offset += length_file_name;
    strcpy(offset, ".");
    offset += 1;
    strcpy(offset, test_name);
    offset += strlen(test_name); /* includes \0 */

#ifdef OS_WINDOWS
    to_path(s);
#endif

    return s;
}

static void approvals_report(struct ApprovalName name)
{
    const char* approved_name = approvals_get_approved_file_name(name);
    const char* received_name = approvals_get_received_file_name(name);
    approval_report_failure(approved_name, received_name);
    free((void*)received_name);
    free((void*)approved_name);
}

const char* __approvals_approve(const char* received,
                                const char* full_file_name,
                                const char* test_name,
                                const char* extension_no_dot)
{
    const char* base_name = get_approval_name(full_file_name, test_name);
    const struct ApprovalName name = {full_file_name, test_name, extension_no_dot};
    /* TODO use basename here, drop struct ApprovalName */
    const char* approved = approvals_read_approved(name);

    approvals_write_received_file(name, received);
    if (approvals_approve_text(approved, received)) {
        /* OK */
        approvals_delete_received_file(name);
    }
    else {
        /* FAIL */
        approvals_report(name);
    }
    free((void*)base_name);
    return approved;
}
