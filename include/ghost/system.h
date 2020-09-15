/**
 * @file include/ghost/system.h
 * 
 * `include/ghost/system.h` defines a generic interface to system functions,
 * such as file I/O, and memory mapping.
 *
 * Most functions in `system.h` are based on Linux system calls, but should
 * be able to be implimnted in other systems using equivliant system calls,
 * or combinations of system calls and wrapper logic.
 *
 * @author H Paterson, 2020.
 * @copyright BSL-1.0.
 */

#include "ghost/types.h"
#include <stddef.h>

#define STDOUT 1

/**
 * `write` writes upto `count` bytes from the buffer starting at `buf` into
 * the file refered to by the file descriptor `fd`.
 *
 * @param fd    File descriptor to write to.
 * @param buf   Buffer to copy from.
 * @param count Number of bytes to write.
 * @return      The number of bytes actually written, or -1 on error.
 */
ssize_t write(int fd, const void* buf, size_t count);
