/**
 * @file include/ghost/auxv.h
 * 
 * `include/ghost/auxv.h` defines an auxiliary vector structure.
 * 
 * The auxiliary vector contains information passed from the kernel to the
 * loader about the target program and host system.
 *
 * @note `auxv.h` is modeled on the Linux-ELF-glibc auxiliary vector. Similiar
 * information should be available on other platforms. The user must assume
 * not every field in `struct auxiliary_vector` is populated, and test for NULL
 * or 0 values.
 *
 * @author H Paterson, 2020.
 * @copyright BSL-1.0.
 */

#ifndef GHOST_AUXV_H_
#define GHOST_AUXV_H_

#include "ghost/types.h"
#include <stdint.h>

/**
 *  * The auxiliary vector contains information passed from the kernel to the
 * loader about the target program and host system.
 *
 * @note `auxv.h` is modeled on the Linux-ELF-glibc auxiliary vector. Similiar
 * information should be available on other platforms. The user must assume
 * not every field in `struct auxiliary_vector` is populated, and test for NULL
 * or 0 values.
 */
struct auxiliary_vector {
    /** Number of command line arguments. */
    size_t argc;

    /** Location of command line argument pointers. */
    intptr_t argv;

    /** Number of environment variables. */
    size_t envc;

    /** Location of environment variable pointers. */
    intptr_t envv;

    /** File descriptor of the target program. */
    size_t exec_fd;

    /** Program headers of the target program. */
    intptr_t program_headers;

    /** Size of a single target program header. */
    size_t program_header_size;

    /** Number of target program headers. */
    size_t program_header_num;

    /** Host system page size. */
    size_t page_size;

    /** Base address of the interpreter. */
    intptr_t ghost_base;

    /** Mysterious flags. */
    size_t flags;

    /** Entry point of the target program. */
    intptr_t entry_point;

    /** The target program is not an elf. */
    size_t not_elf;

    /** Real user ID. */
    size_t uid;

    /** Effective user ID. */
    size_t euid;

    /** Real group ID. */
    size_t gid;

    /** Effective group ID. */
    size_t egid;

    /** String identifying CPU. */
    intptr_t platform;

    /** Frequency at which time incriments. */
    size_t clock_tick;
};

#endif
