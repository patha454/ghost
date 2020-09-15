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

#ifndef GHOST_SYSTEM_H_
#define GHOST_SYSTEM_H_

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

/**
 * `exit_group` exits all threads in the current group.
 *
 * This should include the current process, and all child threads.
 *
 * @param status_code    The exit code to return to the system.
 */
void exit_group(int status_code);

#endif
