#include "ghost/string.h"
#include "ghost/system_calls.h"
#pragma message "Using external libelf-dev headers."
#include "elf.h"
#include "ghost/asm/arch.h"
#pragma message "Using external printf library"
#include "ghost/auxv.h"
#include "printf.h"
#include "ghost/format/elf64.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

void __start(void);

void _main(intptr_t sp)
{
    struct auxiliary_vector auxv;
    parse_auxiliary_vector(&auxv, sp);
    print_auxiliary_vector(&auxv);
    if (auxv.ghost_base != 0)
    {
        printf("Ghost: Ghost does not support being invoked implicitly from the .interp segment.\n");
        exit_group(EXIT_FAILURE);

    } else if (auxv.argc < 2)
    {
        printf("Ghost: A target program must be supplied on the command line.\n");
        exit_group(EXIT_FAILURE);
    }
    load_static_name(auxv.argv[0]);
    printf("Start: 0x%p\n", &__start);
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
