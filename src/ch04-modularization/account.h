/*
 * account.h — INTERFACE de um módulo de conta (o "o quê").
 *
 * Projeto:  PIESC — Estruturas de Dados e Algoritmos em C
 * Capítulo: 4 — Modularização (.h/.c)
 * Padrão:   C17 (ISO/IEC 9899:2018)
 */
#ifndef ACCOUNT_H // header guard: impede incluir este arquivo duas vezes
#define ACCOUNT_H

#include <stdbool.h> // bool

// Tipo público: saldo em CENTAVOS (inteiro) — nunca use float para dinheiro.
typedef struct {
    long balance_cents;
} Account;

// O contrato que o módulo oferece. Só isto o resto do programa enxerga.
void account_init(Account *a, long initial_cents);
void account_deposit(Account *a, long cents);
bool account_withdraw(Account *a, long cents); // false se saldo insuficiente
long account_balance(const Account *a);

#endif // ACCOUNT_H
