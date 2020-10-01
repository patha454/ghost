/**
 * @file include/ghost/format/elf64.h
 *
 * `include/ghost/format/elf64.h` declares handeling for ELF64 binaries.
 *
 * @author H Paterson, 2020.
 * @copyright BSL-1.0.
 */

#ifndef GHOST_FORMAT_ELF64_H_
#define GHOST_FORMAT_ELF64_H_

#include <stddef.h>

/**
 * Load a statically linked file into memory.
 *
 * @param fd    File descriptor for the target binary.
 * @return      0 on failure, 1 on success.
 */
int load_static(size_t fd);

/**
 * Load a statically linked file into memory.
 *
 * @param name  File name of the target binary.
 * @return      0 oon failure, 1 on success.
 */
int load_static_name(const char* name);

#endif
