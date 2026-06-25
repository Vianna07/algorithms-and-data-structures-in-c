/*
 * huffman.h — Compactador de arquivos com o algoritmo de Huffman.
 *
 * Projeto:   PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo:  11 — Desafio final: compactador de Huffman
 * Padrão:    C17 (ISO/IEC 9899:2018)
 * Build:     gcc/clang -std=c17 -Wall -Wextra -Wpedantic   (ver Makefile)
 */
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stddef.h> // size_t

// Resultado da compressão. A árvore de Huffman vai EMBUTIDA em `bytes` (no
// início), seguida do conteúdo codificado. `original_len` diz à descompressão
// quantos bytes produzir (e quando parar).
typedef struct {
    unsigned char *bytes;
    size_t size;
    size_t original_len;
} Compressed;

// Comprime `n` bytes. Em caso de falha de memória, devolve {NULL, 0, 0}.
Compressed huff_compress(const unsigned char *data, size_t n);

// Descomprime; escreve o tamanho em *out_len. Devolve buffer a liberar com free
// (ou NULL em erro). O chamador é dono da memória devolvida.
unsigned char *huff_decompress(const Compressed *c, size_t *out_len);

void huff_free_compressed(Compressed *c);

#endif // HUFFMAN_H
