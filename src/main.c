#include "ghost/asm/linux.h"

int __start(void)
{
    write(1, "test print\0", 30);
    exit_group(15);
}
