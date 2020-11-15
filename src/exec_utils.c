/***********************************************************************
 * ApprovalTests.c - micro Approval Tests for C99.
 * Copyright (c) 2020, Peter Kofler. All rights reserved.
 * BSD3 licensed.
 */
#include <stdlib.h>
#include <string.h>

#include "file_utils.h"
#include "string_utils.h"
/*
  1. diff exe ************************************************

  public boolean checkFileExists()
  -> approvals_file_exists
*/

static const char* get_path_in_program_files(const char* diff_program)
{
    char* s = (char*)malloc(100 + 1);

    char* offset = s;
    strcpy(offset, "C:\\Program Files\\");
    offset += strlen("C:\\Program Files\\");
    strcpy(offset, diff_program);
    offset += strlen(diff_program);
    offset += 1; /* copied /0 */
    /*

    paths.add(System.getenv("ProgramFiles(x86)")); // getenv("MY_ENV_VAR");
    paths.add(System.getenv("ProgramFiles"));
    paths.add(System.getenv("ProgramW6432"));
    if paths != null

    if path+diff_program exists
      return path+diff_program

    return null
    */
    return s;
}

/* TODO rename to create resolved program_path */
const char* aprovals_resolve_program_path(const char* diff_program)
{
    const char* tag = "{ProgramFiles}";
    if (string_starts_with(diff_program, tag)) {
        int substring_start = strlen(tag);
        size_t substring_length = strlen(diff_program) - strlen(tag);
        const char* remaining_name =
            string_create_substring(diff_program, substring_start, substring_length);
        const char* resolved_program = get_path_in_program_files(remaining_name);
        free((void*)remaining_name);
        return resolved_program; /* resolved or null */
    }

    if (approvals_file_exists(diff_program)) {
        /* copy name for consistent semantic of this method */
        size_t length = strlen(diff_program) + 1;
        char* resolved_program = (char*)malloc(length);
        strcpy(resolved_program, diff_program);
        return resolved_program;
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
