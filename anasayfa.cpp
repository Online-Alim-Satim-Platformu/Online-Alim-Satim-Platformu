#include "anasayfa.h"
#include "ui_anasayfa.h"

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
