#include "ghost/string.h"
#include "ghost/system.h"
#pragma message "Using external libelf-dev headers."
#include "elf.h"

#define TEST_EXIT_CODE 69

void __start(void)
{
    puts("Test print\n");
    exit_group(TEST_EXIT_CODE);
}
