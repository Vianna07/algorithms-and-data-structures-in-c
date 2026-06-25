/*
 * huffman.c — Implementação do compactador de Huffman.
 *
 * Projeto:  PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo: 11 — Desafio final: compactador de Huffman
 * Padrão:   C17 (ISO/IEC 9899:2018)
 */
#include "huffman.h"

#include <stdbool.h> // bool
#include <stdint.h>  // uint32_t, uint8_t
#include <stdlib.h>  // malloc, realloc, free, calloc

// ---------------------------------------------------------------------------
// Nó da árvore de Huffman: folha (com um byte) ou interno (com dois filhos).
// ---------------------------------------------------------------------------
typedef struct HuffNode {
    unsigned char byte; // válido só nas folhas
    size_t freq;
    struct HuffNode *left;
    struct HuffNode *right;
} HuffNode;

static HuffNode *leaf_new(unsigned char byte, size_t freq) {
    HuffNode *n = malloc(sizeof(HuffNode));
    if (n != NULL) {
        n->byte = byte;
        n->freq = freq;
        n->left = NULL;
        n->right = NULL;
    }
    return n;
}

static HuffNode *internal_new(HuffNode *left, HuffNode *right) {
    HuffNode *n = malloc(sizeof(HuffNode));
    if (n != NULL) {
        n->byte = 0;
        n->freq = left->freq + right->freq;
        n->left = left;
        n->right = right;
    }
    return n;
}

