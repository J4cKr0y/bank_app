#include "catch.hpp"
#include <stdlib.h> 


extern "C" {
    #include "account/account.h" 
}

// -----------------------------------------------------
// TEST CASE 1 : Création et Initialisation de Compte
// -----------------------------------------------------
TEST_CASE("Account creation and initialization", "[account][create]") {
    
    // GIVEN : Des paramètres valides pour la création
    int id = 1001;
    int client_id = 55;
    AccountBalance initial_balance = 500.50;
    
    // WHEN : On crée un nouveau compte
    Account* new_account = create_account(id, client_id, initial_balance);
    
    // THEN : Le compte doit exister et les champs doivent être corrects
    REQUIRE(new_account != NULL);
    REQUIRE(new_account->id == id);
    REQUIRE(new_account->client_id == client_id);
    REQUIRE(new_account->balance == initial_balance); // Test de l'initialisation du solde
    
    // Nettoyage (important !)
    free(new_account);
}
