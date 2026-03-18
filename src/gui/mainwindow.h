#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

extern "C" {
    #include "../system/bank_interface.h"
    #include "../system/memory_driver.h"
	#include "../persistence/storage_interface.h"
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
	void on_registerButton_clicked(); // inscription

private:
    Ui::MainWindow *ui;
    BankDriver bank; // Notre moteur en C 
	StorageDriver storage; // Interface de stockage
	
protected:
    void closeEvent(QCloseEvent *event) override;
};
#endif
