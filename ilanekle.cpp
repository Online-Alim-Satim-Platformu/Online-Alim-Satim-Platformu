#include "ilanekle.h"
#include "ui_ilanekle.h"
#include "databasemanager.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QDateTime>
#include <QLabel>
#include "session.h"

IlanEkle::IlanEkle(QWidget *parent) : QWidget(parent), ui(new Ui::IlanEkle) {
    ui->setupUi(this);

    ui->spinStok->setRange(1, 9999);
    ui->spinStok->setValue(1);
    ui->spinStok->setAlignment(Qt::AlignCenter);
    ui->spinStok->setButtonSymbols(QAbstractSpinBox::NoButtons);

    QLabel *lbller[5] = { ui->lblFoto1, ui->lblFoto2, ui->lblFoto3, ui->lblFoto4, ui->lblFoto5 };
    QPushButton *btnler[5] = { ui->btnFoto1, ui->btnFoto2, ui->btnFoto3, ui->btnFoto4, ui->btnFoto5 };
    for (int i = 0; i < 5; i++) {
        lbller[i]->setStyleSheet("color: #555555; font-size: 9pt;");
        btnler[i]->setStyleSheet(
            "QPushButton { background-color: #6366f1; color: white; border-radius: 4px; }"
            "QPushButton:hover { background-color: #4f46e5; }");
        connect(btnler[i], &QPushButton::clicked, this, [this, i]() { fotoSec(i); });
    }

    connect(ui->cmbKategori, &QComboBox::currentTextChanged, this, &IlanEkle::on_cmbKategori_currentTextChanged);
    on_cmbKategori_currentTextChanged(ui->cmbKategori->currentText());
}

IlanEkle::~IlanEkle() {
    delete ui;
}

void IlanEkle::fotoSec(int index) {
    QString dosya = QFileDialog::getOpenFileName(
        this, "Fotoğraf Seç", "", "Resimler (*.png *.jpg *.jpeg *.bmp)");
    if (dosya.isEmpty()) return;

    secilenFotolar[index] = dosya;

    QLabel *lbller[5] = { ui->lblFoto1, ui->lblFoto2, ui->lblFoto3, ui->lblFoto4, ui->lblFoto5 };
    lbller[index]->setText("Foto " + QString::number(index + 1) + ": " + QFileInfo(dosya).fileName());
    lbller[index]->setStyleSheet("color: #1a7f37; font-size: 9pt;");
}

void IlanEkle::on_btnStokArttir_clicked() {
    ui->spinStok->setValue(ui->spinStok->value() + 1);
}

void IlanEkle::on_btnStokAzalt_clicked() {
    int yeniDeger = ui->spinStok->value() - 1;
    if (yeniDeger < 1) yeniDeger = 1; // En az 1 stok olsun
    ui->spinStok->setValue(yeniDeger);
}

void IlanEkle::on_btnYayinla_clicked() {
    QString baslik = ui->txtBaslik->text();
    double fiyat = ui->txtFiyat->text().toDouble();
    int stokAdedi = ui->spinStok->value();

    // Boşluk ve fiyat kontrolü
    if (baslik.isEmpty() || fiyat <= 0) {
        QMessageBox::warning(this, "Hata", "Lütfen bir başlık ve geçerli bir fiyat giriniz!");
        return;
    }

    if (stokAdedi <= 0) {
        QMessageBox::warning(this, "Hata", "Stok adedi en az 1 olmalıdır!");
        return;
    }

    // Veritabanı bağlantısını al
    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    if (!db.isOpen()) {
        if (!DatabaseManager::getInstance()->baglantiKur()) {
            QMessageBox::critical(this, "Hata", "Veritabanı bağlantısı kurulamadı!");
            return;
        }
    }

    // Her fotoğrafı images/ klasörüne kopyala
    QString imagesDir = qApp->applicationDirPath() + "/images";
    QDir().mkpath(imagesDir);

    QString kayitliYollar[5];
    for (int i = 0; i < 5; i++) {
        if (!secilenFotolar[i].isEmpty()) {
            QString hedef = imagesDir + "/" +
                            QString::number(QDateTime::currentMSecsSinceEpoch()) + "_" +
                            QString::number(i) + ".jpg";
            QFile::copy(secilenFotolar[i], hedef);
            kayitliYollar[i] = hedef;
        }
    }

    QStringList ozellikList;
    for (auto it = ozellikAlanlari.begin(); it != ozellikAlanlari.end(); ++it) {
        if (!it.value()->text().isEmpty()) {
            ozellikList << it.key() + ": " + it.value()->text();
        }
    }
    QString ozelliklerStr = ozellikList.join(" | ");

    QSqlQuery query(db);
    query.prepare("INSERT INTO Ilan (baslik, fiyat, kategori, aciklama, stokAdedi, "
                  "foto1, foto2, foto3, foto4, foto5, kullaniciId, ozellikler) "
                  "VALUES (:b, :f, :k, :a, :s, :f1, :f2, :f3, :f4, :f5, :uid, :ozel)");
    query.bindValue(":b",   baslik);
    query.bindValue(":f",   fiyat);
    query.bindValue(":k",   ui->cmbKategori->currentText());
    query.bindValue(":a",   ui->txtAciklama->toPlainText());
    query.bindValue(":s",   stokAdedi);
    query.bindValue(":f1",  kayitliYollar[0]);
    query.bindValue(":f2",  kayitliYollar[1]);
    query.bindValue(":f3",  kayitliYollar[2]);
    query.bindValue(":f4",  kayitliYollar[3]);
    query.bindValue(":f5",  kayitliYollar[4]);
    query.bindValue(":uid", aktifKullaniciId);
    query.bindValue(":ozel", ozelliklerStr);

    // Sorguyu çalıştır ve sonucu kontrol et
    if (query.exec()) {
        QMessageBox::information(this, "Başarılı", "İlan başarıyla yayınlandı!");
        this->close();
    } else {
        QMessageBox::critical(this, "Sorgu Hatası", "İlan kaydedilemedi!\nHata: " + query.lastError().text());
    }
}

