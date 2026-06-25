/*
 * main.c — Demonstração: comprime um texto, confere o round-trip e a taxa.
 *
 * Projeto:  PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo: 11 — Desafio final: compactador de Huffman
 * Padrão:   C17 (ISO/IEC 9899:2018)
 */
#include "huffman.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// start snippet main
int main(void) {
    const char *text =
        "a compressao de huffman da codigos curtos aos simbolos mais "
        "frequentes e codigos longos aos raros. quanto mais repetitivo "
        "o texto, melhor a taxa de compressao. letras como a, e, o e os "
        "espacos aparecem muito; outras, como z, q ou k, quase nunca. e "
        "por isso que vale a pena dar a cada uma um codigo de tamanho "
        "diferente, em vez de gastar 8 bits fixos para todas.";
    size_t n = strlen(text);

    // Comprime e, em seguida, descomprime de volta.
    Compressed c = huff_compress((const unsigned char *)text, n);

    size_t out_len = 0;
    unsigned char *back = huff_decompress(&c, &out_len);
    bool ok = (back != NULL && out_len == n && memcmp(back, text, n) == 0);

    printf("original:   %zu bytes\n", n);
    printf("comprimido: %zu bytes (inclui a arvore no cabecalho)\n", c.size);
    printf("taxa:       %.1f%% do original\n",
           100.0 * (double)c.size / (double)n);
    printf("round-trip: %s\n", ok ? "OK (identico ao original)" : "FALHOU");

    free(back);
    huff_free_compressed(&c);
    return 0;
}
// end snippet main
