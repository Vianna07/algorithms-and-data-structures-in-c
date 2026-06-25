# Makefile — Capítulo 10: min-heap / fila de prioridade.
# Padrão C17. Use `make CC=clang` para compilar com clang.

CC     ?= gcc
CSTD   := c17
CFLAGS := -std=$(CSTD) -Wall -Wextra -Wpedantic -O2
BIN    := demo
OBJ    := heap.o main.o

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c heap.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(BIN)
	./$(BIN)

format:
	clang-format -i heap.h heap.c main.c

clean:
	rm -f $(BIN) $(OBJ)

.PHONY: run format clean
