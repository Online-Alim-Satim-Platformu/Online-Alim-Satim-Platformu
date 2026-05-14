#ifndef PROFIL_H
#define PROFIL_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui { class Profil; }

class Profil : public QWidget {
    Q_OBJECT

public:
    explicit Profil(QWidget *parent = nullptr);
    ~Profil();

    void profilIlanlariniYukle();
    void kullaniciBilgileriniYukle();

private slots:
    void on_btnIlanSil_clicked();
    void on_btnIlanDuzenle_clicked();
    void on_btnGeri_clicked();
    void on_btnSifreDegistir_clicked();

private:
    Ui::Profil *ui;
};

#endif // PROFIL_H
