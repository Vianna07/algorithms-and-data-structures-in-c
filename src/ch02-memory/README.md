# Capítulo 2 — Gerenciamento de memória (código-fonte)

Demonstrações do uso **correto** do heap: `malloc`/`calloc`/`realloc`/`free` e o
ciclo de vida de um bloco. Compilável, testado e **sem vazamentos** (valgrind).

| Item | Valor |
|---|---|
| Padrão da linguagem | **C17** (ISO/IEC 9899:2018) |
| Compiladores testados | gcc 16.1.1, clang 22.1.5 |
| Flags | `-std=c17 -Wall -Wextra -Wpedantic -O2` |
| Formatação | `clang-format` (estilo em [`../../.clang-format`](../../.clang-format)) |

## Arquivo

- `memory.c` — ciclo de vida (`malloc`/`free`), `calloc` e `realloc`. A saída
  aparece no capítulo. Os anti-padrões (leak, dangling, double free) aparecem
  como exemplos **inline** no capítulo, marcados como errados — não fazem parte
  deste código testado.

## Compilar, rodar e checar

```sh
make run        # compila e executa
make valgrind   # confirma: sem vazamentos nem acessos inválidos
make clean
```
