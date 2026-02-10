#ifndef MEMORY_DRIVER_H
#define MEMORY_DRIVER_H

#include "bank_interface.h"
#include "../account/account.h"

#define MAX_ACCOUNTS 100 // Augmentons un peu la limite au passage

// Déplacé ici pour que le main.c puisse "voir" le type de données
typedef struct {
    Account accounts[MAX_ACCOUNTS];
    int count;
} MemoryDatabase;

// Crée et configure le driver "En Mémoire"
BankDriver create_memory_driver();

// Fonction utilitaire pour les tests : remplit la mémoire avec des comptes bidons
void setup_test_accounts(BankDriver* driver);

// Permet d'ajouter un compte existant dans la mémoire du driver (utile au chargement)
void driver_add_account(BankDriver* driver, Account account);

#endif // MEMORY_DRIVER_H
