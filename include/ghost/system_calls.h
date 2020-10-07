/**
 * @file include/ghost/system_calls.h
 * 
 * `include/ghost/system_calls.h` defines a generic interface to system functions,
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

/* This shouldn't be here, but this whole program is a quick hack, so... */
#define PAGE_SIZE 4096

/**
 * `write` writes upto `count` bytes from the buffer starting at `buf` into
 * the file refered to by the file descriptor `fd`.
 *
 * @param fd    File descriptor to write to.
 * @param buf   Buffer to copy from.
 * @param count Number of bytes to write.
 * @return      The number of bytes actually written, or -1 on error.
 */
ssize_t write(unsigned int fd, const void* buf, size_t count);

/**
 * `exit_group` exits all threads in the current group.
 *
 * This should include the current process, and all child threads.
 *
 * @param status_code    The exit code to return to the system.
 */
void exit_group(int status_code);

/**
 * `open` opens the file at the given path.
 *
 * @param path  The path to the file to be opened.
 * @return      A file descriptor to the open file.
 */
int open(const char* pathname);

/**
 * `close` closes a file indicated by a file descriptor.
 *
 * @param fd    The fild descriptor to close.
 */
void close(size_t fd);

/**
 * `read` attempts to bytes from a file.
 *
 * @param fd    File descriptor to read from.
 * @param buf   Buffer to copy bytes to.
 * @param count Number of bytes to copy.
 * @return      The number of bytes actually read, or a negative error code.
 */
ssize_t read(int fd, void* buf, size_t count);

/**
 * `seek` moves the file pointer to a specified index from the start of a file.
 *
 * @param fd        File descriptor to seek in.
 * @param offset    Offset to seek to.
 */
void seek(int fd, unsigned int offset);

/* mmap related constants. */
#define PROT_READ 0x1
#define PROT_WRITE 0x2
#define PROT_EXEC 0x4
#define MAP_PRIVATE 0x2
#define MAP_ANON 0x20
#define MAP_FIXED 0x10

/**
 * `mmap` maps memory segments.
 * 
 * @note The semantics of mmap match the Linux mmap implimentation.
 * @param addr      Start address of the mapping in memory.
 * @param length    Length of the mapping in memory.
 * @param prot      Protection mode flags.
 * @param flags     Indicates the visiblity of the mapping.
 * @param fd        File descriptor for a file backed mapping.
 * @param offset    Offset of the file backing contents.
 * @return          The address of the new mapping.
 */
void* mmap(void* addr,
    unsigned long length,
    unsigned long prot,
    unsigned long flags,
    unsigned long fd,
    unsigned long offset);

#endif
