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
    void on_btnIlanVer_clicked();
    void on_btnEmlak_clicked();
    void on_btnVasita_clicked();
    void on_btnElektronik_clicked();
    void on_btnGiyim_clicked();

private:
    Ui::AnaSayfa *ui;
};

#endif // ANASAYFA_H
