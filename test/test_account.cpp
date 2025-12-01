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

// -----------------------------------------------------
// TEST CASE 2 : Dépôt d'argent (Deposit)
// -----------------------------------------------------
TEST_CASE("Deposit function correctly increases balance", "[account][deposit]") {
    // GIVEN : Un compte avec un solde initial
    Account* account = create_account(1002, 56, 100.00);
    AccountBalance deposit_amount = 50.50;
    AccountBalance initial_balance = account->balance;

    // WHEN : On effectue un dépôt valide
    int success = deposit(account, deposit_amount);

    // THEN 1 : L'opération doit réussir
    REQUIRE(success == 1); 

    // THEN 2 : Le nouveau solde doit être l'ancien solde + le montant du dépôt
    AccountBalance expected_balance = initial_balance + deposit_amount;
    REQUIRE(account->balance == expected_balance);

    // Nettoyage
    free(account);
}

// -----------------------------------------------------
// TEST CASE 3 : Dépôt invalide (Montant négatif ou nul)
// -----------------------------------------------------
TEST_CASE("Deposit function handles invalid amounts (zero or negative)", "[account][deposit][edge_case]") {
    // GIVEN : Un compte avec un solde initial
    Account* account = create_account(1003, 57, 100.00);
    AccountBalance initial_balance = account->balance;

    // WHEN & THEN : Tenter un dépôt négatif doit échouer et ne pas modifier le solde
    REQUIRE(deposit(account, -10.00) == 0);
    REQUIRE(account->balance == initial_balance);

    // WHEN & THEN : Tenter un dépôt de zéro doit échouer et ne pas modifier le solde
    REQUIRE(deposit(account, 0.00) == 0);
    REQUIRE(account->balance == initial_balance);
    
    // Nettoyage
    free(account);
}
