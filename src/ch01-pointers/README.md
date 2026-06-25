# Capítulo 1 — Ponteiros (código-fonte)

Demonstrações didáticas, compiláveis e testadas. O livro inclui este arquivo
diretamente (via `include-code-files`).

| Item | Valor |
|---|---|
| Padrão da linguagem | **C17** (ISO/IEC 9899:2018) |
| Compiladores testados | gcc 16.1.1, clang 22.1.5 |
| Flags | `-std=c17 -Wall -Wextra -Wpedantic -O2` |
| Formatação | `clang-format` (estilo em [`../../.clang-format`](../../.clang-format)) |

## Arquivo

- `pointers.c` — endereço × valor, `&`/`*`, aritmética de ponteiros, ponteiro
  para ponteiro e `void*`. A saída (determinística) aparece no capítulo.

## Compilar, rodar e formatar

```sh
make run      # compila com -std=c17 e executa o demo
make format   # aplica clang-format
make clean
```
