#ifndef SIFREMIUNUTTUM_H
#define SIFREMIUNUTTUM_H

#include <QDialog>

namespace Ui {
class SifremiUnuttum;
}

class SifremiUnuttum : public QDialog
{
    Q_OBJECT

public:
    explicit SifremiUnuttum(QWidget *parent = nullptr);
    ~SifremiUnuttum();

private:
    Ui::SifremiUnuttum *ui;
};

#endif // SIFREMIUNUTTUM_H
// private slots: altına şunu ekle
private slots:
void on_btnSifreGuncelle_clicked();
