#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#define PAGE_SIZE 4096
#define PAGE_ALIGN_DOWN(x) ((x) & ~(PAGE_SIZE - 1))
#define PAGE_ALIGN_UP(x)   (((x) + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1))

static inline int verify(const Elf64_Ehdr * hdr) {
    printf("\n******* ELF info *******\n");
    if ((hdr->e_ident[0] && ELFMAG0) && (hdr->e_ident[1] && ELFMAG1) &&
        (hdr->e_ident[2] && ELFMAG2) && (hdr->e_ident[3] && ELFMAG3))
        printf("Valid magic number\n");
    else {
        printf("Invalid magic number\n ");
        // return -1;
    }

    if (hdr->e_ident[4] && ELFCLASSNONE) {
        printf("Invalid ELF class\n");
        return -1;
    }

    char * elfclass = (hdr->e_ident[EI_CLASS] == ELFCLASS32) ? "32-bit" : "64-bit";
    if (!elfclass)
        printf("%s architecture \n", elfclass);
    else
        return -1;


    if ((hdr->e_ident[EI_DATA] != ELFDATA2LSB)  || (hdr->e_ident[EI_DATA] != ELFDATA2MSB)) {
        printf("Unknown DATA encoding scheme\n");
        return -1;
    }

    return 0;
}

int main(int argc, char * argv[]) {
    if (argc <  2) {
        fprintf(stderr, "usage: elf_loader $ELF_FILE_PATH\n");
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "*** Failed to open ELF file : %s ***\n", strerror(errno));
        exit(EXIT_FAILURE);
    }


    Elf64_Ehdr ehdr;
    size_t bytes_read = read(fd, &ehdr, sizeof(Elf64_Ehdr));
    if (bytes_read <= 0)  {
        fprintf(stderr, "Unknown file format supports only ELF64\n");
        exit(EXIT_FAILURE);
    }

    if (verify(&ehdr) == 0)
        printf("Verified the ELF inforation\n");


    if (lseek(fd, ehdr.e_phoff, SEEK_SET) < 0) {
        perror("lseek phdr");
        return 1;
    }

    Elf64_Phdr *phdrs = calloc(ehdr.e_phnum, sizeof(Elf64_Phdr));
    if (!phdrs) {
        perror("calloc");
        return 1;
    }

    if (read(fd, phdrs, ehdr.e_phnum * sizeof(Elf64_Phdr)) < 0) {
        perror("read phdrs");
        return 1;
    }

    for (int i = 0; i < ehdr.e_phnum; i++) {
        Elf64_Phdr *ph = &phdrs[i];
        if (ph->p_type != PT_LOAD)
            continue;

        uintptr_t seg_start = PAGE_ALIGN_DOWN(ph->p_vaddr);
        uintptr_t seg_end   = PAGE_ALIGN_UP(ph->p_vaddr + ph->p_memsz);
        size_t seg_size     = seg_end - seg_start;

        void *addr = mmap(
            (void *)seg_start,
            seg_size,
            PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED,
            -1,
            0
            );

        if (addr == MAP_FAILED) {
            perror("mmap");
            return 1;
        }

        if (lseek(fd, ph->p_offset, SEEK_SET) < 0) {
            perror("lseek segment");
            return 1;
        }

        if (read(fd, (void *)ph->p_vaddr, ph->p_filesz) != (ssize_t)ph->p_filesz) {
            perror("read segment");
            return 1;
        }

        memset((void *)(ph->p_vaddr + ph->p_filesz), 0, ph->p_memsz - ph->p_filesz);

        int prot = 0;
        if (ph->p_flags & PF_R) prot |= PROT_READ;
        if (ph->p_flags & PF_W) prot |= PROT_WRITE;
        if (ph->p_flags & PF_X) prot |= PROT_EXEC;

        if (mprotect((void *)seg_start, seg_size, prot) != 0) {
            perror("mprotect");
            return 1;
        }
    }

    free(phdrs);
    close(fd);

    printf("Jumping to entry point: %p\n", (void *)ehdr.e_entry);
    void (*entry)(void) = (void (*)(void))ehdr.e_entry;
    entry();

    return 0;
}
