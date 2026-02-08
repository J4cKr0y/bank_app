#ifndef TRANSACTION_H
#define TRANSACTION_H

// Enumération : C'est une liste de possibilités.
// Une transaction ne peut être QUE soit un DEPOT, soit un RETRAIT.
typedef enum {
    DEPOSIT,   // 0
    WITHDRAWAL // 1
} TransactionType;

// La structure "Ticket de caisse"
typedef struct {
    int id;               // Numéro unique du ticket
    TransactionType type; // Est-ce un dépôt ou un retrait ?
    double amount;        // Le montant
} Transaction;

// Fonction pour fabriquer un nouveau ticket
Transaction create_transaction(int id, TransactionType type, double amount);

#endif // TRANSACTION_H
