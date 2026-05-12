#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

class DatabaseManager {
public:
    static DatabaseManager* getInstance();
    bool baglantiKur();
    QSqlDatabase& getDatabase();  // ← referans döndür
private:
    DatabaseManager();
    static DatabaseManager* instance;
    QSqlDatabase db;
};
#endif // DATABASEMANAGER_H
