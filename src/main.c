#include "ghost/asm/linux.h"

void __start(void)
{
    write(1, "test print\0", 30);
    exit_group(15);
}
