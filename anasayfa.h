#ifndef ANASAYFA_H
#define ANASAYFA_H

#include <QWidget>
#include <QListWidgetItem>
#include <QSqlQuery>
#include <QPushButton>
namespace Ui { class AnaSayfa; }

class AnaSayfa : public QWidget {
    Q_OBJECT

public:
    explicit AnaSayfa(QWidget *parent = nullptr);
    ~AnaSayfa();
    void ilanlariYukle();
    void kategoriIlanlariYukle(const QString &kategori);

private slots:
    void on_btnTumVitrin_clicked();
    void on_btnEmlak_clicked();
    void on_btnVasita_clicked();
    void on_btnElektronik_clicked();
    void on_btnGiyim_clicked();

    void on_btnIlanVer_clicked();
    void on_btnProfil_clicked();
    void on_btnCikisYap_clicked();   // oturum kapatma

    void on_txtSearch_textChanged(const QString &arananKelime);
    void on_listVitrin_itemDoubleClicked(QListWidgetItem *item);
    void on_btnFiltrele_clicked();

private:
    Ui::AnaSayfa *ui;
    void listeyiDoldur(QSqlQuery &query);
    QPushButton *btnFiltrele;
    QString guncelKategori;
};

#endif // ANASAYFA_H
