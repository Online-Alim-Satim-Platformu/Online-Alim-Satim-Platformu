/********************************************************************************
** Form generated from reading UI file 'girisekrani.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GIRISEKRANI_H
#define UI_GIRISEKRANI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GirisEkrani
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lblBaslik;
    QSpacerItem *verticalSpacer_2;
    QLabel *lblEmail;
    QLineEdit *txtEmail;
    QLabel *lblSifre;
    QLineEdit *txtSifre;
    QHBoxLayout *horizontalLayout;
    QCheckBox *chkOturumAcikKalsin;
    QPushButton *btnSifremiUnuttum;
    QSpacerItem *verticalSpacer;
    QPushButton *btnGirisYap;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lblHesapYokMu;
    QPushButton *btnHesapAc;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *GirisEkrani)
    {
        if (GirisEkrani->objectName().isEmpty())
            GirisEkrani->setObjectName("GirisEkrani");
        GirisEkrani->resize(400, 500);
        verticalLayout = new QVBoxLayout(GirisEkrani);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(40, 40, 40, 40);
        lblBaslik = new QLabel(GirisEkrani);
        lblBaslik->setObjectName("lblBaslik");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        lblBaslik->setFont(font);
        lblBaslik->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(lblBaslik);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        lblEmail = new QLabel(GirisEkrani);
        lblEmail->setObjectName("lblEmail");

        verticalLayout->addWidget(lblEmail);

        txtEmail = new QLineEdit(GirisEkrani);
        txtEmail->setObjectName("txtEmail");
        txtEmail->setMinimumSize(QSize(0, 35));

        verticalLayout->addWidget(txtEmail);

        lblSifre = new QLabel(GirisEkrani);
        lblSifre->setObjectName("lblSifre");

        verticalLayout->addWidget(lblSifre);

        txtSifre = new QLineEdit(GirisEkrani);
        txtSifre->setObjectName("txtSifre");
        txtSifre->setMinimumSize(QSize(0, 35));
        txtSifre->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout->addWidget(txtSifre);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        chkOturumAcikKalsin = new QCheckBox(GirisEkrani);
        chkOturumAcikKalsin->setObjectName("chkOturumAcikKalsin");

        horizontalLayout->addWidget(chkOturumAcikKalsin);

        btnSifremiUnuttum = new QPushButton(GirisEkrani);
        btnSifremiUnuttum->setObjectName("btnSifremiUnuttum");
        btnSifremiUnuttum->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnSifremiUnuttum->setFlat(true);

        horizontalLayout->addWidget(btnSifremiUnuttum);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        btnGirisYap = new QPushButton(GirisEkrani);
        btnGirisYap->setObjectName("btnGirisYap");
        btnGirisYap->setMinimumSize(QSize(0, 40));
        QFont font1;
        font1.setBold(true);
        btnGirisYap->setFont(font1);
        btnGirisYap->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        verticalLayout->addWidget(btnGirisYap);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        lblHesapYokMu = new QLabel(GirisEkrani);
        lblHesapYokMu->setObjectName("lblHesapYokMu");

        horizontalLayout_2->addWidget(lblHesapYokMu);

        btnHesapAc = new QPushButton(GirisEkrani);
        btnHesapAc->setObjectName("btnHesapAc");
        btnHesapAc->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnHesapAc->setFlat(true);

        horizontalLayout_2->addWidget(btnHesapAc);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(GirisEkrani);

        QMetaObject::connectSlotsByName(GirisEkrani);
    } // setupUi

    void retranslateUi(QWidget *GirisEkrani)
    {
        GirisEkrani->setWindowTitle(QCoreApplication::translate("GirisEkrani", "Giri\305\237 Yap - Online Al\304\261\305\237veri\305\237 Platformu", nullptr));
        lblBaslik->setText(QCoreApplication::translate("GirisEkrani", "G\304\260R\304\260\305\236 YAP", nullptr));
        lblEmail->setText(QCoreApplication::translate("GirisEkrani", "E-posta adresi", nullptr));
        txtEmail->setPlaceholderText(QString());
        lblSifre->setText(QCoreApplication::translate("GirisEkrani", "\305\236ifre", nullptr));
        txtSifre->setPlaceholderText(QString());
        chkOturumAcikKalsin->setText(QCoreApplication::translate("GirisEkrani", "Oturumum a\303\247\304\261k kals\304\261n", nullptr));
        btnSifremiUnuttum->setStyleSheet(QCoreApplication::translate("GirisEkrani", "color: #0078D7;", nullptr));
        btnSifremiUnuttum->setText(QCoreApplication::translate("GirisEkrani", "\305\236ifremi unuttum", nullptr));
        btnGirisYap->setStyleSheet(QCoreApplication::translate("GirisEkrani", "background-color: #0078D7; color: white; border-radius: 5px;", nullptr));
        btnGirisYap->setText(QCoreApplication::translate("GirisEkrani", "E-POSTA \304\260LE G\304\260R\304\260\305\236 YAP", nullptr));
        lblHesapYokMu->setText(QCoreApplication::translate("GirisEkrani", "Hen\303\274z hesab\304\261n yok mu?", nullptr));
        btnHesapAc->setStyleSheet(QCoreApplication::translate("GirisEkrani", "color: #0078D7; text-decoration: underline;", nullptr));
        btnHesapAc->setText(QCoreApplication::translate("GirisEkrani", "Hesap a\303\247", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GirisEkrani: public Ui_GirisEkrani {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GIRISEKRANI_H
