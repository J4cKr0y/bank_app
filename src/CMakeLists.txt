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

# 2. On crée la bibliothèque de base (Utilitaires : Tri et Recherche).
# Cette bibliothèque regroupe les outils algorithmiques du projet.
add_library(core_utils 
    sorting.c
    search.c
)

# 3. On définit les répertoires d'inclusion pour core_utils.
# PUBLIC permet aux tests et aux autres modules d'accéder à sorting.h et search.h.
target_include_directories(core_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# ==============================================================================
# NOTES SUR L'ORGANISATION :
# ==============================================================================
# L'ordre d'inclusion est important si des librairies dépendent d'autres.
# - account_lib (dans src/account) dépend de transaction_lib.
# - system_lib (dans src/system) dépend de account_lib.
# - persistence_lib (dans src/persistence) dépend de account_lib.
#
# CMake gère automatiquement l'ordre de compilation grâce aux commandes
# target_link_libraries que nous avons mises dans les sous-dossiers.
