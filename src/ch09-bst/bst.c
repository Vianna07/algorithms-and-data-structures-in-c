/*
 * bst.c — Implementação da árvore binária de busca.
 *
 * Projeto:  PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo: 9 — Árvores Binárias de Busca
 * Padrão:   C17 (ISO/IEC 9899:2018)
 */
#include "bst.h"

#include <stdlib.h> // malloc, free

void bst_init(BST *t) {
    t->root = NULL;
    t->size = 0;
}

// start snippet insert
static BSTNode *node_new(int value) {
    BSTNode *n = malloc(sizeof(BSTNode));
    if (n != NULL) {
        n->value = value;
        n->left = NULL;
        n->right = NULL;
    }
    return n;
}

// Desce recursivamente: menor vai à esquerda, maior à direita. O(altura).
static BSTNode *insert_rec(BSTNode *node, int value, bool *ok) {
    if (node == NULL) {
        BSTNode *fresh = node_new(value); // achou o lugar: cria a folha
        *ok = (fresh != NULL);
        return (fresh != NULL) ? fresh : node;
    }
    if (value < node->value) {
        node->left = insert_rec(node->left, value, ok);
    } else if (value > node->value) {
        node->right = insert_rec(node->right, value, ok);
    } else {
        *ok = false; // valor já existe: ignora a duplicata
    }
    return node;
}

bool bst_insert(BST *t, int value) {
    bool ok = false;
    t->root = insert_rec(t->root, value, &ok);
    if (ok) {
        t->size++;
    }
    return ok;
}
// end snippet insert

// start snippet contains
// Busca iterativa: a cada nó, vai para um lado só. O(altura).
bool bst_contains(const BST *t, int value) {
    const BSTNode *cur = t->root;
    while (cur != NULL) {
        if (value == cur->value) {
            return true;
        }
        cur = (value < cur->value) ? cur->left : cur->right;
    }
    return false;
}
// end snippet contains

// start snippet remove
// O menor valor de uma subárvore é o nó mais à esquerda.
static BSTNode *find_min(BSTNode *node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

static BSTNode *remove_rec(BSTNode *node, int value, bool *removed) {
    if (node == NULL) {
        return NULL; // não encontrado
    }
    if (value < node->value) {
        node->left = remove_rec(node->left, value, removed);
    } else if (value > node->value) {
        node->right = remove_rec(node->right, value, removed);
    } else {
        *removed = true;
        // Caso 1 e 2: nó sem filho à esquerda — devolve o filho à direita
        // (que pode ser NULL). Cobre folha e nó com um único filho.
        if (node->left == NULL) {
            BSTNode *right = node->right;
            free(node);
            return right;
        }
        if (node->right == NULL) {
            BSTNode *left = node->left;
            free(node);
            return left;
        }
        // Caso 3: dois filhos. Copia o SUCESSOR in-order (o menor da
        // subárvore direita) para cá e remove o sucessor lá embaixo.
        BSTNode *succ = find_min(node->right);
        node->value = succ->value;
        node->right = remove_rec(node->right, succ->value, removed);
    }
    return node;
}

bool bst_remove(BST *t, int value) {
    bool removed = false;
    t->root = remove_rec(t->root, value, &removed);
    if (removed) {
        t->size--;
    }
    return removed;
}
// end snippet remove

// start snippet height
static size_t height_rec(const BSTNode *node) {
    if (node == NULL) {
        return 0;
    }
    size_t l = height_rec(node->left);
    size_t r = height_rec(node->right);
    return 1 + (l > r ? l : r);
}

size_t bst_height(const BST *t) {
    return height_rec(t->root);
}
// end snippet height

// start snippet traversals
// Os três percursos em profundidade diferem APENAS na posição do visit():
static void preorder_rec(const BSTNode *n, VisitFn visit, void *ctx) {
    if (n == NULL)
        return;
    visit(n->value, ctx); // raiz primeiro
    preorder_rec(n->left, visit, ctx);
    preorder_rec(n->right, visit, ctx);
}
static void inorder_rec(const BSTNode *n, VisitFn visit, void *ctx) {
    if (n == NULL)
        return;
    inorder_rec(n->left, visit, ctx);
    visit(n->value, ctx); // raiz no meio → sai em ordem CRESCENTE
    inorder_rec(n->right, visit, ctx);
}
static void postorder_rec(const BSTNode *n, VisitFn visit, void *ctx) {
    if (n == NULL)
        return;
    postorder_rec(n->left, visit, ctx);
    postorder_rec(n->right, visit, ctx);
    visit(n->value, ctx); // raiz por último
}
// end snippet traversals

void bst_preorder(const BST *t, VisitFn visit, void *ctx) {
    preorder_rec(t->root, visit, ctx);
}
void bst_inorder(const BST *t, VisitFn visit, void *ctx) {
    inorder_rec(t->root, visit, ctx);
}
void bst_postorder(const BST *t, VisitFn visit, void *ctx) {
    postorder_rec(t->root, visit, ctx);
}

// start snippet bfs
// Percurso em largura (BFS): visita nível a nível, usando uma FILA de
// ponteiros — a mesma ideia FIFO do capítulo 8.
void bst_levelorder(const BST *t, VisitFn visit, void *ctx) {
    if (t->root == NULL) {
        return;
    }
    const BSTNode **queue = malloc(t->size * sizeof(*queue));
    if (queue == NULL) {
        return;
    }
    size_t head = 0, tail = 0;
    queue[tail++] = t->root; // enfileira a raiz
    while (head < tail) {
        const BSTNode *node = queue[head++]; // desenfileira a frente
        visit(node->value, ctx);
        if (node->left != NULL) {
            queue[tail++] = node->left; // enfileira os filhos
        }
        if (node->right != NULL) {
            queue[tail++] = node->right;
        }
    }
    free(queue);
}
// end snippet bfs

static void free_rec(BSTNode *node) {
    if (node == NULL) {
        return;
    }
    free_rec(node->left); // libera em pós-ordem: filhos antes do pai
    free_rec(node->right);
    free(node);
}

void bst_free(BST *t) {
    free_rec(t->root);
    t->root = NULL;
    t->size = 0;
}

size_t bst_size(const BST *t) {
    return t->size;
}
