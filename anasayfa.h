#ifndef ANASAYFA_H
#define ANASAYFA_H

#include <QWidget>

namespace Ui {
class AnaSayfa;
}

class AnaSayfa : public QWidget
{
    Q_OBJECT

public:
    explicit AnaSayfa(QWidget *parent = nullptr);
    ~AnaSayfa();

private:
    Ui::AnaSayfa *ui;
};

#endif // ANASAYFA_H
