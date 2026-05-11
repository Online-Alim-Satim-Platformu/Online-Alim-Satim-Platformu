#include "ilanekle.h"
#include "ui_ilanekle.h"
#include "databasemanager.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDir>
#include <QDateTime>

IlanEkle::IlanEkle(QWidget *parent) : QWidget(parent), ui(new Ui::IlanEkle) {
    ui->setupUi(this);
    secilenFotoYolu = "";
}

IlanEkle::~IlanEkle() { delete ui; }

void IlanEkle::on_btnFotoEkle_clicked() {
    QString dosya = QFileDialog::getOpenFileName(this, "Fotoğraf Seç", "", "Resimler (*.png *.jpg *.jpeg)");
    if (!dosya.isEmpty()) {
        secilenFotoYolu = dosya;
        ui->lblFotoOnizleme->setPixmap(QPixmap(dosya).scaled(ui->lblFotoOnizleme->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void IlanEkle::on_btnYayinla_clicked() {
    QString baslik = ui->txtBaslik->text();
    double fiyat = ui->txtFiyat->text().toDouble();

    if (baslik.isEmpty() || fiyat <= 0) {
        QMessageBox::warning(this, "Hata", "Başlık ve geçerli bir fiyat giriniz!");
        return;
    }

    QString kaydedilecekAdres = "";
    if (!secilenFotoYolu.isEmpty()) {
        QString imagesDir = qApp->applicationDirPath() + "/images";
        QDir().mkpath(imagesDir);
        kaydedilecekAdres = imagesDir + "/" + QString::number(QDateTime::currentMSecsSinceEpoch()) + ".jpg";
        QFile::copy(secilenFotoYolu, kaydedilecekAdres);
    }

    QSqlQuery query;
    query.prepare("INSERT INTO Ilan (baslik, fiyat, kategori, aciklama, stokAdedi, fotografYolu) "
                  "VALUES (:b, :f, :k, :a, :s, :foto)");
    query.bindValue(":b", baslik);
    query.bindValue(":f", fiyat);
    query.bindValue(":k", ui->cmbKategori->currentText());
    query.bindValue(":a", ui->txtAciklama->toPlainText());
    query.bindValue(":s", 1);
    query.bindValue(":foto", kaydedilecekAdres);

    if (query.exec()) {
        QMessageBox::information(this, "Başarılı", "İlan yayınlandı!");
        this->close();
    }
}

void IlanEkle::on_btnIptal_clicked() { this->close(); }
