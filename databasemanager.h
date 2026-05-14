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

    // Oturum (Session) yönetimi için eklendi
    int getAktifKullaniciID() const { return aktifKullaniciID; }
    void setAktifKullaniciID(int id) { aktifKullaniciID = id; }

private:
    DatabaseManager();
    static DatabaseManager* instance;
    QSqlDatabase db;

    // Sisteme kimse giriş yapmadıysa varsayılan değer -1
    int aktifKullaniciID = -1;
};

#endif // DATABASEMANAGER_H
