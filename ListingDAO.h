#ifndef LISTINGDAO_H
#define LISTINGDAO_H

#include <QList>
#include "Ilan.h"

class ListingDAO {
public:
    ListingDAO();
    ~ListingDAO();

    Ilan* findById(int id);
    QList<Ilan*> findBySeller(int sellerId);
    QList<Ilan*> findByCategory(int categoryId);
    bool save(Ilan* ilan);
    bool update(Ilan* ilan);
    bool remove(int id);
    QList<Ilan*> getAll();
};

#endif // LISTINGDAO_H
