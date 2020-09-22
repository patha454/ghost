/**
 * @file asm/x86_64/linux.s
 *
 * `asm/x86_64/linux.s` defines relevant system calls for an x86-64 Linux host.
 *
 * @see `include/asm/linux.h`
 *
 * @author H Paterson, 2020.
 * @copyright BSL-1.0.
 */

.text


.func sys_write
.hidden sys_write
.global sys_write

sys_write:
    push %rbp               # Push base pointer to stack.
    mov %rsp, %rbp          # Set old stack pointer as base pointer.
    mov $1, %rax            # Syscall #1 (write.)
    syscall                 # fs, buf, len should already be in %rdi, %rsi, %rdx
                            # according to the SysV function call ABI.
    mov %rbp, %rsp          # Restore original base pointer
    pop %rbp
    ret                     # Return value should already be in %rax after
                            # syscall.       

.endfunc

.func sys_exit_group
.hidden sys_exit_group
.global sys_exit_group

sys_exit_group:
    push %rbp               # Push base pointer to stack.
    mov %rsp, %rbp          # Set base pointer to old stack pointer.
    mov $231, %rax          # Syscall #231 (exit_group.)
    syscall                 # exit_code should already be on %rdi.
    mov %rbp, %rsp          # Should not return from syscall. Just in case...
    pop %rbp
    ret         

.endfunc
