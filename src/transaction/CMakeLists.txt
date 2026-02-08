add_library(transaction_lib transaction.c)

target_include_directories(transaction_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
