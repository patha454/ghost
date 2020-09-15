/**
 * @file src/system/linux.h
 * 
 * `src/system/linux.h` impliments a generic interface to system functions,
 * such as file I/O, and memory mapping.
 *
 * @see `include/ghost/system.h`
 * 
 * @note These are mostly thin wrappers around Linux system calls because the
 * Ghost generic system interface is based on Linux system calls.
 *
 * @author H Paterson, 2020.
 * @copyright BSL-1.0.
 */

#include "ghost/asm/linux.h"
#include "ghost/types.h"
#include <stddef.h>

/**
 * `write` writes upto `count` bytes from the buffer starting at `buf` into
 * the file refered to by the file descriptor `fd`.
 *
 * @param fd    File descriptor to write to.
 * @param buf   Buffer to copy from.
 * @param count Number of bytes to write.
 * @return      The number of bytes actually written, or -1 on error.
 */
ssize_t write(unsigned int fd, const char* buf, size_t count)
{
    return sys_write(fd, buf, count);
}

/**
 * `exit_group` exits all threads in the current group.
 *
 * This should include the current process, and all child threads.
 *
 * @param status_code    The exit code to return to the system.
 */
void exit_group(int status_code)
{
    sys_exit_group(status_code);
}
