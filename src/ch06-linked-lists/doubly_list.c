/*
 * doubly_list.c — Implementação da lista duplamente encadeada.
 *
 * Projeto:  PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo: 6 — Listas encadeadas
 * Padrão:   C17 (ISO/IEC 9899:2018)
 */
#include "doubly_list.h"

#include <stdlib.h> // malloc, free

// start snippet dlife
void dlist_init(DList *list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void dlist_free(DList *list) {
    DNode *cur = list->head;
    while (cur != NULL) {
        DNode *next = cur->next;
        free(cur);
        cur = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}
// end snippet dlife

// start snippet dpushback
// Insere no fim em O(1) — só é possível porque guardamos a cauda (tail).
bool dlist_push_back(DList *list, int value) {
    DNode *node = malloc(sizeof(DNode));
    if (node == NULL) {
        return false;
    }
    node->value = value;
    node->next = NULL;       // será o novo último nó
    node->prev = list->tail; // costura para trás, à cauda atual

    if (list->tail != NULL) {
        list->tail->next = node; // a antiga cauda aponta para o novo nó
    } else {
        list->head = node; // lista estava vazia: node é cabeça e cauda
    }
    list->tail = node;
    list->size += 1;
    return true;
}
// end snippet dpushback

// Insere no início em O(1), simétrico ao push_back.
bool dlist_push_front(DList *list, int value) {
    DNode *node = malloc(sizeof(DNode));
    if (node == NULL) {
        return false;
    }
    node->value = value;
    node->prev = NULL;
    node->next = list->head;

    if (list->head != NULL) {
        list->head->prev = node;
    } else {
        list->tail = node;
    }
    list->head = node;
    list->size += 1;
    return true;
}

// start snippet dremove
// Remove um nó conhecido em O(1): o ponteiro 'prev' dispensa varrer a lista
// para achar o anterior (era o que tornava a remoção O(n) na lista simples).
void dlist_remove(DList *list, DNode *node) {
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        list->head = node->next; // node era a cabeça
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev; // node era a cauda
    }
    free(node);
    list->size -= 1;
}
// end snippet dremove

size_t dlist_size(const DList *list) {
    return list->size;
}
