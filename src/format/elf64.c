/**
 * @file src/ghost/format/elf64.c
 *
 * `src/ghost/format/elf64.c` defines functions for handling ELF64 format
 * binaries.
 *
 * @author H Paterson, 2020.
 * @copyright BSL-1.0.
 */

#include "ghost/system_calls.h"
#include "ghost/types.h"
#include "printf.h"

void load_static(size_t fd)
{
    printf("Load static %d\n", fd);
}

void load_static_name(const char* const name)
{
    int fd = open(name);
    load_static(fd);
    close(fd);
}
