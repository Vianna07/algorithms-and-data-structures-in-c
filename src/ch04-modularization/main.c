/*
 * main.c — Usa o módulo account SÓ pela interface (account.h).
 *
 * Projeto:  PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo: 4 — Modularização (.h/.c)
 * Padrão:   C17 (ISO/IEC 9899:2018)
 */
#include "account.h" // só a interface; não sabe NADA do account.c

#include <stdio.h>

// start snippet main
int main(void) {
    Account a;
    account_init(&a, 10000);   // abre com R$ 100,00 (em centavos)
    account_deposit(&a, 5000); // + R$ 50,00  -> 15000

    bool ok1 = account_withdraw(&a, 12000); // R$ 120,00 -> ok, sobra 3000
    bool ok2 = account_withdraw(&a, 99999); // saldo insuficiente -> negado

    printf("saldo: %ld centavos\n", account_balance(&a));
    printf("saque 120,00: %s | saque 999,99: %s\n", ok1 ? "ok" : "negado",
           ok2 ? "ok" : "negado");
    // can_afford(&a, 100); // ERRO de link: é static, invisível aqui
    return 0;
}
// end snippet main
