#ifndef ANASAYFA_H
#define ANASAYFA_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui { class AnaSayfa; }

class AnaSayfa : public QWidget {
    Q_OBJECT

public:
    explicit AnaSayfa(QWidget *parent = nullptr);
    ~AnaSayfa();
    void ilanlariYukle();                                // Tüm ilanlar (Ana Sayfa)
    void kategoriIlanlariYukle(const QString &kategori); // Kategori filtresi

private slots:
    // Sol sidebar butonları
    void on_btnTumVitrin_clicked();     // Ana Sayfa → tüm ilanlar
    void on_btnEmlak_clicked();
    void on_btnVasita_clicked();
    void on_btnElektronik_clicked();
    void on_btnGiyim_clicked();

    // Üst bar
    void on_btnIlanVer_clicked();
    void on_btnProfil_clicked();

    // Arama kutusu → canlı filtreleme
    void on_txtSearch_textChanged(const QString &arananKelime);

    // İlana çift tıklayınca detay popup
    void on_listVitrin_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::AnaSayfa *ui;
    void listeyiDoldur(QSqlQuery &query); // Ortak liste doldurma
};

#endif // ANASAYFA_H
