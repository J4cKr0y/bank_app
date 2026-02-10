# 🏦 BankApp — Système Bancaire Modulaire en C

Une application bancaire robuste, développée en C avec une architecture orientée **"Features"** et une approche de **Test-Driven Development (TDD)**.

---

## ✨ Fonctionnalités

- **Gestion de Comptes** : Création, dépôts et retraits sécurisés.
- **Sécurité** : Authentification par code PIN avec hachage (algorithme DJB2).
- **Persistance** : Sauvegarde et chargement des données au format CSV.
- **Virements** : Transferts de fonds sécurisés entre comptes avec gestion d'erreurs atomique.
- **Architecture Découplée** : Utilisation d'interfaces (Drivers) pour faciliter le passage futur vers une base de données SQL.

---

## 🏗️ Architecture du Projet

Le projet suit une structure modulaire stricte pour garantir la maintenabilité :

- `src/common/` : Gestion centralisée des codes d'erreur (`BankStatus`).
- `src/auth/` : Logique de sécurité et de hachage.
- `src/persistence/` : Couche d'accès aux données (CSV Driver).
- `src/system/` : Interface de la banque et implémentation en mémoire.
- `src/core/` : Algorithmes de tri et de recherche optimisés (O(n log n) et O(log n)).

---

## 🚀 Installation & Compilation

### Prérequis

- Un compilateur C (GCC ou Clang)
- CMake (version 3.10 ou supérieure)
- Make ou Ninja

### Instructions

**1. Cloner le dépôt :**

```bash
git clone https://github.com/ton-pseudo/bank-app.git
cd bank-app
```

**2. Préparer le build :**

```bash
mkdir build && cd build
cmake ..
```

**3. Compiler :**

```bash
cmake --build .
```

---

## 🧪 Tests Unitaires

Ce projet utilise **Catch2** pour garantir la fiabilité de chaque module.

Pour lancer les tests :

```bash
./test/run_core_tests
```

---

## 💻 Utilisation

Une fois compilé, lancez l'application via :

```bash
./src/bank_app
```

L'application crée automatiquement un fichier `bank_data.csv` pour mémoriser vos comptes.
