#ifndef GIRISEKRANI_H
#define GIRISEKRANI_H

#include <QWidget>

namespace Ui {
class GirisEkrani;
}

class GirisEkrani : public QWidget
{
    Q_OBJECT

public:
    explicit GirisEkrani(QWidget *parent = nullptr);
    ~GirisEkrani();

private:
    Ui::GirisEkrani *ui;
};

#endif // GIRISEKRANI_H
