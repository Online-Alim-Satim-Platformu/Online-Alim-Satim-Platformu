#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

class DatabaseManager {
public:
    static DatabaseManager* getInstance();
    bool baglantiKur();
    QSqlDatabase getDatabase();

    // Oturum yönetimi için eklenen fonksiyonlar
    void setAktifKullaniciID(int id);
    int getAktifKullaniciID();

private:
    DatabaseManager();
    static DatabaseManager* instance;
    QSqlDatabase db;

    // Aktif kullanıcıyı tutacak değişken (-1 kimse girmemiş demek)
    int aktifKullaniciID = -1;
};

#endif // DATABASEMANAGER_H
