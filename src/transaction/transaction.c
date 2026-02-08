#include "transaction.h"

Transaction create_transaction(int id, TransactionType type, double amount) {
    Transaction t;
    t.id = id;
    t.type = type;
    t.amount = amount;
    return t;
}
