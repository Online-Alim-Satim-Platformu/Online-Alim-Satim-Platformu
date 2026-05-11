#ifndef ILANEKLE_H
#define ILANEKLE_H

#include <QWidget>
#include <QString>

namespace Ui {
class IlanEkle;
}

class IlanEkle : public QWidget
{
    Q_OBJECT

public:
    explicit IlanEkle(QWidget *parent = nullptr);
    ~IlanEkle();

private slots:
    void on_btnYayinla_clicked();
    void on_btnFotoEkle_clicked(); // Yeni fotoğraf butonumuz

private:
    Ui::IlanEkle *ui;
    QString secilenFotoYolu; // Fotoğraf seçildiğinde adresini burada tutacağız
};

#endif // ILANEKLE_H
