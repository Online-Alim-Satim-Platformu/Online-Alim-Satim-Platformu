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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IlanEkle
{
public:
    QHBoxLayout *horizontalLayout_Main;
    QVBoxLayout *verticalLayout;
    QLabel *lblBaslikGenel;
    QLabel *lblFotoBaslik;
    QHBoxLayout *fotoSatir1;
    QLabel *lblFoto1;
    QPushButton *btnFoto1;
    QHBoxLayout *fotoSatir2;
    QLabel *lblFoto2;
    QPushButton *btnFoto2;
    QHBoxLayout *fotoSatir3;
    QLabel *lblFoto3;
    QPushButton *btnFoto3;
    QHBoxLayout *fotoSatir4;
    QLabel *lblFoto4;
    QPushButton *btnFoto4;
    QHBoxLayout *fotoSatir5;
    QLabel *lblFoto5;
    QPushButton *btnFoto5;
    QLabel *lblBaslik;
    QLineEdit *txtBaslik;
    QLabel *lblFiyat;
    QLineEdit *txtFiyat;
    QLabel *lblKategori;
    QComboBox *cmbKategori;
    QLabel *lblStok;
    QHBoxLayout *stokLayout;
    QSpacerItem *stokSpacerSol;
    QPushButton *btnStokAzalt;
    QSpinBox *spinStok;
    QPushButton *btnStokArttir;
    QSpacerItem *stokSpacerSag;
    QLabel *lblAciklama;
    QTextEdit *txtAciklama;
    QPushButton *btnYayinla;
    QVBoxLayout *layoutOzellikler;

    void setupUi(QWidget *IlanEkle)
    {
        if (IlanEkle->objectName().isEmpty())
            IlanEkle->setObjectName("IlanEkle");
        IlanEkle->resize(850, 720);
        horizontalLayout_Main = new QHBoxLayout(IlanEkle);
        horizontalLayout_Main->setObjectName("horizontalLayout_Main");
        verticalLayout = new QVBoxLayout();
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

        lblFotoBaslik = new QLabel(IlanEkle);
        lblFotoBaslik->setObjectName("lblFotoBaslik");

        verticalLayout->addWidget(lblFotoBaslik);

        fotoSatir1 = new QHBoxLayout();
        fotoSatir1->setObjectName("fotoSatir1");
        lblFoto1 = new QLabel(IlanEkle);
        lblFoto1->setObjectName("lblFoto1");

        fotoSatir1->addWidget(lblFoto1);

        btnFoto1 = new QPushButton(IlanEkle);
        btnFoto1->setObjectName("btnFoto1");
        btnFoto1->setMinimumSize(QSize(70, 28));

        fotoSatir1->addWidget(btnFoto1);


        verticalLayout->addLayout(fotoSatir1);

        fotoSatir2 = new QHBoxLayout();
        fotoSatir2->setObjectName("fotoSatir2");
        lblFoto2 = new QLabel(IlanEkle);
        lblFoto2->setObjectName("lblFoto2");

        fotoSatir2->addWidget(lblFoto2);

        btnFoto2 = new QPushButton(IlanEkle);
        btnFoto2->setObjectName("btnFoto2");
        btnFoto2->setMinimumSize(QSize(70, 28));

        fotoSatir2->addWidget(btnFoto2);


        verticalLayout->addLayout(fotoSatir2);

        fotoSatir3 = new QHBoxLayout();
        fotoSatir3->setObjectName("fotoSatir3");
        lblFoto3 = new QLabel(IlanEkle);
        lblFoto3->setObjectName("lblFoto3");

        fotoSatir3->addWidget(lblFoto3);

        btnFoto3 = new QPushButton(IlanEkle);
        btnFoto3->setObjectName("btnFoto3");
        btnFoto3->setMinimumSize(QSize(70, 28));

        fotoSatir3->addWidget(btnFoto3);


        verticalLayout->addLayout(fotoSatir3);

        fotoSatir4 = new QHBoxLayout();
        fotoSatir4->setObjectName("fotoSatir4");
        lblFoto4 = new QLabel(IlanEkle);
        lblFoto4->setObjectName("lblFoto4");

        fotoSatir4->addWidget(lblFoto4);

        btnFoto4 = new QPushButton(IlanEkle);
        btnFoto4->setObjectName("btnFoto4");
        btnFoto4->setMinimumSize(QSize(70, 28));

        fotoSatir4->addWidget(btnFoto4);


        verticalLayout->addLayout(fotoSatir4);

        fotoSatir5 = new QHBoxLayout();
        fotoSatir5->setObjectName("fotoSatir5");
        lblFoto5 = new QLabel(IlanEkle);
        lblFoto5->setObjectName("lblFoto5");

        fotoSatir5->addWidget(lblFoto5);

        btnFoto5 = new QPushButton(IlanEkle);
        btnFoto5->setObjectName("btnFoto5");
        btnFoto5->setMinimumSize(QSize(70, 28));

        fotoSatir5->addWidget(btnFoto5);


        verticalLayout->addLayout(fotoSatir5);

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

        lblStok = new QLabel(IlanEkle);
        lblStok->setObjectName("lblStok");

        verticalLayout->addWidget(lblStok);

        stokLayout = new QHBoxLayout();
        stokLayout->setSpacing(5);
        stokLayout->setObjectName("stokLayout");
        stokSpacerSol = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        stokLayout->addItem(stokSpacerSol);

        btnStokAzalt = new QPushButton(IlanEkle);
        btnStokAzalt->setObjectName("btnStokAzalt");
        btnStokAzalt->setMinimumSize(QSize(40, 40));
        btnStokAzalt->setMaximumSize(QSize(40, 40));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        btnStokAzalt->setFont(font1);

        stokLayout->addWidget(btnStokAzalt);

        spinStok = new QSpinBox(IlanEkle);
        spinStok->setObjectName("spinStok");
        spinStok->setMinimumSize(QSize(80, 40));
        spinStok->setMaximumSize(QSize(80, 40));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        spinStok->setFont(font2);
        spinStok->setAlignment(Qt::AlignCenter);
        spinStok->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinStok->setMinimum(1);
        spinStok->setMaximum(9999);
        spinStok->setValue(1);

        stokLayout->addWidget(spinStok);

        btnStokArttir = new QPushButton(IlanEkle);
        btnStokArttir->setObjectName("btnStokArttir");
        btnStokArttir->setMinimumSize(QSize(40, 40));
        btnStokArttir->setMaximumSize(QSize(40, 40));
        btnStokArttir->setFont(font1);

        stokLayout->addWidget(btnStokArttir);

        stokSpacerSag = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        stokLayout->addItem(stokSpacerSag);


        verticalLayout->addLayout(stokLayout);

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


        horizontalLayout_Main->addLayout(verticalLayout);

        layoutOzellikler = new QVBoxLayout();
        layoutOzellikler->setObjectName("layoutOzellikler");

        horizontalLayout_Main->addLayout(layoutOzellikler);


        retranslateUi(IlanEkle);

        QMetaObject::connectSlotsByName(IlanEkle);
    } // setupUi

    void retranslateUi(QWidget *IlanEkle)
    {
        IlanEkle->setWindowTitle(QCoreApplication::translate("IlanEkle", "Yeni \304\260lan Ekle", nullptr));
        lblBaslikGenel->setText(QCoreApplication::translate("IlanEkle", "YEN\304\260 \304\260LAN EKLE", nullptr));
        lblFotoBaslik->setText(QCoreApplication::translate("IlanEkle", "Foto\304\237raflar (Maks 5):", nullptr));
        lblFoto1->setText(QCoreApplication::translate("IlanEkle", "Foto 1: \342\200\224", nullptr));
        btnFoto1->setText(QCoreApplication::translate("IlanEkle", "Se\303\247...", nullptr));
        lblFoto2->setText(QCoreApplication::translate("IlanEkle", "Foto 2: \342\200\224", nullptr));
        btnFoto2->setText(QCoreApplication::translate("IlanEkle", "Se\303\247...", nullptr));
        lblFoto3->setText(QCoreApplication::translate("IlanEkle", "Foto 3: \342\200\224", nullptr));
        btnFoto3->setText(QCoreApplication::translate("IlanEkle", "Se\303\247...", nullptr));
        lblFoto4->setText(QCoreApplication::translate("IlanEkle", "Foto 4: \342\200\224", nullptr));
        btnFoto4->setText(QCoreApplication::translate("IlanEkle", "Se\303\247...", nullptr));
        lblFoto5->setText(QCoreApplication::translate("IlanEkle", "Foto 5: \342\200\224", nullptr));
        btnFoto5->setText(QCoreApplication::translate("IlanEkle", "Se\303\247...", nullptr));
        lblBaslik->setText(QCoreApplication::translate("IlanEkle", "\304\260lan Ba\305\237l\304\261\304\237\304\261:", nullptr));
        lblFiyat->setText(QCoreApplication::translate("IlanEkle", "Fiyat (TL):", nullptr));
        lblKategori->setText(QCoreApplication::translate("IlanEkle", "Kategori Se\303\247iniz:", nullptr));
        cmbKategori->setItemText(0, QCoreApplication::translate("IlanEkle", "Emlak", nullptr));
        cmbKategori->setItemText(1, QCoreApplication::translate("IlanEkle", "Vas\304\261ta", nullptr));
        cmbKategori->setItemText(2, QCoreApplication::translate("IlanEkle", "Elektronik", nullptr));
        cmbKategori->setItemText(3, QCoreApplication::translate("IlanEkle", "Giyim", nullptr));

        lblStok->setText(QCoreApplication::translate("IlanEkle", "Stok Adedi:", nullptr));
        btnStokAzalt->setStyleSheet(QCoreApplication::translate("IlanEkle", "background-color: #f44336; color: white; border-radius: 4px;", nullptr));
        btnStokAzalt->setText(QCoreApplication::translate("IlanEkle", "-", nullptr));
        btnStokArttir->setStyleSheet(QCoreApplication::translate("IlanEkle", "background-color: #4CAF50; color: white; border-radius: 4px;", nullptr));
        btnStokArttir->setText(QCoreApplication::translate("IlanEkle", "+", nullptr));
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
