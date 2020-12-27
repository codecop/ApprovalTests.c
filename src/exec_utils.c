/***********************************************************************
 * ApprovalTests.c - Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asserts.h"
#include "file_utils.h"
#include "string_utils.h"
#include "system_utils.h"

static const char* program_files[] = {
    "C:\\Program Files", /* Windows */
    "/Applications",     /* Mac */
    "/usr/bin",          /* Linux */
    0,
};

static const char* windows_program_files_env[] = {
    "ProgramFiles(x86)", /* */
    "ProgramFiles",      /* */
    "ProgramW6432",      /* */
    0,
};

static const char* get_path_in_program_files(const char* diff_program)
{
    assert_str_not_empty(diff_program);

    const char** base_path;
    for (base_path = program_files; *base_path; base_path++) {
        const char* path = string_create_joined(3, *base_path, OS_SLASH, diff_program);
        if (path == NULL) {
            return NULL; /* error */
        }
        if (approvals_file_exists(path)) {
            return path;
        }
        free((void*)path);
    }

    const char** env_key;
    for (env_key = windows_program_files_env; *env_key; env_key++) {
        const char* pf = getenv(*env_key);
        if (pf) {
            const char* path = string_create_joined(3, pf, OS_SLASH, diff_program);
            if (path == NULL) {
                return NULL; /* error */
            }
            if (approvals_file_exists(path)) {
                return path;
            }
            free((void*)path);
        }
    }

    return NULL;
}

static const char* tag = "{ProgramFiles}";

static const char* strip_tag(const char* diff_program)
{
    assert_str_longer_than(diff_program, strlen(tag));

    size_t substring_start = strlen(tag);
    size_t substring_length = strlen(diff_program) - strlen(tag);
    return string_create_substring(diff_program, substring_start, substring_length);
}

const char* approvals_create_resolved_path(const char* diff_program)
{
    assert_str_not_empty(diff_program);

    if (approvals_file_exists(diff_program)) {
        /* copy name for consistent semantic of this method */
        return string_create_joined(1, diff_program);
    }

    if (string_starts_with(diff_program, tag)) {
        const char* remaining_name = strip_tag(diff_program);
        if (remaining_name == NULL) {
            return NULL; /* error */
        }
        const char* resolved_program = get_path_in_program_files(remaining_name);
        free((void*)remaining_name);
        return resolved_program; /* resolved or NULL */
    }

    return NULL;
}

const char* approvals_create_command_line(const char* diff_program,
                                          const char* parameters,
                                          const char* args1,
                                          const char* args2)
{
    assert_str_not_empty(diff_program);
    assert_str_not_empty(parameters);
    assert_str_not_empty(args1);
    assert_str_not_empty(args2);

    size_t length = string_count_joined(4, diff_program, parameters, args1, args2) /* */
                    + 2  /* maybe quotes around diff tool */
                    + 1  /* space after diff program */
                    + 4; /* maybe quotes around arguments */
    char* command = (char*)malloc(length + 1);
    if (command == NULL) {
        return NULL; /* error */
    }

    char* offset = command;
#ifdef OS_WINDOWS
    *offset = '"';
    offset += 1;
#endif
    strcpy(offset, diff_program);
    offset += strlen(diff_program);
#ifdef OS_WINDOWS
    *offset = '"';
    offset += 1;
#endif
    *offset = ' ';
    offset += 1;
    sprintf(offset, parameters, args1, args2);

    return command;
}
