#include "catch.hpp"

extern "C" {
    #include "system/bank_interface.h"
    #include "system/memory_driver.h"
    #include "common/status.h"
}

TEST_CASE("Transfer via Interface moves funds correctly", "[transfer][interface]") {
    BankDriver bank = create_memory_driver();
    setup_test_accounts(&bank);

    REQUIRE(bank.get_balance(bank.context, 1001) == 100.0);
    REQUIRE(bank.get_balance(bank.context, 1002) == 0.0);

    REQUIRE(bank.transfer(bank.context, 1001, 1002, 40.0) == STATUS_SUCCESS);

    REQUIRE(bank.get_balance(bank.context, 1001) == 60.0);
    REQUIRE(bank.get_balance(bank.context, 1002) == 40.0);

    free_memory_driver(&bank);
}

TEST_CASE("Transfer fails if source account has insufficient funds", "[transfer][interface]") {
    BankDriver bank = create_memory_driver();
    setup_test_accounts(&bank);

    REQUIRE(bank.transfer(bank.context, 1001, 1002, 500.0) == ERR_INSUFFICIENT_FUNDS);

    REQUIRE(bank.get_balance(bank.context, 1001) == 100.0);

    free_memory_driver(&bank);
}