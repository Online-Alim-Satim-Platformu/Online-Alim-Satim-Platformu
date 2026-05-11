#include "anasayfa.h"
#include "ui_anasayfa.h"
#include "ilanekle.h" // İlan ekleme ekranını açabilmek için ekledik

AnaSayfa::AnaSayfa(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AnaSayfa)
{
    ui->setupUi(this);
}

AnaSayfa::~AnaSayfa()
{
    delete ui;
}

// İlan ver butonuna tıklandığında çalışacak kod:
void AnaSayfa::on_btnIlanVer_clicked()
{
    IlanEkle *ilanEkrani = new IlanEkle();
    ilanEkrani->show();
}
