#include "DatabaseManager.h"

DatabaseManager* DatabaseManager::instance = nullptr;

DatabaseManager::DatabaseManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
}

DatabaseManager::~DatabaseManager() {
    baglantiKapat();
}

DatabaseManager* DatabaseManager::getInstance() {
    if (instance == nullptr) {
        instance = new DatabaseManager();
    }
    return instance;
}

bool DatabaseManager::baglantiKur(const QString& dbPath) {
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qDebug() << "Veritabanı açılamadı:" << db.lastError().text();
        return false;
    }
    return true;
}

void DatabaseManager::baglantiKapat() {
    if (db.isOpen()) {
        db.close();
    }
}

QSqlQuery DatabaseManager::sorguCalistir(const QString& sql) {
    QSqlQuery query;
    if (!query.exec(sql)) {
        qDebug() << "Sorgu hatası:" << query.lastError().text() << "\nSorgu:" << sql;
    }
    return query;
}

bool DatabaseManager::beginTransaction() {
    return db.transaction();
}

bool DatabaseManager::commit() {
    return db.commit();
}

bool DatabaseManager::initTables() {
    QString query = "CREATE TABLE IF NOT EXISTS Ilanlar ("
                    "ilanNo INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "baslik TEXT, "
                    "fiyat REAL, "
                    "kategoriId INTEGER, "
                    "aciklama TEXT, "
                    "saticiId INTEGER, "
                    "stokAdedi INTEGER, "
                    "durum INTEGER, "
                    "tip TEXT, "
                    "detay TEXT" 
                    ")";
    QSqlQuery q;
    if (!q.exec(query)) {
        qDebug() << "Tablo oluşturma hatası:" << q.lastError().text();
        return false;
    }
    return true;
}
