# Makefile — Capítulo 9: árvore binária de busca.
# Padrão C17. Use `make CC=clang` para compilar com clang.

CC     ?= gcc
CSTD   := c17
CFLAGS := -std=$(CSTD) -Wall -Wextra -Wpedantic -O2
BIN    := demo
OBJ    := bst.o main.o

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c bst.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(BIN)
	./$(BIN)

format:
	clang-format -i bst.h bst.c main.c

clean:
	rm -f $(BIN) $(OBJ)

.PHONY: run format clean
