#include "anasayfa.h"
#include "ui_anasayfa.h"
#include "ilanekle.h"
#include "databasemanager.h"
#include "profil.h"
#include "ilandetay.h" // <--- Detay sayfasını açabilmek için bu include şart
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QIcon>
#include <QListWidgetItem>
#include <QFont>

AnaSayfa::AnaSayfa(QWidget *parent) : QWidget(parent), ui(new Ui::AnaSayfa) {
    ui->setupUi(this);

    // Veritabanı bağlantısını kur ve ilanları yükle [cite: 1096]
    if(DatabaseManager::getInstance()->baglantiKur()) {
        ilanlariYukle();
    }
}

AnaSayfa::~AnaSayfa() {
    delete ui;
}

void AnaSayfa::ilanlariYukle() {
    ui->listVitrin->clear(); // Listeyi temizle

    // Tasarım Ayarları: Raporundaki vitrin görünümü için ayarlar [cite: 421]
    ui->listVitrin->setViewMode(QListView::IconMode); // İkon modu
    ui->listVitrin->setIconSize(QSize(150, 150)); // Resim boyutu
    ui->listVitrin->setResizeMode(QListView::Adjust);
    ui->listVitrin->setSpacing(20);
    ui->listVitrin->setWordWrap(true);

    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    QSqlQuery query(db);

    // Sorguya ilanNo'yu ekledik çünkü tıklanan ilanı ID ile bulacağız [cite: 250, 1081]
    if (query.exec("SELECT ilanNo, baslik, fiyat, fotografYolu FROM Ilan")) {
        while (query.next()) {
            int ilanNo = query.value("ilanNo").toInt();
            QString baslik = query.value("baslik").toString();
            QString fiyat = query.value("fiyat").toString();
            QString fotoYolu = query.value("fotografYolu").toString();

            QListWidgetItem *item = new QListWidgetItem();

            // ID'yi (ilanNo) item içerisine gizliyoruz
            item->setData(Qt::UserRole, ilanNo);

            // İstediğin format: "İlan:" ve "Fiyat:" başlıkları siyah ve kalın
            item->setText("İlan: " + baslik + "\nFiyat: " + fiyat + " TL");
            item->setTextAlignment(Qt::AlignCenter);

            // Yazı tipi ayarları
            QFont font;
            font.setBold(true);
            item->setFont(font);
            item->setForeground(Qt::black);

            // Fotoğraf yükleme işlemi
            if (!fotoYolu.isEmpty()) {
                item->setIcon(QIcon(fotoYolu));
            } else {
                item->setIcon(style()->standardIcon(QStyle::SP_FileIcon));
            }

            ui->listVitrin->addItem(item);
        }
    } else {
        qDebug() << "Vitrin yükleme hatası:" << query.lastError().text();
    }
}

// LİSTEDEKİ BİR İLANA ÇİFT TIKLANDIĞINDA ÇALIŞAN FONKSİYON
void AnaSayfa::on_listVitrin_itemDoubleClicked(QListWidgetItem *item) {
    // Gizlediğimiz ilanNo bilgisini geri alıyoruz
    int secilenIlanNo = item->data(Qt::UserRole).toInt();

    // Detay ekranını oluştur ve bu ID'yi gönder [cite: 138-139, 773]
    IlanDetay *detayEkrani = new IlanDetay(secilenIlanNo);
    detayEkrani->setAttribute(Qt::WA_DeleteOnClose);
    detayEkrani->show();
}

// PROFİL EKRANINI AÇAN BUTON [cite: 1070]
void AnaSayfa::on_btnProfil_clicked() {
    Profil *p = new Profil();
    p->setAttribute(Qt::WA_DeleteOnClose);
    p->show();
}

void AnaSayfa::on_btnTumVitrin_clicked() {
    ilanlariYukle();
}

// İLAN VERME EKRANINI AÇAN BUTON [cite: 1067]
void AnaSayfa::on_btnIlanVer_clicked() {
    IlanEkle *ekran = new IlanEkle();
    connect(ekran, &IlanEkle::destroyed, this, [this](){
        this->ilanlariYukle();
    });
    ekran->setAttribute(Qt::WA_DeleteOnClose);
    ekran->show();
}

// FİLTRELEME BUTONLARI [cite: 1068]
void AnaSayfa::on_btnEmlak_clicked() { ilanlariYukle(); }
void AnaSayfa::on_btnVasita_clicked() { ilanlariYukle(); }
void AnaSayfa::on_btnElektronik_clicked() { ilanlariYukle(); }
void AnaSayfa::on_btnGiyim_clicked() { ilanlariYukle(); }
