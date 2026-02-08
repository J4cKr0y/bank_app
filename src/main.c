#include <stdio.h>
#include "sorting.h" // Inclut la déclaration de quick_sort
#include "search.h"  // Inclut la déclaration de binary_search

// Fonction utilitaire pour afficher le tableau
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    // 1. Déclaration du tableau à trier
    int data[] = {7, 2, 9, 1, 5, 8, 3, 6, 4};
    int n = sizeof(data) / sizeof(data[0]);
    int target = 5;
    
    printf("--- Application Bancaire (Minimal Main) ---\n");
    
    // --- Phase 1: Tri (QuickSort) ---
    printf("\nTableau original :\n");
    print_array(data, n);
    
    // Appel de la fonction de tri (QuickSort)
    quick_sort(data, 0, n - 1);
    
    printf("\nTableau trié (via QuickSort) :\n");
    print_array(data, n);
    
    // --- Phase 2: Recherche (Binary Search) ---
    printf("\n--- Recherche de l'élément ---\n");
    
    // Appel de la fonction de recherche binaire
    int index = binary_search(data, 0, n - 1, target);
    
    if (index != -1) {
        printf("Succès : L'élément %d a été trouvé à l'indice (position) %d.\n", target, index);
    } else {
        printf("Échec : L'élément %d n'a pas été trouvé.\n", target);
    }
    
    return 0;
}
