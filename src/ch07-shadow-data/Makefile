# Makefile — Capítulo 7: Shadow Data (void*) e contêiner por macro.
# Padrão C17. Use `make CC=clang` para compilar com clang.

CC     ?= gcc
CSTD   := c17
CFLAGS := -std=$(CSTD) -Wall -Wextra -Wpedantic -O2

all: demo macro_demo

demo: generic_list.o main.o
	$(CC) $(CFLAGS) -o $@ $^

macro_demo: macro_demo.o
	$(CC) $(CFLAGS) -o $@ $^

generic_list.o: generic_list.c generic_list.h
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c generic_list.h
	$(CC) $(CFLAGS) -c $< -o $@

macro_demo.o: macro_demo.c generic_macro.h
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./demo && ./macro_demo

format:
	clang-format -i generic_list.h generic_list.c main.c generic_macro.h macro_demo.c

clean:
	rm -f demo macro_demo *.o

.PHONY: all run format clean
