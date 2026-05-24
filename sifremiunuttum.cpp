#include "sifremiunuttum.h"
#include "ui_sifremiunuttum.h"
#include <QMessageBox>
#include <QSqlQuery>

SifremiUnuttum::SifremiUnuttum(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SifremiUnuttum)
{
    ui->setupUi(this);
}

SifremiUnuttum::~SifremiUnuttum()
{
    delete ui;
}

void SifremiUnuttum::on_btnSifreGuncelle_clicked()
{
    QString kullaniciAdi = ui->txtKullaniciAdi->text().trimmed();
    QString email = ui->txtEmail->text().trimmed();
    QString yeniSifre = ui->txtYeniSifre->text().trimmed();

    if (kullaniciAdi.isEmpty() || email.isEmpty() || yeniSifre.isEmpty()) {
        QMessageBox::warning(this, "Uyarı", "Lütfen boş alan bırakmayınız.");
        return;
    }

    // 1. Önce kullanıcı adı ve e-posta veritabanında eşleşiyor mu diye bakıyoruz
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT * FROM Kullanici WHERE kullaniciAdi = :kullaniciAdi AND email = :email");
    checkQuery.bindValue(":kullaniciAdi", kullaniciAdi);
    checkQuery.bindValue(":email", email);

    if (checkQuery.exec() && checkQuery.next()) {
        // 2. Eşleşme bulundu! Şifreyi güncelliyoruz (UPDATE sorgusu)
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE Kullanici SET sifre = :sifre WHERE kullaniciAdi = :kullaniciAdi AND email = :email");
        updateQuery.bindValue(":sifre", yeniSifre);
        updateQuery.bindValue(":kullaniciAdi", kullaniciAdi);
        updateQuery.bindValue(":email", email);

        if (updateQuery.exec()) {
            QMessageBox::information(this, "Başarılı", "Şifreniz başarıyla güncellendi!\nYeni şifrenizle giriş yapabilirsiniz.");
            this->close(); // Başarılı olunca küçük pencereyi kapatıyoruz
        } else {
            QMessageBox::critical(this, "Hata", "Şifre güncellenirken sistemsel bir hata oluştu.");
        }
    } else {
        QMessageBox::warning(this, "Hata", "Girilen bilgilere ait bir kullanıcı bulunamadı!");
    }
}
