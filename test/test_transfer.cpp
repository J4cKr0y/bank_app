#include "catch.hpp"

extern "C" {
    #include "system/bank_interface.h"
    #include "system/memory_driver.h"
    #include "common/status.h"
}

TEST_CASE("Transfer via Interface moves funds correctly", "[transfer][interface]") {
    BankDriver bank = create_memory_driver();
    setup_test_accounts(&bank);

    // Vérifions l'état initial (Alice a 100, Bob a 0)
    REQUIRE(bank.get_balance(bank.context, 1001) == 100.0);
    REQUIRE(bank.get_balance(bank.context, 1002) == 0.0);

    // WHEN : On effectue un virement via l'INTERFACE générique
    REQUIRE(bank.transfer(bank.context, 1001, 1002, 40.0) == STATUS_SUCCESS);

    // THEN : Les soldes sont mis à jour
    REQUIRE(bank.get_balance(bank.context, 1001) == 60.0); // 100 - 40
    REQUIRE(bank.get_balance(bank.context, 1002) == 40.0); // 0 + 40
}

TEST_CASE("Transfer fails if source account has insufficient funds", "[transfer][interface]") {
    BankDriver bank = create_memory_driver();
    setup_test_accounts(&bank);

    // WHEN : Alice essaie de virer 500 (elle n'a que 100)
    REQUIRE(bank.transfer(bank.context, 1001, 1002, 500.0) == ERR_INSUFFICIENT_FUNDS);

    // THEN : Rien ne bouge
    REQUIRE(bank.get_balance(bank.context, 1001) == 100.0);
}