#include "girisekrani.h"
#include "databasemanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Veritabanı bağlantısını başlat
    DatabaseManager::getInstance()->baglantiKur();

    // Giriş ekranını göster
    GirisEkrani w;
    w.show();

    return a.exec();
}
