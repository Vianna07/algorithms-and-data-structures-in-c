# Capítulo 3 — Structs e uniões (código-fonte)

Demonstrações didáticas, compiláveis e testadas. O livro inclui este arquivo
diretamente (via `include-code-files`).

| Item | Valor |
|---|---|
| Padrão da linguagem | **C17** (ISO/IEC 9899:2018) |
| Compiladores testados | gcc 16.1.1, clang 22.1.5 |
| Flags | `-std=c17 -Wall -Wextra -Wpedantic -O2` |
| Formatação | `clang-format` (estilo em [`../../.clang-format`](../../.clang-format)) |

> Os valores de `sizeof`/`offsetof` da saída referem-se ao ABI x86-64 (System V).
> Os bytes da união assumem little-endian.

## Arquivo

- `structs.c` — composição com `struct`, alinhamento/`padding` (via `offsetof`) e
  `union`. A saída aparece no capítulo.

## Compilar, rodar e formatar

```sh
make run      # compila com -std=c17 e executa
make format   # aplica clang-format
make clean
```
