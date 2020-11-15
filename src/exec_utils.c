/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdlib.h>
#include <string.h>

#include "file_utils.h"
#include "string_utils.h"
#include "system_utils.h"

static const char* program_files[] = {
    "C:\\Program Files", /* Windows */
    "/Applications",     /* Mac */
    "/usr/bin",          /* Linux */
};
static size_t count_program_files()
{
    return sizeof(program_files) / sizeof(char*);
}

static const char* windows_program_files_env[] = {
    "ProgramFiles(x86)", /* */
    "ProgramFiles",      /* */
    "ProgramW6432",      /* */
};
static size_t count_windows_program_files_env()
{
    return sizeof(windows_program_files_env) / sizeof(char*);
}

static const char* get_path_in_program_files(const char* diff_program)
{
    size_t i;

    for (i = 0; i < count_program_files(); i++) {
        const char* path = string_create_joined(3, program_files[i], OS_SLASH, diff_program);
        if (approvals_file_exists(path)) {
            return path;
        }
        free((void*)path);
    }

    for (i = 0; i < count_windows_program_files_env(); i++) {
        const char* pf = getenv(windows_program_files_env[i]);
        if (pf) {
            const char* path = string_create_joined(3, pf, OS_SLASH, diff_program);
            if (approvals_file_exists(path)) {
                return path;
            }
            free((void*)path);
        }
    }

    return 0;
}

static const char* tag = "{ProgramFiles}";

static const char* strip_tag(const char* diff_program)
{
    int substring_start = strlen(tag);
    size_t substring_length = strlen(diff_program) - strlen(tag);
    return string_create_substring(diff_program, substring_start, substring_length);
}

const char* aprovals_create_resolved_path(const char* diff_program)
{
    if (approvals_file_exists(diff_program)) {
        /* copy name for consistent semantic of this method */
        return string_create_joined(1, diff_program);
    }

    if (string_starts_with(diff_program, tag)) {
        const char* remaining_name = strip_tag(diff_program);
        const char* resolved_program = get_path_in_program_files(remaining_name);
        free((void*)remaining_name);
        return resolved_program; /* resolved or null */
    }

    return 0;
}

/* FileUtils.create_if_needed(approved); */

const char* get_command_line(const char* parameters, const char* args1, const char* args2)
{
    (void)parameters; /* unused */
    (void)args1;      /* unused */
    (void)args2;      /* unused */
    /*
      2. command line ****************************************************
      getCommandLine
    String full = String.format(arguments, "{received}", "{approved}");
    List<String> argsSplitOnSpace = Arrays.stream(full.split(" "))
        .map(t -> t.replace("{received}", received).replace("{approved}",
    approved)).collect(Collectors.toList()); ArrayList<String> commands = new
    ArrayList<String>(); commands.add(diffProgram); commands.addAll(argsSplitOnSpace);
    System.out.println(commands);
    return commands.toArray(new String[0]);

    */
    return 0;
}

/*
3. launch ***********************************************************

launch(command, parameters);


  ProcessBuilder builder = new ProcessBuilder(getCommandLine(received, approved));
  preventProcessFromClosing(builder);
  builder.start();

*/
