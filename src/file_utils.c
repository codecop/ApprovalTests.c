/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asserts.h"
#include "x86_x64.h"

static void close_verbosely(FILE* file, const char* filename)
{
    int error_close = fclose(file);
    if (error_close) {
        fprintf(stderr, "Could not close %s, error %d.\n", filename, error_close);
    }
}

bool approval_file_exists(const char* filename)
{
    assert_str_not_empty(filename);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return false;
    }
    close_verbosely(file, filename);
    return true;
}

long approval_file_size(const char* filename)
{
    assert_str_not_empty(filename);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open %s.\n", filename);
        return 0;
    }

    int error_seek = fseek(file, 0, SEEK_END);
    if (error_seek) {
        fprintf(stderr, "Could not go to end of file %s, error %d.\n", filename, error_seek);
        fclose(file);
        return 0;
    }

    long file_size = ftell(file);

    close_verbosely(file, filename);

    return file_size;
}

const char* approval_load_text_file(const char* filename)
{
    assert_str_not_empty(filename);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open %s.\n", filename);
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
    size_t buffer_size = (size_t)file_size; /* might truncate for large files */
    error_seek = fseek(file, 0, SEEK_SET);
    if (error_seek) {
        fprintf(stderr, "Could not reset file %s, error %d.\n", filename, error_seek);
        fclose(file);
        return "";
    }

    char* read_buffer = malloc(sizeof(char) * (buffer_size + 1));
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
        /* TODO add logic counting newlines and adapting the read count on windows */
    }

    close_verbosely(file, filename);

    return read_buffer;
}

void approval_save_text_file(const char* filename, const char* data)
{
    assert_str_not_empty(filename);
    assert_not_null(data);

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
    close_verbosely(file, filename);
}

bool approval_delete_file(const char* filename)
{
    assert_str_not_empty(filename);

    int error_remove = remove(filename);
    if (error_remove) {
        fprintf(stderr, "Could not delete %s, error %d.\n", filename, error_remove);
        return false;
    }
    return true;
}

bool approval_create_if_needed(const char* filename)
{
    assert_str_not_empty(filename);

    if (approval_file_exists(filename)) {
        return false;
    }
    approval_save_text_file(filename, "");
    return true;
}
