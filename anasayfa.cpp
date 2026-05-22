#include "anasayfa.h"
#include "ui_anasayfa.h"
#include "ilanekle.h"
#include "databasemanager.h"
#include "profil.h"
#include "session.h"
#include "girisekrani.h"
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

    // Dinamik yenile butonu — sadece ikon, yazısız
    QPushButton *btnYenile = new QPushButton(this);
    btnYenile->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));
    btnYenile->setIconSize(QSize(20, 20));
    btnYenile->setFixedSize(35, 35);
    btnYenile->setToolTip("Yenile");
    btnYenile->setStyleSheet(
        "QPushButton { background-color: #444444; border-radius: 5px; }"
        "QPushButton:hover { background-color: #555555; }");
    connect(btnYenile, &QPushButton::clicked, this, &AnaSayfa::ilanlariYukle);
    ui->topBarLayout->insertWidget(2, btnYenile);  // arama kutusunun hemen sağına

    if (DatabaseManager::getInstance()->baglantiKur()) {
        ilanlariYukle();
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
        double  fiyatVal = query.value("fiyat").toDouble();
        QString fiyat    = QString("%L1").arg(fiyatVal, 0, 'f', 0);
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

    if (!query.exec("SELECT ilanNo, baslik, fiyat, COALESCE(foto1, fotografYolu) AS fotografYolu FROM Ilan")) {
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

    query.prepare("SELECT ilanNo, baslik, fiyat, COALESCE(foto1, fotografYolu) AS fotografYolu FROM Ilan WHERE kategori = :kat");
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

    query.prepare("SELECT ilanNo, baslik, fiyat, COALESCE(foto1, fotografYolu) AS fotografYolu FROM Ilan WHERE baslik LIKE :kelime");
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

    query.prepare(
        "SELECT i.baslik, i.fiyat, i.kategori, i.aciklama, i.stokAdedi, "
        "       i.foto1, i.foto2, i.foto3, i.foto4, i.foto5, i.fotografYolu, "
        "       k.kullaniciAdi AS ekleyen, k.email AS ekleyenEmail "
        "FROM Ilan i "
        "LEFT JOIN Kullanici k ON i.kullaniciId = k.kullaniciId "
        "WHERE i.ilanNo = :id");
    query.bindValue(":id", ilanNo);

    if (!query.exec() || !query.next()) {
        QMessageBox::warning(this, "Hata", "İlan detayları yüklenemedi.");
        return;
    }

    QString baslik       = query.value("baslik").toString();
    QString fiyat        = QString("%L1").arg(query.value("fiyat").toDouble(), 0, 'f', 0);
    QString kategori     = query.value("kategori").toString();
    QString aciklama     = query.value("aciklama").toString();
    int     stok         = query.value("stokAdedi").toInt();
    QString ekleyen      = query.value("ekleyen").toString();
    QString ekleyenEmail = query.value("ekleyenEmail").toString();

    // Fotoğraf listesi: foto1..foto5, yoksa fotografYolu (eski kayıtlar için)
    QStringList fotolar;
    const QString kolonlar[5] = {"foto1","foto2","foto3","foto4","foto5"};
    for (const QString &k : kolonlar) {
        QString v = query.value(k).toString();
        if (!v.isEmpty()) fotolar << v;
    }
    if (fotolar.isEmpty()) {
        QString eski = query.value("fotografYolu").toString();
        if (!eski.isEmpty()) fotolar << eski;
    }

    QDialog *detay = new QDialog(this);
    detay->setWindowTitle("İlan Detayı");
    detay->setMinimumSize(500, 480);
    detay->setStyleSheet("background-color: #1e1e1e; color: white;");
    detay->setAttribute(Qt::WA_DeleteOnClose);

    QVBoxLayout *anaLayout = new QVBoxLayout(detay);
    anaLayout->setSpacing(12);
    anaLayout->setContentsMargins(20, 20, 20, 20);

    // ── Fotoğraf Slider ──
    if (!fotolar.isEmpty()) {
        int *sliderIndex = new int(0);  // detay sahibi olduğundan ömrü diyaloğa bağlı

        QHBoxLayout *sliderLayout = new QHBoxLayout();

        QPushButton *btnGeri = new QPushButton("<");
        btnGeri->setFixedSize(32, 80);
        btnGeri->setStyleSheet("QPushButton{background:#333;color:white;border-radius:4px;font-weight:bold;}"
                               "QPushButton:hover{background:#555;}");

        QLabel *lblFotoSlider = new QLabel();
        lblFotoSlider->setAlignment(Qt::AlignCenter);
        lblFotoSlider->setMinimumSize(400, 200);

        QPushButton *btnIleri = new QPushButton(">");
        btnIleri->setFixedSize(32, 80);
        btnIleri->setStyleSheet("QPushButton{background:#333;color:white;border-radius:4px;font-weight:bold;}"
                                "QPushButton:hover{background:#555;}");

        auto guncelleFoto = [=]() {
            QPixmap px(fotolar[*sliderIndex]);
            if (!px.isNull())
                lblFotoSlider->setPixmap(px.scaled(400, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            else
                lblFotoSlider->setText("Görsel yüklenemedi");
            btnGeri->setEnabled(*sliderIndex > 0);
            btnIleri->setEnabled(*sliderIndex < fotolar.size() - 1);
        };

        connect(btnGeri,  &QPushButton::clicked, detay, [=]() { --(*sliderIndex); guncelleFoto(); });
        connect(btnIleri, &QPushButton::clicked, detay, [=]() { ++(*sliderIndex); guncelleFoto(); });

        // detay kapanınca int'i temizle
        connect(detay, &QDialog::destroyed, detay, [sliderIndex](){ delete sliderIndex; });

        sliderLayout->addWidget(btnGeri);
        sliderLayout->addWidget(lblFotoSlider, 1);
        sliderLayout->addWidget(btnIleri);
        anaLayout->addLayout(sliderLayout);

        guncelleFoto();
    }

    QLabel *lblBaslik = new QLabel(baslik);
    lblBaslik->setStyleSheet("font-size: 18px; font-weight: bold; color: white;");
    lblBaslik->setWordWrap(true);
    anaLayout->addWidget(lblBaslik);

    QLabel *lblFiyat = new QLabel("💰 " + fiyat + " TL");
    lblFiyat->setStyleSheet("font-size: 16px; font-weight: bold; color: #4CAF50;");
    anaLayout->addWidget(lblFiyat);

    QLabel *lblStok = new QLabel("📦 Stok Adedi: " + QString::number(stok));
    lblStok->setStyleSheet("font-size: 14px; font-weight: bold; color: #FF9F00;");
    anaLayout->addWidget(lblStok);

    QLabel *lblKategori = new QLabel("📂 Kategori: " + kategori);
    lblKategori->setStyleSheet("font-size: 13px; color: #aaaaaa;");
    anaLayout->addWidget(lblKategori);

    // ── İlanı ekleyenin bilgisi ──
    if (!ekleyen.isEmpty()) {
        QLabel *lblEkleyen = new QLabel("👤 İlanı Ekleyen: " + ekleyen +
                                        (ekleyenEmail.isEmpty() ? "" : "  (" + ekleyenEmail + ")"));
        lblEkleyen->setStyleSheet("font-size: 13px; color: #90caf9; font-weight: bold;");
        anaLayout->addWidget(lblEkleyen);
    }

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

void AnaSayfa::on_btnTumVitrin_clicked()    { ilanlariYukle(); }
void AnaSayfa::on_btnEmlak_clicked()        { kategoriIlanlariYukle("Emlak");      }
void AnaSayfa::on_btnVasita_clicked()       { kategoriIlanlariYukle("Vasıta");     }
void AnaSayfa::on_btnElektronik_clicked()   { kategoriIlanlariYukle("Elektronik"); }
void AnaSayfa::on_btnGiyim_clicked()        { kategoriIlanlariYukle("Giyim");      }

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

void AnaSayfa::on_btnCikisYap_clicked() {
    aktifKullaniciId = 0;

    GirisEkrani *giris = new GirisEkrani();
    giris->show();
    this->close();
}
