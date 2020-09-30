/**
 * @file src/system_calls/linux.c
 * 
 * `src/system_calls/linux.c` impliments aninterface to Linux system functions,
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

/**
 * `open` opens the file at the given path.
 *
 * @param path  The path to the file to be opened.
 * @return      A file descriptor to the open file.
 */
int open(const char* pathname)
{
    const int O_RDONLY = 0;
    return sys_open(pathname, O_RDONLY);
}

/**
 * `close` closes a file indicated by a file descriptor.
 *
 * @param fd    The fild descriptor to close.
 */
void close(size_t fd)
{
    sys_close(fd);
}

/**
 * `read` attempts to bytes from a file.
 *
 * @param fd    File descriptor to read from.
 * @param buf   Buffer to copy bytes to.
 * @param count Number of bytes to copy.
 * @return      The number of bytes actually read, or a negative error code.
 */
ssize_t read(int fd, void* buf, size_t count)
{
    return sys_read(fd, buf, count);
}
