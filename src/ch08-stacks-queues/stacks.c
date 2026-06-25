/*
 * stacks.c — Implementação das duas pilhas.
 *
 * Projeto:  PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo: 8 — Estruturas restritas: Pilhas e Filas
 * Padrão:   C17 (ISO/IEC 9899:2018)
 */
#include "stacks.h"

#include <stdlib.h> // malloc, realloc, free

// start snippet arrops
// Pilha sobre array: empilhar é "append no fim"; desempilhar é "remove do fim".
bool as_push(ArrayStack *s, int value) {
    if (s->size == s->cap) { // cheio: dobra (como no cap. 5)
        size_t nc = s->cap ? s->cap * 2 : 4;
        int *nd = realloc(s->data, nc * sizeof(int));
        if (nd == NULL) {
            return false;
        }
        s->data = nd;
        s->cap = nc;
    }
    s->data[s->size++] = value;
    return true;
}

bool as_pop(ArrayStack *s, int *out) {
    if (s->size == 0) {
        return false;
    }
    *out = s->data[--s->size];
    return true;
}
// end snippet arrops

void as_init(ArrayStack *s) {
    s->data = NULL;
    s->size = 0;
    s->cap = 0;
}
void as_free(ArrayStack *s) {
    free(s->data);
    s->data = NULL;
    s->size = 0;
    s->cap = 0;
}
bool as_peek(const ArrayStack *s, int *out) {
    if (s->size == 0) {
        return false;
    }
    *out = s->data[s->size - 1];
    return true;
}
bool as_empty(const ArrayStack *s) {
    return s->size == 0;
}

// start snippet listops
// Pilha sobre lista: o topo é a cabeça — empilhar/desempilhar é O(1) e nunca
// realoca, mas cada elemento custa um malloc e um ponteiro a mais.
bool ls_push(ListStack *s, int value) {
    LSNode *node = malloc(sizeof(LSNode));
    if (node == NULL) {
        return false;
    }
    node->value = value;
    node->next = s->top; // o novo nó vira o topo
    s->top = node;
    s->size++;
    return true;
}

bool ls_pop(ListStack *s, int *out) {
    if (s->top == NULL) {
        return false;
    }
    LSNode *top = s->top;
    *out = top->value;
    s->top = top->next; // o topo desce um
    free(top);
    s->size--;
    return true;
}
// end snippet listops

void ls_init(ListStack *s) {
    s->top = NULL;
    s->size = 0;
}
void ls_free(ListStack *s) {
    LSNode *cur = s->top;
    while (cur != NULL) {
        LSNode *next = cur->next;
        free(cur);
        cur = next;
    }
    s->top = NULL;
    s->size = 0;
}
bool ls_peek(const ListStack *s, int *out) {
    if (s->top == NULL) {
        return false;
    }
    *out = s->top->value;
    return true;
}
bool ls_empty(const ListStack *s) {
    return s->top == NULL;
}
