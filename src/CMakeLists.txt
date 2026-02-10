# ==============================================================================
# CONFIGURATION DES SOURCES - BankApp
# ==============================================================================

# 1. On déclare les sous-répertoires (les features).
# Chaque dossier doit avoir son propre fichier CMakeLists.txt.
add_subdirectory(account)
add_subdirectory(transaction)
add_subdirectory(auth)
add_subdirectory(system)
add_subdirectory(persistence)
add_subdirectory(common)

# 2. On crée la bibliothèque de base (Utilitaires : Tri et Recherche).
# Cette bibliothèque regroupe les outils algorithmiques du projet.
add_library(core_utils 
    sorting.c
    search.c
)

# 3. On définit les répertoires d'inclusion pour core_utils.
# PUBLIC permet aux tests et aux autres modules d'accéder à sorting.h et search.h.
target_include_directories(core_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# --- L'APPLICATION ---
add_executable(bank_app main.c)

target_include_directories(bank_app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# On lie l'exécutable avec TOUTES nos features
target_link_libraries(bank_app 
    PRIVATE 
    core_utils 
    account_lib 
    transaction_lib 
    auth_lib
    system_lib 
    persistence_lib
	common_lib
)
