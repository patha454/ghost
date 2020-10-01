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

.hidden sys_open
.global sys_open

sys_open:
    push %rbp
    mov %rsp, %rbp
    mov $2, %rax            # Syscall #2 (open)
    syscall
    mov %rbp, %rsp
    pop %rbp
    ret

.hidden sys_close
.global sys_close

sys_close:
    push %rbp
    mov %rsp, %rbp
    mov $3, %rax            # Syscall #3 (close)
    syscall
    mov %rbp, %rsp
    pop %rbp
    ret

.hidden sys_read
.global sys_read

sys_read:
    push %rbp
    mov %rsp, %rbp
    mov $0, %rax            # Syscall #0 (read)
    syscall
    mov %rbp, %rsp
    pop %rbp
    ret

.hidden sys_lseek
.global sys_lseek

sys_lseek:
    push %rbp
    mov %rsp, %rbp
    mov $8, %rax            # Syscall #8 (lseek)
    syscall
    mov %rbp, %rsp
    pop %rbp
    ret