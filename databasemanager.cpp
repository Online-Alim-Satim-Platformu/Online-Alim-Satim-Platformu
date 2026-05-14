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

    query.exec("CREATE TABLE IF NOT EXISTS Kullanici ("
               "kullaniciID INTEGER PRIMARY KEY AUTOINCREMENT, "
               "kullaniciAdi TEXT, sifre TEXT, email TEXT UNIQUE, rol TEXT)");

    query.exec("CREATE TABLE IF NOT EXISTS Ilan ("
               "ilanNo INTEGER PRIMARY KEY AUTOINCREMENT, "
               "baslik TEXT, fiyat REAL, kategori TEXT, aciklama TEXT, "
               "stokAdedi INTEGER, fotografYolu TEXT)");

    QSqlQuery checkQuery(db);
    if (checkQuery.exec("SELECT COUNT(*) FROM Kullanici")) {
        if (checkQuery.next() && checkQuery.value(0).toInt() == 0) {
            QSqlQuery insertQuery(db);
            insertQuery.exec("INSERT INTO Kullanici (kullaniciAdi, email, sifre, rol) "
                             "VALUES ('Berat', 'berat@2sinifpcmüh.com', '1234', 'admin')");
        }
    }

    return true;
}

QSqlDatabase DatabaseManager::getDatabase() {
    return db;
}

<<<<<<< Updated upstream
void DatabaseManager::setAktifEmail(const QString& email) {
    aktifEmail = email;
}

QString DatabaseManager::getAktifEmail() const {
    return aktifEmail;
=======
// Oturum yönetimi için eklenen fonksiyonların gövdeleri
void DatabaseManager::setAktifKullaniciID(int id) {
    aktifKullaniciID = id;
}

int DatabaseManager::getAktifKullaniciID() {
    return aktifKullaniciID;
>>>>>>> Stashed changes
}
