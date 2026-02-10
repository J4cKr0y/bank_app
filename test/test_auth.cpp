#include "catch.hpp"

extern "C" {
    #include "auth/auth.h"
}

TEST_CASE("Hashing function is consistent", "[auth]") {
    const char* pin = "1234";
    
    // Le hash de "1234" doit toujours être le même
    unsigned long hash1 = hash_pin(pin);
    unsigned long hash2 = hash_pin(pin);

    REQUIRE(hash1 == hash2);
    
    // Le hash de "0000" doit être différent
    REQUIRE(hash_pin("0000") != hash1);
}

TEST_CASE("PIN verification works", "[auth]") {
    const char* true_pin = "5678";
    unsigned long stored_hash = hash_pin(true_pin);

    // WHEN : On teste le bon PIN
    // THEN : Ça marche
    REQUIRE(verify_pin(stored_hash, "5678") == true);

    // WHEN : On teste un mauvais PIN
    // THEN : Ça échoue
    REQUIRE(verify_pin(stored_hash, "0000") == false);
}
