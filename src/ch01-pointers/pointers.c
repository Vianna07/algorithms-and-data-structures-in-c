/*
 * pointers.c — Demonstrações didáticas de ponteiros.
 *
 * Projeto:  PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo: 1 — Ponteiros e aritmética de ponteiros
 * Padrão:   C17 (ISO/IEC 9899:2018)
 * Build:    gcc/clang -std=c17 -Wall -Wextra -Wpedantic   (ver Makefile)
 */
#include <stdio.h>

// start snippet basics
// Endereço vs. valor: `&` pega o endereço; `*` acessa o valor apontado.
static void basics(void) {
    int x = 42;
    int *p = &x; // p guarda o ENDEREÇO de x (p "aponta para" x)

    printf("x        = %d\n", x);  // o valor de x
    printf("*p       = %d\n", *p); // o valor APONTADO por p (o mesmo de x)

    *p = 99;                      // escreve em x ATRAVÉS do ponteiro
    printf("x depois = %d\n", x); // 99: mudamos x sem citar o nome x
}
// end snippet basics

// start snippet arithmetic
// Aritmética de ponteiros: conta em ELEMENTOS, não em bytes.
static void arithmetic(void) {
    int v[4] = {10, 20, 30, 40};
    int *p = v; // o nome do array "decai" no endereço de v[0]

    printf("*p       = %d\n", *p);       // 10
    printf("*(p + 2) = %d\n", *(p + 2)); // 30: avança 2 ELEMENTOS

    // p + 1 pula sizeof(int) bytes; a distância em bytes prova isso:
    printf("bytes(v[1] - v[0]) = %td\n", (char *)&v[1] - (char *)&v[0]);
}
// end snippet arithmetic

// start snippet ptr2ptr
// Ponteiro para ponteiro: um endereço de um endereço.
static void pointer_to_pointer(void) {
    int x = 7;
    int *p = &x;   // p aponta para x
    int **pp = &p; // pp aponta para p

    printf("x=%d  *p=%d  **pp=%d\n", x, *p, **pp); // 7 7 7
    **pp = 50;                                     // chega em x com dois saltos
    printf("x agora = %d\n", x);                   // 50
}
// end snippet ptr2ptr

// start snippet voidptr
// void*: guarda QUALQUER endereço, mas esquece o tipo. Para usá-lo, um cast
// recupera o tipo. É a base da estratégia Shadow Data (capítulo 7).
static void generic_pointer(void) {
    int n = 1234;
    void *anon = &n;                  // um endereço "sem tipo"
    int *back = (int *)anon;          // o cast devolve o tipo int*
    printf("via void*: %d\n", *back); // 1234
}
// end snippet voidptr

int main(void) {
    basics();
    arithmetic();
    pointer_to_pointer();
    generic_pointer();
    return 0;
}
