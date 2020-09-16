/**
 * @file include/asm/arch.h
 *
 * `include/asm/arch.h` declares host CPU architecture related functions.
 *
 * @author H Paterson, 2020.
 * @copyright BSL-1.0.
 */

/**
 * Get the stack pointer of the program *before* `get_stack_pointer` was
 * called.
 *
 * `get_stack_pointer` is intended for getting the stack frame provided to the
 * loader by the syster - often containing information passed from the kernel.
 *
 * @note Under most ABIs, calling `get_stack_pointer` would change the stack
 * pointer into the function's own frame, so these implementations will return
 * the base pointer - which is the caller's stack pointer.
 */
extern intptr_t get_stack_pointer();
