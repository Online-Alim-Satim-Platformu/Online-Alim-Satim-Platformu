#ifndef ANASAYFA_H
#define ANASAYFA_H

#include <QWidget>
#include <QListWidgetItem>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class AnaSayfa; }
QT_END_NAMESPACE

class AnaSayfa : public QWidget
{
    Q_OBJECT
public:
    AnaSayfa(QWidget *parent = nullptr);
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
    void on_btnCikisYap_clicked(); // Çıkış yapma slotu
    void on_txtSearch_textChanged(const QString &arananKelime);
    void on_listVitrin_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::AnaSayfa *ui;
    void listeyiDoldur(QSqlQuery &query);
};

#endif // ANASAYFA_H
