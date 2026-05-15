/********************************************************************************
** Form generated from reading UI file 'ilanekle.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ILANEKLE_H
#define UI_ILANEKLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IlanEkle
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lblBaslikGenel;
    QHBoxLayout *fotoLayout;
    QLabel *lblFotoOnizleme;
    QPushButton *btnFotoEkle;
    QLabel *lblBaslik;
    QLineEdit *txtBaslik;
    QLabel *lblFiyat;
    QLineEdit *txtFiyat;
    QLabel *lblKategori;
    QComboBox *cmbKategori;
    QLabel *lblAciklama;
    QTextEdit *txtAciklama;
    QPushButton *btnYayinla;

    void setupUi(QWidget *IlanEkle)
    {
        if (IlanEkle->objectName().isEmpty())
            IlanEkle->setObjectName("IlanEkle");
        IlanEkle->resize(500, 650);
        verticalLayout = new QVBoxLayout(IlanEkle);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(30, 30, 30, 30);
        lblBaslikGenel = new QLabel(IlanEkle);
        lblBaslikGenel->setObjectName("lblBaslikGenel");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        lblBaslikGenel->setFont(font);
        lblBaslikGenel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lblBaslikGenel);

        fotoLayout = new QHBoxLayout();
        fotoLayout->setObjectName("fotoLayout");
        lblFotoOnizleme = new QLabel(IlanEkle);
        lblFotoOnizleme->setObjectName("lblFotoOnizleme");
        lblFotoOnizleme->setMinimumSize(QSize(150, 150));
        lblFotoOnizleme->setAlignment(Qt::AlignCenter);

        fotoLayout->addWidget(lblFotoOnizleme);

        btnFotoEkle = new QPushButton(IlanEkle);
        btnFotoEkle->setObjectName("btnFotoEkle");
        btnFotoEkle->setMinimumSize(QSize(120, 40));

        fotoLayout->addWidget(btnFotoEkle);


        verticalLayout->addLayout(fotoLayout);

        lblBaslik = new QLabel(IlanEkle);
        lblBaslik->setObjectName("lblBaslik");

        verticalLayout->addWidget(lblBaslik);

        txtBaslik = new QLineEdit(IlanEkle);
        txtBaslik->setObjectName("txtBaslik");

        verticalLayout->addWidget(txtBaslik);

        lblFiyat = new QLabel(IlanEkle);
        lblFiyat->setObjectName("lblFiyat");

        verticalLayout->addWidget(lblFiyat);

        txtFiyat = new QLineEdit(IlanEkle);
        txtFiyat->setObjectName("txtFiyat");

        verticalLayout->addWidget(txtFiyat);

        lblKategori = new QLabel(IlanEkle);
        lblKategori->setObjectName("lblKategori");

        verticalLayout->addWidget(lblKategori);

        cmbKategori = new QComboBox(IlanEkle);
        cmbKategori->addItem(QString());
        cmbKategori->addItem(QString());
        cmbKategori->addItem(QString());
        cmbKategori->addItem(QString());
        cmbKategori->setObjectName("cmbKategori");

        verticalLayout->addWidget(cmbKategori);

        lblAciklama = new QLabel(IlanEkle);
        lblAciklama->setObjectName("lblAciklama");

        verticalLayout->addWidget(lblAciklama);

        txtAciklama = new QTextEdit(IlanEkle);
        txtAciklama->setObjectName("txtAciklama");

        verticalLayout->addWidget(txtAciklama);

        btnYayinla = new QPushButton(IlanEkle);
        btnYayinla->setObjectName("btnYayinla");
        btnYayinla->setMinimumSize(QSize(0, 45));

        verticalLayout->addWidget(btnYayinla);


        retranslateUi(IlanEkle);

        QMetaObject::connectSlotsByName(IlanEkle);
    } // setupUi

    void retranslateUi(QWidget *IlanEkle)
    {
        IlanEkle->setWindowTitle(QCoreApplication::translate("IlanEkle", "Yeni \304\260lan Ekle", nullptr));
        lblBaslikGenel->setText(QCoreApplication::translate("IlanEkle", "YEN\304\260 \304\260LAN EKLE", nullptr));
        lblFotoOnizleme->setStyleSheet(QCoreApplication::translate("IlanEkle", "background-color: #e0e0e0; border: 2px dashed #aaa;", nullptr));
        lblFotoOnizleme->setText(QCoreApplication::translate("IlanEkle", "Foto\304\237raf Yok", nullptr));
        btnFotoEkle->setText(QCoreApplication::translate("IlanEkle", "Foto\304\237raf Se\303\247...", nullptr));
        lblBaslik->setText(QCoreApplication::translate("IlanEkle", "\304\260lan Ba\305\237l\304\261\304\237\304\261:", nullptr));
        lblFiyat->setText(QCoreApplication::translate("IlanEkle", "Fiyat (TL):", nullptr));
        lblKategori->setText(QCoreApplication::translate("IlanEkle", "Kategori Se\303\247iniz:", nullptr));
        cmbKategori->setItemText(0, QCoreApplication::translate("IlanEkle", "Emlak", nullptr));
        cmbKategori->setItemText(1, QCoreApplication::translate("IlanEkle", "Vas\304\261ta", nullptr));
        cmbKategori->setItemText(2, QCoreApplication::translate("IlanEkle", "Elektronik", nullptr));
        cmbKategori->setItemText(3, QCoreApplication::translate("IlanEkle", "Giyim", nullptr));

        lblAciklama->setText(QCoreApplication::translate("IlanEkle", "\304\260lan A\303\247\304\261klamas\304\261:", nullptr));
        btnYayinla->setStyleSheet(QCoreApplication::translate("IlanEkle", "background-color: #4CAF50; color: white; font-weight: bold;", nullptr));
        btnYayinla->setText(QCoreApplication::translate("IlanEkle", "\304\260lan\304\261 Yay\304\261nla", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IlanEkle: public Ui_IlanEkle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ILANEKLE_H
