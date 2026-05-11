#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

class DatabaseManager {
public:
    // Bu metod, dışarıdan sınıfa erişmek için kullanacağımız tek kapı.
    static DatabaseManager* getInstance();

    // Veritabanı dosyasını açan ve tabloları oluşturan ana fonksiyon.
    bool baglantiKur();

    // Veritabanı nesnesinin kendisine ulaşmamız gerekirse diye:
    QSqlDatabase getDatabase();

private:
    // --- SINGLETON KURALLARI ---

    // 1. Yapıcı metot (Constructor) private olmalı.
    // Böylece kimse dışarıdan "new DatabaseManager()" diyemez.
    DatabaseManager();

    // 2. Bellekte bu sınıftan sadece bir tane olduğunu garanti eden statik değişken.
    static DatabaseManager* instance;

    // Gerçek veritabanı bağlantı nesnemiz.
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
