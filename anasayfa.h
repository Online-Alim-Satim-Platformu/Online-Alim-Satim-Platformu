#ifndef ANASAYFA_H
#define ANASAYFA_H

#include <QWidget>

namespace Ui { class AnaSayfa; }

class AnaSayfa : public QWidget {
    Q_OBJECT

public:
    explicit AnaSayfa(QWidget *parent = nullptr);
    ~AnaSayfa();
    void ilanlariYukle();

private slots:
    // Mevcut butonlar
    void on_btnIlanVer_clicked();
    void on_btnEmlak_clicked();
    void on_btnVasita_clicked();
    void on_btnElektronik_clicked();
    void on_btnGiyim_clicked();
    void on_btnTumVitrin_clicked();

    // PROFIL EKRANINI ACACAK OLAN YENI SLOT
    void on_btnProfil_clicked();

private:
    Ui::AnaSayfa *ui;
};

#endif // ANASAYFA_H
