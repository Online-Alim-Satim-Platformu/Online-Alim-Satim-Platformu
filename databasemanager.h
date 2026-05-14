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
    void setAktifEmail(const QString& email);
    QString getAktifEmail() const;
=======
    // Oturum yönetimi için eklenen fonksiyonlar
    void setAktifKullaniciID(int id);
    int getAktifKullaniciID();
>>>>>>> Stashed changes

private:
    DatabaseManager();
    static DatabaseManager* instance;
    QSqlDatabase db;

<<<<<<< Updated upstream
    QString aktifEmail;
=======
    // Aktif kullanıcıyı tutacak değişken (-1 kimse girmemiş demek)
    int aktifKullaniciID = -1;
>>>>>>> Stashed changes
};

#endif // DATABASEMANAGER_H
