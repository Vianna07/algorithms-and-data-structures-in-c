# Makefile — Capítulo 2: gerenciamento de memória.
# Padrão C17. Use `make CC=clang` para compilar com clang.

CC     ?= gcc
CFLAGS := -std=c17 -Wall -Wextra -Wpedantic -O2
BIN    := demo

$(BIN): memory.c
	$(CC) $(CFLAGS) -o $@ memory.c

run: $(BIN)
	./$(BIN)

# Verifica que não há vazamentos nem acessos inválidos.
valgrind: $(BIN)
	valgrind --leak-check=full --error-exitcode=1 ./$(BIN)

format:
	clang-format -i memory.c

clean:
	rm -f $(BIN)

.PHONY: run valgrind format clean
