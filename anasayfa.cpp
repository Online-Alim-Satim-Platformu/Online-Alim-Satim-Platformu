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
#include <QFormLayout>
#include <QLineEdit>
#include <QMap>

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

    btnFiltrele = new QPushButton(" Filtrele", this);
    btnFiltrele->setIcon(style()->standardIcon(QStyle::SP_FileDialogDetailedView));
    btnFiltrele->setFixedHeight(35);
    btnFiltrele->setStyleSheet(
        "QPushButton { background-color: #2196F3; color: white; border-radius: 5px; padding: 0 15px; font-weight: bold; }"
        "QPushButton:hover { background-color: #1976D2; }");
    btnFiltrele->hide();
    connect(btnFiltrele, &QPushButton::clicked, this, &AnaSayfa::on_btnFiltrele_clicked);
    ui->topBarLayout->insertWidget(3, btnFiltrele);

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
    ui->listVitrin->setMovement(QListView::Static);
    ui->listVitrin->setDragDropMode(QAbstractItemView::NoDragDrop);

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
    guncelKategori = "";
    btnFiltrele->hide();
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
    guncelKategori = kategori;
    btnFiltrele->show();
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

    query.prepare("SELECT ilanNo, baslik, fiyat, COALESCE(foto1, fotografYolu) AS fotografYolu FROM Ilan WHERE baslik LIKE :kelime OR aciklama LIKE :kelime");
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
        "       i.foto1, i.foto2, i.foto3, i.foto4, i.foto5, i.fotografYolu, i.ozellikler, "
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
    QString ozellikler   = query.value("ozellikler").toString();

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
    detay->setMinimumSize(500, 550);
    detay->resize(520, 620);
    detay->setStyleSheet("background-color: #1e1e1e; color: white;");
    detay->setAttribute(Qt::WA_DeleteOnClose);

    // Dialog layout holding the scroll area and the pinned bottom action bar
    QVBoxLayout *dialogLayout = new QVBoxLayout(detay);
    dialogLayout->setContentsMargins(0, 0, 0, 0);
    dialogLayout->setSpacing(0);

    QScrollArea *mainScroll = new QScrollArea(detay);
    mainScroll->setWidgetResizable(true);
    mainScroll->setStyleSheet("QScrollArea { border: none; background-color: #1e1e1e; }");

    QWidget *scrollContent = new QWidget();
    scrollContent->setStyleSheet("background-color: #1e1e1e;");
    QVBoxLayout *anaLayout = new QVBoxLayout(scrollContent);
    anaLayout->setSpacing(12);
    anaLayout->setContentsMargins(20, 20, 20, 10);
    mainScroll->setWidget(scrollContent);
    dialogLayout->addWidget(mainScroll, 1);

    // Pinned bottom bar for buttons
    QWidget *bottomBar = new QWidget(detay);
    bottomBar->setStyleSheet("background-color: #1e1e1e; border-top: 1px solid #2d2d2d;");
    QVBoxLayout *bottomLayout = new QVBoxLayout(bottomBar);
    bottomLayout->setSpacing(8);
    bottomLayout->setContentsMargins(20, 12, 20, 15);
    dialogLayout->addWidget(bottomBar);

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

        QLabel *lblSayac = new QLabel();
        lblSayac->setAlignment(Qt::AlignCenter);
        lblSayac->setStyleSheet("color: #aaaaaa; font-size: 11px;");

        auto guncelleFoto = [=]() {
            QPixmap px(fotolar[*sliderIndex]);
            if (!px.isNull())
                lblFotoSlider->setPixmap(px.scaled(400, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            else
                lblFotoSlider->setText("Görsel yüklenemedi");
            btnGeri->setEnabled(*sliderIndex > 0);
            btnIleri->setEnabled(*sliderIndex < fotolar.size() - 1);
            lblSayac->setText(QString("%1 / %2").arg(*sliderIndex + 1).arg(fotolar.size()));
        };

        connect(btnGeri,  &QPushButton::clicked, detay, [=]() { --(*sliderIndex); guncelleFoto(); });
        connect(btnIleri, &QPushButton::clicked, detay, [=]() { ++(*sliderIndex); guncelleFoto(); });

        // detay kapanınca int'i temizle
        connect(detay, &QDialog::destroyed, detay, [sliderIndex](){ delete sliderIndex; });

        sliderLayout->addWidget(btnGeri);
        sliderLayout->addWidget(lblFotoSlider, 1);
        sliderLayout->addWidget(btnIleri);
        anaLayout->addLayout(sliderLayout);
        anaLayout->addWidget(lblSayac);

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

    if (!ozellikler.isEmpty()) {
        QLabel *lblOzel = new QLabel("⚙ Özellikler:\n" + ozellikler.replace(" | ", "\n"));
        lblOzel->setStyleSheet("font-size: 13px; color: #b3e5fc; font-weight: bold; background-color: #2d2d2d; padding: 6px; border-radius: 4px;");
        lblOzel->setWordWrap(true);
        anaLayout->addWidget(lblOzel);
    }

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
    lblAciklama->setStyleSheet("font-size: 13px; color: white; padding: 12px; "
                               "background-color: #2d2d2d; border-radius: 6px;");
    lblAciklama->setWordWrap(true);
    lblAciklama->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    anaLayout->addWidget(lblAciklama);

    if (aktifKullaniciId > 0) {
        QSqlQuery favKontrol(db);
        favKontrol.prepare("SELECT 1 FROM Favoriler WHERE kullaniciId = :uid AND ilanNo = :ilan");
        favKontrol.bindValue(":uid",  aktifKullaniciId);
        favKontrol.bindValue(":ilan", ilanNo);
        bool zatenFav = favKontrol.exec() && favKontrol.next();

        QPushButton *btnFavori = new QPushButton(zatenFav ? "★ Favorilerden Çıkar" : "☆ Favoriye Ekle");
        btnFavori->setStyleSheet(
            "QPushButton { background-color: #f59e0b; color: white; border-radius: 6px; "
            "padding: 8px; font-weight: bold; }"
            "QPushButton:hover { background-color: #d97706; }");

        connect(btnFavori, &QPushButton::clicked, detay, [=]() {
            QSqlDatabase db2 = DatabaseManager::getInstance()->getDatabase();
            QSqlQuery kontrol(db2);
            kontrol.prepare("SELECT 1 FROM Favoriler WHERE kullaniciId = :uid AND ilanNo = :ilan");
            kontrol.bindValue(":uid",  aktifKullaniciId);
            kontrol.bindValue(":ilan", ilanNo);

            if (kontrol.exec() && kontrol.next()) {
                QSqlQuery sil(db2);
                sil.prepare("DELETE FROM Favoriler WHERE kullaniciId = :uid AND ilanNo = :ilan");
                sil.bindValue(":uid",  aktifKullaniciId);
                sil.bindValue(":ilan", ilanNo);
                sil.exec();
                btnFavori->setText("☆ Favoriye Ekle");
            } else {
                QSqlQuery ekle(db2);
                ekle.prepare("INSERT OR IGNORE INTO Favoriler (kullaniciId, ilanNo) VALUES (:uid, :ilan)");
                ekle.bindValue(":uid",  aktifKullaniciId);
                ekle.bindValue(":ilan", ilanNo);
                ekle.exec();
                btnFavori->setText("★ Favorilerden Çıkar");
            }
        });

        bottomLayout->addWidget(btnFavori);
    }

    QPushButton *btnKapat = new QPushButton("✖ Kapat");
    btnKapat->setStyleSheet("QPushButton { background-color: #555555; color: white; "
                            "border-radius: 6px; padding: 8px; font-weight: bold; }"
                            "QPushButton:hover { background-color: #777777; }");
    connect(btnKapat, &QPushButton::clicked, detay, &QDialog::close);
    bottomLayout->addWidget(btnKapat);

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

void AnaSayfa::on_btnFiltrele_clicked() {
    QDialog *filtreDialog = new QDialog(this);
    filtreDialog->setWindowTitle(guncelKategori + " Filtrele");
    filtreDialog->setMinimumWidth(380);
    filtreDialog->setStyleSheet("background-color: #1e1e1e; color: white; font-family: 'Segoe UI', Arial, sans-serif;");

    QVBoxLayout *layout = new QVBoxLayout(filtreDialog);
    layout->setSpacing(15);
    layout->setContentsMargins(20, 20, 20, 20);

    QLabel *lblInfo = new QLabel("<b>" + guncelKategori + " İçin Detaylı Filtre</b>", filtreDialog);
    lblInfo->setStyleSheet("font-size: 16px; color: #4CAF50; margin-bottom: 5px;");
    layout->addWidget(lblInfo);

    QFormLayout *formLayout = new QFormLayout();
    formLayout->setSpacing(10);

    QString editStyle = "QLineEdit { background-color: #2d2d2d; color: white; border: 1px solid #444; border-radius: 4px; padding: 6px; }"
                        "QLineEdit:focus { border: 1px solid #4CAF50; }";

    // Kategoriye özel özellikleri belirle
    QStringList ozellikler;
    if (guncelKategori == "Emlak") {
        ozellikler << "Bina Yaşı" << "Metrekare" << "Oda Sayısı" << "Bulunduğu Kat" << "Konum (İl/İlçe)" << "Isıtma Tipi" << "Balkon (Var/Yok)";
    } else if (guncelKategori == "Vasıta") {
        ozellikler << "Marka" << "Model" << "Yıl" << "Kilometre" << "Yakıt Tipi" << "Vites Tipi" << "Hasar Kaydı (TL)";
    } else if (guncelKategori == "Elektronik") {
        ozellikler << "Marka" << "Model" << "Renk" << "Durum (Sıfır/İkinci El)" << "Garanti (Var/Yok)" << "Fatura (Var/Yok)" << "Kutu (Var/Yok)";
    } else if (guncelKategori == "Giyim") {
        ozellikler << "Marka" << "Beden" << "Renk" << "Durum" << "Kumaş Tipi" << "Cinsiyet" << "Kullanım Türü";
    }

    // Özellik editlerini oluştur ve ekle
    QMap<QString, QLineEdit*> ozellikEditleri;
    for (const QString &ozellik : ozellikler) {
        QLineEdit *edit = new QLineEdit(filtreDialog);
        edit->setStyleSheet(editStyle);
        edit->setPlaceholderText(ozellik + " girin...");
        
        QLabel *lblField = new QLabel(ozellik + ":", filtreDialog);
        lblField->setStyleSheet("font-weight: bold; color: #ccc;");
        
        formLayout->addRow(lblField, edit);
        ozellikEditleri[ozellik] = edit;
    }

    // Genel "Özelliklerde Ara" alanı
    QLineEdit *txtKelime = new QLineEdit(filtreDialog);
    txtKelime->setStyleSheet(editStyle);
    txtKelime->setPlaceholderText("Örn: 3+1, İkinci El, Mavi vb.");
    QLabel *lblKelime = new QLabel("Özellik/Açıklamada Ara:", filtreDialog);
    lblKelime->setStyleSheet("font-weight: bold; color: #ccc;");
    formLayout->addRow(lblKelime, txtKelime);

    // Fiyat filtreleri
    QLineEdit *txtMinFiyat = new QLineEdit(filtreDialog);
    txtMinFiyat->setStyleSheet(editStyle);
    txtMinFiyat->setPlaceholderText("Minimum fiyat...");
    QLabel *lblMinF = new QLabel("Min Fiyat (TL):", filtreDialog);
    lblMinF->setStyleSheet("font-weight: bold; color: #ccc;");
    formLayout->addRow(lblMinF, txtMinFiyat);

    QLineEdit *txtMaxFiyat = new QLineEdit(filtreDialog);
    txtMaxFiyat->setStyleSheet(editStyle);
    txtMaxFiyat->setPlaceholderText("Maksimum fiyat...");
    QLabel *lblMaxF = new QLabel("Max Fiyat (TL):", filtreDialog);
    lblMaxF->setStyleSheet("font-weight: bold; color: #ccc;");
    formLayout->addRow(lblMaxF, txtMaxFiyat);

    layout->addLayout(formLayout);

    // Buton satırı
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(10);

    QPushButton *btnUygula = new QPushButton("Filtreleri Uygula", filtreDialog);
    btnUygula->setStyleSheet(
        "QPushButton { background-color: #4CAF50; color: white; padding: 10px; font-weight: bold; border-radius: 6px; font-size: 13px; border: none; }"
        "QPushButton:hover { background-color: #45a049; }"
        "QPushButton:pressed { background-color: #3e8e41; }"
    );

    QPushButton *btnIptal = new QPushButton("İptal", filtreDialog);
    btnIptal->setStyleSheet(
        "QPushButton { background-color: #444; color: white; padding: 10px; font-weight: bold; border-radius: 6px; font-size: 13px; border: none; }"
        "QPushButton:hover { background-color: #555; }"
        "QPushButton:pressed { background-color: #333; }"
    );

    btnLayout->addWidget(btnIptal);
    btnLayout->addWidget(btnUygula);
    layout->addLayout(btnLayout);

    connect(btnUygula, &QPushButton::clicked, filtreDialog, [=]() {
        QString kelime = txtKelime->text().trimmed();
        double minFiyat = txtMinFiyat->text().toDouble();
        double maxFiyat = txtMaxFiyat->text().toDouble();

        QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
        QSqlQuery query(db);

        QString sql = "SELECT ilanNo, baslik, fiyat, COALESCE(foto1, fotografYolu) AS fotografYolu FROM Ilan WHERE kategori = :kat";
        
        if (!kelime.isEmpty()) {
            sql += " AND (ozellikler LIKE :kelime OR aciklama LIKE :kelime)";
        }

        if (minFiyat > 0) sql += " AND fiyat >= :minF";
        if (maxFiyat > 0) sql += " AND fiyat <= :maxF";

        // Kategori özelliklerini filtreye ekle
        int paramIndex = 0;
        QMap<QString, QString> filtreDegerleri;
        for (auto it = ozellikEditleri.begin(); it != ozellikEditleri.end(); ++it) {
            QString val = it.value()->text().trimmed();
            if (!val.isEmpty()) {
                QString paramName = QString(":param_%1").arg(paramIndex++);
                sql += QString(" AND ozellikler LIKE %1").arg(paramName);
                filtreDegerleri[paramName] = "%" + it.key() + ": " + val + "%";
            }
        }

        query.prepare(sql);
        query.bindValue(":kat", guncelKategori);
        if (!kelime.isEmpty()) query.bindValue(":kelime", "%" + kelime + "%");
        if (minFiyat > 0) query.bindValue(":minF", minFiyat);
        if (maxFiyat > 0) query.bindValue(":maxF", maxFiyat);

        // Dinamik parametreleri bağla
        for (auto it = filtreDegerleri.begin(); it != filtreDegerleri.end(); ++it) {
            query.bindValue(it.key(), it.value());
        }

        if (query.exec()) {
            listeyiDoldur(query);
            filtreDialog->accept();
        } else {
            QMessageBox::warning(this, "Hata", "Filtre uygulanamadı: " + query.lastError().text());
        }
    });

    connect(btnIptal, &QPushButton::clicked, filtreDialog, &QDialog::reject);

    filtreDialog->exec();
}
