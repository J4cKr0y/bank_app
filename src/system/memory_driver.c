#include "memory_driver.h"
#include "../account/account.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// --- Fonctions internes (cachées) ---

// Trouve un pointeur vers un compte dans la base de données via son ID
static Account* find_account(MemoryDatabase* db, int id) {
    for (int i = 0; i < db->count; i++) {
        if (db->accounts[i].id == id) {
            return &db->accounts[i];
        }
    }
    return NULL; // Pas trouvé
}

// Agrandit le tableau des comptes si nécessaire (doublement de capacité via realloc).
// Retourne 1 en cas de succès, 0 en cas d'échec d'allocation.
static int grow_accounts_if_needed(MemoryDatabase* db) {
    if (db->count >= db->capacity) {
        int new_capacity = db->capacity * 2;
        Account* temp = (Account*)realloc(
            db->accounts,
            new_capacity * sizeof(Account)
        );
        if (temp == NULL) {
            return 0; // Échec critique : RAM pleine
        }
        db->accounts = temp;
        db->capacity = new_capacity;
    }
    return 1;
}

// --- Implémentation des fonctions de l'interface ---

// Implémentation concrète de "get_balance"
static double memory_get_balance(void* context, int id) {
    MemoryDatabase* db = (MemoryDatabase*)context;
    Account* acc = find_account(db, id);
    if (acc) {
        return acc->balance;
    }
    return -1.0; // Code d'erreur (compte introuvable)
}

// Implémentation concrète de "transfer"
static BankStatus memory_transfer(void* context, int from_id, int to_id, double amount) {
    MemoryDatabase* db = (MemoryDatabase*)context;

    Account* source = find_account(db, from_id);
    Account* dest = find_account(db, to_id);

    if (!source) return ERR_ACCOUNT_NOT_FOUND;
    if (!dest)   return ERR_ACCOUNT_NOT_FOUND;

    // On tente le retrait sur la source
    BankStatus result = withdraw(source, amount);

    // Si le retrait a marché, on dépose
    if (result == STATUS_SUCCESS) {
        deposit(dest, amount);
        return STATUS_SUCCESS;
    }

    // Sinon, on renvoie l'erreur du retrait (ex: ERR_INSUFFICIENT_FUNDS)
    return result;
}

// --- Constructeur du Driver ---

BankDriver create_memory_driver() {
    static MemoryDatabase db;
    db.count = 0;

    // ALLOCATION INITIALE du tableau de comptes
    db.capacity = 10;
    db.accounts = (Account*)malloc(db.capacity * sizeof(Account));

    BankDriver driver;
    driver.context = &db;

    driver.get_balance = memory_get_balance;
    driver.transfer    = memory_transfer;

    return driver;
}

// FERMETURE DE LA BANQUE — libère toute la mémoire allouée dynamiquement
void free_memory_driver(BankDriver* driver) {
    MemoryDatabase* db = (MemoryDatabase*)driver->context;
    if (db->accounts != NULL) {
        // On libère d'abord l'historique de CHAQUE compte
        for (int i = 0; i < db->count; i++) {
            free_account(&db->accounts[i]);
        }
        // Puis on libère le grand tableau des comptes
        free(db->accounts);
        db->accounts = NULL;
        db->count    = 0;
        db->capacity = 0;
    }
}

// Fonction d'aide pour les tests (pour peupler la base)
void setup_test_accounts(BankDriver* driver) {
    MemoryDatabase* db = (MemoryDatabase*)driver->context;

    // On libère proprement l'état précédent avant de reset
    free_memory_driver(driver);

    db->capacity = 10;
    db->accounts = (Account*)malloc(db->capacity * sizeof(Account));
    db->count    = 0;

    // Création compte Alice (ID 1001) avec 100€
    Account alice = create_account(1001, "Alice", "1234");
    deposit(&alice, 100.0);
    driver_add_account(driver, alice);

    // Création compte Bob (ID 1002) avec 0€
    Account bob = create_account(1002, "Bob", "0000");
    driver_add_account(driver, bob);
}

// Permet d'ajouter un compte dans la base du driver (utile au chargement)
bool driver_add_account(BankDriver* driver, Account account) {
    MemoryDatabase* db = (MemoryDatabase*)driver->context;

    // 1. SECURITE : Vérifier si l'ID existe déjà
    for (int i = 0; i < db->count; i++) {
        if (db->accounts[i].id == account.id) {
            return false; // ID déjà utilisé !
        }
    }

    // 2. AGRANDISSEMENT DYNAMIQUE si nécessaire (fini la limite de MAX_ACCOUNTS !)
    if (!grow_accounts_if_needed(db)) {
        return false; // RAM pleine
    }

    db->accounts[db->count] = account;
    db->count++;
    return true;
}