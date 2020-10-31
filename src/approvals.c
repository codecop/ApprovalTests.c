/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "approval_writer.h"
#include "x86_x64.h"

const char* approvals_load(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file %s.\n", filename);
        return "";
    }

    int error_seek = fseek(file, 0, SEEK_END);
    if (error_seek) {
        fprintf(stderr, "Could not go to end of file %s, error %d.\n", filename, error_seek);
        fclose(file);
        return "";
    }
    long file_size = ftell(file);
    if (file_size < 0) {
        fprintf(stderr, "Could not get file size of file %s, file size %ld.\n", filename, file_size);
        fclose(file);
        return "";
    }
    size_t buffer_size = file_size;
    error_seek = fseek(file, 0, SEEK_SET);
    if (error_seek) {
        fprintf(stderr, "Could not reset file %s, error %d.\n", filename, error_seek);
        fclose(file);
        return "";
    }

    char* read_buffer = malloc(sizeof(char[buffer_size + 1]));
    if (read_buffer == NULL) {
        fprintf(stderr,
                "Could not allocate buffer for file %s, need " PF_SIZE_T " bytes.\n",
                filename, buffer_size);
        fclose(file);
        return "";
    }

    size_t read = fread(read_buffer, sizeof(char), buffer_size, file);
    read_buffer[read] = '\0';
    if (read != buffer_size) {
        fprintf(stderr,
                "Did not read whole file %s, got " PF_SIZE_T
                " bytes instead of " PF_SIZE_T ".\n",
                filename, read, buffer_size);
    }

    int error_close = fclose(file);
    if (error_close) {
        fprintf(stderr, "Could not close %s, error %d.\n", filename, error_close);
    }

    return read_buffer;
}

void approvals_delete(const char* filename)
{
    int error_remove = remove(filename);
    if (error_remove) {
        fprintf(stderr, "Could not delete %s, error %d.\n", filename, error_remove);
    }
}

const char* __approvals_verify(const char* received,
                               const char* full_file_name,
                               const char* test_name,
                               const char* extension_no_dot)
{
    approvals_write_received_file(full_file_name, test_name, extension_no_dot, received);

    const char* approved_name =
        approvals_get_approved_file_name(full_file_name, test_name, extension_no_dot);
    const char* approved = approvals_load(approved_name);

    if (strcmp(approved, received) == 0) {
        /* OK */
        const char* received_name =
            approvals_get_received_file_name(full_file_name, test_name, extension_no_dot);
        approvals_delete(received_name);
        free((void*)received_name);
    }

    free((void*)approved_name);

    return approved;
}
