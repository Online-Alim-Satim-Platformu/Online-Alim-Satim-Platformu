/********************************************************************************
** Form generated from reading UI file 'profil.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFIL_H
#define UI_PROFIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Profil
{
public:
    QVBoxLayout *mainLayout;
    QGroupBox *groupKullanici;
    QFormLayout *formLayout;
    QLabel *label_1;
    QLabel *lblAdSoyad;
    QLabel *label_2;
    QLabel *lblEmail;
    QPushButton *btnSifreDegistir;
    QLabel *lblIlanBaslik;
    QListWidget *listProfilIlanlar;
    QPushButton *btnIlanSil;
    QPushButton *btnGeri;

    void setupUi(QWidget *Profil)
    {
        if (Profil->objectName().isEmpty())
            Profil->setObjectName("Profil");
        Profil->resize(500, 650);
        Profil->setStyleSheet(QString::fromUtf8("background-color: #f9fafb;"));
        mainLayout = new QVBoxLayout(Profil);
        mainLayout->setSpacing(15);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(25, 25, 25, 25);
        groupKullanici = new QGroupBox(Profil);
        groupKullanici->setObjectName("groupKullanici");
        groupKullanici->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    font-weight: bold;\n"
"    border: 2px solid #e5e7eb;\n"
"    border-radius: 12px;\n"
"    margin-top: 15px;\n"
"    padding-top: 20px;\n"
"    background-color: white;\n"
"    color: #000000;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 10px;\n"
"    color: #000000;\n"
"}\n"
"QLabel {\n"
"    color: #000000;\n"
"}"));
        formLayout = new QFormLayout(groupKullanici);
        formLayout->setObjectName("formLayout");
        formLayout->setHorizontalSpacing(15);
        formLayout->setVerticalSpacing(12);
        formLayout->setContentsMargins(15, 10, 15, 15);
        label_1 = new QLabel(groupKullanici);
        label_1->setObjectName("label_1");
        QFont font;
        font.setBold(true);
        label_1->setFont(font);
        label_1->setStyleSheet(QString::fromUtf8("color: #000000;"));

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label_1);

        lblAdSoyad = new QLabel(groupKullanici);
        lblAdSoyad->setObjectName("lblAdSoyad");
        lblAdSoyad->setStyleSheet(QString::fromUtf8("color: #000000; font-size: 11pt; font-weight: bold;"));

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, lblAdSoyad);

        label_2 = new QLabel(groupKullanici);
        label_2->setObjectName("label_2");
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("color: #000000;"));

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        lblEmail = new QLabel(groupKullanici);
        lblEmail->setObjectName("lblEmail");
        lblEmail->setStyleSheet(QString::fromUtf8("color: #000000; font-size: 11pt; font-weight: bold;"));

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, lblEmail);

        btnSifreDegistir = new QPushButton(groupKullanici);
        btnSifreDegistir->setObjectName("btnSifreDegistir");
        btnSifreDegistir->setMinimumSize(QSize(0, 32));
        btnSifreDegistir->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnSifreDegistir->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #4B5563;\n"
"    color: white;\n"
"    border-radius: 6px;\n"
"    font-weight: bold;\n"
"    padding: 0 15px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #374151;\n"
"}"));

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, btnSifreDegistir);


        mainLayout->addWidget(groupKullanici);

        lblIlanBaslik = new QLabel(Profil);
        lblIlanBaslik->setObjectName("lblIlanBaslik");
        QFont font1;
        font1.setPointSize(13);
        font1.setBold(true);
        lblIlanBaslik->setFont(font1);
        lblIlanBaslik->setStyleSheet(QString::fromUtf8("color: #000000; margin-top: 5px;"));

        mainLayout->addWidget(lblIlanBaslik);

        listProfilIlanlar = new QListWidget(Profil);
        listProfilIlanlar->setObjectName("listProfilIlanlar");
        listProfilIlanlar->setStyleSheet(QString::fromUtf8("QListWidget {\n"
"    background-color: white;\n"
"    border: 2px solid #e5e7eb;\n"
"    border-radius: 10px;\n"
"    padding: 8px;\n"
"    font-size: 11pt;\n"
"    color: #000000;\n"
"}\n"
"QListWidget::item {\n"
"    color: #000000;\n"
"    padding: 10px;\n"
"    border-bottom: 1px solid #f3f4f6;\n"
"}\n"
"QListWidget::item:selected {\n"
"    background-color: #eff6ff;\n"
"    color: #1d4ed8;\n"
"    border-radius: 6px;\n"
"}"));

        mainLayout->addWidget(listProfilIlanlar);

        btnIlanSil = new QPushButton(Profil);
        btnIlanSil->setObjectName("btnIlanSil");
        btnIlanSil->setMinimumSize(QSize(0, 45));
        btnIlanSil->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnIlanSil->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #ef4444;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    font-size: 10pt;\n"
"    border-radius: 8px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #dc2626;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #991b1b;\n"
"}"));

        mainLayout->addWidget(btnIlanSil);

        btnGeri = new QPushButton(Profil);
        btnGeri->setObjectName("btnGeri");
        btnGeri->setMinimumSize(QSize(0, 38));
        btnGeri->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnGeri->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #9ca3af;\n"
"    color: white;\n"
"    border-radius: 8px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #6b7280;\n"
"}"));

        mainLayout->addWidget(btnGeri);


        retranslateUi(Profil);

        QMetaObject::connectSlotsByName(Profil);
    } // setupUi

    void retranslateUi(QWidget *Profil)
    {
        Profil->setWindowTitle(QCoreApplication::translate("Profil", "Profilim ve \304\260lan Y\303\266netimi", nullptr));
        groupKullanici->setTitle(QCoreApplication::translate("Profil", "Kullan\304\261c\304\261 Bilgileri", nullptr));
        label_1->setText(QCoreApplication::translate("Profil", "Ad Soyad:", nullptr));
        lblAdSoyad->setText(QCoreApplication::translate("Profil", "-", nullptr));
        label_2->setText(QCoreApplication::translate("Profil", "E-posta:", nullptr));
        lblEmail->setText(QCoreApplication::translate("Profil", "-", nullptr));
        btnSifreDegistir->setText(QCoreApplication::translate("Profil", "\360\237\224\222 \305\236ifre De\304\237i\305\237tir", nullptr));
        lblIlanBaslik->setText(QCoreApplication::translate("Profil", "\304\260lanlar\304\261m", nullptr));
        btnIlanSil->setText(QCoreApplication::translate("Profil", "\360\237\227\221 Se\303\247ili \304\260lan\304\261 Sil", nullptr));
        btnGeri->setText(QCoreApplication::translate("Profil", "\342\206\220 Anasayfaya D\303\266n", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Profil: public Ui_Profil {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFIL_H
