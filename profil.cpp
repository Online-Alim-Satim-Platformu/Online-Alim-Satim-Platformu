#include "profil.h"
#include "ui_profil.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

Profil::Profil(QWidget *parent) : QWidget(parent), ui(new Ui::Profil) {
    ui->setupUi(this);

    // Pencere açıldığı an bilgileri ve ilanları yükle
    kullaniciBilgileriniYukle();
    profilIlanlariniYukle();
}

Profil::~Profil() {
    delete ui;
}

void Profil::kullaniciBilgileriniYukle() {
    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    QSqlQuery query(db);

    // Kullanıcı tablosundan ilk kaydı çekiyoruz
    if (query.exec("SELECT kullaniciAdi, email FROM Kullanici LIMIT 1")) {
        if (query.next()) {
            ui->lblAdSoyad->setText(query.value("kullaniciAdi").toString());
            ui->lblEmail->setText(query.value("email").toString());
        } else {
            // Tablo boşsa varsayılan bilgileri göster
            ui->lblAdSoyad->setText("Berat");
            ui->lblEmail->setText("berat@example.com");
        }
    } else {
        qDebug() << "Kullanıcı bilgisi çekilirken hata:" << query.lastError().text();
    }
}

void Profil::profilIlanlariniYukle() {
    ui->listProfilIlanlar->clear(); // Önce listeyi temizle

    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    if (!db.isOpen()) {
        qDebug() << "Veritabanı kapalı, açılıyor...";
        db.open();
    }

    QSqlQuery query(db);
    // 'Ilan' tablosundaki tüm verileri çekiyoruz
    if (query.exec("SELECT ilanNo, baslik, fiyat FROM Ilan")) {
        int ilanSayisi = 0;
        while (query.next()) {
            ilanSayisi++;
            int id = query.value("ilanNo").toInt();
            QString baslik = query.value("baslik").toString();
            QString fiyat = query.value("fiyat").toString();

            // Listeye yeni bir öğe ekliyoruz
            QListWidgetItem *item = new QListWidgetItem();
            item->setText(baslik + " - " + fiyat + " TL");

            // Silme işlemi için ilanNo bilgisini gizli veri (UserRole) olarak saklıyoruz
            item->setData(Qt::UserRole, id);

            ui->listProfilIlanlar->addItem(item);
        }
        qDebug() << "Profil ekranına " << ilanSayisi << " adet ilan yüklendi.";
    } else {
        qDebug() << "İlanlar yüklenirken sorgu hatası:" << query.lastError().text();
        QMessageBox::critical(this, "Hata", "İlanlar veritabanından çekilemedi!");
    }
}

void Profil::on_btnIlanSil_clicked() {
    QListWidgetItem *seciliItem = ui->listProfilIlanlar->currentItem();

    if (!seciliItem) {
        QMessageBox::warning(this, "Uyarı", "Lütfen önce silinecek ilanı seçin!");
        return;
    }

    // 1. ONAY KUTUSU AYARLARI
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Onay");
    msgBox.setText("Bu ilanı silmek istediğinize emin misiniz?");
    msgBox.setIcon(QMessageBox::Question);
    QPushButton *evetButonu = msgBox.addButton("Evet", QMessageBox::YesRole);
    QPushButton *hayirButonu = msgBox.addButton("Hayır", QMessageBox::NoRole);

    // Siyah yazı ve beyaz arka plan stili
    QString stil = "QMessageBox { background-color: #ffffff; }"
                   "QLabel { color: #000000; font-size: 11pt; font-weight: bold; }"
                   "QPushButton { color: #000000; background-color: #e1e1e1; border: 1px solid #adadad; padding: 5px; min-width: 80px; border-radius: 4px; }";
    msgBox.setStyleSheet(stil);
    msgBox.exec();

    if (msgBox.clickedButton() == evetButonu) {
        int id = seciliItem->data(Qt::UserRole).toInt();
        QSqlQuery query(DatabaseManager::getInstance()->getDatabase());
        query.prepare("DELETE FROM Ilan WHERE ilanNo = :id");
        query.bindValue(":id", id);

        if (query.exec()) {
            // 2. BAŞARILI MESAJI (Görüntüdeki ekranın renkli hali)
            QMessageBox infoBox(this);
            infoBox.setWindowTitle("Başarılı");
            infoBox.setText("İlan başarıyla silindi.");
            infoBox.setIcon(QMessageBox::Information);

            // Tamam butonunu siyah yapalım
            QPushButton *okButonu = infoBox.addButton("Tamam", QMessageBox::AcceptRole);
            infoBox.setStyleSheet(stil); // Aynı siyah-beyaz stili buna da uyguluyoruz

            infoBox.exec();

            profilIlanlariniYukle(); // Listeyi yenile
        } else {
            // Hata mesajı gerekirse onu da renklendirebilirsin
            qDebug() << "Hata:" << query.lastError().text();
        }
    }
}

void Profil::on_btnSifreDegistir_clicked() {
    QMessageBox::information(this, "Bilgi", "Şifre değiştirme fonksiyonu yakında aktif edilecek.");
}

void Profil::on_btnGeri_clicked() {
    this->close();
}
