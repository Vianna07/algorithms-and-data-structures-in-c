/*
 * main.c — Demonstração da BST: inserção, percursos, busca e remoção.
 *
 * Projeto:  PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo: 9 — Árvores Binárias de Busca
 * Padrão:   C17 (ISO/IEC 9899:2018)
 */
#include "bst.h"

#include <stdio.h>

// start snippet main
static void print_int(int value, void *ctx) {
    (void)ctx;
    printf(" %d", value);
}

int main(void) {
    BST t;
    bst_init(&t);

    // Inserções formam a árvore equilibrada usada no capítulo.
    int vals[] = {50, 30, 70, 20, 40, 60, 80};
    for (size_t i = 0; i < sizeof(vals) / sizeof(vals[0]); i++) {
        bst_insert(&t, vals[i]);
    }

    printf("inorder (ordenado):");
    bst_inorder(&t, print_int, NULL);
    printf("\npreorder          :");
    bst_preorder(&t, print_int, NULL);
    printf("\npostorder         :");
    bst_postorder(&t, print_int, NULL);
    printf("\nlevelorder (BFS)  :");
    bst_levelorder(&t, print_int, NULL);

    printf("\ncontem 40? %s | contem 45? %s\n",
           bst_contains(&t, 40) ? "sim" : "nao",
           bst_contains(&t, 45) ? "sim" : "nao");
    printf("altura: %zu\n", bst_height(&t));

    // Remover a raiz (50): tem dois filhos, então o sucessor (60) assume.
    bst_remove(&t, 50);
    printf("apos remover 50    :");
    bst_inorder(&t, print_int, NULL);
    printf("\n");

    bst_free(&t);
    return 0;
}
// end snippet main
