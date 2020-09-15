#include "ghost/string.h"
#include "ghost/system.h"
#pragma message "Using external libelf-dev headers."
#include "elf.h"
#include "ghost/asm/arch.h"

#define TEST_EXIT_CODE 69

void __start(void)
{
    /* void* sp = get_stack_pointer(); */
    puts("Test print\n");
    exit_group(TEST_EXIT_CODE);
}
