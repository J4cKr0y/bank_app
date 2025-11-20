# Ajout de l'exécutable de test.
add_executable(run_tests test_sorting.cpp)

# 1. Le chemin vers Catch2 (dans le dossier test, catch.hpp' y est).
target_include_directories(run_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# 2. Le chemin vers les en-têtes de notre code (ex: sorting.h).
target_include_directories(run_tests PUBLIC ${CMAKE_SOURCE_DIR}/src)

# On doit lier (linker) l'exécutable de test avec notre librairie "sorting".
target_link_libraries(run_tests PRIVATE sorting)

# Ajout d'une commande pour lancer les tests automatiquement après la compilation.
enable_testing()
add_test(NAME QuickSortTests COMMAND run_tests)
