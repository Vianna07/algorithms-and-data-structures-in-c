/*
 * main.c — Demonstração do min-heap: inserção, mínimo, heapsort e build-heap.
 *
 * Projeto:  PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo: 10 — Filas de prioridade (Heaps)
 * Padrão:   C17 (ISO/IEC 9899:2018)
 */
#include "heap.h"

#include <stdio.h>

// start snippet main
int main(void) {
    int xs[] = {5, 3, 8, 1, 9, 2, 7};
    size_t n = sizeof(xs) / sizeof(xs[0]);

    // Inserindo um a um; o mínimo borbulha para a raiz.
    MinHeap h;
    heap_init(&h);
    for (size_t i = 0; i < n; i++) {
        heap_push(&h, xs[i]);
    }
    int m;
    heap_peek(&h, &m);
    printf("min (peek): %d\n", m);

    // Extrair tudo, repetidamente, sai em ordem CRESCENTE — isto é o heapsort.
    printf("extraindo (heapsort):");
    int v;
    while (heap_pop(&h, &v)) {
        printf(" %d", v);
    }
    printf("\n");
    heap_free(&h);

    // build-heap: monta o heap a partir do array de uma vez, em O(n).
    MinHeap h2;
    heap_init(&h2);
    heap_build(&h2, xs, n);
    heap_peek(&h2, &m);
    printf("build-heap O(n), min: %d\n", m);
    heap_free(&h2);

    return 0;
}
// end snippet main
