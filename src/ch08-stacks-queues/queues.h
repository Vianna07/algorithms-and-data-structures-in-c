/*
 * queues.h — Fila (FIFO) sobre DOIS backings: array circular e lista encadeada.
 *
 * Projeto:   PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo:  8 — Estruturas restritas: Pilhas e Filas
 * Padrão:    C17 (ISO/IEC 9899:2018)
 * Build:     gcc/clang -std=c17 -Wall -Wextra -Wpedantic   (ver Makefile)
 */
#ifndef QUEUES_H
#define QUEUES_H

#include <stddef.h>  // size_t
#include <stdbool.h> // bool

// --- Fila sobre ARRAY CIRCULAR (ring buffer; capacidade fixa)
typedef struct {
    int *data;
    size_t cap;   // tamanho do buffer
    size_t head;  // índice do próximo a SAIR (a frente)
    size_t count; // quantos elementos há agora
} RingQueue;

bool rq_init(RingQueue *q, size_t cap);
void rq_free(RingQueue *q);
bool rq_enqueue(RingQueue *q, int value); // O(1); false se cheia
bool rq_dequeue(RingQueue *q, int *out);  // O(1)
bool rq_full(const RingQueue *q);
bool rq_empty(const RingQueue *q);

// --- Fila sobre LISTA ENCADEADA (head + tail; cresce sem limite)
typedef struct LQNode {
    int value;
    struct LQNode *next;
} LQNode;

typedef struct {
    LQNode *head; // sai por aqui (a frente)
    LQNode *tail; // entra por aqui (o fim) — torna o enqueue O(1)
    size_t size;
} ListQueue;

void lq_init(ListQueue *q);
void lq_free(ListQueue *q);
bool lq_enqueue(ListQueue *q, int value); // O(1)
bool lq_dequeue(ListQueue *q, int *out);  // O(1)
bool lq_empty(const ListQueue *q);

#endif // QUEUES_H
