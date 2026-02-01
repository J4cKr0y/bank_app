#include "account.h"
#include <string.h>

Account create_account(int id, const char* owner) {
    Account new_account;
    new_account.id = id;
    new_account.balance = 0.0;
    strncpy(new_account.owner, owner, sizeof(new_account.owner) - 1);
    new_account.owner[sizeof(new_account.owner) - 1] = '\0';
    return new_account;
}

void deposit(Account* account, double amount) {
    // On vérifie que le montant est positif
    if (amount > 0) {
        // On accède au champ via la flèche '->' car 'account' est un pointeur
        account->balance += amount;
    }
}

bool withdraw(Account* account, double amount) {
    // Vérification de sécurité : montant négatif ou nul
    if (amount <= 0) {
        return false;
    }

    // Vérification des fonds : est-ce qu'on a assez d'argent ?
    if (account->balance >= amount) {
        account->balance -= amount;
        return true; // Succès
    }

    return false; // Échec (Fonds insuffisants)
}
