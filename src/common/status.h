#ifndef STATUS_H
#define STATUS_H

typedef enum {
    STATUS_SUCCESS = 0,         // Tout va bien
    
    // Erreurs liées aux comptes
    ERR_ACCOUNT_NOT_FOUND,      // ID introuvable
    ERR_ACCOUNT_FULL,           // Plus de place en mémoire
    ERR_INVALID_AMOUNT,         // Montant négatif
    ERR_INSUFFICIENT_FUNDS,     // Pas assez d'argent
    
    // Erreurs liées à la sécurité
    ERR_AUTH_FAILED,            // Mauvais PIN
    
    // Erreurs système / IO
    ERR_DB_WRITE_FAILED,        // Impossible d'écrire le fichier
    ERR_DB_READ_FAILED,         // Fichier corrompu ou absent
    
    // Erreurs génériques
    ERR_UNKNOWN                 // Cas imprévu
} BankStatus;

// Une fonction pour transformer le code (ex: 3) en texte (ex: "Fonds insuffisants")
// Très utile pour le main.c !
const char* get_status_message(BankStatus status);

#endif // STATUS_H