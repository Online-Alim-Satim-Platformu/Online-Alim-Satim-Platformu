/********************************************************************************
** Form generated from reading UI file 'anasayfa.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANASAYFA_H
#define UI_ANASAYFA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AnaSayfa
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *topBarLayout;
    QLabel *lblLogo;
    QLineEdit *txtSearch;
    QPushButton *btnProfil;
    QPushButton *btnIlanVer;
    QFrame *line;
    QHBoxLayout *contentLayout;
    QFrame *frameSidebar;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btnEmlak;
    QPushButton *btnVasita;
    QPushButton *btnElektronik;
    QPushButton *btnGiyim;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *vitrinLayout;
    QHBoxLayout *vitrinHeaderLayout;
    QLabel *lblVitrinBaslik;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnYenile;
    QListWidget *listVitrin;

    void setupUi(QWidget *AnaSayfa)
    {
        if (AnaSayfa->objectName().isEmpty())
            AnaSayfa->setObjectName("AnaSayfa");
        AnaSayfa->resize(849, 650);
        verticalLayout = new QVBoxLayout(AnaSayfa);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(20, 20, 20, 20);
        topBarLayout = new QHBoxLayout();
        topBarLayout->setSpacing(20);
        topBarLayout->setObjectName("topBarLayout");
        lblLogo = new QLabel(AnaSayfa);
        lblLogo->setObjectName("lblLogo");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        lblLogo->setFont(font);
        lblLogo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        topBarLayout->addWidget(lblLogo);

        txtSearch = new QLineEdit(AnaSayfa);
        txtSearch->setObjectName("txtSearch");
        txtSearch->setMinimumSize(QSize(300, 35));

        topBarLayout->addWidget(txtSearch);

        btnProfil = new QPushButton(AnaSayfa);
        btnProfil->setObjectName("btnProfil");
        btnProfil->setMinimumSize(QSize(100, 35));
        btnProfil->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        topBarLayout->addWidget(btnProfil);

        btnIlanVer = new QPushButton(AnaSayfa);
        btnIlanVer->setObjectName("btnIlanVer");
        btnIlanVer->setMinimumSize(QSize(110, 35));
        QFont font1;
        font1.setBold(true);
        btnIlanVer->setFont(font1);
        btnIlanVer->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        topBarLayout->addWidget(btnIlanVer);


        verticalLayout->addLayout(topBarLayout);

        line = new QFrame(AnaSayfa);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line);

        contentLayout = new QHBoxLayout();
        contentLayout->setObjectName("contentLayout");
        frameSidebar = new QFrame(AnaSayfa);
        frameSidebar->setObjectName("frameSidebar");
        frameSidebar->setMinimumSize(QSize(160, 0));
        frameSidebar->setMaximumSize(QSize(160, 16777215));
        verticalLayout_2 = new QVBoxLayout(frameSidebar);
        verticalLayout_2->setObjectName("verticalLayout_2");
        btnEmlak = new QPushButton(frameSidebar);
        btnEmlak->setObjectName("btnEmlak");

        verticalLayout_2->addWidget(btnEmlak);

        btnVasita = new QPushButton(frameSidebar);
        btnVasita->setObjectName("btnVasita");

        verticalLayout_2->addWidget(btnVasita);

        btnElektronik = new QPushButton(frameSidebar);
        btnElektronik->setObjectName("btnElektronik");

        verticalLayout_2->addWidget(btnElektronik);

        btnGiyim = new QPushButton(frameSidebar);
        btnGiyim->setObjectName("btnGiyim");

        verticalLayout_2->addWidget(btnGiyim);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        contentLayout->addWidget(frameSidebar);

        vitrinLayout = new QVBoxLayout();
        vitrinLayout->setObjectName("vitrinLayout");
        vitrinHeaderLayout = new QHBoxLayout();
        vitrinHeaderLayout->setObjectName("vitrinHeaderLayout");
        lblVitrinBaslik = new QLabel(AnaSayfa);
        lblVitrinBaslik->setObjectName("lblVitrinBaslik");
        QFont font2;
        font2.setPointSize(13);
        font2.setBold(true);
        lblVitrinBaslik->setFont(font2);

        vitrinHeaderLayout->addWidget(lblVitrinBaslik);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        vitrinHeaderLayout->addItem(horizontalSpacer);

        btnYenile = new QPushButton(AnaSayfa);
        btnYenile->setObjectName("btnYenile");
        btnYenile->setMinimumSize(QSize(90, 30));
        btnYenile->setFont(font1);
        btnYenile->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        vitrinHeaderLayout->addWidget(btnYenile);


        vitrinLayout->addLayout(vitrinHeaderLayout);

        listVitrin = new QListWidget(AnaSayfa);
        listVitrin->setObjectName("listVitrin");
        listVitrin->setResizeMode(QListView::ResizeMode::Adjust);
        listVitrin->setSpacing(20);
        listVitrin->setViewMode(QListView::ViewMode::IconMode);
        listVitrin->setWordWrap(true);

        vitrinLayout->addWidget(listVitrin);


        contentLayout->addLayout(vitrinLayout);


        verticalLayout->addLayout(contentLayout);


        retranslateUi(AnaSayfa);

        QMetaObject::connectSlotsByName(AnaSayfa);
    } // setupUi

    void retranslateUi(QWidget *AnaSayfa)
    {
        AnaSayfa->setWindowTitle(QCoreApplication::translate("AnaSayfa", "Ana Sayfa - Online Al\304\261\305\237veri\305\237 Platformu", nullptr));
        AnaSayfa->setStyleSheet(QCoreApplication::translate("AnaSayfa", "background-color: #1a1a1a; color: white;", nullptr));
        lblLogo->setStyleSheet(QCoreApplication::translate("AnaSayfa", "color: #0078D7; background-color: white; padding: 10px; border-radius: 15px;", nullptr));
        lblLogo->setText(QCoreApplication::translate("AnaSayfa", "Online\n"
"Al\304\261m Sat\304\261m", nullptr));
        txtSearch->setStyleSheet(QCoreApplication::translate("AnaSayfa", "background-color: #333333; color: white; border: 1px solid #444444; border-radius: 5px; padding-left: 10px;", nullptr));
        txtSearch->setPlaceholderText(QCoreApplication::translate("AnaSayfa", "\304\260lanlarda ara...", nullptr));
        btnProfil->setStyleSheet(QCoreApplication::translate("AnaSayfa", "QPushButton { background-color: #444444; color: white; border-radius: 5px; font-weight: bold; }\n"
"QPushButton:hover { background-color: #555555; }", nullptr));
        btnProfil->setText(QCoreApplication::translate("AnaSayfa", "\360\237\221\244 Profilim", nullptr));
        btnIlanVer->setStyleSheet(QCoreApplication::translate("AnaSayfa", "QPushButton { background-color: #0078D7; color: white; border-radius: 5px; padding: 5px; }\n"
"QPushButton:hover { background-color: #005a9e; }", nullptr));
        btnIlanVer->setText(QCoreApplication::translate("AnaSayfa", "\342\236\225 \304\260lan Ver", nullptr));
        line->setStyleSheet(QCoreApplication::translate("AnaSayfa", "background-color: #333333;", nullptr));
        frameSidebar->setStyleSheet(QCoreApplication::translate("AnaSayfa", "QPushButton {\n"
"    background-color: #FF9F00;\n"
"    color: #000000;\n"
"    border: 1px solid #CC7A00;\n"
"    padding: 10px;\n"
"    border-radius: 8px;\n"
"    font-weight: bold;\n"
"    text-align: center;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #FFB84D;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #E68A00;\n"
"}", nullptr));
        btnEmlak->setText(QCoreApplication::translate("AnaSayfa", "\360\237\217\240 Emlak", nullptr));
        btnVasita->setText(QCoreApplication::translate("AnaSayfa", "\360\237\232\227 Vas\304\261ta", nullptr));
        btnElektronik->setText(QCoreApplication::translate("AnaSayfa", "\360\237\222\273 Elektronik", nullptr));
        btnGiyim->setText(QCoreApplication::translate("AnaSayfa", "\360\237\221\225 Giyim", nullptr));
        lblVitrinBaslik->setStyleSheet(QCoreApplication::translate("AnaSayfa", "color: white; margin-bottom: 5px;", nullptr));
        lblVitrinBaslik->setText(QCoreApplication::translate("AnaSayfa", "Anasayfa Vitrini", nullptr));
        btnYenile->setStyleSheet(QCoreApplication::translate("AnaSayfa", "QPushButton { background-color: #333333; color: white; border-radius: 5px; padding: 5px; border: 1px solid #555555; }\n"
"QPushButton:hover { background-color: #555555; }", nullptr));
        btnYenile->setText(QCoreApplication::translate("AnaSayfa", "\360\237\224\204 Yenile", nullptr));
        listVitrin->setStyleSheet(QCoreApplication::translate("AnaSayfa", "QListWidget {\n"
"    background-color: #ffffff;\n"
"    border: 2px solid #333333;\n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"    color: black;\n"
"}\n"
"QListWidget::item {\n"
"    color: black;\n"
"    font-weight: bold;\n"
"    padding: 5px;\n"
"}", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AnaSayfa: public Ui_AnaSayfa {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANASAYFA_H
