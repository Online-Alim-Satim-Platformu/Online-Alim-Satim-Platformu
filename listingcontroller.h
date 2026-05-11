#ifndef LISTINGCONTROLLER_H
#define LISTINGCONTROLLER_H

#include <QObject>
#include <QList>
#include "Ilan.h"

class ListingController : public QObject {
    Q_OBJECT
private:
    QList<Ilan*> m_ilanlar;

public:
    explicit ListingController(QObject *parent = nullptr);

    bool createListing(Ilan* ilan);
    bool updateListing(int id, Ilan* yeniVeri);
    bool deleteListing(int id);
    bool changeStatus(int id, ListingStatus yeniDurum);
    QList<Ilan*> getAll() const;
};

#endif
