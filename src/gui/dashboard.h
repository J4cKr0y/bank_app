#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QDialog>

extern "C" {
    #include "../system/bank_interface.h"
    #include "../system/memory_driver.h"
}

namespace Ui { class Dashboard; }

class Dashboard : public QDialog {
    Q_OBJECT

public:
    explicit Dashboard(BankDriver bank, int userId, QWidget *parent = nullptr);
    ~Dashboard();

private slots:
    void on_transferButton_clicked();
    void on_pdfButton_clicked(); // Déclaration ajoutée ici
    void updateUI();

private:
    Ui::Dashboard *ui;
    BankDriver m_bank;
    int m_userId;
};

#endif