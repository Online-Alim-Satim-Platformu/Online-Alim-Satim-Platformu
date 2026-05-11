#include "ListingController.h"
#include <QDebug>

ListingController::ListingController(QObject *parent) : QObject(parent) {}

bool ListingController::createListing(Ilan* ilan) {
    if(ilan) {
        m_ilanlar.append(ilan);
        qDebug() << "İlan başarıyla oluşturuldu:" << ilan->baslik;
        return true;
    }
    return false;
}

bool ListingController::updateListing(int id, Ilan* yeniVeri) {
    qDebug() << id << "nolu ilan güncelleniyor.";
    return true;
}

bool ListingController::deleteListing(int id) {
    for(int i = 0; i < m_ilanlar.size(); ++i) {
        if(m_ilanlar[i]->ilanNo == id) {
            delete m_ilanlar.takeAt(i);
            qDebug() << id << "nolu ilan silindi.";
            return true;
        }
    }
    return false;
}

bool ListingController::changeStatus(int id, ListingStatus yeniDurum) {
    qDebug() << id << "nolu ilanın durumu değiştirildi.";
    return true;
}

QList<Ilan*> ListingController::getAll() const {
    return m_ilanlar;
}
