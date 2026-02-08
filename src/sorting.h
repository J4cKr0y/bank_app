#ifndef SORTING_H
#define SORTING_H

// Déclare la fonction qui fait l'échange (swap) de deux nombres.
void swap(int* a, int* b);

// Déclare la fonction principale du QuickSort.
// Elle trie une partie d'un tableau (de 'low' à 'high').
void quick_sort(int arr[], int low, int high);

// Déclare la fonction qui choisit un pivot et réorganise le tableau autour de lui.
int partition(int arr[], int low, int high);

#endif 
