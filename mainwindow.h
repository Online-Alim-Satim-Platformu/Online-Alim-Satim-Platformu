#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ListingController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnListele_clicked();
    void on_btnEkle_clicked();
    void on_btnSil_clicked();

private:
    Ui::MainWindow *ui;
    ListingController* controller;
    void refreshList();
};
#endif // MAINWINDOW_H
