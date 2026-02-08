#include "catch.hpp"

extern "C" {
    #include "search.h"
}

// 1. Test de la recherche binaire : élément trouvé au milieu
TEST_CASE("binary_search finds element in the middle", "[binary_search]") {
    // GIVEN : Un tableau trié (pré-requis pour binary_search)
    int arr[] = {10, 20, 30, 40, 50, 60};
    int n = 6;
    
    // THEN : On trouve 30 à l'index 2
    REQUIRE(binary_search(arr, 0, n - 1, 30) == 2);
}

// 2. Test de la recherche binaire : élément non trouvé
TEST_CASE("binary_search returns -1 for missing element", "[binary_search]") {
    int arr[] = {10, 20, 30, 40, 50, 60};
    int n = 6;
    
    // THEN : 15 n'est pas dans le tableau
    REQUIRE(binary_search(arr, 0, n - 1, 15) == -1);
}

// 3. Test de la recherche binaire : élément trouvé au début
TEST_CASE("binary_search finds first element", "[binary_search]") {
    int arr[] = {10, 20, 30, 40, 50, 60};
    int n = 6;
    
    REQUIRE(binary_search(arr, 0, n - 1, 10) == 0);
}

// 4. Test de la recherche binaire : élément trouvé à la fin
TEST_CASE("binary_search finds last element", "[binary_search]") {
    int arr[] = {10, 20, 30, 40, 50, 60};
    int n = 6;
    
    REQUIRE(binary_search(arr, 0, n - 1, 60) == 5);
}
