/*
 * account.c — IMPLEMENTAÇÃO do módulo de conta (o "como").
 *
 * Projeto:  PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo: 4 — Modularização (.h/.c)
 * Padrão:   C17 (ISO/IEC 9899:2018)
 */
#include "account.h" // a implementação inclui a própria interface

// start snippet impl
// Helper PRIVADO do módulo: 'static' o torna invisível fora deste .c.
static bool can_afford(const Account *a, long cents) {
    return a->balance_cents >= cents;
}

void account_init(Account *a, long initial_cents) {
    a->balance_cents = initial_cents;
}

void account_deposit(Account *a, long cents) {
    a->balance_cents += cents;
}

bool account_withdraw(Account *a, long cents) {
    if (!can_afford(a, cents)) {
        return false; // saldo insuficiente
    }
    a->balance_cents -= cents;
    return true;
}

long account_balance(const Account *a) {
    return a->balance_cents;
}
// end snippet impl
