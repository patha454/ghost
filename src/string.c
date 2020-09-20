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

#include "ghost/system_calls.h"

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

/**
 * Writes a single chracter to the stdout.
 *
 * @warning This function is provided as support for a third party printf
 * implimentation. It may be removed along with the library at a later date,
 * and should not be used directly by Ghost. It does not appear in header files
 * for this reason.
 *
 * @param ch    Character to write to the stdout.
 */
void _putchar(char ch)
{
    write(STDOUT, &ch, 1);
}
