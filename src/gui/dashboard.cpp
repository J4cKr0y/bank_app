#include "dashboard.h"
#include "ui_dashboard.h"
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QDateTime>

extern "C" {
    #include "../system/bank_interface.h"
    #include "../system/memory_driver.h"    // Pour MemoryDatabase
    #include "../common/status.h"           // Pour BankStatus
	#include "account/account.h"
    #include "transaction/transaction.h"
}

Dashboard::Dashboard(BankDriver bank, int userId, QWidget *parent) :
    QDialog(parent), ui(new Ui::Dashboard), m_bank(bank), m_userId(userId) 
{
    ui->setupUi(this);
    updateUI();
}

Dashboard::~Dashboard() { delete ui; }

void Dashboard::updateUI() {
    double bal = m_bank.get_balance(m_bank.context, m_userId);
    ui->balanceLabel->setText(QString("Solde actuel : %1 €").arg(bal, 0, 'f', 2));
    ui->welcomeLabel->setText(QString("Compte N° %1").arg(m_userId));

    ui->historyList->clear();
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
            // Correction : Utilisation d'une date fixe ou index car 'timestamp' n'existe pas
            QString item = QString("Opération %1 | %2 : %3 €")
                            .arg(i + 1) 
                            .arg(type)
                            .arg(t.amount);
            ui->historyList->addItem(item);
        }
    }
}

void Dashboard::on_transferButton_clicked() {
    int destId = ui->destInput->text().toInt();
    double amount = ui->amountInput->text().toDouble();

    BankStatus status = m_bank.transfer(m_bank.context, m_userId, destId, amount);

    if (status == STATUS_SUCCESS) {
        QMessageBox::information(this, "Succès", "Virement effectué !");
        updateUI();
    } else {
        QMessageBox::critical(this, "Erreur", "Le virement a échoué.");
    }
}

void Dashboard::on_pdfButton_clicked() {
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter le relevé", "", "PDF (*.pdf)");
    if (fileName.isEmpty()) return;

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    QPainter painter(&pdfWriter);

    painter.drawText(100, 500, "RELEVÉ BANCAIRE - MY BANK");
    painter.drawText(100, 800, QString("Compte : %1").arg(m_userId));

    int y = 1200;
    MemoryDatabase* db = (MemoryDatabase*)m_bank.context;
    for(int i = 0; i < db->count; i++) {
        if (db->accounts[i].id == m_userId) {
            for (int j = 0; j < db->accounts[i].transaction_count; j++) {
                Transaction t = db->accounts[i].history[j];
                painter.drawText(100, y, QString("Opération : %1 €").arg(t.amount));
                y += 200;
            }
        }
    }
    painter.end();
    QMessageBox::information(this, "PDF", "Fichier généré !");
}