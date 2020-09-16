#include "ghost/string.h"
#include "ghost/system.h"
#pragma message "Using external libelf-dev headers."
#include "elf.h"
#include "ghost/asm/arch.h"
#pragma message "Using external printf library"
#include "printf.h"

#define EXIT_SUCCESS 0
#define EXIT_STACK_CHECK_FAILED 255

/* 
 * Horrible code, but sufficent for now to prove I am running where I think
 * I am, and getting passed the information I should be as interpreter.
 */
int print_elf_auxv_t(Elf64_auxv_t auxv)
{
    switch (auxv.a_type) {
    case AT_NULL:
        printf("AT_NULL: 0x%lx [%p]\n", auxv.a_un.a_val, &auxv);
        return 0;
        break;
    case AT_IGNORE:
        printf("AT_IGNORE: ");
        break;
    case AT_EXECFD:
        printf("AT_EXECFD: ");
        break;
    case AT_PHENT:
        printf("AT_PHENT: ");
        break;
    case AT_PHNUM:
        printf("AT_PHNUM: ");
        break;
    case AT_PAGESZ:
        printf("AT_PGSIZE: ");
        break;
    case AT_BASE:
        printf("AT_BASE: ");
        break;
    case AT_FLAGS:
        printf("AT_FLAGS: ");
        break;
    case AT_ENTRY:
        printf("AT_ENTRY: ");
        break;
    case AT_NOTELF:
        printf("AT_NOTELF: ");
        break;
    case AT_UID:
        printf("AT_UID: ");
        break;
    case AT_EUID:
        printf("AT_EUID: ");
        break;
    case AT_GID:
        printf("AT_GID: ");
        break;
    case AT_EGID:
        printf("AT_EGUID: ");
        break;
    case AT_CLKTCK:
        printf("AT_CLKTCK: ");
        break;
    case AT_PLATFORM:
        printf("AT_PLATFORM: ");
        break;
    case AT_DCACHEBSIZE:
        printf("AT_DCACHEBSIZE: ");
        break;
    case AT_UCACHEBSIZE:
        printf("AT_UCACHEBSIZE: ");
        break;
    default:
        printf("Unknown AUXV type %lu: ", auxv.a_type);
    }
    printf("0x%lx [%p]\n", auxv.a_un.a_val, &auxv);
    return 1;
}

void print_elf_auxvs(intptr_t auxv)
{
    int i = 0;
    intptr_t auxv_itr = auxv;
    Elf64_auxv_t* auxv_e = NULL;
    printf("ELF Auxiliary Vectors:\n");
    printf("argc: %zu [0x%p]\n", *(size_t*)auxv_itr, (size_t*)auxv_itr);
    auxv_itr += sizeof(size_t);
    while (*(char**)auxv_itr) {
        printf("argv[%d]: %s [0x%p]\n", i++, *(char**)auxv_itr, (char**)auxv_itr);
        auxv_itr += sizeof(char**);
    }
    /* skip NULL seperator. */
    auxv_itr += sizeof(char**);
    i = 0;
    while (*(char**)auxv_itr) {
        printf("envv[%d]: %s [0x%p]\n", i++, *(char**)auxv_itr, (char**)auxv_itr);
        auxv_itr += sizeof(char**);
    }
    auxv_e = (Elf64_auxv_t*)(auxv_itr + sizeof(char**));
    while (print_elf_auxv_t(*auxv_e)) {
        auxv_e += 1;
    }
}

void _main(intptr_t sp)
{
    print_elf_auxvs(sp);
    exit_group(EXIT_SUCCESS);
}

void __start(void)
{
    intptr_t sp = get_stack_pointer();
    /* The SP points the the 'empty' slot above the end of the stack, in the
     * x64 ABI. What about others? Correct the SP to point to the auxiliary
     * vectors, anyway. */
    sp += sizeof(intptr_t);
    _main(sp);
}

/**
 * Stub for the compiler to call when stack smashing protection checks fail.
 */
void __stack_chk_fail()
{
    printf("Ghost: Error: Stack check failed.\n");
    exit_group(EXIT_STACK_CHECK_FAILED);
}
