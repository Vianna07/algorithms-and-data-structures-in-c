/*
 * main.c — Demonstração das listas encadeadas (a saída aparece no capítulo).
 *
 * Projeto:  PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo: 6 — Listas encadeadas
 * Padrão:   C17 (ISO/IEC 9899:2018)
 */

// start snippet main
#include "doubly_list.h"
#include "singly_list.h"

#include <stdio.h>

int main(void) {
    // Lista simples: push_front INVERTE a ordem (cada novo nó vira a cabeça).
    SList s;
    slist_init(&s);
    slist_push_front(&s, 10);
    slist_push_front(&s, 20);
    slist_push_front(&s, 30);

    printf("simples (size=%zu):  ", slist_size(&s));
    for (SNode *p = s.head; p != NULL; p = p->next) {
        printf("%d ", p->value);
    }
    slist_remove(&s, 20); // tira o nó do meio
    printf("\napós remover 20:    ");
    for (SNode *p = s.head; p != NULL; p = p->next) {
        printf("%d ", p->value);
    }
    slist_free(&s);

    // Lista dupla: push_back PRESERVA a ordem (O(1) graças à cauda) e dá para
    // percorrer nos dois sentidos usando o ponteiro 'prev'.
    DList d;
    dlist_init(&d);
    dlist_push_back(&d, 10);
    dlist_push_back(&d, 20);
    dlist_push_back(&d, 30);

    printf("\ndupla (frente->tras):");
    for (DNode *p = d.head; p != NULL; p = p->next) {
        printf(" %d", p->value);
    }
    printf("\ndupla (tras->frente):");
    for (DNode *p = d.tail; p != NULL; p = p->prev) {
        printf(" %d", p->value);
    }
    printf("\n");
    dlist_free(&d);
    return 0;
}
// end snippet main
