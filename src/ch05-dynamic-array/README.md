# Capítulo 5 — Array dinâmico (código-fonte)

Código de referência do capítulo, **compilável e testado**. O livro inclui estes
arquivos diretamente (via `include-code-files`), então o que você lê é exatamente
o que compila — não há cópia divergente.

| Item | Valor |
|---|---|
| Padrão da linguagem | **C17** (ISO/IEC 9899:2018) |
| Compiladores testados | gcc 16.1.1, clang 22.1.5 |
| Flags | `-std=c17 -Wall -Wextra -Wpedantic -O2` |
| Formatação | `clang-format` (estilo em [`../../.clang-format`](../../.clang-format)) |

## Arquivos

- `dynamic_array.h` — interface (a struct e as assinaturas).
- `dynamic_array.c` — implementação.
- `main.c` — demonstração; a saída aparece no capítulo.

## Compilar, rodar e formatar

```sh
make run      # compila com -std=c17 e executa o demo
make format   # aplica clang-format aos três arquivos
make clean    # remove binário e objetos
```

> Marcadores `// start snippet <nome>` / `// end snippet <nome>` delimitam as
> regiões que o livro mostra. São comentários comuns: não afetam a compilação e
> não aparecem no texto renderizado.
