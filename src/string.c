/**
 * @file src/ghost/string.c.
 *
 * `src/ghost/string.h` impliments C standard library style string handeling
 * functions, which are unavailable due to our ambition to be a free standing,
 * platform-independent tool.
 *
 * @author H Paterson, 2020.
 * @copyright BSL-1.0.
 */

#include "ghost/system.h"

/**
 * Writes a string to the stdout, upto but not including a null character.
 *
 * @param string    The string to write to the standard out.
 * @return  1 on success, -1 on failure.
 */
int puts(const char* const string)
{
    int string_length = 0;
    while (string[string_length++]) {
        ;
    }
    if (write(STDOUT, string, string_length) != string_length) {
        return -1;
    }
    return 1;
}
