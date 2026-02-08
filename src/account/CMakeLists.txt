# On crée une librairie nommée "account_lib"
add_library(account_lib account.c)

# On permet aux autres fichiers de trouver "account.h"
target_include_directories(account_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

# On dit que "account_lib" a besoin de "transaction_lib" pour fonctionner.
target_link_libraries(account_lib PRIVATE transaction_lib)