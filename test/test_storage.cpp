#include "catch.hpp"
#include <cstdio>
#include <cstring>

extern "C" {
    #include "persistence/storage_interface.h"
    #include "persistence/csv_driver.h"
    #include "account/account.h"
}

TEST_CASE("CSV Driver saves and loads accounts correctly", "[storage][csv]") {
    const char* filename = "test_db.csv";

    StorageDriver storage = create_csv_driver(filename);

    Account accounts_to_save[2];
    accounts_to_save[0] = create_account(1, "Batman", "9999");
    deposit(&accounts_to_save[0], 1000.0);

    accounts_to_save[1] = create_account(2, "Robin", "8888");

    // WHEN : On sauvegarde
    REQUIRE(storage.save(storage.context, accounts_to_save, 2) == true);

    // Libération des comptes sources
    free_account(&accounts_to_save[0]);
    free_account(&accounts_to_save[1]);

    // AND : On recharge
    Account accounts_loaded[10];
    int loaded_count = storage.load(storage.context, accounts_loaded, 10);

    // THEN : On doit retrouver nos petits
    REQUIRE(loaded_count == 2);

    REQUIRE(accounts_loaded[0].id == 1);
    REQUIRE(strcmp(accounts_loaded[0].owner, "Batman") == 0);
    REQUIRE(accounts_loaded[0].balance == 1000.0);

    REQUIRE(accounts_loaded[1].id == 2);
    REQUIRE(strcmp(accounts_loaded[1].owner, "Robin") == 0);

    // Libération des comptes chargés (csv_load alloue leur history)
    for (int i = 0; i < loaded_count; i++) {
        free_account(&accounts_loaded[i]);
    }

    remove(filename);
}