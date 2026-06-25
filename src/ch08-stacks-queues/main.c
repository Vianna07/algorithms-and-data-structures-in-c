/*
 * main.c — Demonstração: pilhas (LIFO) e filas (FIFO) nos dois backings.
 *
 * Projeto:  PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo: 8 — Estruturas restritas: Pilhas e Filas
 * Padrão:   C17 (ISO/IEC 9899:2018)
 */
#include "queues.h"
#include "stacks.h"

#include <stdio.h>

// start snippet main
int main(void) {
    int v;

    // Pilha sobre array (LIFO): sai na ordem INVERSA da entrada.
    ArrayStack as;
    as_init(&as);
    for (int i = 1; i <= 3; i++) {
        as_push(&as, i * 10);
    }
    printf("pilha/array (LIFO):");
    while (as_pop(&as, &v)) {
        printf(" %d", v);
    }
    as_free(&as);

    // Pilha sobre lista (LIFO): MESMO comportamento, outro backing.
    ListStack ls;
    ls_init(&ls);
    for (int i = 1; i <= 3; i++) {
        ls_push(&ls, i * 10);
    }
    printf("\npilha/lista (LIFO):");
    while (ls_pop(&ls, &v)) {
        printf(" %d", v);
    }
    ls_free(&ls);

    // Fila sobre lista (FIFO): sai na ordem de CHEGADA.
    ListQueue lq;
    lq_init(&lq);
    for (int i = 1; i <= 3; i++) {
        lq_enqueue(&lq, i * 10);
    }
    printf("\nfila/lista  (FIFO):");
    while (lq_dequeue(&lq, &v)) {
        printf(" %d", v);
    }
    lq_free(&lq);

    // Fila circular (cap 3): o 40 "dá a volta" e ocupa o slot que o 10 deixou.
    RingQueue rq;
    rq_init(&rq, 3);
    rq_enqueue(&rq, 10);
    rq_enqueue(&rq, 20);
    rq_enqueue(&rq, 30); // cheia
    rq_dequeue(&rq, &v); // sai o 10, libera um slot
    rq_enqueue(&rq, 40); // 40 entra no slot do 10 (wrap)
    printf("\nfila circular     :");
    while (rq_dequeue(&rq, &v)) {
        printf(" %d", v); // 20 30 40
    }
    rq_free(&rq);

    printf("\n");
    return 0;
}
// end snippet main
