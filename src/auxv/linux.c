/**
 * @file src/auxv/linux.c
 * 
 * `src/auxv/linux.c` impliments parsing for Linux ELF Auxiliary vectors.
 *
 * @see `include/ghost/auxv.h`
 *
 * @author H Paterson, 2020.
 * @copyright BSL-1.0.
 */

#include "ghost/auxv.h"
#include "ghost/types.h"
#include "printf.h"
#pragma message "Using external libelf-dev headers."
#include "elf.h"

int store_auxv_entry(struct auxiliary_vector* const auxv, Elf64_auxv_t entry)
{
    switch (entry.a_type) {
    case AT_NULL:
        /* Alert the caller to stop processing entries. */
        return 0;
        break;
    case AT_EXECFD:
        auxv->exec_fd = entry.a_un.a_val;
        break;
    case AT_PHDR:
        auxv->program_headers = entry.a_un.a_val;
        break;
    case AT_PHENT:
        auxv->program_header_size = entry.a_un.a_val;
        break;
    case AT_PHNUM:
        auxv->program_header_num = entry.a_un.a_val;
        break;
    case AT_PAGESZ:
        auxv->page_size = entry.a_un.a_val;
        break;
    case AT_BASE:
        auxv->ghost_base = entry.a_un.a_val;
        break;
    case AT_FLAGS:
        auxv->flags = entry.a_un.a_val;
        break;
    case AT_ENTRY:
        auxv->entry_point = entry.a_un.a_val;
        break;
    case AT_NOTELF:
        auxv->not_elf = entry.a_un.a_val;
        break;
    case AT_UID:
        auxv->uid = entry.a_un.a_val;
        break;
    case AT_EUID:
        auxv->euid = entry.a_un.a_val;
        break;
    case AT_GID:
        auxv->gid = entry.a_un.a_val;
        break;
    case AT_EGID:
        auxv->egid = entry.a_un.a_val;
        break;
    case AT_PLATFORM:
        auxv->platform = (char*)entry.a_un.a_val;
        break;
    case AT_CLKTCK:
        auxv->clock_tick = entry.a_un.a_val;
        break;
    default:
        /* Skip over values we're not interested in. */
        break;
    }
    return 1;
}

void parse_auxiliary_vector(struct auxiliary_vector* const auxv,
    intptr_t auxv_base)
{
    intptr_t ptr = auxv_base;
    auxv->argc = *(size_t*)ptr;
    ptr += sizeof(auxv->argc);
    auxv->argv = (char**)ptr;
    /* The end of the arguments are makred with NULL, which we must skip over. */
    ptr += (auxv->argc + 1) * sizeof(*auxv->argv);
    auxv->envv = (char**)ptr;
    auxv->envc = 0;
    while (auxv->envv[auxv->envc]) {
        auxv->envc++;
    }
    /* The end of the env. vars are makred with NULL, which we must skip over. */
    ptr += (auxv->envc + 1) * sizeof(*auxv->envv);
    while (store_auxv_entry(auxv, *(Elf64_auxv_t*)ptr)) {
        ptr += sizeof(Elf64_auxv_t);
    }
}

void print_auxiliary_vector(const struct auxiliary_vector* const auxv)
{
    size_t i = 0;
    printf("--- Auxiliary Vector ---\n");
    printf("argc: %zu\n", auxv->argc);
    for (i = 0; i < auxv->argc; i++) {
        printf("argv[%zu]: %s\n", i, auxv->argv[i]);
    }
    printf("argc: %zu\n", auxv->envc);
    for (i = 0; i < auxv->envc; i++) {
        printf("envv[%zu]: %s\n", i, auxv->envv[i]);
    }
    printf("Target headers: 0x%lx\n", auxv->program_headers);
    printf("Target header size: 0d%zu\n", auxv->program_header_size);
    printf("Target header count: 0d%zu\n", auxv->program_header_num);
    printf("Host page size: %zu\n", auxv->page_size);
    printf("Interpreter base: 0x%lx\n", auxv->ghost_base);
    printf("Flags: 0x%zx\n", auxv->flags);
    printf("Target entry point: 0x%lx\n", auxv->entry_point);
    printf("UID: %zu\n", auxv->uid);
    printf("EUID: %zu\n", auxv->euid);
    printf("GID: %zu\n", auxv->gid);
    printf("EGID: %zu\n", auxv->egid);
    printf("Platform: %s\n", auxv->platform);
    printf("Clock tick: %zu\n", auxv->clock_tick);
}
