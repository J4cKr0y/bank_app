#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <stdbool.h>
// On inclut la définition des transactions pour pouvoir les utiliser ici
#include "../transaction/transaction.h" 

#include "../common/status.h"

typedef struct {
    int id;
    char owner[100];
    double balance;
    unsigned long pin_hash;
    
    // --- Historique dynamique ---
    Transaction* history; 
    int transaction_count;
    int history_capacity;
} Account;

Account create_account(int id, const char* owner, const char* pin); 

// Ajoute un montant au solde du compte.
// Prend un pointeur (Account*) pour modifier la structure originale.
void deposit(Account* account, double amount);

// Tente de retirer un montant.
// Retourne true si succès, false si fonds insuffisants ou montant invalide.
BankStatus withdraw(Account* account, double amount);

// Fonction de nettoyage
void free_account(Account* account);

#endif // ACCOUNT_H
