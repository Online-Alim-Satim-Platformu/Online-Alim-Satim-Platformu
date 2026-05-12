#ifndef ILAN_H
#define ILAN_H

#include <QString>
#include <QObject>
#include <QDebug>
#include <QList>
#include "IObserver.h"

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

    void ekleGozlemci(IObserver* gozlemci) {
        if (gozlemci && !gozlemciler.contains(gozlemci)) {
            gozlemciler.append(gozlemci);
        }
    }

    void bildir() {
        for (IObserver* gozlemci : gozlemciler) {
            gozlemci->guncelle(this);
        }
    }

    bool isActive() const {
        return durum == ListingStatus::Active;
    }

protected:
    QList<IObserver*> gozlemciler;
};

#endif
