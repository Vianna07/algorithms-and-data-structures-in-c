# Makefile — Capítulo 8: pilhas e filas (dois backings cada).
# Padrão C17. Use `make CC=clang` para compilar com clang.

CC     ?= gcc
CSTD   := c17
CFLAGS := -std=$(CSTD) -Wall -Wextra -Wpedantic -O2
BIN    := demo
OBJ    := stacks.o queues.o main.o

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

stacks.o: stacks.c stacks.h
	$(CC) $(CFLAGS) -c $< -o $@

queues.o: queues.c queues.h
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c stacks.h queues.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(BIN)
	./$(BIN)

format:
	clang-format -i stacks.h stacks.c queues.h queues.c main.c

clean:
	rm -f $(BIN) $(OBJ)

.PHONY: run format clean
