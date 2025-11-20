cmake_minimum_required(VERSION 3.10) 

# Le nom de notre projet.
project(BankApp C) 

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

# Ajout du sous-répertoire 'src' (pour les sources de l'application) et 'test' (pour les tests).
add_subdirectory(src)
add_subdirectory(test)
