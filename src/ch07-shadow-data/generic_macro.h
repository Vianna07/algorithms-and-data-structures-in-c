/*
 * generic_macro.h — Contêiner genérico em TEMPO DE COMPILAÇÃO (molde via
 * macro).
 *
 * Projeto:   PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo:  7 — Estratégia Shadow Data
 * Padrão:    C17 (ISO/IEC 9899:2018)
 */
#ifndef GENERIC_MACRO_H
#define GENERIC_MACRO_H

#include <stddef.h>  // size_t
#include <stdbool.h> // bool
#include <stdlib.h>  // realloc, free

// Molde: gera uma pilha type-safe e SEM overhead (dados inline) para o tipo T.
// Uso: DEFINE_STACK(int, IntStack) gera IntStack, IntStack_push/pop/free.
#define DEFINE_STACK(T, Name)                          \
    typedef struct {                                   \
        T *data;                                       \
        size_t size;                                   \
        size_t cap;                                    \
    } Name;                                            \
                                                       \
    static inline void Name##_init(Name *s) {          \
        s->data = NULL;                                \
        s->size = 0;                                   \
        s->cap = 0;                                    \
    }                                                  \
                                                       \
    static inline bool Name##_push(Name *s, T value) { \
        if (s->size == s->cap) {                       \
            size_t nc = s->cap ? s->cap * 2 : 4;       \
            T *nd = realloc(s->data, nc * sizeof(T));  \
            if (nd == NULL)                            \
                return false;                          \
            s->data = nd;                              \
            s->cap = nc;                               \
        }                                              \
        s->data[s->size++] = value;                    \
        return true;                                   \
    }                                                  \
                                                       \
    static inline bool Name##_pop(Name *s, T *out) {   \
        if (s->size == 0)                              \
            return false;                              \
        *out = s->data[--s->size];                     \
        return true;                                   \
    }                                                  \
                                                       \
    static inline void Name##_free(Name *s) {          \
        free(s->data);                                 \
        s->data = NULL;                                \
        s->size = 0;                                   \
        s->cap = 0;                                    \
    }

#endif // GENERIC_MACRO_H
