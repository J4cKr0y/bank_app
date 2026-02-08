#include "catch.hpp"
#include <cstdio> // Pour remove() (supprimer le fichier après le test)
#include <cstring>

extern "C" {
    #include "persistence/storage_interface.h"
    #include "persistence/csv_driver.h"
    #include "account/account.h"
}

TEST_CASE("CSV Driver saves and loads accounts correctly", "[storage][csv]") {
    // GIVEN : Un fichier temporaire et quelques comptes
    const char* filename = "test_db.csv";
    
    // On crée le driver CSV
    StorageDriver storage = create_csv_driver(filename);

    Account accounts_to_save[2];
    accounts_to_save[0] = create_account(1, "Batman");
    deposit(&accounts_to_save[0], 1000.0);
    
    accounts_to_save[1] = create_account(2, "Robin");
    // Robin a 0.0

    // WHEN : On sauvegarde (Save)
    bool save_result = storage.save(storage.context, accounts_to_save, 2);
    REQUIRE(save_result == true);

    // ... On efface la mémoire pour être sûr qu'on ne triche pas ...
    Account accounts_loaded[10]; 
    int loaded_count = 0;

    // AND : On recharge (Load)
    loaded_count = storage.load(storage.context, accounts_loaded, 10);

    // THEN : On doit retrouver nos petits
    REQUIRE(loaded_count == 2);
    
    REQUIRE(accounts_loaded[0].id == 1);
    REQUIRE(strcmp(accounts_loaded[0].owner, "Batman") == 0);
    REQUIRE(accounts_loaded[0].balance == 1000.0);

    REQUIRE(accounts_loaded[1].id == 2);
    REQUIRE(strcmp(accounts_loaded[1].owner, "Robin") == 0);

    // Nettoyage : On supprime le fichier de test
    remove(filename);
}
