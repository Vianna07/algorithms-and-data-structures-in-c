# Makefile — Capítulo 3: structs e uniões.
# Padrão C17. Use `make CC=clang` para compilar com clang.

CC     ?= gcc
CFLAGS := -std=c17 -Wall -Wextra -Wpedantic -O2
BIN    := demo

$(BIN): structs.c
	$(CC) $(CFLAGS) -o $@ structs.c

run: $(BIN)
	./$(BIN)

format:
	clang-format -i structs.c

clean:
	rm -f $(BIN)

.PHONY: run format clean
