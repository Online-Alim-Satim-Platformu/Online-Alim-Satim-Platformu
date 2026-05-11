#include "girisekrani.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Proje başladığında ekranda gösterilecek ilk sınıfımız:
    GirisEkrani w;
    w.show();

    return a.exec();
}
