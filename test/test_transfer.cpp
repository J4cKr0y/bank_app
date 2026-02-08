#include "catch.hpp"

extern "C" {
    #include "system/bank_interface.h"
    #include "system/memory_driver.h" // On a besoin du constructeur du driver
}

TEST_CASE("Transfer via Interface moves funds correctly", "[transfer][interface]") {
    // GIVEN : On initialise notre "Système Maison" (Driver Mémoire)
    // C'est ici qu'on "branche" notre système actuel.
    BankDriver bank = create_memory_driver();

    // On prépare le terrain (on triche un peu pour injecter des comptes dans notre mémoire)
    // Dans un vrai système, on utiliserait bank.create_account(...)
    setup_test_accounts(&bank); 

    // Vérifions l'état initial (Alice a 100, Bob a 0)
    REQUIRE(bank.get_balance(bank.context, 1001) == 100.0); // Alice
    REQUIRE(bank.get_balance(bank.context, 1002) == 0.0);   // Bob

    // WHEN : On effectue un virement via l'INTERFACE générique
    bool result = bank.transfer(bank.context, 1001, 1002, 40.0);

    // THEN : Le virement réussit et les soldes sont mis à jour
    REQUIRE(result == true);
    REQUIRE(bank.get_balance(bank.context, 1001) == 60.0); // 100 - 40
    REQUIRE(bank.get_balance(bank.context, 1002) == 40.0); // 0 + 40
}

TEST_CASE("Transfer fails if source account has insufficient funds", "[transfer][interface]") {
    BankDriver bank = create_memory_driver();
    setup_test_accounts(&bank);

    // WHEN : Alice essaie de virer 500 (elle n'a que 100)
    bool result = bank.transfer(bank.context, 1001, 1002, 500.0);

    // THEN : Échec et rien ne bouge
    REQUIRE(result == false);
    REQUIRE(bank.get_balance(bank.context, 1001) == 100.0);
}
