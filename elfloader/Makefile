CC=gcc
CFLAGS= -g -O2 -Wall

all: elf_loader hello

elf_loader:
	$(CC) $(CFLAGS) loader.c -o elf_loader

hello:
	$(CC) -nostdlib -static test/hello.c -o hello

clean:
	rm elf_loader hello

PHONY: clean

