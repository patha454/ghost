#include "ghost/asm/linux.h"

#define TEST_WRITE_LEN 11
#define TEST_EXIT_CODE 69

void __start(void)
{
    write(1, "test print\n", TEST_WRITE_LEN);
    exit_group(TEST_EXIT_CODE);
}
