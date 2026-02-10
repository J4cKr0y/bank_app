cmake_minimum_required(VERSION 3.10) 

# Le nom de notre projet.
project(BankApp C CXX) 

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

# --- Activation de CTest --- 
enable_testing() 

# Ajout du sous-répertoire 'src' (pour les sources de l'application) et 'test' (pour les tests).
add_subdirectory(src)
add_subdirectory(test)

# Création de l'exécutable principal
add_executable(BankApp main.c)

# Liaison avec les bibliothèques nécessaires
# Note: main.c utilise sorting.h et search.h qui sont dans core_utils
target_link_libraries(BankApp PRIVATE core_utils)