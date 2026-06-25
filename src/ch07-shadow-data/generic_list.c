/*
 * generic_list.c — Implementação da lista genérica (Shadow Data).
 *
 * Projeto:  PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo: 7 — Estratégia Shadow Data
 * Padrão:   C17 (ISO/IEC 9899:2018)
 */
#include "generic_list.h"

#include <stdlib.h> // malloc, free

// start snippet glife
void glist_init(GList *list, FreeFn free_fn) {
    list->head = NULL;
    list->size = 0;
    list->free_fn = free_fn; // guarda como liberar o dado de negócio
}

// Destrói a lista. Repare na separação Shadow Data: liberamos o DADO (negócio,
// via free_fn — se a lista for dona) e depois o NÓ (controle, sempre nosso).
void glist_free(GList *list) {
    GNode *cur = list->head;
    while (cur != NULL) {
        GNode *next = cur->next;
        if (list->free_fn != NULL) {
            list->free_fn(cur->data); // o dado de negócio
        }
        free(cur); // o nó-sombra (controle)
        cur = next;
    }
    list->head = NULL;
    list->size = 0;
}
// end snippet glife

// start snippet gpushfront
// Insere no início. O nó é genérico: só guarda o ponteiro para o dado. O(1).
bool glist_push_front(GList *list, void *data) {
    GNode *node = malloc(sizeof(GNode));
    if (node == NULL) {
        return false;
    }
    node->data = data; // a sombra (nó) passa a apontar o dado real
    node->next = list->head;
    list->head = node;
    list->size += 1;
    return true;
}
// end snippet gpushfront

// start snippet gfind
// Busca usando um comparador fornecido pelo chamador (igual ao qsort/bsearch).
// A lista não sabe comparar "o tipo"; ela delega ao CmpFn.
void *glist_find(const GList *list, const void *key, CmpFn cmp) {
    for (GNode *cur = list->head; cur != NULL; cur = cur->next) {
        if (cmp(cur->data, key) == 0) {
            return cur->data;
        }
    }
    return NULL;
}
// end snippet gfind

// start snippet gforeach
// Percorre aplicando uma função a cada dado, com um contexto opcional (ctx).
void glist_foreach(const GList *list, ApplyFn fn, void *ctx) {
    for (GNode *cur = list->head; cur != NULL; cur = cur->next) {
        fn(cur->data, ctx);
    }
}
// end snippet gforeach

size_t glist_size(const GList *list) {
    return list->size;
}
