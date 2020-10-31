/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "x86_x64.h"

static const char* approvals_file_name_for(const char* full_file_name,
                                           const char* test_name,
                                           const char* suffix,
                                           const char* extension_no_dot)
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
    length += 1;              /* . */
    length += strlen(suffix); /* "approved" or "received" */
    length += 1;              /* . */
    length += strlen(extension_no_dot);
    length += 1; /* \0 */
    char* s = (char*)malloc(length);

    char* offset = s;
    strcpy(offset, full_file_name);
    offset += length_file_name;
    strcpy(offset, ".");
    offset += 1;
    strcpy(offset, test_name);
    offset += strlen(test_name);
    strcpy(offset, ".");
    offset += 1;
    strcpy(offset, suffix);
    offset += 8;
    strcpy(offset, ".");
    offset += 1;
    strcpy(offset, extension_no_dot); /* includes \0 */

    return s;
}

const char* approvals_get_approved_file_name(const char* full_file_name,
                                             const char* test_name,
                                             const char* extension_no_dot)
{
    return approvals_file_name_for(full_file_name, test_name, "approved", extension_no_dot);
}

const char* approvals_get_received_file_name(const char* full_file_name,
                                             const char* test_name,
                                             const char* extension_no_dot)
{
    return approvals_file_name_for(full_file_name, test_name, "received", extension_no_dot);
}

static void approvals_save(const char* filename, const char* data)
{
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Could not create file %s.\n", filename);
        return;
    }
    size_t written = fwrite(data, sizeof(char), strlen(data), file);
    if (written != strlen(data)) {
        fprintf(stderr,
                "Could not write whole %s, " PF_SIZE_T " instead " PF_SIZE_T " bytes.\n",
                filename, strlen(data), written);
    }
    int error_flush = fflush(file);
    if (error_flush) {
        fprintf(stderr, "Could not flush %s, error %d.\n", filename, error_flush);
    }
    int error_close = fclose(file);
    if (error_close) {
        fprintf(stderr, "Could not close %s, error %d.\n", filename, error_close);
    }
}

void approvals_write_received_file(const char* full_file_name,
                                   const char* test_name,
                                   const char* extension_no_dot,
                                   const char* received)
{
    const char* received_name =
        approvals_get_received_file_name(full_file_name, test_name, extension_no_dot);

    approvals_save(received_name, received);

    free((void*)received_name);
}

static void approvals_delete(const char* filename)
{
    int error_remove = remove(filename);
    if (error_remove) {
        fprintf(stderr, "Could not delete %s, error %d.\n", filename, error_remove);
    }
}

void approvals_delete_received_file(const char* full_file_name, const char* test_name, const char* extension_no_dot)
{
    const char* received_name =
        approvals_get_received_file_name(full_file_name, test_name, extension_no_dot);
    approvals_delete(received_name);
    free((void*)received_name);
}
