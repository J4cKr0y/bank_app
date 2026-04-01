#include "csv_driver.h"
#include <stdio.h>
#include <stdlib.h>

// Structure pour stocker le nom du fichier
typedef struct {
    const char* filename;
} CsvContext;

// --- Implémentation SAVE ---
static bool csv_save(void* context, Account* accounts, int count) {
    CsvContext* ctx = (CsvContext*)context;

    // 1. Ouvrir le fichier en mode écriture ("w" = write)
    // Cela écrase le fichier s'il existe déjà.
    FILE* file = fopen(ctx->filename, "w");
    if (file == NULL) {
        return false; // Erreur (disque plein, droits d'accès...)
    }

    // 2. Écrire l'en-tête (optionnel mais propre pour Excel)
    fprintf(file, "ID,Owner,Balance,PIN\n");

    // 3. Boucle sur les comptes
    for (int i = 0; i < count; i++) {
        // Format CSV : 1,Batman,1000.00,<pin_hash>
        fprintf(file, "%d,%s,%.2f,%lu\n",
                accounts[i].id,
                accounts[i].owner,
                accounts[i].balance,
                accounts[i].pin_hash);
    }

    // 4. Fermer le fichier (Très important !)
    fclose(file);
    return true;
}

// --- Implémentation LOAD ---
static int csv_load(void* context, Account* accounts_buffer, int max_size) {
    CsvContext* ctx = (CsvContext*)context;

    // 1. Ouvrir le fichier en mode lecture ("r" = read)
    FILE* file = fopen(ctx->filename, "r");
    if (file == NULL) {
        return 0; // Fichier n'existe pas encore, donc 0 comptes chargés
    }

    // 2. Sauter la première ligne (l'en-tête)
    char buffer[256];
    fgets(buffer, sizeof(buffer), file);

    int loaded_count = 0;

    // 3. Lire ligne par ligne
    // %d = un entier
    // %99[^,] = lire une chaine de max 99 caractères tant qu'on ne voit pas de virgule
    // %lf = un double (long float)
    while (loaded_count < max_size &&
           fscanf(file, "%d,%99[^,],%lf,%lu\n",
                  &accounts_buffer[loaded_count].id,
                  accounts_buffer[loaded_count].owner,
                  &accounts_buffer[loaded_count].balance,
                  &accounts_buffer[loaded_count].pin_hash) == 4) {

        // Initialisation des champs de l'historique :
        // Le compte est chargé depuis le disque, son pointeur `history` est
        // invalide (données brutes). On alloue une capacité initiale propre.
        accounts_buffer[loaded_count].transaction_count = 0;
        accounts_buffer[loaded_count].history_capacity  = 10;
        accounts_buffer[loaded_count].history = (Transaction*)malloc(10 * sizeof(Transaction));

        loaded_count++;
    }

    fclose(file);
    return loaded_count;
}

// --- Constructeur ---
StorageDriver create_csv_driver(const char* filename) {
    static CsvContext ctx;
    ctx.filename = filename;

    StorageDriver driver;
    driver.context = &ctx;
    driver.save    = csv_save;
    driver.load    = csv_load;

    return driver;
}