void IlanEkle::on_btnIptal_clicked() {
    this->close();
}

void IlanEkle::ozellikleriTemizle() {
    QLayoutItem *child;
    while ((child = ui->layoutOzellikler->takeAt(0)) != nullptr) {
        if (child->widget()) {
            delete child->widget();
            delete child;
        } else if (child->layout()) {
            QLayout *subLayout = child->layout();
            QLayoutItem *subchild;
            while ((subchild = subLayout->takeAt(0)) != nullptr) {
                if (subchild->widget()) {
                    delete subchild->widget();
                }
                delete subchild;
            }
            delete subLayout;
        } else {
            delete child;
        }
    }
    ozellikAlanlari.clear();
}

void IlanEkle::ozellikEkle(const QString &label) {
    QHBoxLayout *hLayout = new QHBoxLayout();
    QLabel *lbl = new QLabel(label + ":", this);
    lbl->setStyleSheet("font-weight: bold;");
    QLineEdit *txt = new QLineEdit(this);
    hLayout->addWidget(lbl);
    hLayout->addWidget(txt);
    ui->layoutOzellikler->addLayout(hLayout);
    ozellikAlanlari[label] = txt;
}

void IlanEkle::on_cmbKategori_currentTextChanged(const QString &kategori) {
    ozellikleriTemizle();
    
    QLabel *baslik = new QLabel("<b>" + kategori + " Özellikleri</b>", this);
    baslik->setStyleSheet("font-size: 16px; color: #4CAF50; margin-bottom: 10px;");
    ui->layoutOzellikler->addWidget(baslik);

    if (kategori == "Emlak") {
        ozellikEkle("Bina Yaşı");
        ozellikEkle("Metrekare");
        ozellikEkle("Oda Sayısı");
        ozellikEkle("Bulunduğu Kat");
        ozellikEkle("Konum (İl/İlçe)");
        ozellikEkle("Isıtma Tipi");
        ozellikEkle("Balkon (Var/Yok)");
    } else if (kategori == "Vasıta") {
        ozellikEkle("Marka");
        ozellikEkle("Model");
        ozellikEkle("Yıl");
        ozellikEkle("Kilometre");
        ozellikEkle("Yakıt Tipi");
        ozellikEkle("Vites Tipi");
        ozellikEkle("Hasar Kaydı (TL)");
    } else if (kategori == "Elektronik") {
        ozellikEkle("Marka");
        ozellikEkle("Model");
        ozellikEkle("Renk");
        ozellikEkle("Durum (Sıfır/İkinci El)");
        ozellikEkle("Garanti (Var/Yok)");
        ozellikEkle("Fatura (Var/Yok)");
        ozellikEkle("Kutu (Var/Yok)");
    } else if (kategori == "Giyim") {
        ozellikEkle("Marka");
        ozellikEkle("Beden");
        ozellikEkle("Renk");
        ozellikEkle("Durum");
        ozellikEkle("Kumaş Tipi");
        ozellikEkle("Cinsiyet");
        ozellikEkle("Kullanım Türü");
    }
    ui->layoutOzellikler->addStretch();
}
