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
    void on_btnFotoEkle_clicked();
    void on_btnIptal_clicked();
    void on_btnStokArttir_clicked();
    void on_btnStokAzalt_clicked();

private:
    Ui::IlanEkle *ui;
    QString secilenFotoYolu;
};

#endif // ILANEKLE_H
