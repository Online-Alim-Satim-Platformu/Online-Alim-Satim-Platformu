#include "anasayfa.h"
#include "ui_anasayfa.h"
#include "ilanekle.h"
#include "databasemanager.h"
#include "profil.h"
#include "ilandetay.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QIcon>
#include <QFont>

AnaSayfa::AnaSayfa(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AnaSayfa)
{
    ui->setupUi(this);

    // Singleton DatabaseManager üzerinden bağlantı kontrolü
    if(DatabaseManager::getInstance()->baglantiKur()) {
        qDebug() << "Veritabanı bağlantısı kuruldu, vitrin hazırlanıyor...";
        ilanlariYukle();
    } else {
        QMessageBox::critical(this, "Bağlantı Hatası", "Veritabanı açılamadı!");
    }
}

AnaSayfa::~AnaSayfa()
{
    delete ui;
}

void AnaSayfa::ilanlariYukle() {
    // Listeyi temizle
    ui->listVitrin->clear();

    // XML'deki tasarıma sadık kalarak vitrin ayarları
    ui->listVitrin->setViewMode(QListView::IconMode);
    ui->listVitrin->setIconSize(QSize(170, 170));
    ui->listVitrin->setSpacing(15);
    ui->listVitrin->setWordWrap(true);

    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    QSqlQuery query(db);

    // İlanları çekiyoruz. ID bilgisi (ilanNo) detay ekranı için şarttır.
    QString sql = "SELECT ilanNo, baslik, fiyat, fotografYolu FROM ILAN";

    if (query.exec(sql)) {
        while (query.next()) {
            int id = query.value("ilanNo").toInt();
            QString baslik = query.value("baslik").toString();
            QString fiyat = query.value("fiyat").toString();
            QString foto = query.value("fotografYolu").toString();

            QListWidgetItem *item = new QListWidgetItem();

            // Tıklanan ilanı bulmak için ID'yi item'a gömüyoruz
            item->setData(Qt::UserRole, id);

            // Görsel Metin Formatı
            item->setText("İlan: " + baslik + "\nFiyat: " + fiyat + " TL");
            item->setTextAlignment(Qt::AlignCenter);

            // Yazı Tipi Ayarı
            QFont font;
            font.setBold(true);
            item->setFont(font);
            item->setForeground(Qt::black);

            // Fotoğraf Kontrolü
            if (!foto.isEmpty()) {
                item->setIcon(QIcon(foto));
            } else {
                item->setIcon(style()->standardIcon(QStyle::SP_FileIcon));
            }

            ui->listVitrin->addItem(item);
        }
        qDebug() << "Vitrin başarıyla güncellendi.";
    } else {
        qDebug() << "Sorgu Hatası:" << query.lastError().text();
    }
}

// İlan Detayını Açan Fonksiyon
void AnaSayfa::on_listVitrin_itemDoubleClicked(QListWidgetItem *item) {
    if(!item) return;

    // Gömülü olan ID'yi al
    int secilenID = item->data(Qt::UserRole).toInt();
    qDebug() << "Seçilen İlan ID:" << secilenID;

    // Detay penceresini aç
    IlanDetay *detay = new IlanDetay(secilenID);
    detay->setAttribute(Qt::WA_DeleteOnClose);
    detay->show();
}

// SOL PANEL (KATEGORİLER)
void AnaSayfa::on_btnTumVitrin_clicked() {
    qDebug() << "Tüm vitrin yükleniyor...";
    ilanlariYukle();
}

void AnaSayfa::on_btnEmlak_clicked() {
    qDebug() << "Emlak kategorisi seçildi.";
    ilanlariYukle(); // Filtreleme mantığı buraya eklenebilir
}

void AnaSayfa::on_btnVasita_clicked() {
    qDebug() << "Vasıta kategorisi seçildi.";
    ilanlariYukle();
}

void AnaSayfa::on_btnElektronik_clicked() {
    qDebug() << "Elektronik kategorisi seçildi.";
    ilanlariYukle();
}

void AnaSayfa::on_btnGiyim_clicked() {
    qDebug() << "Giyim kategorisi seçildi.";
    ilanlariYukle();
}

// ÜST PANEL
void AnaSayfa::on_btnProfil_clicked() {
    Profil *p = new Profil();
    p->setAttribute(Qt::WA_DeleteOnClose);
    p->show();
}

void AnaSayfa::on_btnIlanVer_clicked() {
    IlanEkle *e = new IlanEkle();
    // İlan ekleme ekranı kapandığında vitrini tazele
    connect(e, &IlanEkle::destroyed, this, [this](){
        this->ilanlariYukle();
    });
    e->setAttribute(Qt::WA_DeleteOnClose);
    e->show();
}
