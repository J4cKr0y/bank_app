#ifndef CSV_DRIVER_H
#define CSV_DRIVER_H

#include "storage_interface.h"

// Crée un driver configuré pour un fichier CSV spécifique
StorageDriver create_csv_driver(const char* filename);

#endif // CSV_DRIVER_H
