# Makefile — Capítulo 1: ponteiros.
# Padrão C17. Use `make CC=clang` para compilar com clang.

CC     ?= gcc
CFLAGS := -std=c17 -Wall -Wextra -Wpedantic -O2
BIN    := demo

$(BIN): pointers.c
	$(CC) $(CFLAGS) -o $@ pointers.c

run: $(BIN)
	./$(BIN)

format:
	clang-format -i pointers.c

clean:
	rm -f $(BIN)

.PHONY: run format clean
