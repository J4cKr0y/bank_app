# Créer une librairie 
add_library(core_utils sorting.c search.c)
add_subdirectory(account) 
add_subdirectory(transaction)
add_subdirectory(system)


# --- Ajout du fichier 'account.c' --- 
target_sources(core_utils PRIVATE account/account.c )

target_sources(core_utils PRIVATE transaction/transaction.c )

target_sources(core_utils PRIVATE system/memory_driver.c )

target_sources(core_utils PRIVATE system/bank_interface.c )

# Définir l'emplacement des fichiers d'en-tête (headers) 
target_include_directories(core_utils PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/account
${CMAKE_CURRENT_SOURCE_DIR}/transaction
${CMAKE_CURRENT_SOURCE_DIR}/system
)

# Créer l'exécutable final de notre application à partir de main.c
add_executable(bank_app main.c) 

# Lier l'exécutable avec notre librairie d'utilitaires (core_utils)
target_link_libraries(bank_app PRIVATE core_utils) 
