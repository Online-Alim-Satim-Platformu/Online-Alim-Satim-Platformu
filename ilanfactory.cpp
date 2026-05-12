#include "IlanFactory.h"
#include "IlanTipleri.h"

Ilan* IlanFactory::ilanOlustur(const QString &tip) {
    if (tip == "Emlak") return new EmlakIlan();
    if (tip == "Vasita") return new VasitaIlan();
    if (tip == "Elektronik") return new ElektronikIlan();
    if (tip == "Giyim") return new GiyimIlan();
    return nullptr;
}
