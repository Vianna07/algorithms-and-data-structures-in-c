/*
 * memory.c — O ciclo de vida da memória no heap (uso correto).
 *
 * Projeto:  PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo: 2 — Gerenciamento de memória
 * Padrão:   C17 (ISO/IEC 9899:2018)
 * Build:    gcc/clang -std=c17 -Wall -Wextra -Wpedantic   (ver Makefile)
 */
#include <stdio.h>
#include <stdlib.h>

// start snippet lifecycle
// O ciclo de vida de um bloco no heap: pedir, usar, devolver — e zerar.
static void lifecycle(void) {
    int *a = malloc(3 * sizeof(int)); // 1) PEDIR memória
    if (a == NULL) {
        return; // malloc pode falhar (sem memória): sempre cheque
    }
    a[0] = 10; // 2) USAR
    a[1] = 20;
    a[2] = 30;
    printf("a = [%d, %d, %d]\n", a[0], a[1], a[2]);

    free(a);  // 3) DEVOLVER ao sistema
    a = NULL; // 4) ZERAR o ponteiro (evita dangling e double free)
}
// end snippet lifecycle

// start snippet calloc
// calloc: igual a malloc, mas ZERA a memória. Ideal para começar em zero.
static void calloc_demo(void) {
    int *zeros = calloc(4, sizeof(int)); // 4 ints, todos 0
    if (zeros == NULL) {
        return;
    }
    printf("calloc: [%d, %d, %d, %d]\n", zeros[0], zeros[1], zeros[2],
           zeros[3]);
    free(zeros);
}
// end snippet calloc

// start snippet realloc
// realloc: redimensiona um bloco preservando o conteúdo — e pode MOVÊ-LO.
static void realloc_demo(void) {
    int *v = malloc(2 * sizeof(int));
    if (v == NULL) {
        return;
    }
    v[0] = 1;
    v[1] = 2;

    int *bigger = realloc(v, 4 * sizeof(int)); // cresce de 2 para 4 ints
    if (bigger == NULL) {
        free(v); // realloc falhou: o bloco antigo (v) ainda é válido; libere-o
        return;
    }
    v = bigger; // só sobrescreve v DEPOIS de confirmar o sucesso
    v[2] = 3;
    v[3] = 4;
    printf("realloc: [%d, %d, %d, %d]\n", v[0], v[1], v[2], v[3]);
    free(v);
}
// end snippet realloc

int main(void) {
    lifecycle();
    calloc_demo();
    realloc_demo();
    return 0;
}
