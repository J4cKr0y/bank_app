# test/CMakeLists.txt

# --- Configuration de Catch2 (pour FetchContent) ---
# include(FetchContent)
# FetchContent_Declare(...)
# FetchContent_MakeAvailable(Catch2)

# Activation explicite du support C++ 
# Obligatoire car les fichiers de tests (.cpp) sont en C++.
enable_language(CXX)

# --- Fichiers Sources C++ des Tests ---
# Définition de la liste de tous les fichiers de test C++
set(CORE_TEST_SOURCES 
    test_sorting.cpp 
    test_search.cpp
    test_account.cpp
    test_transaction.cpp
)

# --- Exécutable de Test ---
# 1. Créer UN SEUL exécutable de test à partir de tous les fichiers C++
# Le nom de cet exécutable est "run_core_tests"
add_executable(run_core_tests ${CORE_TEST_SOURCES})

# --- Chemins d'Inclusion (Headers) ---
# 2. Indiquer où trouver les en-têtes de Catch2 (si vous avez catch.hpp dans test/)
target_include_directories(run_core_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 3. Indiquer où trouver les en-têtes de notre code source (sorting.h, search.h)
target_include_directories(run_core_tests PUBLIC ${CMAKE_SOURCE_DIR}/src)

# --- Lien des Librairies (Linker) ---
# 4. Lier l'exécutable avec notre nouvelle librairie C "core_utils"
target_link_libraries(run_core_tests PRIVATE core_utils 
  account_lib
  transaction_lib
) 

# --- Ajouter une définition de préprocesseur --- 
# 5. Fixe les erreurs sysconf/constexpr et 'non-constexpr' 
target_compile_definitions(run_core_tests PRIVATE CATCH_CONFIG_DISABLE_FATAL_STD_LIBRARIES) 
target_compile_definitions(run_core_tests PRIVATE CATCH_CONFIG_NO_POSIX_SIGNALS)

# --- Configuration de l'Exécution des Tests ---
# 6. Permettre à CMake de reconnaître et d'exécuter les tests
enable_testing()
add_test(NAME CoreTests COMMAND run_core_tests)
