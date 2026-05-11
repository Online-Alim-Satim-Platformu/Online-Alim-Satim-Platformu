#include "kayitekrani.h"
#include "ui_kayitekrani.h"
#include "girisekrani.h"
#include "databasemanager.h"
#include <QMessageBox>
#include <QSqlQuery>

KayitEkrani::KayitEkrani(QWidget *parent) : QWidget(parent), ui(new Ui::KayitEkrani) {
    ui->setupUi(this);
}

KayitEkrani::~KayitEkrani() {
    delete ui;
}

void KayitEkrani::on_btnHesapAc_clicked() {
    QString ad = ui->txtAd->text();
    QString soyad = ui->txtSoyad->text();
    QString email = ui->txtEmail->text();
    QString sifre = ui->txtSifre->text();

    if (ad.isEmpty() || soyad.isEmpty() || email.isEmpty() || sifre.isEmpty()) {
        QMessageBox::warning(this, "Uyarı", "Lütfen tüm alanları doldurunuz!");
        return;
    }

    QString kullaniciAdi = ad + " " + soyad;

    QSqlQuery query;
    query.prepare("INSERT INTO Kullanici (kullaniciAdi, sifre, email, rol) VALUES (:ad, :sifre, :email, :rol)");
    query.bindValue(":ad", kullaniciAdi);
    query.bindValue(":sifre", sifre);
    query.bindValue(":email", email);
    query.bindValue(":rol", "Alici");

    if (query.exec()) {
        QMessageBox::information(this, "Başarılı", "Kayıt işlemi tamamlandı! Giriş yapabilirsiniz.");
        GirisEkrani *giris = new GirisEkrani();
        giris->show();
        this->close();
    } else {
        QMessageBox::critical(this, "Hata", "Kayıt yapılamadı! Bu e-posta kullanımda olabilir.");
    }
}

void KayitEkrani::on_btnGirisYapDon_clicked() {
    GirisEkrani *giris = new GirisEkrani();
    giris->show();
    this->close();
}
