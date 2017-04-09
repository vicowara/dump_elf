#include <stdio.h>
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <elf.h>

#define DUMP(x) do {printf("  " #x " = %u(0x%x)\n", (uint32_t)x, (uint32_t)x);} while(0);

void dump_ehdr(Elf64_Ehdr *ehdr){
    DUMP(ehdr->e_type);
    DUMP(ehdr->e_machine);
    DUMP(ehdr->e_version);
    DUMP(ehdr->e_entry);
    DUMP(ehdr->e_phoff);
    DUMP(ehdr->e_shoff);
    DUMP(ehdr->e_flags);
    DUMP(ehdr->e_ehsize);
    DUMP(ehdr->e_phentsize);
    DUMP(ehdr->e_phnum);
    DUMP(ehdr->e_shentsize);
    DUMP(ehdr->e_shnum);
    DUMP(ehdr->e_shstrndx);
    printf("\n");
}

void dump_phdr(Elf64_Phdr *phdr, int e_phnum){
    int i;
    for (i = 0; i < e_phnum; i++, phdr++) {
        DUMP(phdr->p_type);
        DUMP(phdr->p_flags);
        DUMP(phdr->p_offset);
        DUMP(phdr->p_vaddr);
        DUMP(phdr->p_paddr);
        DUMP(phdr->p_filesz);
        DUMP(phdr->p_memsz);
        DUMP(phdr->p_align);
        printf("\n");
    }
    printf("\n");
}

void dump_shdr(Elf64_Shdr *shdr, int e_shnum){
    int i;
    for (i = 0; i < e_shnum; i++, shdr++) {
        DUMP(shdr->sh_name);
        DUMP(shdr->sh_type);
        DUMP(shdr->sh_flags);
        DUMP(shdr->sh_addr);
        DUMP(shdr->sh_offset);
        DUMP(shdr->sh_size);
        DUMP(shdr->sh_link);
        DUMP(shdr->sh_info);
        DUMP(shdr->sh_addralign);
        DUMP(shdr->sh_entsize);
        printf("\n");
    }
    printf("\n");
}

int main(void){
    Elf64_Ehdr *ehdr;
    Elf64_Phdr *phdr;
    Elf64_Shdr *shdr;
    int fd;
    FILE *fp;
    struct stat stbuf;

    fd = open("hello", O_RDONLY);
    assert(fd);
    fp = fdopen(fd, "rb");
    assert(fp);

    fstat(fd, &stbuf);
    unsigned char buf[stbuf.st_size];
    assert(fread(buf, 1, sizeof(buf), fp) == (unsigned long)stbuf.st_size);
    fclose(fp);

    printf("Elf file header(equivalent as readelf -h)\n");
    ehdr = (Elf64_Ehdr *)buf;
    dump_ehdr(ehdr);

    printf("Program header(equivalent as readelf -l)\n");
    phdr = (Elf64_Phdr *)(&buf[ehdr->e_phoff]);
    dump_phdr(phdr, ehdr->e_phnum);

    printf("Section header(equivalent as readelf -s)\n");
    shdr = (Elf64_Shdr *)(&buf[ehdr->e_shoff]);
    dump_shdr(shdr, ehdr->e_shnum);

    return 0;
}
