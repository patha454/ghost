/**
 * @file include/ghost/string.h.
 *
 * `include/ghost/string.h` defines C standard library style string handeling
 * functions, which are unavailable due to our ambition to be a free standing,
 * platform-independent tool.
 *
 * @author H Paterson, 2020.
 * @copyright BSL-1.0.
 */

#ifndef GHOST_STRING_H_
#define GHOST_STRING_H_

/**
 * Writes a string, upto but not including a null character.
 *
 * @return The number of characters written, or -1 on error.
 */
int puts(const char* str);

#endif
