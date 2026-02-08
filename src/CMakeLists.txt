# Créer une librairie 
add_library(core_utils sorting.c search.c)
add_subdirectory(account) 


# --- Ajout du fichier 'account.c' --- 
target_sources(core_utils PRIVATE account/account.c )

# Définir l'emplacement des fichiers d'en-tête (headers) 
target_include_directories(core_utils PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/account)

# Créer l'exécutable final de notre application à partir de main.c
add_executable(bank_app main.c) 

# Lier l'exécutable avec notre librairie d'utilitaires (core_utils)
target_link_libraries(bank_app PRIVATE core_utils) 
