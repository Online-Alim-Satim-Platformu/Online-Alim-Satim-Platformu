#include "anasayfa.h"
#include "ui_anasayfa.h"
#include "ilanekle.h"
#include "databasemanager.h"
#include "profil.h"
#include "girisekrani.h" // Giriş ekranına dönmek için gerekli
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QIcon>
#include <QListWidgetItem>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QScrollArea>

AnaSayfa::AnaSayfa(QWidget *parent) : QWidget(parent), ui(new Ui::AnaSayfa) {
    ui->setupUi(this);

    if (DatabaseManager::getInstance()->baglantiKur()) {
        ilanlariYukle();
    } else {
        QMessageBox::critical(this, "Bağlantı Hatası", "Veritabanı açılamadı!");
    }
}

AnaSayfa::~AnaSayfa() {
    delete ui;
}

void AnaSayfa::listeyiDoldur(QSqlQuery &query) {
    ui->listVitrin->clear();
    ui->listVitrin->setViewMode(QListView::IconMode);
    ui->listVitrin->setIconSize(QSize(150, 150));
    ui->listVitrin->setResizeMode(QListView::Adjust);
    ui->listVitrin->setSpacing(20);
    ui->listVitrin->setWordWrap(true);

    while (query.next()) {
        int     ilanNo   = query.value("ilanNo").toInt();
        QString baslik   = query.value("baslik").toString();
        QString fiyat    = query.value("fiyat").toString();
        QString fotoYolu = query.value("fotografYolu").toString();

        QListWidgetItem *item = new QListWidgetItem();
        item->setText(baslik + "\n" + fiyat + " TL");
        item->setTextAlignment(Qt::AlignCenter);
        item->setData(Qt::UserRole, ilanNo);

        if (!fotoYolu.isEmpty()) {
            item->setIcon(QIcon(fotoYolu));
        } else {
            item->setIcon(style()->standardIcon(QStyle::SP_FileIcon));
        }

        item->setForeground(Qt::black);
        ui->listVitrin->addItem(item);
    }
}

void AnaSayfa::ilanlariYukle() {
    ui->lblVitrinBaslik->setText("Anasayfa Vitrini");
    ui->txtSearch->clear();

    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    QSqlQuery query(db);

    if (!query.exec("SELECT ilanNo, baslik, fiyat, fotografYolu FROM Ilan")) {
        qDebug() << "Vitrin yükleme hatası:" << query.lastError().text();
        return;
    }

    listeyiDoldur(query);
}

void AnaSayfa::kategoriIlanlariYukle(const QString &kategori) {
    ui->lblVitrinBaslik->setText(kategori + " İlanları");
    ui->txtSearch->clear();

    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    QSqlQuery query(db);

    query.prepare("SELECT ilanNo, baslik, fiyat, fotografYolu FROM Ilan WHERE kategori = :kat");
    query.bindValue(":kat", kategori);

    if (!query.exec()) {
        qDebug() << "Kategori filtre hatası:" << query.lastError().text();
        return;
    }

    listeyiDoldur(query);
}

void AnaSayfa::on_txtSearch_textChanged(const QString &arananKelime) {
    if (arananKelime.isEmpty()) {
        ilanlariYukle();
        return;
    }

    ui->lblVitrinBaslik->setText("Arama: \"" + arananKelime + "\"");

    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    QSqlQuery query(db);

    query.prepare("SELECT ilanNo, baslik, fiyat, fotografYolu FROM Ilan "
                  "WHERE baslik LIKE :kelime");
    query.bindValue(":kelime", "%" + arananKelime + "%");

    if (!query.exec()) {
        qDebug() << "Arama hatası:" << query.lastError().text();
        return;
    }

    listeyiDoldur(query);
}

