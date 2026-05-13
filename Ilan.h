#ifndef ILAN_H
#define ILAN_H

#include <QString>         //String icin
#include <QObject>         //Nesne ve signal-slot yapisi icin
#include <QDebug>
#include <QList>          //liste icin
#include "IObserver.h"
                                //degisken sadece belirli degerleri alsin diye enum kullandik
enum class ListingStatus { Draft, Active, Sold, Removed }; //isimler enum ile global alana karismasin diye enum class kullandik
                                           //ListingSatus::Active seklinde kullanacagin icin artik baska Active varsa karismaz
class Ilan : public QObject {     //QObject'ten miras al
    Q_OBJECT
public:                       //constructer olusturuluyor, calisinca varsayilan durum Draft olsun
    explicit Ilan(QObject *parent = nullptr) : QObject(parent), durum(ListingStatus::Draft) {}
    virtual ~Ilan() = default;  //ilan nesnesini silebilmek icin destructer'i virtual yaptik

    int ilanNo;
    QString baslik;
    double fiyat;
    int kategoriId;
    QString aciklama;
    int saticiId;
    int stokAdedi;
    ListingStatus durum;
                            //virtual polymorphism icin    //hepsinde farkli detaylar var ve hepsinde gerekli
    virtual QString getDetay() const = 0; //=0 child class'larin override etmesini zorunlu kilar
    virtual QString getTip() const = 0;   //const fonk.sadece bilgi return edecek,nesneyi degistirmeyecek

    void ekleGozlemci(IObserver* gozlemci) {
        if (gozlemci && !gozlemciler.contains(gozlemci)) { //gozlemci nullptr degilse ve listede gozlemci yoksa onu listeye ekle
            gozlemciler.append(gozlemci);     //if(gozlemci) pointer bos degilse demek
        }
    }

    void bildir() {
        for (IObserver* gozlemci : gozlemciler) {   //tum observerlari dolas
            gozlemci->guncelle(this);              //observer'a bu ilan degisti de
        }
    }

    bool isActive() const {          //helper func. daha kisa yazabilmek icin
        return durum == ListingStatus::Active;
    }

protected:
    QList<IObserver*> gozlemciler;     //ilani takip edenler icin gozlemciler listesi olusturuldu
};                                     //fiyat dustu,stok bitti,ilan kaldirildi durumlarini gozlemcilere haber vermek icin

#endif
