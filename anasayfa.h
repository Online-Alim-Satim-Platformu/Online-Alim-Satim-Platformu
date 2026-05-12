#ifndef ANASAYFA_H
#define ANASAYFA_H

#include <QWidget>
#include <QListWidgetItem> // Çift tıklama algılaması için bu kütüphane şart

namespace Ui {
class AnaSayfa;
}

class AnaSayfa : public QWidget
{
    Q_OBJECT

public:
    explicit AnaSayfa(QWidget *parent = nullptr);
    ~AnaSayfa();

    void ilanlariYukle();

private slots:
    // Mevcut buton fonksiyonların
    void on_btnProfil_clicked();
    void on_btnTumVitrin_clicked();
    void on_btnIlanVer_clicked();
    void on_btnEmlak_clicked();
    void on_btnVasita_clicked();
    void on_btnElektronik_clicked();
    void on_btnGiyim_clicked();

    // İŞTE HATAYA SEBEP OLAN EKSİK SATIR BURASI:
    void on_listVitrin_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::AnaSayfa *ui;
};

#endif // ANASAYFA_H
