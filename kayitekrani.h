#ifndef KAYITEKRANI_H
#define KAYITEKRANI_H

#include <QWidget>

namespace Ui {
class KayitEkrani;
}

class KayitEkrani : public QWidget
{
    Q_OBJECT

public:
    explicit KayitEkrani(QWidget *parent = nullptr);
    ~KayitEkrani();

private slots:
    void on_btnHesapAc_clicked();       // Kayıt olma butonu
    void on_btnGirisYapDon_clicked();   // Giriş ekranına geri dönme butonu

private:
    Ui::KayitEkrani *ui;
};

#endif // KAYITEKRANI_H
