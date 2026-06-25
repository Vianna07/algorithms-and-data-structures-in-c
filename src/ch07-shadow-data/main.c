/*
 * main.c — Demonstração da lista genérica: UMA implementação, vários tipos.
 *
 * Projeto:  PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo: 7 — Estratégia Shadow Data
 * Padrão:   C17 (ISO/IEC 9899:2018)
 */
#include "generic_list.h"

#include <stdio.h>
#include <stdlib.h>

// start snippet helpers
// Caixa um int no heap (a lista guardará o ponteiro para ele).
static int *box_int(int v) {
    int *p = malloc(sizeof(int));
    if (p != NULL) {
        *p = v;
    }
    return p;
}

// ApplyFn p/ int e p/ string; CmpFn p/ int (estilo qsort: <0, 0, >0).
static void print_int(void *data, void *ctx) {
    (void)ctx;
    printf(" %d", *(int *)data);
}
static void print_str(void *data, void *ctx) {
    (void)ctx;
    printf(" %s", (char *)data);
}
static int cmp_int(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}
// end snippet helpers

// start snippet main
int main(void) {
    // A MESMA lista, dois tipos diferentes.
    // Lista de ints no heap: aqui a lista é DONA dos dados (free_fn = free).
    GList nums;
    glist_init(&nums, free);
    glist_push_front(&nums, box_int(10));
    glist_push_front(&nums, box_int(20));
    glist_push_front(&nums, box_int(30));

    printf("ints:");
    glist_foreach(&nums, print_int, NULL);

    int key = 20;
    int *hit = glist_find(&nums, &key, cmp_int);
    printf("\nbuscar 20 -> %s\n", hit != NULL ? "achou" : "nao achou");
    glist_free(&nums); // libera os nós E os ints (via free_fn)

    // Lista de strings literais: a lista NÃO é dona (free_fn = NULL).
    GList names;
    glist_init(&names, NULL);
    glist_push_front(&names, "ada");
    glist_push_front(&names, "linus");
    glist_push_front(&names, "grace");

    printf("nomes:");
    glist_foreach(&names, print_str, NULL);
    printf("\n");
    glist_free(&names); // libera só os nós; free_fn = NULL não toca nos dados

    return 0;
}
// end snippet main
