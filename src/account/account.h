#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <stdbool.h> // Pour utiliser 'bool', 'true', 'false'

typedef struct {
    int id;
    char owner[100];
    double balance;
} Account;

Account create_account(int id, const char* owner);

// Ajoute un montant au solde du compte.
// Prend un pointeur (Account*) pour modifier la structure originale.
void deposit(Account* account, double amount);

// Tente de retirer un montant.
// Retourne true si succès, false si fonds insuffisants ou montant invalide.
bool withdraw(Account* account, double amount);

#endif // ACCOUNT_H
