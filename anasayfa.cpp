#include "anasayfa.h"
#include "ui_anasayfa.h"
#include "ilanekle.h"
#include "databasemanager.h"
#include "profil.h" // <--- BU SATIR COK KRITIK, MUTLAKA OLMALI
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QIcon>
#include <QListWidgetItem>

AnaSayfa::AnaSayfa(QWidget *parent) : QWidget(parent), ui(new Ui::AnaSayfa) {
    ui->setupUi(this);

    // Veritabanı bağlantısını kur ve ilanları yükle
    if(DatabaseManager::getInstance()->baglantiKur()) {
        ilanlariYukle();
    }
}

AnaSayfa::~AnaSayfa() {
    delete ui;
}

void AnaSayfa::ilanlariYukle() {
    ui->listVitrin->clear(); // Listeyi temizle

    // Tasarım Ayarları: İkonların boyutunu ve metnin konumunu ayarla
    ui->listVitrin->setViewMode(QListView::IconMode); // İkon modu (Resim üstte metin altta)
    ui->listVitrin->setIconSize(QSize(150, 150));    // Resim boyutu
    ui->listVitrin->setResizeMode(QListView::Adjust); // Pencere boyutuna göre hizala
    ui->listVitrin->setSpacing(20);                  // İlanlar arası boşluk
    ui->listVitrin->setWordWrap(true);               // Uzun başlıkları alt satıra geçir

    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    QSqlQuery query(db);

    // Veritabanından Başlık, Fiyat ve Fotoğraf Yolu bilgilerini çekiyoruz
    if (query.exec("SELECT baslik, fiyat, fotografYolu FROM Ilan")) {
        while (query.next()) {
            QString baslik = query.value("baslik").toString();
            QString fiyat = query.value("fiyat").toString();
            QString fotoYolu = query.value("fotografYolu").toString();

            QListWidgetItem *item = new QListWidgetItem();

            // Metni Oluştur: Üstte Başlık, bir alt satırda Fiyat
            // \n karakteri fiyatı başlığın altına atar
            item->setText(baslik + "\n" + fiyat + " TL");
            item->setTextAlignment(Qt::AlignCenter); // Metni ortala

            // Fotoğraf varsa yükle, yoksa varsayılan ikon koy
            if (!fotoYolu.isEmpty()) {
                item->setIcon(QIcon(fotoYolu));
            } else {
                item->setIcon(style()->standardIcon(QStyle::SP_FileIcon));
            }

            // Stili Güzelleştirmek İçin (İsteğe bağlı: Yazı rengini siyah yapalım)
            item->setForeground(Qt::black);

            ui->listVitrin->addItem(item);
        }
    } else {
        qDebug() << "Vitrin yükleme hatası:" << query.lastError().text();
    }
}

// PROFIL EKRANINI ACAN BUTON FONKSIYONU
void AnaSayfa::on_btnProfil_clicked() {
    Profil *p = new Profil(); // Profil sınıfından yeni bir pencere oluşturur
    p->setAttribute(Qt::WA_DeleteOnClose); // Pencere kapandığında hafızadan siler
    p->show(); // Pencereyi ekranda gösterir
}

void AnaSayfa::on_btnTumVitrin_clicked() {
    ilanlariYukle();
}

void AnaSayfa::on_btnIlanVer_clicked() {
    IlanEkle *ekran = new IlanEkle();
    connect(ekran, &IlanEkle::destroyed, this, [this](){
        this->ilanlariYukle();
    });
    ekran->setAttribute(Qt::WA_DeleteOnClose);
    ekran->show();
}

// Filtreleme butonları (Geliştirilebilir)
void AnaSayfa::on_btnEmlak_clicked() { ilanlariYukle(); }
void AnaSayfa::on_btnVasita_clicked() { ilanlariYukle(); }
void AnaSayfa::on_btnElektronik_clicked() { ilanlariYukle(); }
void AnaSayfa::on_btnGiyim_clicked() { ilanlariYukle(); }
