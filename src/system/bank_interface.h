#ifndef BANK_INTERFACE_H
#define BANK_INTERFACE_H

#include <stdbool.h>
#include "../common/status.h"

// Définition générique du "Driver".
// C'est comme une télécommande universelle.
typedef struct {
    // Le "Contexte" : C'est la base de données. 
    // void* veut dire "N'importe quoi". Pour nous ce sera un tableau, 
    // pour une API ce sera peut-être une URL ou un Token de connexion.
    void* context; 

    // --- Les boutons de la télécommande (Pointeurs de fonctions) ---

    // Fonction pour obtenir un solde à partir d'un ID
    double (*get_balance)(void* context, int account_id);

    // Fonction pour transférer de l'argent entre deux IDs
    BankStatus (*transfer)(void* context, int from_id, int to_id, double amount);
} BankDriver;

#endif // BANK_INTERFACE_H
