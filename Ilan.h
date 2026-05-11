#ifndef ILAN_H
#define ILAN_H

#include <QString>
#include <QObject>
#include <QDebug>

enum class ListingStatus { Draft, Active, Sold, Removed };

class Ilan : public QObject {
    Q_OBJECT
public:
    explicit Ilan(QObject *parent = nullptr) : QObject(parent), durum(ListingStatus::Draft) {}
    virtual ~Ilan() = default;

    int ilanNo;
    QString baslik;
    double fiyat;
    int kategoriId;
    QString aciklama;
    int saticiId;
    int stokAdedi;
    ListingStatus durum;

    virtual QString getDetay() const = 0;
    virtual QString getTip() const = 0;
};

// Alt Sınıflar
class EmlakIlan : public Ilan {
public:
    QString metrekare;
    QString getTip() const override { return "Emlak"; }
    QString getDetay() const override { return metrekare + " m2"; }
};

class VasitaIlan : public Ilan {
public:
    int kilometre;
    QString getTip() const override { return "Vasita"; }
    QString getDetay() const override { return QString::number(kilometre) + " KM"; }
};
#endif
