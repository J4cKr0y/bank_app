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

// Implémentations minimales pour éviter les erreurs du linker
// TO DO //
int deposit(Account* account, AccountBalance amount) {
    return 0; 
}

int withdraw(Account* account, AccountBalance amount) {
    return 0; 
}
