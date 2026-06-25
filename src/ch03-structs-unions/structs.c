/*
 * structs.c — Structs, alinhamento/padding e uniões.
 *
 * Projeto:  PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo: 3 — Structs e uniões
 * Padrão:   C17 (ISO/IEC 9899:2018)
 * Build:    gcc/clang -std=c17 -Wall -Wextra -Wpedantic   (ver Makefile)
 */
#include <stddef.h> // offsetof, size_t
#include <stdio.h>

// start snippet struct
// Uma struct AGRUPA campos (de tipos quaisquer) sob um único tipo.
struct Point {
    int x;
    int y;
};

static void struct_basics(void) {
    struct Point p = {3, 4}; // inicialização por ordem
    p.y = 10;                // acesso a campo por '.'

    struct Point *pp = &p;
    pp->x = 7; // por ponteiro, '->' é açúcar para (*pp).x

    printf("Point = (%d, %d)\n", p.x, p.y);                // (7, 10)
    printf("sizeof(Point) = %zu\n", sizeof(struct Point)); // 8
}
// end snippet struct

// start snippet padding
// A ORDEM dos campos importa: o alinhamento insere "buracos" (padding).
struct Padded { // má ordem
    char a;     // offset 0
    int b;      // precisa de offset múltiplo de 4 → 3 bytes de padding antes
    char c;     // offset 8; mais 3 bytes de padding no fim
}; // sizeof = 12

struct Packed { // boa ordem: do maior para o menor
    int b;      // offset 0
    char a;     // offset 4
    char c;     // offset 5; mais 2 bytes de padding no fim
}; // sizeof = 8

static void padding_demo(void) {
    printf("Padded: sizeof=%zu  (a@%zu b@%zu c@%zu)\n", sizeof(struct Padded),
           offsetof(struct Padded, a), offsetof(struct Padded, b),
           offsetof(struct Padded, c));
    printf("Packed: sizeof=%zu   (b@%zu a@%zu c@%zu)\n", sizeof(struct Packed),
           offsetof(struct Packed, b), offsetof(struct Packed, a),
           offsetof(struct Packed, c));
}
// end snippet padding

// start snippet union
// Uma union SOBREPÕE os campos: todos compartilham os mesmos bytes.
union Value {
    int i;
    float f;
    unsigned char bytes[4];
};

static void union_demo(void) {
    union Value v;
    v.i = 1; // escrevemos como int...

    // ...e lemos os bytes crus (little-endian em x86-64: 1 vira [1 0 0 0]).
    printf("union: sizeof=%zu  i=%d  bytes=[%u %u %u %u]\n",
           sizeof(union Value), v.i, v.bytes[0], v.bytes[1], v.bytes[2],
           v.bytes[3]);
    // Só UM membro é válido por vez: ler 'f' aqui reinterpretaria esses bits.
}
// end snippet union

int main(void) {
    struct_basics();
    padding_demo();
    union_demo();
    return 0;
}
