#include "girisekrani.h"
#include "databasemanager.h"
#include <QApplication>

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

    GirisEkrani w;
    w.show();

    return a.exec();
}
