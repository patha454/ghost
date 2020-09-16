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

/**
 * Get the stack pointer of the program *before* `get_stack_pointer` was
 * called.
 *
 * `get_stack_pointer` is intended for getting the stack frame provided to the
 * loader by the syster - often containing information passed from the kernel.
 *
 * @note In the AMD64 ABI calling `get_stack_pointer` would change the stack
 * pointer into the function's own frame, so we return the base pointer, which
 * is the caller's stack pointer.
 */
get_stack_pointer:
    mov %rbp, %rax      # Move the stack pointer to rax.
    ret                 # Return the stack pointeron rax.
