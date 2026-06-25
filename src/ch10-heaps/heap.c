/*
 * heap.c — Implementação do min-heap binário.
 *
 * Projeto:  PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo: 10 — Filas de prioridade (Heaps)
 * Padrão:   C17 (ISO/IEC 9899:2018)
 */
#include "heap.h"

#include <stdlib.h> // malloc, realloc, free

// start snippet helpers
static void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Cresce o array dobrando a capacidade (a estratégia do capítulo 5).
static bool ensure_cap(MinHeap *h, size_t need) {
    if (need <= h->cap) {
        return true;
    }
    size_t nc = h->cap ? h->cap * 2 : 4;
    while (nc < need) {
        nc *= 2;
    }
    int *nd = realloc(h->data, nc * sizeof(int));
    if (nd == NULL) {
        return false;
    }
    h->data = nd;
    h->cap = nc;
    return true;
}
// end snippet helpers

// start snippet siftup
// Sobe o elemento i enquanto for menor que o pai. O(log n).
static void sift_up(MinHeap *h, size_t i) {
    while (i > 0) {
        size_t parent = (i - 1) / 2;
        if (h->data[i] >= h->data[parent]) {
            break; // o pai já é menor-ou-igual: posição correta
        }
        swap(&h->data[i], &h->data[parent]);
        i = parent;
    }
}
// end snippet siftup

// start snippet siftdown
// Desce o elemento i, trocando com o MENOR filho, até obedecer à regra.
static void sift_down(MinHeap *h, size_t i) {
    for (;;) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        size_t smallest = i;
        if (left < h->size && h->data[left] < h->data[smallest]) {
            smallest = left;
        }
        if (right < h->size && h->data[right] < h->data[smallest]) {
            smallest = right;
        }
        if (smallest == i) {
            break; // já é menor que ambos os filhos
        }
        swap(&h->data[i], &h->data[smallest]);
        i = smallest;
    }
}
// end snippet siftdown

// start snippet push
// Insere no fim do array e "sobe" o novo elemento até seu lugar.
bool heap_push(MinHeap *h, int value) {
    if (!ensure_cap(h, h->size + 1)) {
        return false;
    }
    h->data[h->size] = value;
    h->size++;
    sift_up(h, h->size - 1);
    return true;
}
// end snippet push

// start snippet pop
// Remove e devolve o MÍNIMO (a raiz).
bool heap_pop(MinHeap *h, int *out) {
    if (h->size == 0) {
        return false;
    }
    *out = h->data[0];                 // o mínimo está sempre na raiz
    h->data[0] = h->data[h->size - 1]; // o último elemento vai para a raiz
    h->size--;
    if (h->size > 0) {
        sift_down(h, 0); // e desce até o lugar certo
    }
    return true;
}
// end snippet pop

// start snippet build
// Monta um heap a partir de um array qualquer em O(n) (algoritmo de Floyd):
// heapifica de baixo para cima, do último nó interno (n/2 - 1) até a raiz.
bool heap_build(MinHeap *h, const int *values, size_t n) {
    if (!ensure_cap(h, n)) {
        return false;
    }
    for (size_t i = 0; i < n; i++) {
        h->data[i] = values[i];
    }
    h->size = n;
    for (size_t i = n / 2; i-- > 0;) {
        sift_down(h, i);
    }
    return true;
}
// end snippet build

bool heap_peek(const MinHeap *h, int *out) {
    if (h->size == 0) {
        return false;
    }
    *out = h->data[0];
    return true;
}

void heap_init(MinHeap *h) {
    h->data = NULL;
    h->size = 0;
    h->cap = 0;
}
void heap_free(MinHeap *h) {
    free(h->data);
    h->data = NULL;
    h->size = 0;
    h->cap = 0;
}
size_t heap_size(const MinHeap *h) {
    return h->size;
}
