#include "catch.hpp"

// On inclut le header (qui n'existe pas encore)
extern "C" {
    #include "transaction/transaction.h"
}

TEST_CASE("Transaction structure holds correct data", "[transaction]") {
    // GIVEN : Des données de transaction
    int id = 1;
    double amount = 50.0;
    TransactionType type = DEPOSIT; // On invente un type 'DEPOSIT'

    // WHEN : On crée une transaction (fonction à inventer)
    Transaction t = create_transaction(id, type, amount);

    // THEN : La structure contient les bonnes infos
    REQUIRE(t.id == id);
    REQUIRE(t.type == type);
    REQUIRE(t.amount == amount);
}
