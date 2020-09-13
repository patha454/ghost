#include "asm/linux.h"

int __start(void)
{
    exit_group(15);
}
