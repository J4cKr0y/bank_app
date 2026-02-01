#include "catch.hpp"
#include <cstring> // Pour strcmp (comparaison de texte)

// On inclut le header de notre future feature
extern "C" {
    #include "account/account.h"
}

TEST_CASE("Account creation initializes values correctly", "[account]") {
    // GIVEN : Un ID valide et un nom de client
    int account_id = 1001;
    const char* client_name = "Alice Dupont";

    // WHEN : On crée le compte
    Account account = create_account(account_id, client_name);

    // THEN : Les informations doivent être correctes
    REQUIRE(account.id == account_id);
    
    // On utilise strcmp pour comparer les chaines de caractères en C. 
    // Si strcmp renvoie 0, c'est que les chaines sont identiques.
    REQUIRE(strcmp(account.owner, client_name) == 0);
    
    // Le solde (balance) doit être à 0 à la création
    REQUIRE(account.balance == 0.0);
}

