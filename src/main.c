#include "ghost/string.h"
#include "ghost/system.h"

#define TEST_EXIT_CODE 69

void __start(void)
{
    puts("Test print\n");
    exit_group(TEST_EXIT_CODE);
}
