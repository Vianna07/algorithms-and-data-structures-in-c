# Makefile — Capítulo 4: compilação separada de um projeto modular.
# Cada .c vira um .o independente; o link junta os .o num executável.

CC     ?= gcc
CFLAGS := -std=c17 -Wall -Wextra -Wpedantic -O2

# 1) Link: junta os objetos no executável final.
demo: account.o main.o
	$(CC) $(CFLAGS) -o demo account.o main.o

# 2) Compila cada .c em um .o, separadamente. Recompila se o .c OU o .h mudar.
account.o: account.c account.h
	$(CC) $(CFLAGS) -c account.c

main.o: main.c account.h
	$(CC) $(CFLAGS) -c main.c

run: demo
	./demo

format:
	clang-format -i account.h account.c main.c

clean:
	rm -f demo account.o main.o

.PHONY: run format clean
