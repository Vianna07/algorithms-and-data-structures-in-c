# Makefile — Capítulo 6: listas encadeadas.
# Padrão C17. Use `make CC=clang` para compilar com clang.

CC     ?= gcc
CSTD   := c17
CFLAGS := -std=$(CSTD) -Wall -Wextra -Wpedantic -O2
BIN    := demo
OBJ    := singly_list.o doubly_list.o main.o

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c singly_list.h doubly_list.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(BIN)
	./$(BIN)

format:
	clang-format -i singly_list.h singly_list.c doubly_list.h doubly_list.c main.c

clean:
	rm -f $(BIN) $(OBJ)

.PHONY: run format clean
