#ifndef MEMORY_DRIVER_H
#define MEMORY_DRIVER_H

#include "bank_interface.h"

// Crée et configure le driver "En Mémoire"
BankDriver create_memory_driver();

// Fonction utilitaire pour les tests : remplit la mémoire avec des comptes bidons
void setup_test_accounts(BankDriver* driver);

#endif // MEMORY_DRIVER_H
