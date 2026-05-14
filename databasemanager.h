#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>

class DatabaseManager {
public:
    static DatabaseManager* getInstance();
    bool baglantiKur();
    QSqlDatabase getDatabase();

<<<<<<< Updated upstream
    // Oturum (Session) yönetimi için eklendi
    int getAktifKullaniciID() const { return aktifKullaniciID; }
    void setAktifKullaniciID(int id) { aktifKullaniciID = id; }
=======
    // --- YENİ EKLENEN KISIM ---
    void setAktifEmail(const QString& email);
    QString getAktifEmail() const;
>>>>>>> Stashed changes

private:
    DatabaseManager();
    static DatabaseManager* instance;
    QSqlDatabase db;

<<<<<<< Updated upstream
    // Sisteme kimse giriş yapmadıysa varsayılan değer -1
    int aktifKullaniciID = -1;
=======
    // --- YENİ EKLENEN KISIM ---
    QString aktifEmail;
>>>>>>> Stashed changes
};

#endif // DATABASEMANAGER_H
