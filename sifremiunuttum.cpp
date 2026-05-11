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
    QString email = ui->txtEmail->text();
    QString yeniSifre = ui->txtYeniSifre->text();

    if (email.isEmpty() || yeniSifre.isEmpty()) {
        QMessageBox::warning(this, "Uyarı", "Lütfen boş alan bırakmayınız.");
        return;
    }

    // 1. Önce böyle bir e-posta veritabanında var mı diye bakıyoruz
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT * FROM Kullanici WHERE email = :email");
    checkQuery.bindValue(":email", email);

    if (checkQuery.exec() && checkQuery.next()) {
        // 2. E-posta bulundu! Şifreyi güncelliyoruz (UPDATE sorgusu)
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE Kullanici SET sifre = :sifre WHERE email = :email");
        updateQuery.bindValue(":sifre", yeniSifre);
        updateQuery.bindValue(":email", email);

        if (updateQuery.exec()) {
            QMessageBox::information(this, "Başarılı", "Şifreniz başarıyla güncellendi!\nYeni şifrenizle giriş yapabilirsiniz.");
            this->close(); // Başarılı olunca küçük pencereyi kapatıyoruz
        } else {
            QMessageBox::critical(this, "Hata", "Şifre güncellenirken sistemsel bir hata oluştu.");
        }
    } else {
        QMessageBox::warning(this, "Hata", "Bu e-posta adresine ait bir hesap bulunamadı!");
    }
}
