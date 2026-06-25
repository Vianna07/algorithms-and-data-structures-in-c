/*
 * main.c — Demonstração do array dinâmico (a saída aparece no capítulo).
 *
 * Projeto:  PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo: 5 — Array dinâmico
 * Padrão:   C17 (ISO/IEC 9899:2018)
 */

// start snippet main
#include "dynamic_array.h"

#include <stdio.h>

int main(void) {
    DynamicArray numbers;
    da_init(&numbers, 2); // começa pequeno de propósito

    for (int i = 1; i <= 6; i++) {
        da_push(&numbers, i * 10); // força os crescimentos: 2 -> 4 -> 8
    }

    printf("size = %zu, capacity = %zu\n", da_size(&numbers), numbers.capacity);
    for (size_t i = 0; i < da_size(&numbers); i++) {
        printf("numbers[%zu] = %d\n", i, da_get(&numbers, i));
    }

    da_free(&numbers); // todo malloc tem seu free
    return 0;
}
// end snippet main
