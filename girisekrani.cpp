#include "girisekrani.h"
#include "ui_girisekrani.h"
#include "kayitekrani.h"
#include "anasayfa.h"
#include <QMessageBox>
#include <QSqlQuery>

GirisEkrani::GirisEkrani(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GirisEkrani)
{
    ui->setupUi(this);

    // Büyü burada gerçekleşiyor: Şifre veya E-posta kutusundayken "Enter" tuşuna basılırsa Giriş Yap butonunu tetikle!
    connect(ui->txtSifre, &QLineEdit::returnPressed, this, &GirisEkrani::on_btnGirisYap_clicked);
    connect(ui->txtEmail, &QLineEdit::returnPressed, this, &GirisEkrani::on_btnGirisYap_clicked);
}

GirisEkrani::~GirisEkrani()
{
    delete ui;
}

void GirisEkrani::on_btnHesapAc_clicked()
{
    KayitEkrani *kayitPenceresi = new KayitEkrani();
    kayitPenceresi->show();
    this->close();
}

void GirisEkrani::on_btnGirisYap_clicked()
{
    QString email = ui->txtEmail->text();
    QString sifre = ui->txtSifre->text();

    // 1. Kutucuklar boş mu kontrolü
    if (email.isEmpty() || sifre.isEmpty()) {
        QMessageBox::warning(this, "Uyarı", "Lütfen e-posta ve şifrenizi giriniz!");
        return;
    }

    // 2. Veritabanında kullanıcıyı arama
    QSqlQuery query;
    query.prepare("SELECT * FROM Kullanici WHERE email = :email AND sifre = :sifre");
    query.bindValue(":email", email);
    query.bindValue(":sifre", sifre);

    // Sorgu çalıştıysa ve eşleşen bir kayıt (.next()) bulunduysa:
    if (query.exec() && query.next()) {

        // Araya giren mesaj kutusu kaldırıldı.
        // Doğrudan Ana Sayfaya geçiş yapılıyor.
        AnaSayfa *ana = new AnaSayfa();
        ana->show();
        this->close();

    } else {
        // Kayıt bulunamadıysa:
        QMessageBox::critical(this, "Hata", "E-posta veya şifre hatalı!");
    }
}
