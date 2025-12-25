// Sample hello world ELF

void _start() {
    const char msg[] = "Hello from loaded ELF!\n";
    asm volatile(
        "mov $1, %%rax\n"
        "mov $1, %%rdi\n"
        "lea %0, %%rsi\n"
        "mov %1, %%rdx\n"
        "syscall\n"
        "mov $60, %%rax\n"
        "xor %%rdi, %%rdi\n"
        "syscall\n"
        :
        : "m"(msg), "r"(sizeof(msg)-1)
        : "rax", "rdi", "rsi", "rdx"
    );
}
