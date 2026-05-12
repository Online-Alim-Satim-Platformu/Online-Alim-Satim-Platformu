#include "ListingDAO.h"
#include <QDebug>

ListingDAO::ListingDAO() {
}

ListingDAO::~ListingDAO() {
}

Ilan* ListingDAO::findById(int id) {
    qDebug() << "ListingDAO::findById çağrıldı. id:" << id;
    // Todo: DatabaseManager kullanılarak veritabanından veri çekilecek
    return nullptr;
}

QList<Ilan*> ListingDAO::findBySeller(int sellerId) {
    qDebug() << "ListingDAO::findBySeller çağrıldı. sellerId:" << sellerId;
    return QList<Ilan*>();
}

QList<Ilan*> ListingDAO::findByCategory(int categoryId) {
    qDebug() << "ListingDAO::findByCategory çağrıldı. categoryId:" << categoryId;
    return QList<Ilan*>();
}

bool ListingDAO::save(Ilan* ilan) {
    if (!ilan) return false;
    qDebug() << "ListingDAO::save çağrıldı. ilanNo:" << ilan->ilanNo;
    return true;
}

bool ListingDAO::update(Ilan* ilan) {
    if (!ilan) return false;
    qDebug() << "ListingDAO::update çağrıldı. ilanNo:" << ilan->ilanNo;
    return true;
}

bool ListingDAO::remove(int id) {
    qDebug() << "ListingDAO::remove çağrıldı. id:" << id;
    return true;
}

QList<Ilan*> ListingDAO::getAll() {
    qDebug() << "ListingDAO::getAll çağrıldı.";
    return QList<Ilan*>();
}
