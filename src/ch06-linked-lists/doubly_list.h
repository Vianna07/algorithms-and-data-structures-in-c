/*
 * doubly_list.h — Lista duplamente encadeada de inteiros (com cauda).
 *
 * Projeto:   PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo:  6 — Listas encadeadas
 * Padrão:    C17 (ISO/IEC 9899:2018)
 * Build:     gcc/clang -std=c17 -Wall -Wextra -Wpedantic   (ver Makefile)
 */
#ifndef DOUBLY_LIST_H
#define DOUBLY_LIST_H

#include <stddef.h>  // size_t
#include <stdbool.h> // bool

typedef struct DNode {
    int value;          // dado de negócio
    struct DNode *prev; // nó anterior (NULL na cabeça) — o ponteiro extra
    struct DNode *next; // próximo nó (NULL na cauda)
} DNode;

typedef struct {
    DNode *head; // primeiro nó
    DNode *tail; // último nó: torna o push_back O(1)
    size_t size;
} DList;

void dlist_init(DList *list);
void dlist_free(DList *list);

bool dlist_push_front(DList *list, int value); // O(1)
bool dlist_push_back(DList *list, int value);  // O(1) graças à cauda
void dlist_remove(DList *list, DNode *node);   // O(1) dado o nó

size_t dlist_size(const DList *list);

#endif // DOUBLY_LIST_H
