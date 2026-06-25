/*
 * bst.h — Árvore Binária de Busca (BST) de inteiros.
 *
 * Projeto:   PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo:  9 — Árvores Binárias de Busca
 * Padrão:    C17 (ISO/IEC 9899:2018)
 * Build:     gcc/clang -std=c17 -Wall -Wextra -Wpedantic   (ver Makefile)
 */
#ifndef BST_H
#define BST_H

#include <stddef.h>  // size_t
#include <stdbool.h> // bool

typedef struct BSTNode {
    int value;
    struct BSTNode *left;  // subárvore com valores MENORES
    struct BSTNode *right; // subárvore com valores MAIORES
} BSTNode;

typedef struct {
    BSTNode *root;
    size_t size;
} BST;

// Função aplicada a cada valor durante um percurso.
typedef void (*VisitFn)(int value, void *ctx);

void bst_init(BST *t);
void bst_free(BST *t);

bool bst_insert(BST *t, int value); // ignora duplicatas
bool bst_contains(const BST *t, int value);
bool bst_remove(BST *t, int value); // trata os três casos
size_t bst_height(const BST *t);    // árvore vazia = 0
size_t bst_size(const BST *t);

void bst_preorder(const BST *t, VisitFn visit, void *ctx);
void bst_inorder(const BST *t, VisitFn visit, void *ctx); // sai ORDENADO
void bst_postorder(const BST *t, VisitFn visit, void *ctx);
void bst_levelorder(const BST *t, VisitFn visit, void *ctx); // BFS (usa fila)

#endif // BST_H
