#include "IlanFactory.h"

Ilan* IlanFactory::ilanOlustur(const QString &tip) {
    if (tip == "Emlak") return new EmlakIlan();
    if (tip == "Vasita") return new VasitaIlan();
    return nullptr;
}
