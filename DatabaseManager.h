#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class DatabaseManager {
private:
    static DatabaseManager* instance;
    QSqlDatabase db;

    DatabaseManager();
    ~DatabaseManager();

public:
    static DatabaseManager* getInstance();
    bool baglantiKur(const QString& dbPath);
    void baglantiKapat();
    QSqlQuery sorguCalistir(const QString& sql);
    bool beginTransaction();
    bool commit();
    bool initTables();
};

#endif // DATABASEMANAGER_H
