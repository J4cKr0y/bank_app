#include "auth.h"

// Algorithme de hachage simple (DJB2)
unsigned long hash_pin(const char* pin) {
    unsigned long hash = 5381;
    int c;

    // On parcourt chaque chiffre du PIN
    while ((c = *pin++)) { // *pin++ prend le caractère et avance au suivant
        // hash * 33 + c
        hash = ((hash << 5) + hash) + c; 
    }

    return hash;
}

bool verify_pin(unsigned long stored_hash, const char* input_pin) {
    // 1. On hache le PIN qu'on vient de recevoir
    unsigned long input_hash = hash_pin(input_pin);

    // 2. On compare les deux empreintes (le steak haché stocké vs le nouveau steak haché)
    return (stored_hash == input_hash);
}
