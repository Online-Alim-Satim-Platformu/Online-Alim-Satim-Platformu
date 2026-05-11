#include "kayitekrani.h"
#include "ui_kayitekrani.h"
#include "girisekrani.h"
#include "databasemanager.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

KayitEkrani::KayitEkrani(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::KayitEkrani)
{
    ui->setupUi(this);
}

KayitEkrani::~KayitEkrani()
{
    delete ui;
}

// "HESAP AÇ" butonuna tıklandığında çalışacak kod
void KayitEkrani::on_btnHesapAc_clicked()
{
    // Arayüzdeki kutucuklardan yazıları alıyoruz
    QString ad = ui->txtAd->text();
    QString soyad = ui->txtSoyad->text();
    QString email = ui->txtEmail->text();
    QString sifre = ui->txtSifre->text();

    // 1. Boş alan kontrolü
    if (ad.isEmpty() || soyad.isEmpty() || email.isEmpty() || sifre.isEmpty()) {
        QMessageBox::warning(this, "Uyarı", "Lütfen tüm alanları doldurunuz!");
        return;
    }

    // 2. Veritabanına kayıt işlemi
    QString kullaniciAdi = ad + " " + soyad; // Ad ve soyadı birleştirip tek isim yapıyoruz

    QSqlQuery query;
    // Güvenli SQL yazımı için prepare() kullanıyoruz
    query.prepare("INSERT INTO Kullanici (kullaniciAdi, sifre, email, rol) "
                  "VALUES (:kullaniciAdi, :sifre, :email, :rol)");

    query.bindValue(":kullaniciAdi", kullaniciAdi);
    query.bindValue(":sifre", sifre); // Proje raporunda hash'lenecek denmişti, altyapı hazır. Şimdilik düz kaydediyoruz.
    query.bindValue(":email", email);
    query.bindValue(":rol", "Alici"); // Yeni kayıt olanları varsayılan olarak "Alici" yapıyoruz

    // Sorguyu çalıştır
    if (query.exec()) {
        QMessageBox::information(this, "Başarılı", "Kayıt işlemi başarıyla tamamlandı!\nGiriş yapabilirsiniz.");

        // Kayıt başarılıysa otomatik olarak Giriş Ekranına yönlendir
        GirisEkrani *giris = new GirisEkrani();
        giris->show();
        this->close();
    } else {
        // Eğer aynı e-posta ile kayıt olmaya çalışırlarsa hata verir (Çünkü tabloda UNIQUE dedik)
        QMessageBox::critical(this, "Hata", "Kayıt yapılamadı! Bu e-posta adresi zaten kullanılıyor olabilir.");
    }
}

// "Zaten hesabın var mı? Giriş Yap" butonuna tıklandığında
void KayitEkrani::on_btnGirisYapDon_clicked()
{
    GirisEkrani *giris = new GirisEkrani();
    giris->show();
    this->close();
}
