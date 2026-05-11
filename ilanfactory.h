#ifndef ILANFACTORY_H
#define ILANFACTORY_H

#include "Ilan.h"

class IlanFactory {
public:
    static Ilan* ilanOlustur(const QString &tip);
};

#endif
