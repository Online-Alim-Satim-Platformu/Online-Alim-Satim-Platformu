#include "ListingDAO.h"
#include "DatabaseManager.h"
#include "IlanFactory.h"
#include <QVariant>
#include <QDebug>

ListingDAO::ListingDAO() {
    DatabaseManager::getInstance()->baglantiKur("veritabani.sqlite");
    DatabaseManager::getInstance()->initTables();
}

ListingDAO::~ListingDAO() {
}

Ilan* ListingDAO::findById(int id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Ilanlar WHERE ilanNo = :id");
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        QString tip = query.value("tip").toString();
        Ilan* ilan = IlanFactory::ilanOlustur(tip);
        if (ilan) {
            ilan->ilanNo = query.value("ilanNo").toInt();
            ilan->baslik = query.value("baslik").toString();
            ilan->fiyat = query.value("fiyat").toDouble();
            ilan->durum = static_cast<ListingStatus>(query.value("durum").toInt());
        }
        return ilan;
    }
    return nullptr;
}

QList<Ilan*> ListingDAO::findBySeller(int sellerId) {
    QList<Ilan*> liste;
    QSqlQuery query;
    query.prepare("SELECT * FROM Ilanlar WHERE saticiId = :saticiId");
    query.bindValue(":saticiId", sellerId);
    if (query.exec()) {
        while (query.next()) {
            Ilan* ilan = IlanFactory::ilanOlustur(query.value("tip").toString());
            if (ilan) {
                ilan->ilanNo = query.value("ilanNo").toInt();
                ilan->baslik = query.value("baslik").toString();
                ilan->fiyat = query.value("fiyat").toDouble();
                ilan->durum = static_cast<ListingStatus>(query.value("durum").toInt());
                liste.append(ilan);
            }
        }
    }
    return liste;
}

QList<Ilan*> ListingDAO::findByCategory(int categoryId) {
    QList<Ilan*> liste;
    QSqlQuery query;
    query.prepare("SELECT * FROM Ilanlar WHERE kategoriId = :kategoriId");
    query.bindValue(":kategoriId", categoryId);
    if (query.exec()) {
        while (query.next()) {
            Ilan* ilan = IlanFactory::ilanOlustur(query.value("tip").toString());
            if (ilan) {
                ilan->ilanNo = query.value("ilanNo").toInt();
                ilan->baslik = query.value("baslik").toString();
                ilan->fiyat = query.value("fiyat").toDouble();
                ilan->durum = static_cast<ListingStatus>(query.value("durum").toInt());
                liste.append(ilan);
            }
        }
    }
    return liste;
}

bool ListingDAO::save(Ilan* ilan) {
    if (!ilan) return false;
    QSqlQuery query;
    query.prepare("INSERT INTO Ilanlar (baslik, fiyat, tip, detay, durum) VALUES (:baslik, :fiyat, :tip, :detay, :durum)");
    query.bindValue(":baslik", ilan->baslik);
    query.bindValue(":fiyat", ilan->fiyat);
    query.bindValue(":tip", ilan->getTip());
    query.bindValue(":detay", ilan->getDetay());
    query.bindValue(":durum", static_cast<int>(ilan->durum));
    
    if (query.exec()) {
        ilan->ilanNo = query.lastInsertId().toInt();
        return true;
    }
    qDebug() << "Kaydetme hatası:" << query.lastError().text();
    return false;
}

bool ListingDAO::update(Ilan* ilan) {
    if (!ilan) return false;
    QSqlQuery query;
    query.prepare("UPDATE Ilanlar SET baslik = :baslik, fiyat = :fiyat, durum = :durum WHERE ilanNo = :id");
    query.bindValue(":baslik", ilan->baslik);
    query.bindValue(":fiyat", ilan->fiyat);
    query.bindValue(":durum", static_cast<int>(ilan->durum));
    query.bindValue(":id", ilan->ilanNo);
    return query.exec();
}

bool ListingDAO::remove(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM Ilanlar WHERE ilanNo = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QList<Ilan*> ListingDAO::getAll() {
    QList<Ilan*> liste;
    QSqlQuery query("SELECT * FROM Ilanlar");
    while (query.next()) {
        Ilan* ilan = IlanFactory::ilanOlustur(query.value("tip").toString());
        if (ilan) {
            ilan->ilanNo = query.value("ilanNo").toInt();
            ilan->baslik = query.value("baslik").toString();
            ilan->fiyat = query.value("fiyat").toDouble();
            ilan->durum = static_cast<ListingStatus>(query.value("durum").toInt());
            liste.append(ilan);
        }
    }
    return liste;
}
