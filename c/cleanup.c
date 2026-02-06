//  gcc -g -O2 -Wall -std=c2x file.c -o file
#include <stdio.h>
#include <stdlib.h>

static void cleanup_free(void * p) {
    free(*(void **)p);
}

void leak_check_test() {
    __attribute__((cleanup(cleanup_free))) char * c = malloc(100);

    if (c == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    printf("Data processed\n");
}

int main() {
    leak_check_test();
    return 0;
}

// valgrind --tool=memcheck ./cleanup
// ==550226== Memcheck, a memory error detector
// ==550226== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
// ==550226== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
// ==550226== Command: ./cleanup
// ==550226==
// Data processed
// ==550226==
// ==550226== HEAP SUMMARY:
// ==550226==     in use at exit: 0 bytes in 0 blocks
// ==550226==   total heap usage: 2 allocs, 2 frees, 1,124 bytes allocated
// ==550226==
// ==550226== All heap blocks were freed -- no leaks are possible
// ==550226==
// ==550226== For lists of detected and suppressed errors, rerun with: -s
// ==550226== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
