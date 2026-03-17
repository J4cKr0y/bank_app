#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include "dashboard.h" 

// Inclusion des fonctions C
extern "C" {
    #include "../system/bank_interface.h"
    #include "../system/memory_driver.h"
    #include "../auth/auth.h"
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // Initialisation du moteur C
    bank = create_memory_driver();
    
    // TODO : charger ici les données CSV 
    // avec storage.load() comme on l'a fait dans le main.c
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    QString idStr = ui->idInput->text();
    QString pinStr = ui->pinInput->text();

    if (verify_pin(db->accounts[i].pin_hash, pinStr.toStdString().c_str())) {
        // Cacher la fenêtre de login
        this->hide();
        
        // Ouvrir le Dashboard
        Dashboard dash(bank, id, this);
        dash.exec(); // Bloquant jusqu'à la fermeture du dashboard
        
        // Réafficher le login après déconnexion
        this->show();
    }

    if (idStr.isEmpty() || pinStr.isEmpty()) {
        QMessageBox::warning(this, "Champs vides", "Veuillez remplir tous les champs.");
        return;
    }

    int id = idStr.toInt();
    
    // 1. Accès sécurisé aux données (via le driver C)
    // On doit caster le contexte car Qt est en C++
    MemoryDatabase* db = (MemoryDatabase*)bank.context;
    bool found = false;

    for(int i = 0; i < db->count; i++) {
        if (db->accounts[i].id == id) {
            found = true;
            // 2. Vérification du PIN via notre module auth.c
            if (verify_pin(db->accounts[i].pin_hash, pinStr.toStdString().c_str())) {
                QMessageBox::information(this, "Succès", "Connexion réussie !");
                // Ici, on pourrait ouvrir une nouvelle fenêtre "Tableau de Bord"
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
