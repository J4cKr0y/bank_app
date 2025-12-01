#ifndef ACCOUNT_H
#define ACCOUNT_H

// Type de données pour le solde (double pour supporter les centimes)
typedef double AccountBalance;

// --- Structure de Compte Bancaire ---
typedef struct {
    int id;                 // Identifiant du compte 
    AccountBalance balance; // Le solde actuel du compte
    int client_id;          // L'ID du client 
} Account;

// --- Fonctions (Les headers) ---

/*
 * Crée et initialise une nouvelle structure Account.
 * Retourne le pointeur vers la nouvelle structure allouée.
 */
Account* create_account(int id, int client_id, AccountBalance initial_balance);

/*
 * Dépose un montant sur le compte.
 * Retourne 1 en cas de succès, 0 en cas d'échec (montant <= 0).
 */
int deposit(Account* account, AccountBalance amount);

/*
 * Retire un montant du compte.
 * Retourne 1 en cas de succès, 0 en cas d'échec (solde insuffisant ou montant <= 0).
 */
int withdraw(Account* account, AccountBalance amount);

#endif // ACCOUNT_H
