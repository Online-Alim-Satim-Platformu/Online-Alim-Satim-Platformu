#include "girisekrani.h"
#include "ui_girisekrani.h"
#include "kayitekrani.h"
#include "anasayfa.h"
#include "session.h"
#include "sifremiunuttum.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSettings>

GirisEkrani::GirisEkrani(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GirisEkrani)
{
    ui->setupUi(this);

    QSettings settings("OnlineAlimSatim", "App");
    ui->chkOturumAcikKalsin->setChecked(settings.value("oturum/hatirla", false).toBool());

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

void GirisEkrani::on_btnSifremiUnuttum_clicked()
{
    SifremiUnuttum *s = new SifremiUnuttum();
    s->setAttribute(Qt::WA_DeleteOnClose);
    s->show();
}

void GirisEkrani::on_btnGirisYap_clicked()
{
    QString email = ui->txtEmail->text();
    QString sifre = ui->txtSifre->text();

    if (email.isEmpty() || sifre.isEmpty()) {
        QMessageBox::warning(this, "Uyarı", "Lütfen e-posta ve şifrenizi giriniz!");
        return;
    }

    // kullaniciId de SELECT'e eklendi — oturum yönetimi için
    QSqlQuery query;
    query.prepare("SELECT kullaniciId, kullaniciAdi FROM Kullanici "
                  "WHERE email = :email AND sifre = :sifre");
    query.bindValue(":email", email);
    query.bindValue(":sifre", sifre);

    if (query.exec() && query.next()) {
        aktifKullaniciId = query.value("kullaniciId").toInt();

        QSettings settings("OnlineAlimSatim", "App");
        if (ui->chkOturumAcikKalsin->isChecked()) {
            settings.setValue("oturum/kullaniciId", aktifKullaniciId);
            settings.setValue("oturum/hatirla", true);
        } else {
            settings.remove("oturum/kullaniciId");
            settings.setValue("oturum/hatirla", false);
        }

        QString ad = query.value("kullaniciAdi").toString();
        QMessageBox::information(this, "Başarılı", "Hoşgeldin, " + ad + "!");

        AnaSayfa *ana = new AnaSayfa();
        ana->show();
        this->close();
    } else {
        QMessageBox::critical(this, "Hata", "E-posta veya şifre hatalı!");
    }
}
