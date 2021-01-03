#include "../src/file_utils.h"

#define assume_has_file(needed_file) _assume_has_file((needed_file), __FILE__, __LINE__)

static void _assume_has_file(const char* needed_file, const char* file, const int line)
{
    if (approval_file_exists(needed_file)) {
        return;
    }

    print_error("[          ] - test file %s missing.\n", needed_file);
    _skip(file, line);
}
