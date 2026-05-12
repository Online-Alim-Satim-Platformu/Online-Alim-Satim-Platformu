#ifndef ILANTIPLERI_H
#define ILANTIPLERI_H

#include "Ilan.h"

class EmlakIlan : public Ilan {
public:
    QString metrekare;
    QString odaSayisi;
    QString getDetay() const override { return QString("%1 m2, %2 Oda").arg(metrekare, odaSayisi); }
    QString getTip() const override { return "Emlak"; }
};

class VasitaIlan : public Ilan {
public:
    int kilometre;
    int modelYili;
    QString getDetay() const override { return QString("%1 KM, %2 Model").arg(QString::number(kilometre), QString::number(modelYili)); }
    QString getTip() const override { return "Vasita"; }
};

class ElektronikIlan : public Ilan {
public:
    QString marka;
    int garantiSuresi;
    QString getDetay() const override { return QString("%1 Marka, %2 Ay Garanti").arg(marka, QString::number(garantiSuresi)); }
    QString getTip() const override { return "Elektronik"; }
};

class GiyimIlan : public Ilan {
public:
    QString beden;
    QString renk;
    QString getDetay() const override { return QString("Beden: %1, Renk: %2").arg(beden, renk); }
    QString getTip() const override { return "Giyim"; }
};

#endif // ILANTIPLERI_H
