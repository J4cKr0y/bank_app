#include "sorting.h" 

// 🛠️ Fonction utilitaire : Échanger deux nombres
void swap(int* a, int* b) {
    // Échanger la valeur pointée par 'a' avec celle pointée par 'b'.
    // On utilise un pointeur (*) car on veut modifier la valeur ORIGINALE
    // dans le tableau, et non juste une copie.
    
    int t = *a; // 1. On stocke la valeur de 'a' dans une variable temporaire 't'.
    *a = *b;    // 2. On met la valeur de 'b' à la place de 'a'.
    *b = t;     // 3. On met l'ancienne valeur de 'a' (sauvée dans 't') à la place de 'b'.
}

// Fonction clé : Partitionnement (réorganisation autour d'un "pivot")
int partition(int arr[], int low, int high) {
    // 'low' et 'high' sont les indices (positions) de début et de fin de la partie du tableau à trier.
    
    // On choisit le dernier élément comme "pivot".
    // Le but est de placer ce pivot à sa position finale correcte :
    // tous les nombres plus petits à gauche, tous les plus grands à droite.
    int pivot = arr[high]; 
    
    // 'i' sera l'indice du dernier élément trouvé plus petit que le pivot.
    // On commence avec un indice "imaginaire" juste avant le début du tri.
    int i = (low - 1); 

    // On parcourt la partie du tableau du début ('low') jusqu'à l'avant-dernier élément ('high - 1').
    for (int j = low; j <= high - 1; j++) {
        
        // Est-ce que le nombre à la position 'j' est plus petit que notre pivot ?
        if (arr[j] < pivot) {
            
            i++; // Oui ! On augmente l'indice 'i'. L'emplacement 'i' est l'endroit où
                 // le prochain "petit nombre" doit aller.
            
            swap(&arr[i], &arr[j]); // On échange le petit nombre 'arr[j]' avec le nombre
                                    // qui se trouvait à la position 'i' (qui était un "grand nombre").
                                    // Cela déplace le petit nombre vers la gauche.
        }
    }
    
    //  Fin du parcours ! Le pivot n'est pas encore à sa place.
    // On échange l'élément à 'i + 1' (qui est le premier "grand nombre") avec le pivot.
    // Maintenant, le pivot est ENFIN à sa position finale correcte.
    swap(&arr[i + 1], &arr[high]);
    
    // On renvoie l'indice du pivot (sa nouvelle position), car c'est la "coupure"
    // qui sépare les nombres à trier à gauche et ceux à trier à droite.
    return (i + 1);
}

//  Fonction principale : QuickSort
void quick_sort(int arr[], int low, int high) {
    
    // C'est la condition d'arrêt de la récursivité (le fait que la fonction s'appelle elle-même).
    // Si 'low' est plus petit que 'high', cela signifie qu'il y a au moins deux éléments à trier.
    if (low < high) {
        
        // 1. Appel à Partition : On réorganise le tableau et on obtient la position finale
        //    du pivot ('pi').
        int pi = partition(arr, low, high);

        // 2. Récursivité à Gauche : On rappelle quick_sort pour trier la partie à gauche du pivot.
        quick_sort(arr, low, pi - 1);

        // 3. Récursivité à Droite : On rappelle quick_sort pour trier la partie à droite du pivot.
        quick_sort(arr, pi + 1, high);
        
        // Grâce aux appels récursifs, le processus continue jusqu'à ce que chaque partie
        // ne contienne qu'un seul élément (ou aucun), et tout le tableau est trié.
    }
}
