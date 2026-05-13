#include <QCoreApplication>
#include <QDebug>
#include "IlanFactory.h"
#include "ListingController.h"
#include "IlanTipleri.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    ListingController controller;

    // Factory ile ilan oluşturma
    Ilan* emlak = IlanFactory::ilanOlustur("Emlak");
    if(emlak) {
        emlak->ilanNo = 1;
        emlak->baslik = "Konyaaltı Daire";
        static_cast<EmlakIlan*>(emlak)->metrekare = "120";
        controller.createListing(emlak);
    }

    // Listeleme
    for(Ilan* i : controller.getAll()) {
        qDebug() << "İlan:" << i->baslik << "Detay:" << i->getDetay();
    }

    return 0;
}
