# Capítulo 11 — Compactador de Huffman (código-fonte)

O **projeto integrador** do livro: comprime e descomprime dados com o algoritmo de
Huffman. Compilável e testado, com round-trip verificado.

| Item | Valor |
|---|---|
| Padrão da linguagem | **C17** (ISO/IEC 9899:2018) |
| Compiladores testados | gcc 16.1.1, clang 22.1.5 |
| Flags | `-std=c17 -Wall -Wextra -Wpedantic -O2` |
| Formatação | `clang-format` (estilo em [`../../.clang-format`](../../.clang-format)) |

## Pipeline (5 etapas)

1. **Histograma** — `count_freq`: conta a frequência de cada byte.
2. **Árvore** — `build_tree`: junta os dois nós menos frequentes (usando o
   **heap do cap. 10**) até sobrar a raiz.
3. **Dicionário** — `gen_codes`: códigos curtos para bytes frequentes.
4. **Bits** — `BitWriter`/`BitReader`: escrita e leitura **bit a bit**.
5. **(Des)compressão** — `huff_compress`/`huff_decompress`, com a árvore
   serializada no cabeçalho.

## Arquivos

- `huffman.h` / `.c` — todo o compactador.
- `main.c` — demonstração (comprime um texto e confere o round-trip).

## Compilar, rodar e formatar

```sh
make run      # compila com -std=c17 e executa o demo
make format   # aplica clang-format
make clean
```
