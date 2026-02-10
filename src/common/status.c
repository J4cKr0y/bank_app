#include "status.h"

const char* get_status_message(BankStatus status) {
    switch (status) {
        case STATUS_SUCCESS: return "Opération réussie.";
        case ERR_ACCOUNT_NOT_FOUND: return "Erreur : Compte introuvable.";
        case ERR_ACCOUNT_FULL: return "Erreur : La banque est pleine (mémoire saturée).";
        case ERR_INVALID_AMOUNT: return "Erreur : Le montant est invalide.";
        case ERR_INSUFFICIENT_FUNDS: return "Erreur : Fonds insuffisants pour cette opération.";
        case ERR_AUTH_FAILED: return "Erreur : Authentification échouée (Mauvais PIN).";
        case ERR_DB_WRITE_FAILED: return "Erreur : Échec de la sauvegarde sur disque.";
        default: return "Erreur inconnue.";
    }
}