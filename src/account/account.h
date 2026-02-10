#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <stdbool.h>
// On inclut la définition des transactions pour pouvoir les utiliser ici
#include "../transaction/transaction.h" 

#define MAX_HISTORY 100 // On limite l'historique à 100 opérations pour l'instant

typedef struct {
    int id;
    char owner[100];
    double balance;
    unsigned long pin_hash;
    
    // Un tableau qui stocke les tickets. C'est le carnet de chèques.
    Transaction history[MAX_HISTORY]; 
    // Un compteur pour savoir combien de pages du carnet sont remplies.
    int transaction_count;
    // ----------------
} Account;

Account create_account(int id, const char* owner, const char* pin); 

// Ajoute un montant au solde du compte.
// Prend un pointeur (Account*) pour modifier la structure originale.
void deposit(Account* account, double amount);

// Tente de retirer un montant.
// Retourne true si succès, false si fonds insuffisants ou montant invalide.
bool withdraw(Account* account, double amount);

#endif // ACCOUNT_H
