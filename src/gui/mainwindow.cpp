#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include "dashboard.h" 
#include <QCloseEvent>

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
    bank = create_memory_driver();
	storage = create_csv_driver("bank_data.csv");
    
	// 2. CHARGEMENT DES DONNÉES (Le pont C <-> CSV)
    // On crée un tableau temporaire pour accueillir les comptes du fichier
    Account loaded_accounts[100]; 
    int loaded_count = 0;

    if (storage.load(storage.context, loaded_accounts, 100)) {
        // On injecte chaque compte chargé dans notre driver en mémoire
        for (int i = 0; i < 10; i++) {
            driver_add_account(&bank, loaded_accounts[i]);
        }
        qDebug() << "✅ Données CSV chargées avec succès.";
    } else {
        qWarning() << "⚠️ Aucun fichier de données trouvé ou erreur de lecture. On démarre à vide.";
    }	
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    QString idStr = ui->idInput->text();
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
    for(int i = 0; i < db->count; i++) {
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