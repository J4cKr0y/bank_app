#ifndef AUTH_H
#define AUTH_H

#include <stdbool.h>

// Fonction qui transforme un texte (PIN) en nombre unique (Hash).
unsigned long hash_pin(const char* pin);

// Vérifie si le PIN saisi correspond au hash stocké.
bool verify_pin(unsigned long stored_hash, const char* input_pin);

#endif // AUTH_H
