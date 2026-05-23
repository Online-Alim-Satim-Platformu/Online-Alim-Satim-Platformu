/********************************************************************************
** Form generated from reading UI file 'kayitekrani.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KAYITEKRANI_H
#define UI_KAYITEKRANI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KayitEkrani
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lblBaslik;
    QHBoxLayout *nameLayout;
    QVBoxLayout *adLayout;
    QLabel *lblAd;
    QLineEdit *txtAd;
    QVBoxLayout *soyadLayout;
    QLabel *lblSoyad;
    QLineEdit *txtSoyad;
    QLabel *lblEmail;
    QLineEdit *txtEmail;
    QLabel *lblSifre;
    QLineEdit *txtSifre;
    QSpacerItem *verticalSpacer;
    QPushButton *btnHesapAc;
    QPushButton *btnGirisYapDon;

    void setupUi(QWidget *KayitEkrani)
    {
        if (KayitEkrani->objectName().isEmpty())
            KayitEkrani->setObjectName("KayitEkrani");
        KayitEkrani->resize(400, 600);
        verticalLayout = new QVBoxLayout(KayitEkrani);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(40, 40, 40, 40);
        lblBaslik = new QLabel(KayitEkrani);
        lblBaslik->setObjectName("lblBaslik");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        lblBaslik->setFont(font);
        lblBaslik->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lblBaslik);

        nameLayout = new QHBoxLayout();
        nameLayout->setObjectName("nameLayout");
        adLayout = new QVBoxLayout();
        adLayout->setObjectName("adLayout");
        lblAd = new QLabel(KayitEkrani);
        lblAd->setObjectName("lblAd");

        adLayout->addWidget(lblAd);

        txtAd = new QLineEdit(KayitEkrani);
        txtAd->setObjectName("txtAd");
        txtAd->setMinimumSize(QSize(0, 35));

        adLayout->addWidget(txtAd);


        nameLayout->addLayout(adLayout);

        soyadLayout = new QVBoxLayout();
        soyadLayout->setObjectName("soyadLayout");
        lblSoyad = new QLabel(KayitEkrani);
        lblSoyad->setObjectName("lblSoyad");

        soyadLayout->addWidget(lblSoyad);

        txtSoyad = new QLineEdit(KayitEkrani);
        txtSoyad->setObjectName("txtSoyad");
        txtSoyad->setMinimumSize(QSize(0, 35));

        soyadLayout->addWidget(txtSoyad);


        nameLayout->addLayout(soyadLayout);


        verticalLayout->addLayout(nameLayout);

        lblEmail = new QLabel(KayitEkrani);
        lblEmail->setObjectName("lblEmail");

        verticalLayout->addWidget(lblEmail);

        txtEmail = new QLineEdit(KayitEkrani);
        txtEmail->setObjectName("txtEmail");
        txtEmail->setMinimumSize(QSize(0, 35));

        verticalLayout->addWidget(txtEmail);

        lblSifre = new QLabel(KayitEkrani);
        lblSifre->setObjectName("lblSifre");

        verticalLayout->addWidget(lblSifre);

        txtSifre = new QLineEdit(KayitEkrani);
        txtSifre->setObjectName("txtSifre");
        txtSifre->setMinimumSize(QSize(0, 35));
        txtSifre->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(txtSifre);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        btnHesapAc = new QPushButton(KayitEkrani);
        btnHesapAc->setObjectName("btnHesapAc");
        btnHesapAc->setMinimumSize(QSize(0, 40));
        QFont font1;
        font1.setBold(true);
        btnHesapAc->setFont(font1);
        btnHesapAc->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        verticalLayout->addWidget(btnHesapAc);

        btnGirisYapDon = new QPushButton(KayitEkrani);
        btnGirisYapDon->setObjectName("btnGirisYapDon");
        btnGirisYapDon->setFlat(true);
        btnGirisYapDon->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        verticalLayout->addWidget(btnGirisYapDon);


        retranslateUi(KayitEkrani);

        QMetaObject::connectSlotsByName(KayitEkrani);
    } // setupUi

    void retranslateUi(QWidget *KayitEkrani)
    {
        KayitEkrani->setWindowTitle(QCoreApplication::translate("KayitEkrani", "Hesap A\303\247 - Online Al\304\261\305\237veri\305\237 Platformu", nullptr));
        lblBaslik->setText(QCoreApplication::translate("KayitEkrani", "HESAP A\303\207", nullptr));
        lblAd->setText(QCoreApplication::translate("KayitEkrani", "AD", nullptr));
        lblSoyad->setText(QCoreApplication::translate("KayitEkrani", "Soyad", nullptr));
        lblEmail->setText(QCoreApplication::translate("KayitEkrani", "E-posta adresi", nullptr));
        txtEmail->setPlaceholderText(QCoreApplication::translate("KayitEkrani", "kullanici@gmail.com", nullptr));
        lblSifre->setText(QCoreApplication::translate("KayitEkrani", "\305\236ifre", nullptr));
        txtSifre->setPlaceholderText(QCoreApplication::translate("KayitEkrani", "********", nullptr));
        btnHesapAc->setStyleSheet(QCoreApplication::translate("KayitEkrani", "background-color: #0078D7; color: white; border-radius: 5px;", nullptr));
        btnHesapAc->setText(QCoreApplication::translate("KayitEkrani", "HESAP A\303\207", nullptr));
        btnGirisYapDon->setText(QCoreApplication::translate("KayitEkrani", "Zaten hesab\304\261n var m\304\261? Giri\305\237 Yap", nullptr));
        btnGirisYapDon->setStyleSheet(QCoreApplication::translate("KayitEkrani", "color: #0078D7; text-decoration: underline;", nullptr));
    } // retranslateUi

};

namespace Ui {
    class KayitEkrani: public Ui_KayitEkrani {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KAYITEKRANI_H
