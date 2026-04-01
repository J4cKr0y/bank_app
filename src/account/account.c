#include "account.h"
#include <stdlib.h>
#include <string.h>
#include "../auth/auth.h"

Account create_account(int id, const char* owner, const char* pin) {
    Account new_account;

    // 1. SECURITE : On met toute la structure à zéro
    memset(&new_account, 0, sizeof(Account));

    new_account.id = id;
    new_account.balance = 0.0;
    new_account.transaction_count = 0;

    // 2. Utilisation du hachage pour le PIN
    new_account.pin_hash = hash_pin(pin);

    // 3. Copie sécurisée du nom du propriétaire
    strncpy(new_account.owner, owner, sizeof(new_account.owner) - 1);
    // new_account.owner[sizeof(new_account.owner) - 1] = '\0';

    // 4. ALLOCATION INITIALE de l'historique
    new_account.history_capacity = 10;
    new_account.history = (Transaction*)malloc(new_account.history_capacity * sizeof(Transaction));

    return new_account;
}

// FONCTION DE NETTOYAGE — libère la mémoire allouée dynamiquement
void free_account(Account* account) {
    if (account->history != NULL) {
        free(account->history);
        account->history = NULL;
        account->history_capacity = 0;
        account->transaction_count = 0;
    }
}

// Agrandit l'historique si nécessaire (doublement de capacité via realloc).
// Retourne 1 en cas de succès, 0 en cas d'échec d'allocation.
static int grow_history_if_needed(Account* account) {
    if (account->transaction_count >= account->history_capacity) {
        int new_capacity = account->history_capacity * 2;
        Transaction* temp = (Transaction*)realloc(
            account->history,
            new_capacity * sizeof(Transaction)
        );
        if (temp == NULL) {
            // Échec critique : la mémoire disponible est insuffisante
            return 0;
        }
        account->history = temp;
        account->history_capacity = new_capacity;
    }
    return 1;
}

void deposit(Account* account, double amount) {
    if (amount <= 0) {
        return;
    }

    account->balance += amount;

    // Agrandir l'historique si nécessaire, puis enregistrer la transaction
    if (!grow_history_if_needed(account)) {
        return; // Échec d'allocation : on conserve le solde mais on n'enregistre pas
    }

    int new_id = account->transaction_count + 1;
    Transaction t = create_transaction(new_id, DEPOSIT, amount);
    account->history[account->transaction_count] = t;
    account->transaction_count++;
}

BankStatus withdraw(Account* account, double amount) {
    // Validation 1 : Le montant
    if (amount <= 0) {
        return ERR_INVALID_AMOUNT;
    }

    // Validation 2 : Le solde
    if (account->balance < amount) {
        return ERR_INSUFFICIENT_FUNDS;
    }

    account->balance -= amount;

    // Agrandir l'historique si nécessaire, puis enregistrer la transaction
    if (!grow_history_if_needed(account)) {
        return STATUS_SUCCESS; // Retrait effectué, mais non enregistré (RAM pleine)
    }

    int new_id = account->transaction_count + 1;
    Transaction t = create_transaction(new_id, WITHDRAWAL, amount);
    account->history[account->transaction_count] = t;
    account->transaction_count++;

    return STATUS_SUCCESS;
}