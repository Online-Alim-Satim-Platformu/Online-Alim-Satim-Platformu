#include "databasemanager.h"
#include <QCoreApplication>
#include <QDebug>
#include <QSqlError>

DatabaseManager* DatabaseManager::instance = nullptr;

DatabaseManager::DatabaseManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString path = QCoreApplication::applicationDirPath() + "/online_alisveris.db";
    db.setDatabaseName(path);
}

DatabaseManager* DatabaseManager::getInstance() {
    if (instance == nullptr) {
        instance = new DatabaseManager();
    }
    return instance;
}

bool DatabaseManager::baglantiKur() {
    if (!db.open()) {
        qDebug() << "Hata: Veritabanı açılamadı!" << db.lastError().text();
        return false;
    }

    QSqlQuery query(db);

    // Tabloları YENİDEN ve DOĞRU sütunlarla oluşturuyoruz
    query.exec("CREATE TABLE IF NOT EXISTS Kullanici ("
               "kullaniciID INTEGER PRIMARY KEY AUTOINCREMENT, "
               "kullaniciAdi TEXT, sifre TEXT, email TEXT UNIQUE, rol TEXT)");

    query.exec("CREATE TABLE IF NOT EXISTS Ilan ("
               "ilanNo INTEGER PRIMARY KEY AUTOINCREMENT, "
               "kullaniciID INTEGER, " // Bu sütun artık zorunlu
               "baslik TEXT, fiyat REAL, kategori TEXT, aciklama TEXT, "
               "stokAdedi INTEGER, fotografYolu TEXT)");

    return true;
}

QSqlDatabase DatabaseManager::getDatabase() {
    return db;
}
