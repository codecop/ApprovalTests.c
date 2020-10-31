/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "x86_x64.h"

const char* approvals_load_text_file(const char* filename)
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

void approvals_save_text_file(const char* filename, const char* data)
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

void approvals_delete_file(const char* filename)
{
    int error_remove = remove(filename);
    if (error_remove) {
        fprintf(stderr, "Could not delete %s, error %d.\n", filename, error_remove);
    }
}
