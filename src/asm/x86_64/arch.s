/**
 * @file asm/x86_64/arch.s
 *
 * `asm/x86_64/arch.s` defines architecture related subroutines for x86-64
 * hosts.
 *
 * @see `include/asm/arch.h
 *
 * @author H Paterson, 2020.
 * @copyright BSL-1.0.
 */

.text

.global get_stack_pointer

get_stack_pointer:
    mov %rsp, %rax      # Move the stack pointer to rax.
    ret                 # Return the stack pointeron rax.
