#include "ilanekle.h"
#include "ui_ilanekle.h"
#include "databasemanager.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QFileDialog> // Dosya seçme penceresi için
#include <QPixmap>     // Fotoğrafı arayüzde göstermek için
#include <QDir>
#include <QCoreApplication>
#include <QDateTime>

IlanEkle::IlanEkle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IlanEkle)
{
    ui->setupUi(this);
    secilenFotoYolu = ""; // Başlangıçta boş
}

IlanEkle::~IlanEkle()
{
    delete ui;
}

// "Fotoğraf Seç..." butonuna tıklandığında çalışır
void IlanEkle::on_btnFotoEkle_clicked()
{
    // Bilgisayardan resim seçtiriyoruz
    QString dosya = QFileDialog::getOpenFileName(this, "Fotoğraf Seç", "", "Resim Dosyaları (*.png *.jpg *.jpeg)");

    if (!dosya.isEmpty()) {
        secilenFotoYolu = dosya;

        // Seçilen fotoğrafı arayüzdeki kutuda (lblFotoOnizleme) gösteriyoruz
        QPixmap resim(secilenFotoYolu);
        ui->lblFotoOnizleme->setPixmap(resim.scaled(ui->lblFotoOnizleme->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

// "İlanı Yayınla" butonuna tıklandığında çalışır
void IlanEkle::on_btnYayinla_clicked()
{
    QString baslik = ui->txtBaslik->text();
    double fiyat = ui->txtFiyat->text().toDouble();
    QString kategori = ui->cmbKategori->currentText();
    QString aciklama = ui->txtAciklama->toPlainText();

    if (baslik.isEmpty() || fiyat <= 0) {
        QMessageBox::warning(this, "Hata", "Lütfen başlık ve fiyat kısımlarını doldurun!");
        return;
    }

    // --- FOTOĞRAFI PROJE İÇİNE KOPYALAMA İŞLEMİ ---
    QString kaydedilecekAdres = "";

    if (!secilenFotoYolu.isEmpty()) {
        // Projenin çalıştığı klasörde "images" adında bir yer oluşturuyoruz
        QString imagesKlasoru = QCoreApplication::applicationDirPath() + "/images";
        QDir dir;
        if (!dir.exists(imagesKlasoru)) {
            dir.mkpath(imagesKlasoru);
        }

        // Çakışma olmasın diye fotoğrafa o anın zamanından benzersiz bir isim veriyoruz
        QString yeniIsim = imagesKlasoru + "/" + QString::number(QDateTime::currentMSecsSinceEpoch()) + ".jpg";

        // Seçilen fotoğrafı, bilgisayardan alıp kendi klasörümüze kopyalıyoruz
        if (QFile::copy(secilenFotoYolu, yeniIsim)) {
            kaydedilecekAdres = yeniIsim; // Veritabanına bu yeni adresi yazacağız
        }
    }

    // --- VERİTABANINA BİLGİLERİ KAYDETME ---
    QSqlQuery query;
    query.prepare("INSERT INTO Ilan (baslik, fiyat, kategori, aciklama, stokAdedi, fotografYolu) "
                  "VALUES (:baslik, :fiyat, :kat, :aciklama, :stok, :foto)");

    query.bindValue(":baslik", baslik);
    query.bindValue(":fiyat", fiyat);
    query.bindValue(":kat", kategori);
    query.bindValue(":aciklama", aciklama);
    query.bindValue(":stok", 1);
    query.bindValue(":foto", kaydedilecekAdres); // Fotoğrafın adresini yolluyoruz

    if (query.exec()) {
        QMessageBox::information(this, "Başarılı", "İlanınız fotoğraflı olarak başarıyla yayınlandı!");
        this->close(); // Pencereyi kapat
    } else {
        QMessageBox::critical(this, "Hata", "İlan kaydedilirken veritabanı hatası oluştu.");
    }
}
