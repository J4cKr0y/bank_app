#include "catch.hpp"
#include <cstring> // Pour strcmp (comparaison de texte)

// On inclut le header de notre future feature
extern "C" {
    #include "account/account.h"
	#include "common/status.h"
}

TEST_CASE("Account creation initializes values correctly", "[account]") {
    // GIVEN : Un ID valide et un nom de client
    int account_id = 1001;
    const char* client_name = "Alice Dupont";

    // WHEN : On crée le compte
    Account account = create_account(account_id, client_name, "1234");

    // THEN : Les informations doivent être correctes
    REQUIRE(account.id == account_id);
    
    // On utilise strcmp pour comparer les chaines de caractères en C. 
    // Si strcmp renvoie 0, c'est que les chaines sont identiques.
    REQUIRE(strcmp(account.owner, client_name) == 0);
    
    // Le solde (balance) doit être à 0 à la création
    REQUIRE(account.balance == 0.0);
}

TEST_CASE("Deposit increases account balance", "[account]") {
    // GIVEN : Un compte vide
    Account account = create_account(1, "Bob", "0000");
    
    // WHEN : On dépose 100.0
    // Note : On passe l'adresse du compte (&account) pour le modifier
    deposit(&account, 100.0);

    // THEN : Le solde doit être de 100.0
    REQUIRE(account.balance == 100.0);
    
    // WHEN : On dépose encore 50.0
    deposit(&account, 50.0);

    // THEN : Le solde doit s'accumuler
    REQUIRE(account.balance == 150.0);
}

TEST_CASE("Withdraw decreases account balance when funds are sufficient", "[account]") {
    // GIVEN : Un compte avec 200.0
    Account account = create_account(1, "Bob", "0000");
    deposit(&account, 200.0);

    // WHEN : On retire 50.0
    bool success = withdraw(&account, 50.0);

    // THEN : L'opération réussit et le solde diminue
    REQUIRE(success == true);
    REQUIRE(account.balance == 150.0);
}

TEST_CASE("Withdraw fails when funds are insufficient", "[account]") {
    // GIVEN : Un compte avec seulement 20.0
    Account account = create_account(1, "Bob", "0000");
    deposit(&account, 20.0);

    // WHEN : On essaie de retirer 50.0
    bool success = withdraw(&account, 50.0);

    // THEN : L'opération échoue et le solde ne bouge pas
    REQUIRE(success == false);
    REQUIRE(account.balance == 20.0);
}

TEST_CASE("Cannot deposit or withdraw negative amounts", "[account][edge_case]") {
    Account account = create_account(1, "Bob", "0000");
    deposit(&account, 100.0);

    deposit(&account, -50.0); // Ne devrait rien faire
    REQUIRE(account.balance == 100.0);

    bool success = withdraw(&account, -10.0); // Ne devrait pas marcher
    REQUIRE(success == false);
    REQUIRE(account.balance == 100.0);
}

TEST_CASE("Deposit adds a transaction to history", "[account][history]") {
    // GIVEN : Un compte tout neuf
    Account account = create_account(1, "Alice", "1234");
    
    // Vérifions que l'historique est vide au début
    REQUIRE(account.transaction_count == 0);

    // WHEN : On fait un dépôt
    deposit(&account, 100.0);

    // THEN : On doit avoir 1 transaction dans l'historique
    REQUIRE(account.transaction_count == 1);
    
    // Vérifions le contenu du "ticket"
    REQUIRE(account.history[0].type == DEPOSIT);
    REQUIRE(account.history[0].amount == 100.0);
}

TEST_CASE("Withdraw returns precise error codes", "[account][error]") {
    Account acc = create_account(1, "Test", "0000");
    deposit(&acc, 50.0);

    // 1. Cas nominal (Succès)
    REQUIRE(withdraw(&acc, 20.0) == STATUS_SUCCESS); 

    // 2. Cas Fonds insuffisants
    REQUIRE(withdraw(&acc, 1000.0) == ERR_INSUFFICIENT_FUNDS);
    REQUIRE(acc.balance == 30.0); // Le solde n'a pas bougé (50 - 20)

    // 3. Cas Montant invalide
    REQUIRE(withdraw(&acc, -5.0) == ERR_INVALID_AMOUNT);
}
