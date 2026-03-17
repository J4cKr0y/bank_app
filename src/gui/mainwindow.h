#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

extern "C" {
    #include "../system/bank_interface.h"
    #include "../system/memory_driver.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loginButton_clicked(); // Quand on clique sur "Connexion"

private:
    Ui::MainWindow *ui;
    BankDriver bank; // Notre moteur en C 
};
#endif
