/*
 * dynamic_array.h — Array dinâmico de inteiros (ArrayList).
 *
 * Projeto:   PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo:  5 — Array dinâmico
 * Padrão:    C17 (ISO/IEC 9899:2018)
 * Build:     gcc/clang -std=c17 -Wall -Wextra -Wpedantic   (ver Makefile)
 */
#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>  // size_t
#include <stdbool.h> // bool

typedef struct {
    int *data;       // bloco contíguo de elementos, no heap
    size_t size;     // quantos elementos existem
    size_t capacity; // quantos cabem antes de realocar
} DynamicArray;

// Ciclo de vida.
bool da_init(DynamicArray *da, size_t initial_capacity);
void da_free(DynamicArray *da);

// Inserção e remoção no fim.
bool da_push(DynamicArray *da, int value);
bool da_pop(DynamicArray *da, int *out);

// Acesso por índice e tamanho.
int da_get(const DynamicArray *da, size_t index);
void da_set(DynamicArray *da, size_t index, int value);
size_t da_size(const DynamicArray *da);

#endif // DYNAMIC_ARRAY_H
