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
}

Dashboard::~Dashboard() { delete ui; }

void Dashboard::updateUI() {
    double bal = m_bank.get_balance(m_bank.context, m_userId);
    ui->balanceLabel->setText(QString("Solde actuel : %1 €").arg(bal, 0, 'f', 2));
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
