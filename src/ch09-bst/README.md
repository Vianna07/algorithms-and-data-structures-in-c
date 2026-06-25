# Capítulo 9 — Árvores Binárias de Busca (código-fonte)

Código de referência do capítulo, **compilável e testado**. O livro inclui estes
arquivos diretamente (via `include-code-files`).

| Item | Valor |
|---|---|
| Padrão da linguagem | **C17** (ISO/IEC 9899:2018) |
| Compiladores testados | gcc 16.1.1, clang 22.1.5 |
| Flags | `-std=c17 -Wall -Wextra -Wpedantic -O2` |
| Formatação | `clang-format` (estilo em [`../../.clang-format`](../../.clang-format)) |

## Arquivos

- `bst.h` / `.c` — inserção, busca, remoção (3 casos), 4 percursos e altura.
- `main.c` — demonstração; a saída aparece no capítulo.

## Compilar, rodar e formatar

```sh
make run      # compila com -std=c17 e executa o demo
make format   # aplica clang-format
make clean
```
