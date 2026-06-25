/*
 * stacks.h — Pilha (LIFO) sobre DOIS backings: array dinâmico e lista
 * encadeada.
 *
 * Projeto:   PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo:  8 — Estruturas restritas: Pilhas e Filas
 * Padrão:    C17 (ISO/IEC 9899:2018)
 * Build:     gcc/clang -std=c17 -Wall -Wextra -Wpedantic   (ver Makefile)
 */
#ifndef STACKS_H
#define STACKS_H

#include <stddef.h>  // size_t
#include <stdbool.h> // bool

// --- Pilha sobre ARRAY DINÂMICO (push/pop no fim; ideia do cap. 5)
typedef struct {
    int *data;
    size_t size;
    size_t cap;
} ArrayStack;

void as_init(ArrayStack *s);
void as_free(ArrayStack *s);
bool as_push(ArrayStack *s, int value); // O(1) amortizado
bool as_pop(ArrayStack *s, int *out);   // O(1)
bool as_peek(const ArrayStack *s, int *out);
bool as_empty(const ArrayStack *s);

// --- Pilha sobre LISTA ENCADEADA (push/pop na cabeça; cap. 6)
typedef struct LSNode {
    int value;
    struct LSNode *next;
} LSNode;

typedef struct {
    LSNode *top; // o topo é a cabeça da lista
    size_t size;
} ListStack;

void ls_init(ListStack *s);
void ls_free(ListStack *s);
bool ls_push(ListStack *s, int value); // O(1), sem realocação
bool ls_pop(ListStack *s, int *out);   // O(1)
bool ls_peek(const ListStack *s, int *out);
bool ls_empty(const ListStack *s);

#endif // STACKS_H
