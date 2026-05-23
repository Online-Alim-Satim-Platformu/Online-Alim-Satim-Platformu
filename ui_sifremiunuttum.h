/********************************************************************************
** Form generated from reading UI file 'sifremiunuttum.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIFREMIUNUTTUM_H
#define UI_SIFREMIUNUTTUM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SifremiUnuttum
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *txtEmail;
    QLabel *label_3;
    QLineEdit *txtYeniSifre;
    QPushButton *btnSifreGuncelle;

    void setupUi(QDialog *SifremiUnuttum)
    {
        if (SifremiUnuttum->objectName().isEmpty())
            SifremiUnuttum->setObjectName("SifremiUnuttum");
        SifremiUnuttum->resize(350, 250);
        verticalLayout = new QVBoxLayout(SifremiUnuttum);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(SifremiUnuttum);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(SifremiUnuttum);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        txtEmail = new QLineEdit(SifremiUnuttum);
        txtEmail->setObjectName("txtEmail");
        txtEmail->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(txtEmail);

        label_3 = new QLabel(SifremiUnuttum);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        txtYeniSifre = new QLineEdit(SifremiUnuttum);
        txtYeniSifre->setObjectName("txtYeniSifre");
        txtYeniSifre->setMinimumSize(QSize(0, 30));
        txtYeniSifre->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(txtYeniSifre);

        btnSifreGuncelle = new QPushButton(SifremiUnuttum);
        btnSifreGuncelle->setObjectName("btnSifreGuncelle");
        btnSifreGuncelle->setMinimumSize(QSize(0, 35));
        btnSifreGuncelle->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        verticalLayout->addWidget(btnSifreGuncelle);


        retranslateUi(SifremiUnuttum);

        QMetaObject::connectSlotsByName(SifremiUnuttum);
    } // setupUi

    void retranslateUi(QDialog *SifremiUnuttum)
    {
        SifremiUnuttum->setWindowTitle(QCoreApplication::translate("SifremiUnuttum", "\305\236ifre Yenileme", nullptr));
        label->setText(QCoreApplication::translate("SifremiUnuttum", "\305\236ifremi Unuttum", nullptr));
        label_2->setText(QCoreApplication::translate("SifremiUnuttum", "E-posta Adresiniz:", nullptr));
        label_3->setText(QCoreApplication::translate("SifremiUnuttum", "Yeni \305\236ifre:", nullptr));
        btnSifreGuncelle->setStyleSheet(QCoreApplication::translate("SifremiUnuttum", "background-color: #0078D7; color: white; font-weight: bold; border-radius: 4px;", nullptr));
        btnSifreGuncelle->setText(QCoreApplication::translate("SifremiUnuttum", "\305\236ifreyi G\303\274ncelle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SifremiUnuttum: public Ui_SifremiUnuttum {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIFREMIUNUTTUM_H
