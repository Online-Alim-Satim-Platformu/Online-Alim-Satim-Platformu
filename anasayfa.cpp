#include "anasayfa.h"
#include "ui_anasayfa.h"
#include "ilanekle.h"
#include <QSqlQuery>
#include <QDebug>

AnaSayfa::AnaSayfa(QWidget *parent) : QWidget(parent), ui(new Ui::AnaSayfa) {
    ui->setupUi(this);
    ilanlariYukle();
}

AnaSayfa::~AnaSayfa() { delete ui; }

void AnaSayfa::ilanlariYukle() {
    ui->listVitrin->clear();
    QSqlQuery query("SELECT baslik, fiyat FROM Ilan");
    while (query.next()) {
        ui->listVitrin->addItem(query.value(0).toString() + " - " + query.value(1).toString() + " TL");
    }
}

void AnaSayfa::on_btnIlanVer_clicked() {
    IlanEkle *ekran = new IlanEkle();
    // Pencere kapandığında ana sayfayı tazelemesi için sinyal bağlantısı
    connect(ekran, &IlanEkle::destroyed, this, [=](){
        this->ilanlariYukle();
    });
    ekran->setAttribute(Qt::WA_DeleteOnClose);
    ekran->show();
}

void AnaSayfa::on_btnEmlak_clicked() { /* Filtreleme kodları buraya */ }
void AnaSayfa::on_btnVasita_clicked() { /* Filtreleme kodları buraya */ }
void AnaSayfa::on_btnElektronik_clicked() { /* Filtreleme kodları buraya */ }
void AnaSayfa::on_btnGiyim_clicked() { /* Filtreleme kodları buraya */ }
