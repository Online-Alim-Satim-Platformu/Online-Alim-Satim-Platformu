#include "girisekrani.h"
#include "databasemanager.h" // Veritabanı sınıfımızı ekledik
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Proje başlarken veritabanı bağlantısını kuruyoruz!
    DatabaseManager::getInstance()->baglantiKur();

    GirisEkrani w;
    w.show();

    return a.exec();
}
