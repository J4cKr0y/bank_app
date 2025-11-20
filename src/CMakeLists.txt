# Créer une librairie à partir de notre code de tri.
add_library(sorting src/sorting.c)

# Définir l'emplacement des fichiers d'en-tête (headers) pour que d'autres puissent les utiliser.
target_include_directories(sorting PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
