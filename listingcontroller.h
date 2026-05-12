#ifndef LISTINGCONTROLLER_H
#define LISTINGCONTROLLER_H

#include <QObject>
#include <QList>
#include "Ilan.h"
#include "ListingDAO.h"

class ListingController : public QObject {
    Q_OBJECT
private:
    ListingDAO* dao;

public:
    explicit ListingController(QObject *parent = nullptr);
    ~ListingController();

    bool createListing(Ilan* ilan);
    bool updateListing(int id, Ilan* yeniVeri);
    bool deleteListing(int id);
    bool changeStatus(int id, ListingStatus yeniDurum);
    QList<Ilan*> getAll() const;

    QList<Ilan*> searchListings(const QString& q);
    QList<Ilan*> filterListings(const QString& filterParams);
    QList<Ilan*> getByCategory(int catId);
};

#endif
