/*
 * singly_list.h — Lista simplesmente encadeada de inteiros.
 *
 * Projeto:   PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo:  6 — Listas encadeadas
 * Padrão:    C17 (ISO/IEC 9899:2018)
 * Build:     gcc/clang -std=c17 -Wall -Wextra -Wpedantic   (ver Makefile)
 */
#ifndef SINGLY_LIST_H
#define SINGLY_LIST_H

#include <stddef.h>  // size_t
#include <stdbool.h> // bool

typedef struct SNode {
    int value;          // dado de negócio
    struct SNode *next; // ponteiro para o próximo nó (NULL marca o fim)
} SNode;

typedef struct {
    SNode *head; // primeiro nó (NULL se a lista está vazia)
    size_t size; // quantos nós existem
} SList;

void slist_init(SList *list);
void slist_free(SList *list);

bool slist_push_front(SList *list, int value);                // O(1)
bool slist_insert_after(SList *list, SNode *node, int value); // O(1) dado o nó

SNode *slist_find(const SList *list, int value); // O(n)
bool slist_remove(SList *list, int value);       // O(n): remove a 1ª ocorrência
size_t slist_size(const SList *list);

#endif // SINGLY_LIST_H
