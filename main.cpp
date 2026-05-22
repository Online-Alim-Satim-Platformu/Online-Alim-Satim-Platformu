#include "girisekrani.h"
#include "anasayfa.h"
#include "databasemanager.h"
#include "session.h"
#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // ──────────────────────────────────────────────────────────
    // Global stil: QMessageBox yazıları okunabilir olsun
    // (Koyu tema ile uyumlu)
    // ──────────────────────────────────────────────────────────
    a.setStyleSheet(
        "QMessageBox {"
        "   background-color: #2d2d2d;"
        "   color: white;"
        "}"
        "QMessageBox QLabel {"
        "   color: white;"
        "   font-size: 13px;"
        "}"
        "QMessageBox QPushButton {"
        "   background-color: #444444;"
        "   color: white;"
        "   padding: 5px 15px;"
        "   border-radius: 4px;"
        "   font-weight: bold;"
        "   min-width: 60px;"
        "}"
        "QMessageBox QPushButton:hover {"
        "   background-color: #555555;"
        "}"
        );

    // Veritabanını aç
    if(!DatabaseManager::getInstance()->baglantiKur()){
        return -1;
    }

    QSettings settings("OnlineAlimSatim", "App");
    int kayitliId = settings.value("oturum/kullaniciId", 0).toInt();

    if (kayitliId > 0) {
        aktifKullaniciId = kayitliId;
        AnaSayfa *ana = new AnaSayfa();
        ana->setAttribute(Qt::WA_DeleteOnClose);
        ana->show();
    } else {
        GirisEkrani *w = new GirisEkrani();
        w->setAttribute(Qt::WA_DeleteOnClose);
        w->show();
    }

    return a.exec();
}
