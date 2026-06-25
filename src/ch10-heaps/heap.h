/*
 * heap.h — Min-heap binário (fila de prioridade) sobre array.
 *
 * Projeto:   PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo:  10 — Filas de prioridade (Heaps)
 * Padrão:    C17 (ISO/IEC 9899:2018)
 * Build:     gcc/clang -std=c17 -Wall -Wextra -Wpedantic   (ver Makefile)
 */
#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>  // size_t
#include <stdbool.h> // bool

// Árvore binária COMPLETA guardada num array (reaproveita o cap. 5):
//   filho esquerdo de i = 2*i + 1   |   filho direito = 2*i + 2
//   pai de i = (i - 1) / 2
// Invariante (min-heap): todo pai é <= seus filhos; o mínimo está na raiz [0].
typedef struct {
    int *data;
    size_t size;
    size_t cap;
} MinHeap;

void heap_init(MinHeap *h);
void heap_free(MinHeap *h);

bool heap_push(MinHeap *h, int value);      // insere; O(log n)
bool heap_pop(MinHeap *h, int *out);        // remove o mínimo; O(log n)
bool heap_peek(const MinHeap *h, int *out); // espia o mínimo; O(1)
bool heap_build(MinHeap *h, const int *values, size_t n); // O(n)
size_t heap_size(const MinHeap *h);

#endif // HEAP_H
