#define CATCH_CONFIG_MAIN 
#include "catch.hpp"

extern "C" {
    #include "sorting.h"
}

// 1. Test de la fonction utilitaire swap
TEST_CASE("swap function correctly exchanges two values", "[swap]") {
    // GIVEN (Étant donné) : Deux variables
    int a = 5;
    int b = 10;
    
    // WHEN (Quand) : On appelle la fonction swap
    swap(&a, &b);

    // THEN (Alors) : Les valeurs doivent avoir été échangées
    REQUIRE(a == 10);
    REQUIRE(b == 5);
}

// 2. Test principal : QuickSort sur un tableau normal
TEST_CASE("quick_sort correctly sorts a standard array", "[quick_sort]") {
    // GIVEN : Un tableau non trié
    int arr[] = {10, 80, 30, 90, 40, 50, 70};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    // WHEN : On trie le tableau
    quick_sort(arr, 0, n - 1);

    // THEN : Le tableau doit être trié
    REQUIRE(arr[0] == 10);
    REQUIRE(arr[1] == 30);
    REQUIRE(arr[2] == 40);
    REQUIRE(arr[3] == 50);
    REQUIRE(arr[4] == 70);
    REQUIRE(arr[5] == 80);
    REQUIRE(arr[6] == 90);
}

// 3. Test de cas limites : Tableau déjà trié
TEST_CASE("quick_sort handles an already sorted array", "[quick_sort][edge_case]") {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    quick_sort(arr, 0, n - 1);
    
    REQUIRE(arr[0] == 1);
    REQUIRE(arr[1] == 2);
    REQUIRE(arr[2] == 3);
    REQUIRE(arr[3] == 4);
    REQUIRE(arr[4] == 5);

}

// 4. Test de cas limites : Tableau trié à l'envers
TEST_CASE("quick_sort handles a reverse sorted array", "[quick_sort][edge_case]") {
    int arr[] = {5, 4, 3, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    quick_sort(arr, 0, n - 1);
    
    REQUIRE(arr[0] == 1);
    REQUIRE(arr[4] == 5);
}

// 5. Test de cas limites : Tableau avec un seul élément
TEST_CASE("quick_sort handles a single element array", "[quick_sort][edge_case]") {
    int arr[] = {42};
    int n = 1;
    
    quick_sort(arr, 0, n - 1);
    
    REQUIRE(arr[0] == 42);
}

// 6. Test de cas limites : Tableau avec des doublons
TEST_CASE("quick_sort handles array with duplicate elements", "[quick_sort][edge_case]") {
    int arr[] = {5, 2, 5, 1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    quick_sort(arr, 0, n - 1);
    
    REQUIRE(arr[0] == 1);
    REQUIRE(arr[1] == 2);
    REQUIRE(arr[2] == 2);
    REQUIRE(arr[3] == 3);
    REQUIRE(arr[4] == 5);
    REQUIRE(arr[5] == 5);
}
