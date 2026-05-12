#ifndef ILANDETAY_H
#define ILANDETAY_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class IlanDetay;
}

class IlanDetay : public QWidget
{
    Q_OBJECT

public:
    // Yapıcı fonksiyon tıklanan ilanın numarasını alır
    explicit IlanDetay(int ilanNo, QWidget *parent = nullptr);
    ~IlanDetay();

private slots:
    void on_btnAnasayfa_clicked(); // Anasayfaya dön butonu fonksiyonu
    void on_btnFavori_clicked();   // Favorilere ekle butonu fonksiyonu

private:
    Ui::IlanDetay *ui;
    int m_ilanNo; // Veritabanındaki ilanNo bilgisi
    void ilanBilgileriniYukle(); // Veri çekme ve UI doldurma işlemi
};

#endif // ILANDETAY_H
