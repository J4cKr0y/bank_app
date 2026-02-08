#ifndef STORAGE_INTERFACE_H
#define STORAGE_INTERFACE_H

#include <stdbool.h>
#include "../account/account.h" // On a besoin de connaître la structure Account

typedef struct {
    void* context; // Contiendra le nom du fichier pour le CSV

    // Sauvegarde un tableau de comptes. Retourne true si succès.
    bool (*save)(void* context, Account* accounts, int count);

    // Charge les comptes dans un tableau fourni. Retourne le nombre de comptes lus.
    // 'max_size' empêche de faire déborder le tableau.
    int (*load)(void* context, Account* accounts_buffer, int max_size);

} StorageDriver;

#endif // STORAGE_INTERFACE_H
