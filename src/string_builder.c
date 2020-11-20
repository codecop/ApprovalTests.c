/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_BUFFER 16

struct StringBuilder {
    char* buffer;
    size_t buffer_length;
    size_t position;
};

struct StringBuilder* make_sb(void)
{
    struct StringBuilder* this = (struct StringBuilder*)malloc(sizeof(struct StringBuilder));
    if (this == NULL) {
        return NULL; /* error */
    }
    this->buffer_length = INITIAL_BUFFER;
    this->buffer = malloc(this->buffer_length);
    this->buffer[0] = '\0';
    this->position = 0;
    return this;
}

static int sb_ensure_size(struct StringBuilder* this, size_t length)
{
    size_t required_size = this->position + length + 1;
    if (this->buffer_length > required_size) {
        return EXIT_SUCCESS;
    }

    size_t new_length = this->buffer_length;
    while (new_length < required_size) {
        new_length *= 2;
    }

    char* old_buffer = this->buffer;
    this->buffer = malloc(new_length);
    if (this->buffer == NULL) {
        this->buffer = old_buffer;
        return EXIT_FAILURE;
    }

    this->buffer_length = new_length;
    memcpy(this->buffer, old_buffer, this->position + 1);
    free(old_buffer);
    return EXIT_SUCCESS;
}

struct StringBuilder* make_sb_sized(size_t length)
{
    struct StringBuilder* sb = make_sb();
    int error = sb_ensure_size(sb, length);
    if (error) {
        free(sb);
        return NULL; /* error */
    }
    return sb;
}

int sb_append_len(struct StringBuilder* this, const char* s, size_t length)
{
    int error = sb_ensure_size(this, length);
    if (error) {
        return error;
    }

    memcpy(this->buffer + this->position, s, length + 1);
    this->position += length;
    return EXIT_SUCCESS;
}

int sb_append(struct StringBuilder* this, const char* s)
{
    return sb_append_len(this, s, strlen(s));
}

const char* sb_string(struct StringBuilder* this)
{
    const char* s = this->buffer;
    free(this);
    return s;
}
