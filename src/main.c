#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inclusion de toutes nos briques
#include "account/account.h"
#include "transaction/transaction.h"
#include "auth/auth.h"
#include "system/bank_interface.h"
#include "system/memory_driver.h"
#include "persistence/storage_interface.h"
#include "persistence/csv_driver.h"

#define DB_FILE "bank_data.csv"

// --- Outils pour l'interface (Helpers) ---

void clear_screen() {
    // Une astuce simple pour "nettoyer" la console
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void print_header() {
    printf("========================================\n");
    printf("       🏦  MY BANK APP  v1.0  🏦       \n");
    printf("========================================\n");
}

// Fonction pour lire une chaine proprement (sans débordement)
void get_string(const char* prompt, char* buffer, int size) {
    printf("%s", prompt);
    // On lit toute la ligne
    if (fgets(buffer, size, stdin) != NULL) {
        // On retire le saut de ligne (\n) à la fin si présent
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
}

// Fonction pour lire un entier proprement
int get_int(const char* prompt) {
    char buffer[100];
    get_string(prompt, buffer, sizeof(buffer));
    return atoi(buffer); // Convertit la chaine en nombre
}

// Fonction pour lire un montant (double)
double get_double(const char* prompt) {
    char buffer[100];
    get_string(prompt, buffer, sizeof(buffer));
    return atof(buffer);
}

// --- Le Cœur de l'application ---

int main() {
    // 1. Démarrage : Initialisation des Drivers
    BankDriver bank = create_memory_driver();
    StorageDriver storage = create_csv_driver(DB_FILE);

    // 2. Chargement des données (Disque -> RAM)
    Account temp_buffer[100];
    printf("Chargement des données...\n");
    int loaded_count = storage.load(storage.context, temp_buffer, 100);
    
    // On injecte les comptes chargés dans le moteur bancaire
    for (int i = 0; i < loaded_count; i++) {
        driver_add_account(&bank, temp_buffer[i]);
    }
    printf("%d comptes chargés.\n", loaded_count);

    // Variables d'état
    bool running = true;
    int current_user_id = -1; // -1 signifie "Déconnecté"

    while (running) {
        // clear_screen(); // Décommentez pour effacer l'écran à chaque fois
        print_header();

        if (current_user_id == -1) {
            // === MENU NON CONNECTÉ ===
            printf("\n--- ACCUEIL ---\n");
            printf("1. Se connecter\n");
            printf("2. Créer un nouveau compte\n");
            printf("3. Quitter\n");
            
            int choice = get_int("> Votre choix : ");

            if (choice == 1) {
                // --- LOGIN ---
                int id = get_int("ID Compte : ");
                char pin[10];
                get_string("Code PIN : ", pin, 10);

                // On cherche le compte dans la banque (via get_balance pour vérifier s'il existe)
                double bal = bank.get_balance(bank.context, id);
                if (bal == -1.0) {
                    printf("❌ Compte introuvable.\n");
                } else {
                    // Pour vérifier le PIN, on doit accéder au compte.
                    // Note : Ici on accède à la mémoire interne via une astuce, 
                    // idéalement l'interface Auth devrait être reliée au driver.
                    // Pour simplifier, on va recharger le compte spécifique depuis la mémoire du driver
                    // MAIS comme l'interface est générique, on ne peut pas.
                    
                    // SOLUTION SIMPLE : On scanne le buffer local qu'on a chargé ou
                    // on suppose que le driver a une fonction 'get_account_security'.
                    // Pour l'instant, on va tricher un peu et vérifier dans le buffer chargé au début
                    // OU Mieux : On ajoute une fonction de vérification dans le Main.
                    
                    // Récupérons le compte directement du driver (hack temporaire pour le main)
                    MemoryDatabase* db = (MemoryDatabase*)bank.context;
                    bool login_success = false;
                    for(int i=0; i<db->count; i++) {
                        if (db->accounts[i].id == id) {
                            if (verify_pin(db->accounts[i].pin_hash, pin)) {
                                login_success = true;
                                current_user_id = id;
                                printf("✅ Connexion réussie ! Bienvenue %s.\n", db->accounts[i].owner);
                            }
                        }
                    }
                    if (!login_success) printf("❌ Mauvais code PIN.\n");
                }

            } else if (choice == 2) {
                // --- CRÉATION ---
                char name[100];
                get_string("Nom du propriétaire : ", name, 100);
                char pin[10];
                get_string("Choisissez un code PIN (4 chiffres) : ", pin, 10);

                // Génération ID auto (max ID + 1)
                int new_id = loaded_count + 1001; // Commence à 1001
                
                Account new_acc = create_account(new_id, name, pin);
                
                // Ajout au driver et au compteur local
                driver_add_account(&bank, new_acc);
                loaded_count++;
                
                printf("✅ Compte créé avec succès ! Votre ID est : %d\n", new_id);

            } else if (choice == 3) {
                running = false;
            }

        } else {
            // === MENU CONNECTÉ ===
            printf("\n--- MENU CLIENT (ID: %d) ---\n", current_user_id);
            printf("1. Voir mon solde\n");
            printf("2. Faire un virement\n");
            printf("3. Se déconnecter\n");

            int choice = get_int("> Votre choix : ");

            if (choice == 1) {
                double balance = bank.get_balance(bank.context, current_user_id);
                printf("\n💰 Votre solde est de : %.2f €\n", balance);
            
            } else if (choice == 2) {
                int dest_id = get_int("ID du destinataire : ");
                double amount = get_double("Montant à virer : ");

                if (bank.transfer(bank.context, current_user_id, dest_id, amount)) {
                    printf("✅ Virement effectué avec succès !\n");
                } else {
                    printf("❌ Échec du virement (Fonds insuffisants ou destinataire invalide).\n");
                }

            } else if (choice == 3) {
                current_user_id = -1;
                printf("👋 Au revoir !\n");
            }
        }
        
        if (running) {
            printf("\nAppuyez sur Entrée pour continuer...");
            getchar(); // Pause
        }
    }

    // 3. Arrêt : Sauvegarde des données (RAM -> Disque)
    printf("Sauvegarde des données...\n");
    
    // On doit récupérer tous les comptes du driver pour les sauver
    MemoryDatabase* db_final = (MemoryDatabase*)bank.context;
    
    if (storage.save(storage.context, db_final->accounts, db_final->count)) {
        printf("✅ Données sauvegardées dans %s\n", DB_FILE);
    } else {
        printf("❌ Erreur lors de la sauvegarde !\n");
    }

    return 0;
}