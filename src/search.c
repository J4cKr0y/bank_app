#include "search.h"

//  Fonction de Recherche : Binary Search
int binary_search(int arr[], int low, int high, int target) {
    // low et high sont les indices (positions) de début et de fin de la partie du tableau.
    
    // Tant que la zone de recherche est valide (le début n'a pas dépassé la fin).
    while (low <= high) {
        
        // On calcule l'indice du milieu (la position centrale).
        int mid = low + (high - low) / 2;

        // Cas 1 : La valeur est trouvée.
        if (arr[mid] == target) {
            return mid; 
        }

        // Cas 2 : La valeur cherchée est plus GRANDE (doit être dans la moitié droite).
        if (arr[mid] < target) {
            low = mid + 1;
        }

        // Cas 3 : La valeur cherchée est plus PETITE (doit être dans la moitié gauche).
        else {
            high = mid - 1;
        }
    }
    
    // Si la boucle est finie, la valeur n'est pas dans le tableau.
    return -1; 
}
