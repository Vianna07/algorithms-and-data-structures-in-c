# Capítulo 7 — Estratégia Shadow Data (código-fonte)

Código de referência do capítulo, **compilável e testado**. O livro inclui estes
arquivos diretamente (via `include-code-files`).

| Item | Valor |
|---|---|
| Padrão da linguagem | **C17** (ISO/IEC 9899:2018) |
| Compiladores testados | gcc 16.1.1, clang 22.1.5 |
| Flags | `-std=c17 -Wall -Wextra -Wpedantic -O2` |
| Formatação | `clang-format` (estilo em [`../../.clang-format`](../../.clang-format)) |

## Arquivos

- `generic_list.h` / `.c` — lista encadeada **genérica via `void*`** (Shadow Data).
- `main.c` — demonstra a MESMA lista com dois tipos (ints e strings).
- `generic_macro.h` — o **contraste**: um molde `DEFINE_STACK(T, Name)` que gera
  um contêiner type-safe em tempo de compilação.
- `macro_demo.c` — usa o molde para criar uma `IntStack`.

## Compilar, rodar e formatar

```sh
make run      # compila e executa os dois demos (void* e macro)
make format   # aplica clang-format
make clean
```
