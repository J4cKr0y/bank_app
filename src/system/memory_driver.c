#include "memory_driver.h"
#include "../account/account.h"
#include <stdio.h>

// --- Fonctions internes (cachées) ---

// Trouve un pointeur vers un compte dans la base de données via son ID
static Account* find_account(MemoryDatabase* db, int id) {
    for (int i = 0; i < db->count; i++) {
        if (db->accounts[i].id == id) {
            return &db->accounts[i]; // On retourne l'adresse du compte trouvé
        }
    }
    return NULL; // Pas trouvé
}

// --- Implémentation des fonctions de l'interface ---

// Implémentation concrète de "get_balance"
static double memory_get_balance(void* context, int id) {
    MemoryDatabase* db = (MemoryDatabase*)context; // On "cast" le void* en notre type réel
    Account* acc = find_account(db, id);
    if (acc) {
        return acc->balance;
    }
    return -1.0; // Code d'erreur (compte introuvable)
}

// Implémentation concrète de "transfer"
static bool memory_transfer(void* context, int from_id, int to_id, double amount) {
    MemoryDatabase* db = (MemoryDatabase*)context;
    
    Account* source = find_account(db, from_id);
    Account* dest = find_account(db, to_id);

    // Vérifications de base
    if (!source || !dest) return false; // Un des comptes n'existe pas

    // On utilise nos fonctions existantes (Réutilisation du code !)
    // 1. On essaie de retirer de la source
    if (withdraw(source, amount)) {
        // 2. Si ça marche, on dépose sur la destination
        deposit(dest, amount);
        return true;
    }

    return false; // Fonds insuffisants
}

// --- Constructeur du Driver ---

BankDriver create_memory_driver() {
    // On alloue la base de données (static pour qu'elle persiste pendant le test)
    // Note : Dans un vrai programme, on utiliserait malloc/free.
    static MemoryDatabase db; 
    db.count = 0;

    BankDriver driver;
    driver.context = &db; // On branche notre base de données
    
    // On assigne les fonctions
    driver.get_balance = memory_get_balance;
    driver.transfer = memory_transfer;

    return driver;
}

// Fonction d'aide pour les tests (pour peupler la base)
void setup_test_accounts(BankDriver* driver) {
    MemoryDatabase* db = (MemoryDatabase*)driver->context;
    
    // On reset la base pour le test
    db->count = 0;

    // Création compte Alice (ID 1001) avec 100€
    Account alice = create_account(1001, "Alice", "1234");
    deposit(&alice, 100.0);
    db->accounts[db->count++] = alice;

    // Création compte Bob (ID 1002) avec 0€
    Account bob = create_account(1002, "Bob", "0000");
    db->accounts[db->count++] = bob;
}

// Permet d'ajouter un compte existant dans la mémoire du driver (utile au chargement)
void driver_add_account(BankDriver* driver, Account account) {
    MemoryDatabase* db = (MemoryDatabase*)driver->context;
    if (db->count < MAX_ACCOUNTS) {
        db->accounts[db->count] = account; // Copie le compte
        db->count++;
    }
}