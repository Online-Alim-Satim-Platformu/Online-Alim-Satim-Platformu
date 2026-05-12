#include "ilanekle.h"
#include "ui_ilanekle.h"
#include "databasemanager.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QDateTime>
#include <QFile>
#include <QPixmap>

IlanEkle::IlanEkle(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::IlanEkle)
{
    ui->setupUi(this);
    secilenFotoYolu = "";
}

IlanEkle::~IlanEkle()
{
    delete ui;
}

void IlanEkle::on_btnFotoEkle_clicked()
{
    QString dosya = QFileDialog::getOpenFileName(
        this,
        "Fotograf Sec",
        "",
        "Resimler (*.png *.jpg *.jpeg)"
        );

    if (!dosya.isEmpty()) {
        secilenFotoYolu = dosya;

        ui->lblFotoOnizleme->setPixmap(
            QPixmap(dosya).scaled(
                ui->lblFotoOnizleme->size(),
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation
                )
            );
    }
}

void IlanEkle::on_btnYayinla_clicked()
{
    QString baslik = ui->txtBaslik->text();
    double fiyat = ui->txtFiyat->text().toDouble();

    if (baslik.isEmpty() || fiyat <= 0) {
        QMessageBox::warning(
            this,
            "Hata",
            "Lutfen gecerli bilgiler giriniz!"
            );
        return;
    }

    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();

    if (!db.isOpen()) {
        if (!DatabaseManager::getInstance()->baglantiKur()) {
            QMessageBox::critical(
                this,
                "Hata",
                "Veritabani baglantisi kurulamadi!"
                );
            return;
        }
    }

    QString kaydedilecekAdres = "";

    if (!secilenFotoYolu.isEmpty()) {

        QString imagesKlasoru =
            qApp->applicationDirPath() + "/images";

        QDir().mkpath(imagesKlasoru);

        kaydedilecekAdres =
            imagesKlasoru + "/" +
            QString::number(QDateTime::currentMSecsSinceEpoch()) +
            ".jpg";

        QFile::copy(secilenFotoYolu, kaydedilecekAdres);
    }

    QSqlQuery query(db);

    query.prepare(
        "INSERT INTO Ilan "
        "(baslik, fiyat, kategori, aciklama, stokAdedi, fotografYolu) "
        "VALUES (?, ?, ?, ?, ?, ?)"
        );

    query.addBindValue(baslik);
    query.addBindValue(fiyat);
    query.addBindValue(ui->cmbKategori->currentText());
    query.addBindValue(ui->txtAciklama->toPlainText());
    query.addBindValue(1);
    query.addBindValue(kaydedilecekAdres);

    if (query.exec()) {

        QMessageBox::information(
            this,
            "Basarili",
            "Ilan basariyla yayinlandi!"
            );

        this->close();

    } else {

        QMessageBox::critical(
            this,
            "Sorgu Hatasi",
            "Ilan kaydedilemedi!\nHata:\n" +
                query.lastError().text()
            );

        qDebug() << query.lastError().text();
    }
}

void IlanEkle::on_btnIptal_clicked()
{
    this->close();
}
