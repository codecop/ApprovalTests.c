/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "approval_failure_reporter.h"
#include "approval_namer.h"
#include "approval_writer.h"
#include "approval_xml.h"
#include "asserts.h"
#include "file_utils.h"

static const char* read_approved(struct ApprovalBaseName name)
{
    const char* approved_name = approval_writer_create_approved_file_name(name);
    const char* approved = approvals_load_text_file(approved_name);
    free((void*)approved_name);

    return approved;
}

static bool is_approved(struct ApprovalData data)
{
    assert_not_null(data.approved);
    assert_not_null(data.received);

    return strcmp(data.approved, data.received) == 0;
}

static void report_failure(struct ApprovalBaseName name, struct ApprovalData data, struct ApprovalVerifyLine verify_line)
{
    /* TODO not tested */
    const char* approved_name = approval_writer_create_approved_file_name(name);
    const char* received_name = approval_writer_create_received_file_name(name);
    const struct ApprovalFileNames file_names = {approved_name, received_name};
    approval_report_failure(file_names, data, verify_line);
    free((void*)received_name);
    free((void*)approved_name);
}

static const char* format_received(const char* received, const char* extension_no_dot)
{
    if (strcmp(extension_no_dot, "xml") == 0) {
        return approvals_xml_format(received);
    }
    return received;
}

void __approvals_approve(const char* raw_received,
                         const char* full_file_name,
                         const char* test_name,
                         int line,
                         const char* extension_no_dot)
{
    assert_not_null(raw_received);
    assert_str_not_empty(full_file_name)
    assert_str_not_empty(test_name)
    assert_str_not_empty(extension_no_dot)

    const char* base_name = approval_namer_create_approval_name(full_file_name, test_name);
    const struct ApprovalBaseName name = {base_name, extension_no_dot};
    const char* approved = read_approved(name);

    const char* received = format_received(raw_received, extension_no_dot);
    approval_writer_write_received_file(name, received);

    const struct ApprovalData data = {approved, received};
    if (is_approved(data)) {
        /* OK */
        approval_writer_delete_received_file(name);
    }
    else {
        /* FAIL */
        const struct ApprovalVerifyLine verify_line = {full_file_name, line};
        report_failure(name, data, verify_line);
        /* TODO not tested */
    }

    if (raw_received != received) {
        free((void*)received);
    }
    free((void*)approved);
    free((void*)base_name);
}
