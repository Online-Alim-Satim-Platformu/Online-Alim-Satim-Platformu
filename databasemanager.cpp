#include "databasemanager.h"
#include <QDebug>

DatabaseManager* DatabaseManager::instance = nullptr;

DatabaseManager::DatabaseManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("online_alisveris.db");
}

DatabaseManager* DatabaseManager::getInstance() {
    if (instance == nullptr) {
        instance = new DatabaseManager();
    }
    return instance;
}

bool DatabaseManager::baglantiKur() {
    if (!db.open()) return false;

    QSqlQuery query;
    // Kullanıcı Tablosu
    query.exec("CREATE TABLE IF NOT EXISTS Kullanici ("
               "kullaniciID INTEGER PRIMARY KEY AUTOINCREMENT, "
               "kullaniciAdi TEXT, sifre TEXT, email TEXT UNIQUE, rol TEXT)");

    // İlan Tablosu
    query.exec("CREATE TABLE IF NOT EXISTS Ilan ("
               "ilanNo INTEGER PRIMARY KEY AUTOINCREMENT, "
               "baslik TEXT, fiyat REAL, kategori TEXT, aciklama TEXT, "
               "stokAdedi INTEGER, fotografYolu TEXT)");

    // Sütun ekleme garantisi (Eski DB'ler için)
    query.exec("ALTER TABLE Ilan ADD COLUMN fotografYolu TEXT");

    return true;
}

QSqlDatabase DatabaseManager::getDatabase() { return db; }
