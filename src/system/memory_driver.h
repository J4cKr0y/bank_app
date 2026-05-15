#ifndef MEMORY_DRIVER_H
#define MEMORY_DRIVER_H

#include "bank_interface.h"
#include "../account/account.h"

// Déplacé ici pour que le main.c puisse "voir" le type de données
typedef struct {
    // --- Base de données dynamique ---
    Account* accounts; 
    int count;
    int capacity;
} MemoryDatabase;

// Crée et configure le driver "En Mémoire"
BankDriver create_memory_driver();

// Fonction utilitaire pour les tests : remplit la mémoire avec des comptes bidons
void setup_test_accounts(BankDriver* driver);

// Permet d'ajouter un compte existant dans la mémoire du driver (utile au chargement)
bool driver_add_account(BankDriver* driver, Account account);

// Fonction de nettoyage global
void free_memory_driver(BankDriver* driver);

#endif // MEMORY_DRIVER_H
