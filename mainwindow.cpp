#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "IlanFactory.h"
#include "IlanTipleri.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    controller = new ListingController(this);
    refreshList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshList() {
    ui->listWidget->clear();
    QList<Ilan*> ilanlar = controller->getAll();
    for (Ilan* ilan : ilanlar) {
        QString itemText = QString("ID: %1 | %2 - %3 TL | Tip: %4 | Durum: %5")
            .arg(ilan->ilanNo)
            .arg(ilan->baslik)
            .arg(ilan->fiyat)
            .arg(ilan->getTip())
            .arg(static_cast<int>(ilan->durum) == 1 ? "Aktif" : "Taslak");
            
        QListWidgetItem* item = new QListWidgetItem(itemText);
        item->setData(Qt::UserRole, ilan->ilanNo); // ID'yi sakla
        ui->listWidget->addItem(item);
    }
}

void MainWindow::on_btnListele_clicked()
{
    refreshList();
}

void MainWindow::on_btnEkle_clicked()
{
    Ilan* emlak = IlanFactory::ilanOlustur("Emlak");
    if(emlak) {
        emlak->baslik = "Örnek Emlak İlanı";
        emlak->fiyat = 1500000;
        emlak->durum = ListingStatus::Active;
        static_cast<EmlakIlan*>(emlak)->metrekare = "150";
        static_cast<EmlakIlan*>(emlak)->odaSayisi = "3+1";
        
        if (controller->createListing(emlak)) {
            QMessageBox::information(this, "Başarılı", "İlan eklendi.");
            refreshList();
        } else {
            QMessageBox::warning(this, "Hata", "İlan eklenemedi.");
        }
    }
}

void MainWindow::on_btnSil_clicked()
{
    QListWidgetItem* selected = ui->listWidget->currentItem();
    if (selected) {
        int id = selected->data(Qt::UserRole).toInt();
        if (controller->deleteListing(id)) {
            QMessageBox::information(this, "Başarılı", "İlan silindi.");
            refreshList();
        } else {
            QMessageBox::warning(this, "Hata", "İlan silinemedi.");
        }
    } else {
        QMessageBox::warning(this, "Uyarı", "Lütfen silinecek ilanı seçin.");
    }
}

