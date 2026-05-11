#include "girisekrani.h"
#include "databasemanager.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Veritabanını aç
    if(!DatabaseManager::getInstance()->baglantiKur()){
        return -1;
    }

    GirisEkrani w;
    w.show();

    return a.exec();
}
//malberat
