/**
 * @file `include/ghost/system/linux.h`.
 * 
 * `include/ghost/system/linux.h` defines relevant system calls for the Linux
 * operating system.
 *
 * The system calls are implimented in assembly so we can avoid depending on
 * host libraries which would either need to be dynamically linked (impossible
 * because the dynamic linker must load statically), statically linked (
 * undesirable because it would bloat the executable with unneeded system calls
 * , or depend on the C runtime library (impossible because initialising the
 * CRT twice - once from the loader and once from the target - would create 
 * problems).
 *
 * @author H Paterson, 2020.
 * @copyright BSL-1.0.
 */

#ifndef GHOST_ASM_LINUX_H_
#define GHOST_ASM_LINUX_H_

#include "ghost/types.h"
#include <stddef.h>

/**
 * Linux system call `write`.
 *
 * @param fd    File descriptor to write to.
 * @param buf   Buffer to write to the file.
 * @param count Number of bytes to write to the file.
 * @return      The number of bytes written to the file, or -1 on error.
 */
ssize_t sys_write(unsigned int fd, const char* buf, size_t count);

/**
 * Linux system call `exit_group`.
 *
 * Exit this thread and any threads in its group. This should include forked
 * threads and processes.
 *
 * @param error_code Error code (exit status) to return to the system.
 * @return Should never return.
 */
int sys_exit_group(int error_code);

/**
 * Linux `open` system call.
 *
 * @param path  The path to the file to be opened.
 * @param flags Flags about the file opening.
 * @return      A file descriptor to the open file.
 */
size_t sys_open(const char* pathname, int flags);

/**
 * Linux `closes` system call.
 *
 * @param fd    The fild descriptor to close.
 */
void sys_close(size_t fd);

/**
 * Linux `read` system call.
 *
 * @param fd    File descriptor to read from.
 * @param buf   Buffer to copy bytes to.
 * @param count Number of bytes to copy.
 * @return      The number of bytes actually read, or a negative error code.
 */
ssize_t sys_read(int fd, void* buf, size_t count);

/**
 * Linux `lseek` system call.
 *
 * @param fd        File descriptor to seek in,
 * @param offset    Offset to seek to
 * @param count     Seek relative to where.
 * @return      The number of bytes actually read, or a negative error code.
 */
ssize_t sys_lseek(int fd, unsigned int offset, int whence);

/**
 * Linux `mmap` system call.
 *
 * @param addr      Start address of the mapping in memory.
 * @param length    Length of the mapping in memory.
 * @param prot      Protection mode flags.
 * @param flags     Indicates the visiblity of the mapping.
 * @param fd        File descriptor for a file backed mapping.
 * @param offset    Offset of the file backing contents.
 * @return          The address of the new mapping.
 */
void* sys_mmap(void* addr,
    unsigned long length,
    unsigned long prot,
    unsigned long flags,
    unsigned long fd,
    unsigned long offset);

#endif
