#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QDialog>

extern "C" {
    #include "../system/bank_interface.h"
}

namespace Ui { class Dashboard; }

class Dashboard : public QDialog {
    Q_OBJECT

public:
    // On passe le driver et l'ID du compte connecté au constructeur
    explicit Dashboard(BankDriver bank, int userId, QWidget *parent = nullptr);
    ~Dashboard();

private slots:
    void on_transferButton_clicked();
    void updateUI();

private:
    Ui::Dashboard *ui;
    BankDriver m_bank;
    int m_userId;
};

#endif
