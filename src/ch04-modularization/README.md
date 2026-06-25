# Capítulo 4 — Modularização (código-fonte)

Um módulo C real, separado em **interface** (`.h`) e **implementação** (`.c`),
compilado em partes e ligado num executável.

| Item | Valor |
|---|---|
| Padrão da linguagem | **C17** (ISO/IEC 9899:2018) |
| Compiladores testados | gcc 16.1.1, clang 22.1.5 |
| Flags | `-std=c17 -Wall -Wextra -Wpedantic -O2` |
| Formatação | `clang-format` (estilo em [`../../.clang-format`](../../.clang-format)) |

## Arquivos

- `account.h` — a **interface** (tipos e assinaturas públicas) + header guard.
- `account.c` — a **implementação** (corpos das funções + um helper `static`).
- `main.c` — um cliente que usa o módulo **só pela interface**.
- `Makefile` — a **compilação separada** (`.c` → `.o` → link).

## Compilar, rodar e formatar

```sh
make run      # compila cada .c, liga os .o e executa
make format   # aplica clang-format
make clean
```
