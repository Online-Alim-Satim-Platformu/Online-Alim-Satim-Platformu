#include "profil.h"
#include "ui_profil.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QDebug>

Profil::Profil(QWidget *parent) : QWidget(parent), ui(new Ui::Profil) {
    ui->setupUi(this);

    // Pencere açıldığı an her iki fonksiyonu da çağırıyoruz
    kullaniciBilgileriniYukle();
    profilIlanlariniYukle();
}

Profil::~Profil() {
    delete ui;
}

void Profil::kullaniciBilgileriniYukle() {
    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    QSqlQuery query(db);

    // Tablodan şimdilik ilk kullanıcıyı çekiyoruz
    if (query.exec("SELECT kullaniciAdi, email FROM Kullanici LIMIT 1")) {
        if (query.next()) {
            // Kullanıcı bulunduysa bilgileri ekrana yaz
            ui->lblAdSoyad->setText(query.value("kullaniciAdi").toString());
            ui->lblEmail->setText(query.value("email").toString());
        } else {
            // Kullanıcı yoksa boş kalmasın diye uyarı yazısı
            ui->lblAdSoyad->setText("Kayıtlı Kullanıcı Yok");
            ui->lblEmail->setText("Lütfen önce kayıt olun.");
        }
    } else {
        qDebug() << "Kullanıcı bilgisi çekilemedi:" << query.lastError().text();
    }
}

void Profil::profilIlanlariniYukle() {
    ui->listProfilIlanlar->clear(); // Önceki listeyi temizle

    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    QSqlQuery query(db);

    // İlanları çek ve listeye ekle
    if (query.exec("SELECT ilanNo, baslik, fiyat FROM Ilan")) {
        while (query.next()) {
            int ilanNo = query.value("ilanNo").toInt();
            QString baslik = query.value("baslik").toString();
            QString fiyat = query.value("fiyat").toString();

            QListWidgetItem *item = new QListWidgetItem();
            item->setText(baslik + " - " + fiyat + " TL");

            // Silme işlemi için ilan ID'sini öğeye gizliyoruz
            item->setData(Qt::UserRole, ilanNo);

            ui->listProfilIlanlar->addItem(item);
        }
    } else {
        qDebug() << "İlanlar listelenemedi:" << query.lastError().text();
    }
}

void Profil::on_btnIlanSil_clicked() {
    QListWidgetItem *seciliItem = ui->listProfilIlanlar->currentItem();

    if (!seciliItem) {
        QMessageBox::warning(this, "Uyarı", "Lütfen silmek istediğiniz ilanı listeden seçin.");
        return;
    }

    QMessageBox::StandardButton onay;
    onay = QMessageBox::question(this, "İlanı Sil",
                                 "Bu ilanı kalıcı olarak silmek istediğinize emin misiniz?",
                                 QMessageBox::Yes | QMessageBox::No);

    if (onay == QMessageBox::No) {
        return;
    }

    // Gizlediğimiz ID'yi alıp veritabanından siliyoruz
    int silinecekID = seciliItem->data(Qt::UserRole).toInt();

    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    QSqlQuery query(db);

    query.prepare("DELETE FROM Ilan WHERE ilanNo = :id");
    query.bindValue(":id", silinecekID);

    if (query.exec()) {
        QMessageBox::information(this, "Başarılı", "İlan başarıyla silindi.");
        profilIlanlariniYukle(); // Listeyi yenile ki silinen ilan ekrandan gitsin
    } else {
        QMessageBox::critical(this, "Hata", "İlan silinemedi: " + query.lastError().text());
    }
}

void Profil::on_btnSifreDegistir_clicked() {
    QMessageBox::information(this, "Bilgi", "Şifre değiştirme özelliği daha sonra eklenecektir.");
}

void Profil::on_btnGeri_clicked() {
    this->close(); // Ekranı kapatır ve anasayfaya döndürür
}
