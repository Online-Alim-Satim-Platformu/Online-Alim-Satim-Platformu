#ifndef ILANEKLE_H
#define ILANEKLE_H

#include <QWidget>

namespace Ui { class IlanEkle; }

class IlanEkle : public QWidget {
    Q_OBJECT

public:
    explicit IlanEkle(QWidget *parent = nullptr);
    ~IlanEkle();

private slots:
    void on_btnYayinla_clicked();
    void on_btnIptal_clicked();
    void on_btnStokArttir_clicked();
    void on_btnStokAzalt_clicked();

private:
    Ui::IlanEkle *ui;
    QString secilenFotolar[5];
    void fotoSec(int index);

    QMap<QString, class QLineEdit*> ozellikAlanlari;
    void ozellikleriTemizle();
    void ozellikEkle(const QString &label);

private slots:
    void on_cmbKategori_currentTextChanged(const QString &kategori);
};

#endif // ILANEKLE_H
