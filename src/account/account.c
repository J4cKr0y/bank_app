#include "account.h"
#include <string.h> // Nécessaire pour copier le nom (strncpy)

Account create_account(int id, const char* owner) {
    Account new_account;

    // 1. Assigner l'ID
    new_account.id = id;

    // 2. Initialiser le solde à 0
    new_account.balance = 0.0;

    // 3. Copier le nom du propriétaire
    // On utilise strncpy pour éviter de dépasser la taille du tableau 'owner' (sécurité).
    // sizeof(new_account.owner) - 1 laisse une place pour le caractère de fin de chaîne '\0'.
    strncpy(new_account.owner, owner, sizeof(new_account.owner) - 1);
    
    // On s'assure que la chaîne est bien terminée proprement.
    new_account.owner[sizeof(new_account.owner) - 1] = '\0';

    return new_account;
}
