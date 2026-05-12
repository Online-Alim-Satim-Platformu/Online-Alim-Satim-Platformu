#ifndef IOBSERVER_H
#define IOBSERVER_H

class Ilan;

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void guncelle(Ilan* ilan) = 0;
};

#endif // IOBSERVER_H
