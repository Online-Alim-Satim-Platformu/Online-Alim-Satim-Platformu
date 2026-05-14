#include "ilanekle.h"
#include "ui_ilanekle.h"
#include "databasemanager.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QDateTime>

IlanEkle::IlanEkle(QWidget *parent) : QWidget(parent), ui(new Ui::IlanEkle) {
    ui->setupUi(this);
    secilenFotoYolu = "";

    // Stok spinbox ayarları
    ui->spinStok->setRange(1, 9999);
    ui->spinStok->setValue(1);
    ui->spinStok->setAlignment(Qt::AlignCenter);
    ui->spinStok->setButtonSymbols(QAbstractSpinBox::NoButtons);
}

IlanEkle::~IlanEkle() {
    delete ui;
}

void IlanEkle::on_btnFotoEkle_clicked() {
    QString dosya = QFileDialog::getOpenFileName(this, "Fotoğraf Seç", "", "Resimler (*.png *.jpg *.jpeg)");
    if (!dosya.isEmpty()) {
        secilenFotoYolu = dosya;
        ui->lblFotoOnizleme->setPixmap(QPixmap(dosya).scaled(ui->lblFotoOnizleme->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void IlanEkle::on_btnStokArttir_clicked() {
    ui->spinStok->setValue(ui->spinStok->value() + 1);
}

void IlanEkle::on_btnStokAzalt_clicked() {
    int yeniDeger = ui->spinStok->value() - 1;
    if (yeniDeger < 1) yeniDeger = 1; // En az 1 stok olsun
    ui->spinStok->setValue(yeniDeger);
}

void IlanEkle::on_btnYayinla_clicked() {
    QString baslik = ui->txtBaslik->text();
    double fiyat = ui->txtFiyat->text().toDouble();
    int stokAdedi = ui->spinStok->value();

    // Boşluk ve fiyat kontrolü
    if (baslik.isEmpty() || fiyat <= 0) {
        QMessageBox::warning(this, "Hata", "Lütfen bir başlık ve geçerli bir fiyat giriniz!");
        return;
    }

    if (stokAdedi <= 0) {
        QMessageBox::warning(this, "Hata", "Stok adedi en az 1 olmalıdır!");
        return;
    }

    // Veritabanı bağlantısını al
    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    if (!db.isOpen()) {
        if (!DatabaseManager::getInstance()->baglantiKur()) {
            QMessageBox::critical(this, "Hata", "Veritabanı bağlantısı kurulamadı!");
            return;
        }
    }

    // Fotoğraf kopyalama işlemleri
    QString kaydedilecekAdres = "";
    if (!secilenFotoYolu.isEmpty()) {
        QString imagesDir = qApp->applicationDirPath() + "/images";
        QDir().mkpath(imagesDir);
        kaydedilecekAdres = imagesDir + "/" + QString::number(QDateTime::currentMSecsSinceEpoch()) + ".jpg";
        QFile::copy(secilenFotoYolu, kaydedilecekAdres);
    }

    // Doğru bağlantı üzerinden sorguyu hazırla
    QSqlQuery query(db);
    query.prepare("INSERT INTO Ilan (baslik, fiyat, kategori, aciklama, stokAdedi, fotografYolu) "
                  "VALUES (:b, :f, :k, :a, :s, :foto)");
    query.bindValue(":b", baslik);
    query.bindValue(":f", fiyat);
    query.bindValue(":k", ui->cmbKategori->currentText());
    query.bindValue(":a", ui->txtAciklama->toPlainText());
    query.bindValue(":s", stokAdedi);
    query.bindValue(":foto", kaydedilecekAdres);

    // Sorguyu çalıştır ve sonucu kontrol et
    if (query.exec()) {
        QMessageBox::information(this, "Başarılı", "İlan başarıyla yayınlandı!");
        this->close();
    } else {
        QMessageBox::critical(this, "Sorgu Hatası", "İlan kaydedilemedi!\nHata: " + query.lastError().text());
    }
}

void IlanEkle::on_btnIptal_clicked() {
    this->close();
}
