/*
 * dynamic_array.c — Implementação do array dinâmico.
 *
 * Projeto:  PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo: 5 — Array dinâmico
 * Padrão:   C17 (ISO/IEC 9899:2018)
 */

// start snippet includes
#include "dynamic_array.h"

#include <assert.h> // assert
#include <stdlib.h> // malloc, realloc, free
// end snippet includes

// start snippet lifecycle
// Prepara um array vazio (capacidade inicial opcional).
// Devolve false só se a alocação inicial falhar.
bool da_init(DynamicArray *da, size_t initial_capacity) {
    da->data = NULL;
    da->size = 0;
    da->capacity = 0;

    if (initial_capacity > 0) {
        da->data = malloc(initial_capacity * sizeof(int));
        if (da->data == NULL) {
            return false; // sem memória: struct fica vazia, mas válida
        }
        da->capacity = initial_capacity;
    }
    return true;
}

// Libera o bloco e zera a struct (evita dangling pointer / double free).
void da_free(DynamicArray *da) {
    free(da->data); // free(NULL) é seguro
    da->data = NULL;
    da->size = 0;
    da->capacity = 0;
}
// end snippet lifecycle

// start snippet grow_push
// Cresce o bloco dobrando a capacidade. Detalhe interno (static).
static bool da_grow(DynamicArray *da) {
    size_t new_capacity = (da->capacity == 0) ? 1 : da->capacity * 2;

    int *new_data = realloc(da->data, new_capacity * sizeof(int));
    if (new_data == NULL) {
        return false; // realloc falhou; o bloco antigo continua válido
    }

    da->data = new_data;
    da->capacity = new_capacity;
    return true;
}

// Insere um valor no fim. O(1) amortizado.
bool da_push(DynamicArray *da, int value) {
    if (da->size == da->capacity) { // sem folga?
        if (!da_grow(da)) {
            return false; // falhou ao crescer: nada é perdido
        }
    }
    da->data[da->size] = value; // grava na primeira posição livre
    da->size += 1;
    return true;
}
// end snippet grow_push

// start snippet access
// Lê o elemento em index. O(1).
int da_get(const DynamicArray *da, size_t index) {
    assert(index < da->size); // índice fora do tamanho = erro de programação
    return da->data[index];   // endereço = data + index*sizeof(int)
}

// Sobrescreve o elemento em index. O(1).
void da_set(DynamicArray *da, size_t index, int value) {
    assert(index < da->size);
    da->data[index] = value;
}
// end snippet access

// start snippet pop
// Remove o último elemento; copia-o para *out se out != NULL. O(1).
bool da_pop(DynamicArray *da, int *out) {
    if (da->size == 0) {
        return false; // nada a remover
    }
    da->size -= 1;
    if (out != NULL) {
        *out = da->data[da->size];
    }
    return true;
}

size_t da_size(const DynamicArray *da) {
    return da->size;
}
// end snippet pop
