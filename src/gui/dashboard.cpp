#include "dashboard.h"
#include "ui_dashboard.h"
#include <QMessageBox>

extern "C" {
    #include "../common/status.h"
}

Dashboard::Dashboard(BankDriver bank, int userId, QWidget *parent) :
    QDialog(parent), ui(new Ui::Dashboard), m_bank(bank), m_userId(userId) 
{
    ui->setupUi(this);
    updateUI();
	//titre de fenêtre dynamique
	ui->welcomeLabel->setText(QString("Bonjour, Agent %1").arg(m_userId));
this->setWindowTitle("Interface Bancaire Sécurisée - J4cKr0y Enterprises");
}

Dashboard::~Dashboard() { delete ui; }

void Dashboard::updateUI() {
	// 1. Mise à jour du solde
    double bal = m_bank.get_balance(m_bank.context, m_userId);
    ui->balanceLabel->setText(QString("Solde actuel : %1 €").arg(bal, 0, 'f', 2));
	
	// 2. Mise à jour de l'historique
    ui->historyList->clear();
    
    // On récupère le pointeur vers le compte réel dans la DB
    MemoryDatabase* db = (MemoryDatabase*)m_bank.context;
    Account* acc = nullptr;
    
    for(int i = 0; i < db->count; i++) {
        if (db->accounts[i].id == m_userId) {
            acc = &db->accounts[i];
            break;
        }
    }

    if (acc) {
        for (int i = 0; i < acc->transaction_count; i++) {
            Transaction t = acc->history[i];
            QString type = (t.amount > 0) ? "DEPÔT" : "VIREMENT";
            QString item = QString("[%1] %2 : %3 €")
                            .arg(t.timestamp) // Si tu as un timestamp, sinon "Date"
                            .arg(type)
                            .arg(t.amount);
            
            ui->historyList->addItem(item);
            
            // Un peu de couleur pour le fun
            if (t.amount < 0) 
                ui->historyList->item(ui->historyList->count() - 1)->setForeground(Qt::red);
            else 
                ui->historyList->item(ui->historyList->count() - 1)->setForeground(Qt::darkGreen);
        }
    }
}

void Dashboard::on_transferButton_clicked() {
    int destId = ui->destInput->text().toInt();
    double amount = ui->amountInput->text().toDouble();

    // Appel de la fonction de transfert C 
    BankStatus status = m_bank.transfer(m_bank.context, m_userId, destId, amount);

    if (status == STATUS_SUCCESS) {
        QMessageBox::information(this, "Succès", "Virement effectué !");
        updateUI();
    } else {
        QMessageBox::critical(this, "Erreur", get_status_message(status));
    }
}