static void free_tree(HuffNode *node) {
    if (node == NULL) {
        return;
    }
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

// ---------------------------------------------------------------------------
// Min-heap de nós por frequência: é o heap do capítulo 10, agora guardando
// ponteiros para HuffNode e ordenando pelo campo freq.
// ---------------------------------------------------------------------------
typedef struct {
    HuffNode **data;
    size_t size;
    size_t cap;
} NodeHeap;

static bool nh_reserve(NodeHeap *h, size_t need) {
    if (need <= h->cap) {
        return true;
    }
    size_t nc = h->cap ? h->cap * 2 : 16;
    while (nc < need) {
        nc *= 2;
    }
    HuffNode **nd = realloc(h->data, nc * sizeof(*nd));
    if (nd == NULL) {
        return false;
    }
    h->data = nd;
    h->cap = nc;
    return true;
}

static void nh_swap(HuffNode **a, HuffNode **b) {
    HuffNode *t = *a;
    *a = *b;
    *b = t;
}

static bool nh_push(NodeHeap *h, HuffNode *node) {
    if (!nh_reserve(h, h->size + 1)) {
        return false;
    }
    size_t i = h->size++;
    h->data[i] = node;
    while (i > 0) { // sift-up por frequência
        size_t p = (i - 1) / 2;
        if (h->data[i]->freq >= h->data[p]->freq) {
            break;
        }
        nh_swap(&h->data[i], &h->data[p]);
        i = p;
    }
    return true;
}

static HuffNode *nh_pop(NodeHeap *h) {
    if (h->size == 0) {
        return NULL;
    }
    HuffNode *min = h->data[0];
    h->data[0] = h->data[--h->size];
    size_t i = 0;
    for (;;) { // sift-down por frequência
        size_t l = 2 * i + 1, r = 2 * i + 2, s = i;
        if (l < h->size && h->data[l]->freq < h->data[s]->freq) {
            s = l;
        }
        if (r < h->size && h->data[r]->freq < h->data[s]->freq) {
            s = r;
        }
        if (s == i) {
            break;
        }
        nh_swap(&h->data[i], &h->data[s]);
        i = s;
    }
    return min;
}

// start snippet histogram
// (a) Histograma: conta quantas vezes cada um dos 256 bytes aparece.
static void count_freq(const unsigned char *data, size_t n, size_t freq[256]) {
    for (int i = 0; i < 256; i++) {
        freq[i] = 0;
    }
    for (size_t i = 0; i < n; i++) {
        freq[data[i]]++;
    }
}
// end snippet histogram

// start snippet buildtree
// (b) Árvore de Huffman: enquanto houver mais de um nó, retire os DOIS de menor
// frequência (o heap entrega isso) e junte-os sob um pai cuja frequência é a
// soma. O último nó que sobra é a raiz. Os mais frequentes ficam mais rasos.
static HuffNode *build_tree(const size_t freq[256]) {
    NodeHeap heap = {0};
    for (int b = 0; b < 256; b++) {
        if (freq[b] > 0) {
            nh_push(&heap, leaf_new((unsigned char)b, freq[b]));
        }
    }
    if (heap.size == 0) {
        free(heap.data);
        return NULL; // entrada vazia
    }
    if (heap.size == 1) {
        // Um único símbolo distinto: garante um código de 1 bit com uma folha
        // "fantasma" (que nunca é codificada, mas dá forma à árvore).
        HuffNode *only = nh_pop(&heap);
        nh_push(&heap, only);
        nh_push(&heap, leaf_new(only->byte, 0));
    }
    while (heap.size > 1) {
        HuffNode *a = nh_pop(&heap);
        HuffNode *b = nh_pop(&heap);
        nh_push(&heap, internal_new(a, b));
    }
    HuffNode *root = nh_pop(&heap);
    free(heap.data);
    return root;
}
// end snippet buildtree

// start snippet gencodes
// (c) Dicionário: desce a árvore acumulando bits (0 = esquerda, 1 = direita).
// Cada folha recebe seu código — guardado como os `len` bits baixos de `bits`.
typedef struct {
    uint32_t bits;
    uint8_t len;
} Code;

static void gen_codes(const HuffNode *node, uint32_t bits, uint8_t len,
                      Code table[256]) {
    if (node->left == NULL && node->right == NULL) { // folha
        table[node->byte].bits = bits;
        table[node->byte].len = (len == 0) ? 1 : len; // raiz-folha → 1 bit
        return;
    }
    gen_codes(node->left, (bits << 1) | 0u, (uint8_t)(len + 1), table);
    gen_codes(node->right, (bits << 1) | 1u, (uint8_t)(len + 1), table);
}
// end snippet gencodes

// ---------------------------------------------------------------------------
// (d) Manipulação de bits: empacotar bits soltos em bytes e desempacotá-los.
// ---------------------------------------------------------------------------
typedef struct {
    unsigned char *bytes;
    size_t size;
    size_t cap;
    unsigned acc; // acumulador (até 8 bits pendentes)
    int nbits;
} BitWriter;

static bool bw_reserve(BitWriter *w, size_t need) {
    if (need <= w->cap) {
        return true;
    }
    size_t nc = w->cap ? w->cap * 2 : 64;
    while (nc < need) {
        nc *= 2;
    }
    unsigned char *nd = realloc(w->bytes, nc);
    if (nd == NULL) {
        return false;
    }
    w->bytes = nd;
    w->cap = nc;
    return true;
}

// start snippet bitwriter
// Escreve UM bit. Acumula 8 bits e só então grava um byte (MSB primeiro).
static bool bw_put_bit(BitWriter *w, int bit) {
    w->acc = (w->acc << 1) | (unsigned)(bit & 1);
    w->nbits++;
    if (w->nbits == 8) {
        if (!bw_reserve(w, w->size + 1)) {
            return false;
        }
        w->bytes[w->size++] = (unsigned char)w->acc;
        w->acc = 0;
        w->nbits = 0;
    }
    return true;
}

// No fim, grava o byte parcial preenchendo o resto com zeros (padding).
static bool bw_flush(BitWriter *w) {
    if (w->nbits > 0) {
        w->acc <<= (8 - w->nbits);
        if (!bw_reserve(w, w->size + 1)) {
            return false;
        }
        w->bytes[w->size++] = (unsigned char)w->acc;
        w->acc = 0;
        w->nbits = 0;
    }
    return true;
}
// end snippet bitwriter

static bool bw_put_byte(BitWriter *w, unsigned char b) {
    for (int i = 7; i >= 0; i--) {
        if (!bw_put_bit(w, (b >> i) & 1)) {
            return false;
        }
    }
    return true;
}

typedef struct {
    const unsigned char *bytes;
    size_t size;
    size_t pos;
    int nbits;
} BitReader;

// start snippet bitreader
// Lê UM bit (MSB primeiro). Devolve 0/1, ou -1 quando os dados acabam.
static int br_get_bit(BitReader *r) {
    if (r->pos >= r->size) {
        return -1;
    }
    int bit = (r->bytes[r->pos] >> (7 - r->nbits)) & 1;
    r->nbits++;
    if (r->nbits == 8) {
        r->pos++;
        r->nbits = 0;
    }
    return bit;
}
// end snippet bitreader

static int br_get_byte(BitReader *r) {
    int b = 0;
    for (int i = 0; i < 8; i++) {
        int bit = br_get_bit(r);
        if (bit < 0) {
            return -1;
        }
        b = (b << 1) | bit;
    }
    return b;
}

// start snippet serialize
// A árvore vai no cabeçalho, em pré-ordem: '1' + byte para folha, '0' para
// nó interno (e então recursão). É assim que a descompressão a reconstrói.
static bool write_tree(BitWriter *w, const HuffNode *node) {
    if (node->left == NULL && node->right == NULL) {
        return bw_put_bit(w, 1) && bw_put_byte(w, node->byte);
    }
    return bw_put_bit(w, 0) && write_tree(w, node->left) &&
           write_tree(w, node->right);
}

static HuffNode *read_tree(BitReader *r) {
    int tag = br_get_bit(r);
    if (tag == 1) {
        int byte = br_get_byte(r);
        return (byte < 0) ? NULL : leaf_new((unsigned char)byte, 0);
    }
    if (tag == 0) {
        HuffNode *left = read_tree(r);
        HuffNode *right = read_tree(r);
        if (left == NULL || right == NULL) {
            free_tree(left);
            free_tree(right);
            return NULL;
        }
        return internal_new(left, right);
    }
    return NULL; // bits acabaram
}
// end snippet serialize

// start snippet compress
Compressed huff_compress(const unsigned char *data, size_t n) {
    Compressed result = {0};
    result.original_len = n;

    size_t freq[256];
    count_freq(data, n, freq);
    HuffNode *root = build_tree(freq);
    if (root == NULL) {
        return result; // entrada vazia: comprimido vazio
    }

    Code table[256] = {0};
    gen_codes(root, 0, 0, table);

    BitWriter w = {0};
    write_tree(&w, root);            // (cabeçalho) a árvore
    for (size_t i = 0; i < n; i++) { // (payload) o código de cada byte
        Code code = table[data[i]];
        for (int b = code.len - 1; b >= 0; b--) {
            bw_put_bit(&w, (int)((code.bits >> b) & 1u));
        }
    }
    bw_flush(&w);
    free_tree(root);

    result.bytes = w.bytes;
    result.size = w.size;
    return result;
}
// end snippet compress

// start snippet decompress
unsigned char *huff_decompress(const Compressed *c, size_t *out_len) {
    if (out_len != NULL) {
        *out_len = c->original_len;
    }
    if (c->original_len == 0) {
        return calloc(1, 1); // vazio, mas não-nulo
    }

    BitReader r = {c->bytes, c->size, 0, 0};
    HuffNode *root = read_tree(&r); // reconstrói a árvore do cabeçalho
    if (root == NULL) {
        return NULL;
    }

    unsigned char *out = malloc(c->original_len);
    if (out == NULL) {
        free_tree(root);
        return NULL;
    }
    for (size_t i = 0; i < c->original_len; i++) {
        const HuffNode *node = root;
        while (node->left != NULL || node->right != NULL) { // desce até a folha
            int bit = br_get_bit(&r);
            if (bit < 0) {
                free(out);
                free_tree(root);
                return NULL;
            }
            node = (bit == 0) ? node->left : node->right;
        }
        out[i] = node->byte;
    }
    free_tree(root);
    return out;
}
// end snippet decompress

void huff_free_compressed(Compressed *c) {
    free(c->bytes);
    c->bytes = NULL;
    c->size = 0;
    c->original_len = 0;
}
