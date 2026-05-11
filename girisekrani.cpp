#include "girisekrani.h"
#include "ui_girisekrani.h"

GirisEkrani::GirisEkrani(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GirisEkrani)
{
    ui->setupUi(this);
}

GirisEkrani::~GirisEkrani()
{
    delete ui;
}
