#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <cstring>

extern "C" {
    #include "account/account.h"
    #include "common/status.h"
}

TEST_CASE("Account creation initializes values correctly", "[account]") {
    int account_id = 1001;
    const char* client_name = "Alice Dupont";

    Account account = create_account(account_id, client_name, "1234");

    REQUIRE(account.id == account_id);
    REQUIRE(strcmp(account.owner, client_name) == 0);
    REQUIRE(account.balance == 0.0);

    free_account(&account);
}

TEST_CASE("Deposit increases account balance", "[account]") {
    Account account = create_account(1, "Bob", "0000");

    deposit(&account, 100.0);
    REQUIRE(account.balance == 100.0);

    deposit(&account, 50.0);
    REQUIRE(account.balance == 150.0);

    free_account(&account);
}

TEST_CASE("Withdraw decreases account balance when funds are sufficient", "[account]") {
    Account account = create_account(1, "Bob", "0000");
    deposit(&account, 200.0);

    REQUIRE(withdraw(&account, 50.0) == STATUS_SUCCESS);
    REQUIRE(account.balance == 150.0);

    free_account(&account);
}

TEST_CASE("Withdraw fails when funds are insufficient", "[account]") {
    Account account = create_account(1, "Bob", "0000");
    deposit(&account, 20.0);

    REQUIRE(withdraw(&account, 50.0) == ERR_INSUFFICIENT_FUNDS);
    REQUIRE(account.balance == 20.0);

    free_account(&account);
}

TEST_CASE("Cannot deposit or withdraw negative amounts", "[account][edge_case]") {
    Account account = create_account(1, "Bob", "0000");
    deposit(&account, 100.0);

    deposit(&account, -50.0);
    REQUIRE(account.balance == 100.0);

    REQUIRE(withdraw(&account, -10.0) == ERR_INVALID_AMOUNT);
    REQUIRE(account.balance == 100.0);

    free_account(&account);
}

TEST_CASE("Deposit adds a transaction to history", "[account][history]") {
    Account account = create_account(1, "Alice", "1234");

    REQUIRE(account.transaction_count == 0);

    deposit(&account, 100.0);

    REQUIRE(account.transaction_count == 1);
    REQUIRE(account.history[0].type == DEPOSIT);
    REQUIRE(account.history[0].amount == 100.0);

    free_account(&account);
}

TEST_CASE("Withdraw returns precise error codes", "[account][error]") {
    Account acc = create_account(1, "Test", "0000");
    deposit(&acc, 50.0);

    REQUIRE(withdraw(&acc, 20.0) == STATUS_SUCCESS);
    REQUIRE(withdraw(&acc, 1000.0) == ERR_INSUFFICIENT_FUNDS);
    REQUIRE(acc.balance == 30.0);
    REQUIRE(withdraw(&acc, -5.0) == ERR_INVALID_AMOUNT);

    free_account(&acc);
}