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

#endif
