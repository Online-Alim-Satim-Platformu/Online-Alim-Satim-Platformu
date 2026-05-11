#include "anasayfa.h"
#include "ui_anasayfa.h"
#include "ilanekle.h"
#include "databasemanager.h"
#include "profil.h" // <--- BU SATIR COK KRITIK, MUTLAKA OLMALI
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QIcon>
#include <QListWidgetItem>

AnaSayfa::AnaSayfa(QWidget *parent) : QWidget(parent), ui(new Ui::AnaSayfa) {
    ui->setupUi(this);

    // Veritabanı bağlantısını kur ve ilanları yükle
    if(DatabaseManager::getInstance()->baglantiKur()) {
        ilanlariYukle();
    }
}

AnaSayfa::~AnaSayfa() {
    delete ui;
}

void AnaSayfa::ilanlariYukle() {
    ui->listVitrin->clear();
    ui->listVitrin->setIconSize(QSize(120, 120));

    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    QSqlQuery query(db);

    if (query.exec("SELECT baslik, fiyat, fotografYolu FROM Ilan")) {
        while (query.next()) {
            QListWidgetItem *item = new QListWidgetItem();
            item->setText(query.value("baslik").toString() + "\n" + query.value("fiyat").toString() + " TL");
            item->setTextAlignment(Qt::AlignCenter);

            QString foto = query.value("fotografYolu").toString();
            if (!foto.isEmpty()) {
                item->setIcon(QIcon(foto));
            } else {
                item->setIcon(style()->standardIcon(QStyle::SP_FileIcon));
            }

            ui->listVitrin->addItem(item);
        }
    }
}

// PROFIL EKRANINI ACAN BUTON FONKSIYONU
void AnaSayfa::on_btnProfil_clicked() {
    Profil *p = new Profil(); // Profil sınıfından yeni bir pencere oluşturur
    p->setAttribute(Qt::WA_DeleteOnClose); // Pencere kapandığında hafızadan siler
    p->show(); // Pencereyi ekranda gösterir
}

void AnaSayfa::on_btnTumVitrin_clicked() {
    ilanlariYukle();
}

void AnaSayfa::on_btnIlanVer_clicked() {
    IlanEkle *ekran = new IlanEkle();
    connect(ekran, &IlanEkle::destroyed, this, [this](){
        this->ilanlariYukle();
    });
    ekran->setAttribute(Qt::WA_DeleteOnClose);
    ekran->show();
}

// Filtreleme butonları (Geliştirilebilir)
void AnaSayfa::on_btnEmlak_clicked() { ilanlariYukle(); }
void AnaSayfa::on_btnVasita_clicked() { ilanlariYukle(); }
void AnaSayfa::on_btnElektronik_clicked() { ilanlariYukle(); }
void AnaSayfa::on_btnGiyim_clicked() { ilanlariYukle(); }
