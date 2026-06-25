# Makefile — Capítulo 5: array dinâmico.
# Padrão C17. Use `make CC=clang` para compilar com clang.

CC     ?= gcc
CSTD   := c17
CFLAGS := -std=$(CSTD) -Wall -Wextra -Wpedantic -O2
BIN    := demo
OBJ    := dynamic_array.o main.o

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c dynamic_array.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(BIN)
	./$(BIN)

format:
	clang-format -i dynamic_array.h dynamic_array.c main.c

clean:
	rm -f $(BIN) $(OBJ)

.PHONY: run format clean
