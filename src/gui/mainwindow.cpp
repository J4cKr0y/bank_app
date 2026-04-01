#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include "dashboard.h"
#include <QCloseEvent>
#include <QInputDialog>

// Inclusion des fonctions C
extern "C" {
    #include "../system/bank_interface.h"
    #include "../system/memory_driver.h"
    #include "../auth/auth.h"
    #include "../persistence/csv_driver.h"
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialisation du moteur C
    bank    = create_memory_driver();
    storage = create_csv_driver("bank_data.csv");

    // CHARGEMENT DES DONNÉES (Le pont C <-> CSV)
    // On crée un tableau temporaire pour accueillir les comptes du fichier
    Account loaded_accounts[100];
    int loaded_count = storage.load(storage.context, loaded_accounts, 100);

    if (loaded_count > 0) {
        // On injecte chaque compte chargé dans notre driver en mémoire
        for (int i = 0; i < loaded_count; i++) {
            driver_add_account(&bank, loaded_accounts[i]);
        }
        qDebug() << "✅ Données CSV chargées avec succès.";
    } else {
        qWarning() << "⚠️ Aucun fichier de données trouvé ou erreur de lecture. On démarre à vide.";
    }
}

MainWindow::~MainWindow()
{
    // On libère la RAM allouée par le C avant de détruire la fenêtre
    free_memory_driver(&bank);
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    QString idStr  = ui->idInput->text();
    QString pinStr = ui->pinInput->text();

    // 1. Vérification des champs vides
    if (idStr.isEmpty() || pinStr.isEmpty()) {
        QMessageBox::warning(this, "Champs vides", "Veuillez remplir tous les champs.");
        return;
    }

    int id = idStr.toInt();
    MemoryDatabase* db = (MemoryDatabase*)bank.context;
    bool found = false;

    // 2. Recherche du compte et vérification
    for (int i = 0; i < db->count; i++) {
        if (db->accounts[i].id == id) {
            found = true;

            // On vérifie le PIN
            if (verify_pin(db->accounts[i].pin_hash, pinStr.toStdString().c_str())) {
                QMessageBox::information(this, "Succès", "Connexion réussie !");

                // 3. OUVERTURE DU DASHBOARD (Une fois authentifié)
                this->hide();
                Dashboard dash(bank, id, this);
                dash.exec();
                this->show();

            } else {
                QMessageBox::critical(this, "Erreur", "Code PIN incorrect.");
            }
            break;
        }
    }

    if (!found) {
        QMessageBox::critical(this, "Erreur", "Compte introuvable.");
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    // 1. On récupère les données actuelles de la RAM
    MemoryDatabase* db = (MemoryDatabase*)bank.context;

    // 2. On ordonne au storage C de sauvegarder
    if (storage.save(storage.context, db->accounts, db->count)) {
        qDebug() << "💾 Sauvegarde automatique réussie !";
    }

    event->accept(); // On autorise la fermeture
}

void MainWindow::on_registerButton_clicked() {
    bool ok;

    // 1. Saisie des informations
    QString name = QInputDialog::getText(this, "Inscription", "Nom du titulaire :", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;

    int newId = QInputDialog::getInt(this, "Inscription", "ID du compte :", 1000, 1, 99999, 1, &ok);
    if (!ok) return;

    QString pin = QInputDialog::getText(this, "Sécurité", "Code PIN :", QLineEdit::Password, "", &ok);
    if (!ok || pin.isEmpty()) return;

    // 2. On utilise la fonction de création du moteur C
    // On convertit les QString en const char* pour le C
    Account newAcc = create_account(newId, name.toStdString().c_str(), pin.toStdString().c_str());

    // 3. Tentative d'ajout
    if (driver_add_account(&bank, newAcc)) {
        QMessageBox::information(this, "Succès", "Le compte a été créé avec succès !");
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de créer le compte (ID déjà pris ou base pleine).");
    }
}