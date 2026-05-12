#ifndef ANASAYFA_H
#define ANASAYFA_H

#include <QWidget>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class AnaSayfa; }
QT_END_NAMESPACE

class AnaSayfa : public QWidget
{
    Q_OBJECT

public:
    AnaSayfa(QWidget *parent = nullptr);
    ~AnaSayfa();

    // İlanları veritabanından çeken fonksiyon
    void ilanlariYukle();

private slots:
    // Üst Panel Butonları
    void on_btnIlanVer_clicked();
    void on_btnProfil_clicked();

    // Sol Panel (Kategoriler) Butonları
    void on_btnTumVitrin_clicked();
    void on_btnEmlak_clicked();
    void on_btnVasita_clicked();
    void on_btnElektronik_clicked();
    void on_btnGiyim_clicked();

    // Vitrin Etkileşimi
    void on_listVitrin_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::AnaSayfa *ui;
};

#endif // ANASAYFA_H
