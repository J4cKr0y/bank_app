#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

extern "C" {
    #include "../src/account/account.h"
    #include "../src/system/memory_driver.h"
}

TEST_CASE("Allocation dynamique des transactions", "[memory]") {
    Account acc = create_account(999, "Test Dynamique", "0000");

    REQUIRE(acc.history_capacity == 10); // Capacité de départ

    // On force un dépassement de capacité (15 dépôts)
    for (int i = 0; i < 15; i++) {
        deposit(&acc, 10.0);
    }

    // Le moteur C a dû appeler realloc() tout seul pour doubler la taille !
    REQUIRE(acc.transaction_count == 15);
    REQUIRE(acc.history_capacity == 20); // 10 * 2
    REQUIRE(acc.balance == 150.0);

    // On libère la mémoire proprement pour ne pas faire paniquer les outils de vérification
    free_account(&acc);
}