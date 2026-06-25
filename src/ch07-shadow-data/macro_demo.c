/*
 * macro_demo.c — Demonstração do contêiner gerado por macro (type-safe).
 *
 * Projeto:  PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo: 7 — Estratégia Shadow Data
 * Padrão:   C17 (ISO/IEC 9899:2018)
 */

// start snippet main
#include "generic_macro.h"

#include <stdio.h>

// Uma linha instancia uma pilha de int completa, type-safe e sem void*.
DEFINE_STACK(int, IntStack)

int main(void) {
    IntStack s;
    IntStack_init(&s);
    IntStack_push(&s, 10);
    IntStack_push(&s, 20);
    IntStack_push(&s, 30);
    // IntStack_push(&s, 3.14);  // <- ERRO de compilação: o tipo é checado!

    int v;
    printf("IntStack (pop ate esvaziar):");
    while (IntStack_pop(&s, &v)) {
        printf(" %d", v);
    }
    printf("\n");

    IntStack_free(&s);
    return 0;
}
// end snippet main
