/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* approvals_file_name_for(const char* full_file_name,
                                    const char* test_name,
                                    bool is_approved,
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
    length += 1; /* . */
    length += 8; /* "approved" or "received" */
    length += 1; /* . */
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
    if (is_approved) {
        strcpy(offset, "approved");
    }
    else {
        strcpy(offset, "received");
    }
    offset += 8;
    strcpy(offset, ".");
    offset += 1;
    strcpy(offset, extension_no_dot); /* includes \0 */

    return s;
}

const const char* approvals_load(const char* filename)
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
        fprintf(stderr, "Could not allocate buffer for file %s, need %u bytes.\n", filename, buffer_size);
        fclose(file);
        return "";
    }

    size_t read = fread(read_buffer, sizeof(char), buffer_size, file);
    read_buffer[read] = '\0';
    if (read != buffer_size) {
        fprintf(stderr, "Did not read whole file %s, got %u bytes instead of %u.\n",
                filename, read, buffer_size);
    }

    int error_close = fclose(file);
    if (error_close) {
        fprintf(stderr, "Could not close %s, error %d.\n", filename, error_close);
    }

    return read_buffer;
}

void approvals_save(const char* filename, const char* data)
{
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Could not create file %s.\n", filename);
        return;
    }
    size_t written = fwrite(data, sizeof(char), strlen(data), file);
    if (written != strlen(data)) {
        fprintf(stderr, "Could not write whole %s, %u instead %u bytes.\n", filename,
                strlen(data), written);
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
    const char* received_name =
        approvals_file_name_for(full_file_name, test_name, false, extension_no_dot);
    approvals_save(received_name, received);

    const char* approved_name =
        approvals_file_name_for(full_file_name, test_name, true, extension_no_dot);
    const char* approved = approvals_load(approved_name);

    if (strcmp(approved, received) == 0) {
        /* OK */
        approvals_delete(received_name);
    }

    free((void*)received_name);
    free((void*)approved_name);

    return approved;
}
