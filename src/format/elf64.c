/**
 * @file src/ghost/format/elf64.c
 *
 * `src/ghost/format/elf64.c` defines functions for handling ELF64 format
 * binaries.
 *
 * @author H Paterson, 2020.
 * @copyright BSL-1.0.
 */

#include "ghost/system_calls.h"
#include "ghost/types.h"
#include "printf.h"
#pragma message "Using external libelf-dev headers"
#include "elf.h"

/**
 * Check an ELF header corosponds to a valid ELF64 X64 static executable.
 *
 * @param elf_header    Header to test.
 * @return              0 if invalid, 1 if valid.
 */
int validate_static_elf64_exec(const Elf64_Ehdr* const elf_header)
{
    if (elf_header->e_ident[EI_MAG0] != ELFMAG0 || elf_header->e_ident[EI_MAG1] != ELFMAG1 || elf_header->e_ident[EI_MAG2] != ELFMAG2 || elf_header->e_ident[EI_MAG3] != ELFMAG3) {
        printf("Ghost: Error: Target not ELF.\n");
        return 0;
    }
    if (elf_header->e_ehsize != sizeof(Elf64_Ehdr)) {
        printf("Ghost: Error: ELF heaader size unexpected? New ELF version?\n");
        return 0;
    }
    if (elf_header->e_phentsize != sizeof(Elf64_Phdr)) {
        printf("GHost: Error: ELF64 program header size unexpected.\n");
        return 0;
    }
    if (elf_header->e_ident[EI_CLASS] != ELFCLASS64) {
        printf("Ghost: Error: Target not ELF64.\n");
        return 0;
    }
    if (elf_header->e_type != ET_EXEC) {
        printf("Ghost: Target not ELF static executable.\n");
        return 0;
    }
    if (elf_header->e_machine != EM_X86_64) {
        printf("Ghost: Target not x86_64 binary.\n");
        return 0;
    }
    return 1;
}

/**
 * Attemt to load ELF64 program segments into memory.
 *
 * @param elf_heaer     Elf header to refer to.
 * @param fd            ELF file descriptor.
 * @return  0 on failure, 1 on success.
 */
int load_segments(const Elf64_Ehdr* const elf_header, size_t fd)
{
    size_t segment_n = 0;
    Elf64_Phdr p_header;
    if (elf_header->e_phnum == 0) {
        printf("Ghost: Error: No program headers.\n");
        return 0;
    }
    while (segment_n < elf_header->e_phnum) {
        seek(fd, elf_header->e_phoff + segment_n * sizeof(Elf64_Phdr));
        read(fd, &p_header, sizeof(p_header));
        printf("\nHeader type: %x\n", p_header.p_type);
        printf("Header flags: 0x%x\n", p_header.p_flags);
        printf("Header offset: %lu\n", p_header.p_offset);
        printf("Header vaddr: 0x%lx\n", p_header.p_offset);
        printf("Header vaddr 0x%lx\n", p_header.p_vaddr);
        printf("Header paddr: 0x%lx\n", p_header.p_offset);
        printf("Header memsize: 0x%lu\n", p_header.p_memsz);
        printf("Header filesize: 0x%lx\n", p_header.p_filesz);
        printf("Header align: 0x%lx\n", p_header.p_align);
        segment_n++;
    }
    seek(fd, elf_header->e_phoff);
    return 1;
}

int load_static(size_t fd)
{
    int rv;
    Elf64_Ehdr elf_header;
    rv = read(fd, &elf_header, sizeof(elf_header));
    if (rv != sizeof(elf_header)) {
        printf("Ghost: Error: Could not read in ELF header.\n");
        return 0;
    }
    if (!validate_static_elf64_exec(&elf_header)) {
        printf("Ghost: Error: ELF header invalid.\n");
        return 0;
    }
    if (!load_segments(&elf_header, fd)) {
        printf("Ghost: Error: Could not load program segments\n");
        return 0;
    }

    return 1;
}

int load_static_name(const char* const name)
{
    int status = 0;
    int fd = open(name);
    if (fd <= 0) {
        printf("Ghost: Error: Could not open ELF target.\n");
        return 0;
    }
    status = load_static(fd);
    close(fd);
    return status;
}
