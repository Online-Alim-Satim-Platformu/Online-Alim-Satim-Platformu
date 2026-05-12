#include "ListingController.h"
#include <QDebug>

ListingController::ListingController(QObject *parent) : QObject(parent) {
    dao = new ListingDAO();
}

ListingController::~ListingController() {
    delete dao;
}

bool ListingController::createListing(Ilan* ilan) {
    if(ilan) {
        if (dao->save(ilan)) {
            qDebug() << "İlan başarıyla oluşturuldu ve DAO ile kaydedildi:" << ilan->baslik;
            return true;
        }
    }
    return false;
}

bool ListingController::updateListing(int id, Ilan* yeniVeri) {
    qDebug() << id << "nolu ilan güncelleniyor.";
    if (yeniVeri) {
        yeniVeri->ilanNo = id; // ID'nin doğru olmasını garantile
        return dao->update(yeniVeri);
    }
    return false;
}

bool ListingController::deleteListing(int id) {
    qDebug() << id << "nolu ilan siliniyor.";
    return dao->remove(id);
}

bool ListingController::changeStatus(int id, ListingStatus yeniDurum) {
    qDebug() << id << "nolu ilanın durumu değiştiriliyor.";
    Ilan* ilan = dao->findById(id);
    if (ilan) {
        ilan->durum = yeniDurum;
        ilan->bildir(); // İlan durum değişikliğini observer'lara (StokYöneticisi vs) bildir
        return dao->update(ilan);
    }
    return false;
}

QList<Ilan*> ListingController::getAll() const {
    return dao->getAll();
}

QList<Ilan*> ListingController::searchListings(const QString& q) {
    qDebug() << "Arama yapılıyor:" << q;
    return QList<Ilan*>();
}

QList<Ilan*> ListingController::filterListings(const QString& filterParams) {
    qDebug() << "Filtreleme yapılıyor:" << filterParams;
    return QList<Ilan*>();
}

QList<Ilan*> ListingController::getByCategory(int catId) {
    return dao->findByCategory(catId);
}
