/*
 * queues.c — Implementação das duas filas.
 *
 * Projeto:  PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo: 8 — Estruturas restritas: Pilhas e Filas
 * Padrão:   C17 (ISO/IEC 9899:2018)
 */
#include "queues.h"

#include <stdlib.h> // malloc, free

bool rq_init(RingQueue *q, size_t cap) {
    q->data = malloc(cap * sizeof(int));
    if (q->data == NULL && cap > 0) {
        return false;
    }
    q->cap = cap;
    q->head = 0;
    q->count = 0;
    return true;
}
void rq_free(RingQueue *q) {
    free(q->data);
    q->data = NULL;
    q->cap = 0;
    q->head = 0;
    q->count = 0;
}

// start snippet ringops
// O segredo do ring buffer: os índices "dão a volta" com o módulo (% cap).
// Guardamos head + count (não head + tail) p/ distinguir cheia de vazia.
bool rq_enqueue(RingQueue *q, int value) {
    if (q->count == q->cap) {
        return false; // cheia
    }
    size_t tail = (q->head + q->count) % q->cap; // 1º slot livre, com wrap
    q->data[tail] = value;
    q->count++;
    return true;
}

bool rq_dequeue(RingQueue *q, int *out) {
    if (q->count == 0) {
        return false; // vazia
    }
    *out = q->data[q->head];
    q->head = (q->head + 1) % q->cap; // a frente avança, com wrap
    q->count--;
    return true;
}
// end snippet ringops

bool rq_full(const RingQueue *q) {
    return q->count == q->cap;
}
bool rq_empty(const RingQueue *q) {
    return q->count == 0;
}

// start snippet listqops
// Fila sobre lista: entra no fim (tail), sai pela frente (head). Os dois
// ponteiros tornam enqueue e dequeue O(1), sem limite de capacidade.
bool lq_enqueue(ListQueue *q, int value) {
    LQNode *node = malloc(sizeof(LQNode));
    if (node == NULL) {
        return false;
    }
    node->value = value;
    node->next = NULL;
    if (q->tail != NULL) {
        q->tail->next = node; // costura no fim
    } else {
        q->head = node; // fila estava vazia: node é frente e fim
    }
    q->tail = node;
    q->size++;
    return true;
}

bool lq_dequeue(ListQueue *q, int *out) {
    if (q->head == NULL) {
        return false;
    }
    LQNode *front = q->head;
    *out = front->value;
    q->head = front->next; // a frente avança
    if (q->head == NULL) {
        q->tail = NULL; // ficou vazia: zera a cauda também
    }
    free(front);
    q->size--;
    return true;
}
// end snippet listqops

void lq_init(ListQueue *q) {
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}
void lq_free(ListQueue *q) {
    LQNode *cur = q->head;
    while (cur != NULL) {
        LQNode *next = cur->next;
        free(cur);
        cur = next;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}
bool lq_empty(const ListQueue *q) {
    return q->head == NULL;
}
