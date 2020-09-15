#include "ghost/string.h"

#define TEST_WRITE_LEN 11
#define TEST_EXIT_CODE 69

void __start(void)
{
    puts("Test print\n");
    exit_group(TEST_EXIT_CODE);
}