void AnaSayfa::on_listVitrin_itemDoubleClicked(QListWidgetItem *item) {
    int ilanNo = item->data(Qt::UserRole).toInt();

    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    QSqlQuery query(db);

    query.prepare("SELECT baslik, fiyat, kategori, aciklama, fotografYolu FROM Ilan WHERE ilanNo = :id");
    query.bindValue(":id", ilanNo);

    if (!query.exec() || !query.next()) {
        QMessageBox::warning(this, "Hata", "İlan detayları yüklenemedi.");
        return;
    }

    QString baslik   = query.value("baslik").toString();
    QString fiyat    = query.value("fiyat").toString();
    QString kategori = query.value("kategori").toString();
    QString aciklama = query.value("aciklama").toString();
    QString fotoYolu = query.value("fotografYolu").toString();

    QDialog *detay = new QDialog(this);
    detay->setWindowTitle("İlan Detayı");
    detay->setMinimumSize(500, 450);
    detay->setStyleSheet("background-color: #1e1e1e; color: white;");
    detay->setAttribute(Qt::WA_DeleteOnClose);

    QVBoxLayout *anaLayout = new QVBoxLayout(detay);
    anaLayout->setSpacing(12);
    anaLayout->setContentsMargins(20, 20, 20, 20);

    if (!fotoYolu.isEmpty()) {
        QLabel *lblFoto = new QLabel(detay); // Memory leak önlemi için detay eklendi
        QPixmap px(fotoYolu);
        if (!px.isNull()) {
            lblFoto->setPixmap(px.scaled(460, 220, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            lblFoto->setAlignment(Qt::AlignCenter);
            anaLayout->addWidget(lblFoto);
        }
    }

    QLabel *lblBaslik = new QLabel(baslik);
    lblBaslik->setStyleSheet("font-size: 18px; font-weight: bold; color: white;");
    lblBaslik->setWordWrap(true);
    anaLayout->addWidget(lblBaslik);

    QLabel *lblFiyat = new QLabel("💰 " + fiyat + " TL");
    lblFiyat->setStyleSheet("font-size: 16px; font-weight: bold; color: #4CAF50;");
    anaLayout->addWidget(lblFiyat);

    QLabel *lblKategori = new QLabel("📂 Kategori: " + kategori);
    lblKategori->setStyleSheet("font-size: 13px; color: #aaaaaa;");
    anaLayout->addWidget(lblKategori);

    QFrame *cizgi = new QFrame();
    cizgi->setFrameShape(QFrame::HLine);
    cizgi->setStyleSheet("color: #444444;");
    anaLayout->addWidget(cizgi);

    QLabel *lblAciklamaBaslik = new QLabel("📝 Açıklama:");
    lblAciklamaBaslik->setStyleSheet("font-size: 13px; font-weight: bold; color: #cccccc;");
    anaLayout->addWidget(lblAciklamaBaslik);

    QLabel *lblAciklama = new QLabel(aciklama.isEmpty() ? "Açıklama girilmemiş." : aciklama);
    lblAciklama->setStyleSheet("font-size: 13px; color: white; padding: 8px; "
                               "background-color: #2d2d2d; border-radius: 6px;");
    lblAciklama->setWordWrap(true);
    lblAciklama->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    QScrollArea *scroll = new QScrollArea();
    scroll->setWidget(lblAciklama);
    scroll->setWidgetResizable(true);
    scroll->setMinimumHeight(80);
    scroll->setStyleSheet("border: none; background-color: #2d2d2d;");
    anaLayout->addWidget(scroll);

    QPushButton *btnKapat = new QPushButton("✖ Kapat");
    btnKapat->setStyleSheet("QPushButton { background-color: #555555; color: white; "
                            "border-radius: 6px; padding: 8px; font-weight: bold; }"
                            "QPushButton:hover { background-color: #777777; }");
    connect(btnKapat, &QPushButton::clicked, detay, &QDialog::close);
    anaLayout->addWidget(btnKapat);

    detay->exec();
}

// ──────────────────────────────────────────────────────────────
// ÇIKIŞ YAP FONKSİYONU
// ──────────────────────────────────────────────────────────────
void AnaSayfa::on_btnCikisYap_clicked() {
    // 1. Kullanıcıdan onay al
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Çıkış Yap", "Hesabınızdan çıkış yapmak istediğinize emin misiniz?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 2. Aktif oturumu sıfırla (kimse girmediği için -1 yap)
        DatabaseManager::getInstance()->setAktifKullaniciID(-1);

        // 3. Giriş ekranını oluştur ve göster
        GirisEkrani *login = new GirisEkrani();
        login->show();

        // 4. Mevcut Anasayfayı kapat
        this->close();
    }
}

void AnaSayfa::on_btnTumVitrin_clicked()  { ilanlariYukle(); }
void AnaSayfa::on_btnEmlak_clicked()      { kategoriIlanlariYukle("Emlak"); }
void AnaSayfa::on_btnVasita_clicked()     { kategoriIlanlariYukle("Vasıta"); }
void AnaSayfa::on_btnElektronik_clicked() { kategoriIlanlariYukle("Elektronik"); }
void AnaSayfa::on_btnGiyim_clicked()      { kategoriIlanlariYukle("Giyim"); }

void AnaSayfa::on_btnIlanVer_clicked() {
    IlanEkle *ekran = new IlanEkle();
    connect(ekran, &IlanEkle::destroyed, this, [this]() {
        this->ilanlariYukle();
    });
    ekran->setAttribute(Qt::WA_DeleteOnClose);
    ekran->show();
}

void AnaSayfa::on_btnProfil_clicked() {
    Profil *p = new Profil();
    p->setAttribute(Qt::WA_DeleteOnClose);
    p->show();
}
