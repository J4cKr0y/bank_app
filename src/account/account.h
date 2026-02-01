#ifndef ACCOUNT_H
#define ACCOUNT_H

// Définition de la structure d'un Compte
typedef struct {
    int id;             // Identifiant unique du compte
    char owner[100];    // Nom du propriétaire (max 99 caractères + fin de chaîne)
    double balance;     // Solde du compte (attention aux arrondis avec double, mais ok pour débuter)
} Account;

// Fonction pour créer un nouveau compte
// Elle prend l'ID et le nom, et renvoie une structure Account initialisée.
Account create_account(int id, const char* owner);

#endif // ACCOUNT_H
