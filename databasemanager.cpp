#include "databasemanager.h"
#include <QDebug>
#include <QSqlError>

// Statik değişkenin başlangıç değeri (henüz kimse yaratmadı)
DatabaseManager* DatabaseManager::instance = nullptr;

// Özel Yapıcı Metot (Private Constructor)
DatabaseManager::DatabaseManager() {
    // SQLite sürücüsünü kullanacağımızı belirtiyoruz
    db = QSqlDatabase::addDatabase("QSQLITE");

    // Veritabanı dosyasının adını belirliyoruz. Proje klasöründe oluşacak.
    db.setDatabaseName("online_alisveris.db");
}

// Singleton'ın kalbi: Projedeki herkes veritabanına ulaşmak için bu metodu çağıracak
DatabaseManager* DatabaseManager::getInstance() {
    if (instance == nullptr) {
        instance = new DatabaseManager();
    }
    return instance;
}

// Veritabanını açma ve tabloları oluşturma
bool DatabaseManager::baglantiKur() {
    // Eğer veritabanı dosyası açılamazsa veya oluşturulamazsa hata dön
    if (!db.open()) {
        qDebug() << "Veritabanı açılamadı:" << db.lastError().text();
        return false;
    }

    // Veritabanı açıldıysa, tasarım raporuna uygun Kullanıcı tablomuzu oluşturalım.
    QSqlQuery query;
    QString kullaniciTablosu = "CREATE TABLE IF NOT EXISTS Kullanici ("
                               "kullaniciID INTEGER PRIMARY KEY AUTOINCREMENT, "
                               "kullaniciAdi TEXT, "
                               "sifre TEXT, "
                               "email TEXT UNIQUE, "
                               "rol TEXT)";

    // Sorguyu çalıştır, hata varsa konsola yaz
    if (!query.exec(kullaniciTablosu)) {
        qDebug() << "Kullanıcı tablosu oluşturulamadı:" << query.lastError().text();
        return false;
    }

    qDebug() << "Veritabanı bağlantısı başarılı ve tablolar hazır!";
    return true;
}

QSqlDatabase DatabaseManager::getDatabase() {
    return db;
}
