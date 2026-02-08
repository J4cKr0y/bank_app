#include "account.h"
#include <string.h>

Account create_account(int id, const char* owner) {
    Account new_account;
    new_account.id = id;
    new_account.balance = 0.0;
    
    // Initialiser le compteur de transactions à 0 (historique vide)
    new_account.transaction_count = 0;

    strncpy(new_account.owner, owner, sizeof(new_account.owner) - 1);
    new_account.owner[sizeof(new_account.owner) - 1] = '\0';
    return new_account;
}

void deposit(Account* account, double amount) {
    if (amount > 0) {
        account->balance += amount;

        // --- ENREGISTREMENT DE LA TRANSACTION ---
        // 1. Vérifier qu'on a de la place dans le carnet
        if (account->transaction_count < MAX_HISTORY) {
            
            // 2. Créer le ticket (ID = position actuelle + 1)
            int new_id = account->transaction_count + 1;
            Transaction t = create_transaction(new_id, DEPOSIT, amount);

            // 3. Mettre le ticket dans la case actuelle du tableau
            account->history[account->transaction_count] = t;

            // 4. Passer à la case suivante pour la prochaine fois
            account->transaction_count++;
        }
    }
}

bool withdraw(Account* account, double amount) {
    if (amount <= 0) return false;

    if (account->balance >= amount) {
        account->balance -= amount;

        // --- ENREGISTREMENT DE LA TRANSACTION ---
        if (account->transaction_count < MAX_HISTORY) {
            int new_id = account->transaction_count + 1;
            // Notez le type WITHDRAWAL ici
            Transaction t = create_transaction(new_id, WITHDRAWAL, amount);
            
            account->history[account->transaction_count] = t;
            account->transaction_count++;
        }
        return true;
    }
    return false;
}
