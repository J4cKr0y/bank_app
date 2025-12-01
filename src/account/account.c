#include <stdlib.h> // Nécessaire pour malloc 
#include "account/account.h" 

/*
 * Implémentation : Crée un compte en allouant la mémoire
 * et en initialisant ses champs.
 */
Account* create_account(int id, int client_id, AccountBalance initial_balance) {
    
    // 1. Allouer l'espace mémoire pour la nouvelle structure Account
    Account* new_account = (Account*)malloc(sizeof(Account));

    // Vérifier si l'allocation a échoué 
    if (new_account == NULL) {
        return NULL;
    }
    
    // 2. Initialiser les champs avec les valeurs fournies
    new_account->id = id;
    new_account->client_id = client_id;
    new_account->balance = initial_balance;
    
    // 3. Renvoyer le pointeur vers la structure initialisée
    return new_account;
}


/*
 * Implémentation : Dépose un montant sur le compte.
 */
int deposit(Account* account, AccountBalance amount) {
    // 1. Vérification de la validité du montant
    // Un montant doit être strictement positif pour être déposé.
    if (amount <= 0) {
        return 0; // Échec
    }
    
    // 2. Vérification de la validité du compte
    if (account == NULL) {
        return 0; // Échec
    }

    // 3. Mise à jour du solde
    account->balance += amount;
    
    return 1; // Succès
}


// Implémentations minimales pour éviter les erreurs du linker
// TO DO //

int withdraw(Account* account, AccountBalance amount) {
    return 0; 
}
