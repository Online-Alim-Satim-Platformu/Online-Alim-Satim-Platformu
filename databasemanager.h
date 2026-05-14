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

    void setAktifEmail(const QString& email);
    QString getAktifEmail() const;

private:
    DatabaseManager();
    static DatabaseManager* instance;
    QSqlDatabase db;

    QString aktifEmail;
};

#endif // DATABASEMANAGER_H
