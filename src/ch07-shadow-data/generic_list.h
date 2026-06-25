/*
 * generic_list.h — Lista encadeada GENÉRICA via void* (estratégia Shadow Data).
 *
 * Projeto:   PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo:  7 — Estratégia Shadow Data
 * Padrão:    C17 (ISO/IEC 9899:2018)
 * Build:     gcc/clang -std=c17 -Wall -Wextra -Wpedantic   (ver Makefile)
 */
#ifndef GENERIC_LIST_H
#define GENERIC_LIST_H

#include <stddef.h>  // size_t
#include <stdbool.h> // bool

// Um nó "sombra": guarda só CONTROLE — um ponteiro para o dado de negócio
// (que mora à parte) e o encadeamento. A lista não conhece o tipo do dado.
typedef struct GNode {
    void *data; // ponteiro para o dado real (a "sombra" aponta o negócio)
    struct GNode *next; // metadado de controle: o encadeamento
} GNode;

// Estilo qsort: ponteiros de função descrevem como tratar o tipo concreto.
typedef void (*FreeFn)(void *data);                 // como liberar um dado
typedef int (*CmpFn)(const void *a, const void *b); // <0, 0, >0 (igual qsort)
typedef void (*ApplyFn)(void *data, void *ctx);     // aplica algo a cada dado

typedef struct {
    GNode *head;
    size_t size;
    FreeFn free_fn; // libera cada dado ao destruir; NULL = a lista não é dona
} GList;

void glist_init(GList *list, FreeFn free_fn);
void glist_free(GList *list);
bool glist_push_front(GList *list, void *data);

void *glist_find(const GList *list, const void *key, CmpFn cmp);
void glist_foreach(const GList *list, ApplyFn fn, void *ctx);
size_t glist_size(const GList *list);

#endif // GENERIC_LIST_H
