/*
 * singly_list.c — Implementação da lista simplesmente encadeada.
 *
 * Projeto:  PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo: 6 — Listas encadeadas
 * Padrão:   C17 (ISO/IEC 9899:2018)
 */
#include "singly_list.h"

#include <stdlib.h> // malloc, free

// start snippet slife
void slist_init(SList *list) {
    list->head = NULL;
    list->size = 0;
}

// Libera nó a nó, do início ao fim, sem perder o ponteiro do próximo.
void slist_free(SList *list) {
    SNode *cur = list->head;
    while (cur != NULL) {
        SNode *next = cur->next; // guarda o próximo ANTES de liberar o atual
        free(cur);
        cur = next;
    }
    list->head = NULL;
    list->size = 0;
}
// end snippet slife

// start snippet pushfront
// Insere no início: o caso barato da lista encadeada. O(1).
bool slist_push_front(SList *list, int value) {
    SNode *node = malloc(sizeof(SNode));
    if (node == NULL) {
        return false;
    }
    node->value = value;
    node->next = list->head; // o novo nó aponta para a antiga cabeça
    list->head = node;       // e passa a ser a cabeça
    list->size += 1;
    return true;
}
// end snippet pushfront

// start snippet insert
// Insere logo depois de um nó já conhecido. Sem deslocar nada: O(1).
bool slist_insert_after(SList *list, SNode *node, int value) {
    SNode *fresh = malloc(sizeof(SNode));
    if (fresh == NULL) {
        return false;
    }
    fresh->value = value;
    fresh->next = node->next; // costura: fresh aponta para quem vinha depois
    node->next = fresh;       // e node passa a apontar para fresh
    list->size += 1;
    return true;
}
// end snippet insert

// start snippet find
// Busca a primeira ocorrência de um valor. O(n): segue ponteiro a ponteiro.
SNode *slist_find(const SList *list, int value) {
    for (SNode *cur = list->head; cur != NULL; cur = cur->next) {
        if (cur->value == value) {
            return cur;
        }
    }
    return NULL;
}
// end snippet find

// start snippet remove
// Remove a primeira ocorrência. O(n) para achar, O(1) para religar.
// Truque do "ponteiro para ponteiro": evita tratar a cabeça como caso especial.
bool slist_remove(SList *list, int value) {
    SNode **link = &list->head; // endereço do ponteiro que aponta o nó atual
    while (*link != NULL) {
        SNode *cur = *link;
        if (cur->value == value) {
            *link = cur->next; // religa o anterior diretamente ao próximo
            free(cur);
            list->size -= 1;
            return true;
        }
        link = &cur->next; // avança para o ponteiro 'next' do nó atual
    }
    return false;
}
// end snippet remove

size_t slist_size(const SList *list) {
    return list->size;
}
