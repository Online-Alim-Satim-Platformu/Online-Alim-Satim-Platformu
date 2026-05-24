#include "profil.h"
#include "ui_profil.h"
#include "databasemanager.h"
#include "session.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QFileDialog>
#include <QFileInfo>
#include <QSpinBox>
#include <QScrollArea>
#include <QSizePolicy>
#include <QBrush>
#include <QColor>

// ── Stillendirilmiş MessageBox yardımcı fonksiyonu ──
static void mesajGoster(QWidget *parent, QMessageBox::Icon ikon,
                        const QString &baslik, const QString &metin)
{
    const QString stil =
        "QMessageBox { background-color: #ffffff; }"
        "QLabel { color: #000000; font-size: 11pt; font-weight: bold; }"
        "QPushButton { color: #000000; background-color: #e1e1e1; "
        "border: 1px solid #adadad; padding: 5px; min-width: 80px; border-radius: 4px; }";
    QMessageBox box(parent);
    box.setWindowTitle(baslik);
    box.setText(metin);
    box.setIcon(ikon);
    box.addButton("Tamam", QMessageBox::AcceptRole);
    box.setStyleSheet(stil);
    box.exec();
}

Profil::Profil(QWidget *parent) : QWidget(parent), ui(new Ui::Profil) {
    ui->setupUi(this);
    kullaniciBilgileriniYukle();
    profilIlanlariniYukle();
}

Profil::~Profil() {
    delete ui;
}

// ──────────────────────────────────────────────────────────────
// KULLANICI BİLGİLERİ — aktif oturuma göre
// ──────────────────────────────────────────────────────────────
void Profil::kullaniciBilgileriniYukle() {
    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    QSqlQuery query(db);

    query.prepare("SELECT kullaniciAdi, email FROM Kullanici WHERE kullaniciId = :id");
    query.bindValue(":id", aktifKullaniciId);

    if (query.exec() && query.next()) {
        ui->lblAdSoyad->setText(query.value("kullaniciAdi").toString());
        ui->lblEmail->setText(query.value("email").toString());
    } else {
        ui->lblAdSoyad->setText("—");
        ui->lblEmail->setText("—");
        qDebug() << "Kullanıcı bilgisi hatası:" << query.lastError().text();
    }
}

// ──────────────────────────────────────────────────────────────
// AKTİF KULLANICININ İLANLARI
//   Qt::UserRole   = ilanNo
//   Qt::UserRole+1 = ilanSahibiId  (düzenle/sil kontrolü için)
// ──────────────────────────────────────────────────────────────
void Profil::profilIlanlariniYukle() {
    ui->listProfilIlanlar->clear();

    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    if (!db.isOpen()) db.open();

    QSqlQuery query(db);
    query.prepare(
        "SELECT ilanNo, baslik, fiyat, kategori "
        "FROM Ilan "
        "WHERE kullaniciId = :uid "
        "ORDER BY ilanNo DESC");
    query.bindValue(":uid", aktifKullaniciId);

    if (!query.exec()) {
        qDebug() << "İlan yükleme hatası:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        int     ilanNo   = query.value("ilanNo").toInt();
        QString baslik   = query.value("baslik").toString();
        QString fiyat    = query.value("fiyat").toString();
        QString kategori = query.value("kategori").toString();

        QString metin = baslik + "  —  " + fiyat + " TL\n✏  Kategori: " + kategori;

        QListWidgetItem *item = new QListWidgetItem(metin);
        item->setData(Qt::UserRole,     ilanNo);
        item->setData(Qt::UserRole + 1, aktifKullaniciId);
        item->setForeground(QBrush(QColor("#1a7f37")));

        ui->listProfilIlanlar->addItem(item);
    }
}

// ──────────────────────────────────────────────────────────────
// İLAN DÜZENLE — önce sahiplik kontrolü
// ──────────────────────────────────────────────────────────────
void Profil::on_btnIlanDuzenle_clicked()
{
    QListWidgetItem *secili = ui->listProfilIlanlar->currentItem();
    if (!secili) {
        mesajGoster(this, QMessageBox::Warning, "Uyarı",
                    "Lütfen önce düzenlemek istediğiniz ilanı seçin!");
        return;
    }

    // Sahiplik kontrolü
    int ilanSahibiId = secili->data(Qt::UserRole + 1).toInt();
    if (ilanSahibiId != aktifKullaniciId) {
        mesajGoster(this, QMessageBox::Warning, "Yetki Hatası",
                    "Bu ilan size ait değil!\n"
                    "Yalnızca kendi eklediğiniz ilanları düzenleyebilirsiniz.");
        return;
    }

    int ilanNo = secili->data(Qt::UserRole).toInt();

    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT baslik, fiyat, kategori, aciklama, stokAdedi, "
                  "foto1, foto2, foto3, foto4, foto5, ozellikler "
                  "FROM Ilan WHERE ilanNo = :id");
    query.bindValue(":id", ilanNo);

    if (!query.exec() || !query.next()) {
        mesajGoster(this, QMessageBox::Critical, "Hata", "İlan bilgileri yüklenemedi.");
        return;
    }

    QString mevcutBaslik   = query.value("baslik").toString();
    QString mevcutFiyat    = query.value("fiyat").toString();
    QString mevcutKategori = query.value("kategori").toString();
    QString mevcutAciklama = query.value("aciklama").toString();
    int     mevcutStok     = query.value("stokAdedi").toInt();
    QString mevcutOzellikler = query.value("ozellikler").toString();
    QString secilenFotolar[5];
    const QString fotoKolonlar[5] = {"foto1","foto2","foto3","foto4","foto5"};
    for (int i = 0; i < 5; i++)
        secilenFotolar[i] = query.value(fotoKolonlar[i]).toString();

    QMap<QString, QString> ozellikHaritasi;
    if (!mevcutOzellikler.isEmpty()) {
        QStringList parcalar = mevcutOzellikler.split(" | ");
        for (const QString &parca : parcalar) {
            int ikiNoktaIdx = parca.indexOf(":");
            if (ikiNoktaIdx != -1) {
                QString key = parca.left(ikiNoktaIdx).trimmed();
                QString val = parca.mid(ikiNoktaIdx + 1).trimmed();
                ozellikHaritasi[key] = val;
            }
        }
    }

    // ── Düzenleme Popup'ı ──
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("İlanı Düzenle");
    dialog->setMinimumSize(480, 580);
    dialog->resize(500, 660);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setStyleSheet(
        "QDialog { background-color: #f9fafb; }"
        "QLineEdit, QTextEdit, QComboBox {"
        "  background-color: white; color: #000000;"
        "  border: 1px solid #d1d5db; border-radius: 6px; padding: 6px; font-size: 10pt; }"
        "QLabel { color: #000000; font-weight: bold; font-size: 10pt; }");

    // Dialog layout holding the scroll area and the pinned bottom action bar
    QVBoxLayout *dialogLayout = new QVBoxLayout(dialog);
    dialogLayout->setContentsMargins(0, 0, 0, 0);
    dialogLayout->setSpacing(0);

    QScrollArea *mainScroll = new QScrollArea(dialog);
    mainScroll->setWidgetResizable(true);
    mainScroll->setStyleSheet("QScrollArea { border: none; background-color: #f9fafb; }");

    QWidget *scrollContent = new QWidget();
    scrollContent->setStyleSheet("background-color: #f9fafb;");
    QVBoxLayout *anaLayout = new QVBoxLayout(scrollContent);
    anaLayout->setSpacing(12);
    anaLayout->setContentsMargins(20, 20, 20, 10);
    mainScroll->setWidget(scrollContent);
    dialogLayout->addWidget(mainScroll, 1);

    // Fixed bottom bar for Save / Cancel buttons
    QWidget *bottomBar = new QWidget(dialog);
    bottomBar->setStyleSheet("background-color: #f9fafb; border-top: 1px solid #e5e7eb;");
    QHBoxLayout *butonLayout = new QHBoxLayout(bottomBar);
    butonLayout->setSpacing(12);
    butonLayout->setContentsMargins(20, 12, 20, 15);
    dialogLayout->addWidget(bottomBar);

    anaLayout->addWidget(new QLabel("Başlık:"));
    QLineEdit *txtBaslik = new QLineEdit(mevcutBaslik);
    anaLayout->addWidget(txtBaslik);

    anaLayout->addWidget(new QLabel("Fiyat (TL):"));
    QLineEdit *txtFiyat = new QLineEdit(mevcutFiyat);
    txtFiyat->setPlaceholderText("Örn: 1500");
    anaLayout->addWidget(txtFiyat);

    anaLayout->addWidget(new QLabel("Kategori:"));
    QComboBox *cmbKategori = new QComboBox();
    cmbKategori->addItems({"Emlak", "Vasıta", "Elektronik", "Giyim"});
    int idx = cmbKategori->findText(mevcutKategori);
    if (idx >= 0) cmbKategori->setCurrentIndex(idx);
    cmbKategori->setStyleSheet(
        "QComboBox { background-color: white; color: #000000; "
        "border: 1px solid #d1d5db; border-radius: 6px; padding: 6px; }"
        "QComboBox QAbstractItemView { background-color: white; color: #000000; }");
    anaLayout->addWidget(cmbKategori);

    // Özellikler için dinamik layout
    QVBoxLayout *ozellikLayout = new QVBoxLayout();
    anaLayout->addLayout(ozellikLayout);

    QMap<QString, QLineEdit*> ozellikEditleri;

    auto temizleOzellikler = [ozellikLayout, &ozellikEditleri]() {
        QLayoutItem *child;
        while ((child = ozellikLayout->takeAt(0)) != nullptr) {
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
        ozellikEditleri.clear();
    };

    auto guncelleOzellikler = [=, &ozellikEditleri, &ozellikHaritasi](const QString &kategori) {
        temizleOzellikler();

        QStringList ozellikler;
        if (kategori == "Emlak") {
            ozellikler << "Bina Yaşı" << "Metrekare" << "Oda Sayısı" << "Bulunduğu Kat" << "Konum (İl/İlçe)" << "Isıtma Tipi" << "Balkon (Var/Yok)";
        } else if (kategori == "Vasıta") {
            ozellikler << "Marka" << "Model" << "Yıl" << "Kilometre" << "Yakıt Tipi" << "Vites Tipi" << "Hasar Kaydı (TL)";
        } else if (kategori == "Elektronik") {
            ozellikler << "Marka" << "Model" << "Renk" << "Durum (Sıfır/İkinci El)" << "Garanti (Var/Yok)" << "Fatura (Var/Yok)" << "Kutu (Var/Yok)";
        } else if (kategori == "Giyim") {
            ozellikler << "Marka" << "Beden" << "Renk" << "Durum" << "Kumaş Tipi" << "Cinsiyet" << "Kullanım Türü";
        }

        if (!ozellikler.isEmpty()) {
            QLabel *lblOzelBaslik = new QLabel("<b>" + kategori + " Özellikleri:</b>");
            lblOzelBaslik->setStyleSheet("color: #0078D7; font-size: 10pt; margin-top: 5px;");
            ozellikLayout->addWidget(lblOzelBaslik);

            for (const QString &oz : ozellikler) {
                QHBoxLayout *hLayout = new QHBoxLayout();
                QLabel *lbl = new QLabel(oz + ":");
                lbl->setStyleSheet("font-weight: normal; font-size: 9pt;");
                
                QString deger = (kategori == mevcutKategori) ? ozellikHaritasi.value(oz) : "";
                QLineEdit *txt = new QLineEdit(deger);
                txt->setStyleSheet("QLineEdit { background-color: white; color: #000000; border: 1px solid #d1d5db; border-radius: 6px; padding: 6px; }");

                hLayout->addWidget(lbl);
                hLayout->addWidget(txt);
                ozellikLayout->addLayout(hLayout);

                ozellikEditleri[oz] = txt;
            }
        }
    };

    // İlk kategoriye göre alanları yükle
    guncelleOzellikler(cmbKategori->currentText());

    // Kategori değiştikçe alanları güncelle
    connect(cmbKategori, &QComboBox::currentTextChanged, dialog, [=, &ozellikEditleri, &ozellikHaritasi](const QString &kat) {
        guncelleOzellikler(kat);
    });

    anaLayout->addWidget(new QLabel("Açıklama:"));
    QTextEdit *txtAciklama = new QTextEdit(mevcutAciklama);
    txtAciklama->setMinimumHeight(90);
    anaLayout->addWidget(txtAciklama);

    anaLayout->addWidget(new QLabel("Stok Adedi:"));
    QHBoxLayout *stokLayout = new QHBoxLayout();
    QPushButton *btnStokAzalt = new QPushButton("-");
    btnStokAzalt->setFixedSize(36, 36);
    btnStokAzalt->setStyleSheet(
        "QPushButton { background-color: #ef4444; color: white; font-size: 16px; font-weight: bold; border-radius: 6px; }"
        "QPushButton:hover { background-color: #dc2626; }");
    QSpinBox *spinStok = new QSpinBox();
    spinStok->setRange(0, 9999);
    spinStok->setValue(mevcutStok);
    spinStok->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spinStok->setAlignment(Qt::AlignCenter);
    spinStok->setStyleSheet(
        "QSpinBox { background-color: white; color: #000000; border: 1px solid #d1d5db; "
        "border-radius: 6px; padding: 4px; font-size: 13px; font-weight: bold; }");
    QPushButton *btnStokArttir = new QPushButton("+");
    btnStokArttir->setFixedSize(36, 36);
    btnStokArttir->setStyleSheet(
        "QPushButton { background-color: #22c55e; color: white; font-size: 16px; font-weight: bold; border-radius: 6px; }"
        "QPushButton:hover { background-color: #16a34a; }");
    connect(btnStokAzalt, &QPushButton::clicked, dialog, [spinStok]() {
        if (spinStok->value() > 0) spinStok->setValue(spinStok->value() - 1);
    });
    connect(btnStokArttir, &QPushButton::clicked, dialog, [spinStok]() {
        spinStok->setValue(spinStok->value() + 1);
    });
    stokLayout->addWidget(btnStokAzalt);
    stokLayout->addWidget(spinStok, 1);
    stokLayout->addWidget(btnStokArttir);
    anaLayout->addLayout(stokLayout);

    // 5 fotoğraf satırı
    anaLayout->addWidget(new QLabel("Fotoğraflar:"));
    QLabel  *lblFotolar[5];
    for (int i = 0; i < 5; i++) {
        QHBoxLayout *satir = new QHBoxLayout();
        QString dosyaAdi = secilenFotolar[i].isEmpty()
                           ? "(seçilmedi)"
                           : QFileInfo(secilenFotolar[i]).fileName();
        lblFotolar[i] = new QLabel("Foto " + QString::number(i+1) + ": " + dosyaAdi);
        lblFotolar[i]->setStyleSheet("font-weight: normal; color: #555555; font-size: 9pt;");
        lblFotolar[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

        QPushButton *btnDegistir = new QPushButton("Degistir");
        btnDegistir->setFixedWidth(70);
        btnDegistir->setStyleSheet(
            "QPushButton { background-color: #6366f1; color: white; border-radius: 4px; }"
            "QPushButton:hover { background-color: #4f46e5; }");
        satir->addWidget(lblFotolar[i], 1);
        satir->addWidget(btnDegistir);
        anaLayout->addLayout(satir);

        connect(btnDegistir, &QPushButton::clicked, dialog, [=, &secilenFotolar]() mutable {
            QString dosya = QFileDialog::getOpenFileName(
                dialog, "Fotoğraf Seç", "",
                "Resim Dosyaları (*.png *.jpg *.jpeg *.bmp)");
            if (!dosya.isEmpty()) {
                secilenFotolar[i] = dosya;
                lblFotolar[i]->setText("Foto " + QString::number(i+1) + ": " + QFileInfo(dosya).fileName());
                lblFotolar[i]->setStyleSheet("font-weight: normal; color: #1a7f37; font-size: 9pt;");
            }
        });
    }

    // Kaydet / İptal
    QPushButton *btnKaydet = new QPushButton("💾 Kaydet");
    QPushButton *btnIptal  = new QPushButton("✖ İptal");
    btnKaydet->setMinimumHeight(38);
    btnIptal->setMinimumHeight(38);
    btnKaydet->setStyleSheet(
        "QPushButton { background-color: #0078D7; color: white; font-weight: bold; border-radius: 7px; }"
        "QPushButton:hover { background-color: #005a9e; }");
    btnIptal->setStyleSheet(
        "QPushButton { background-color: #9ca3af; color: white; font-weight: bold; border-radius: 7px; }"
        "QPushButton:hover { background-color: #6b7280; }");
    butonLayout->addWidget(btnKaydet);
    butonLayout->addWidget(btnIptal);

    connect(btnIptal, &QPushButton::clicked, dialog, &QDialog::reject);

    connect(btnKaydet, &QPushButton::clicked, dialog, [=, &secilenFotolar, &ozellikEditleri]() mutable {
        QString yeniBaslik   = txtBaslik->text().trimmed();
        QString yeniFiyatStr = txtFiyat->text().trimmed();
        QString yeniKategori = cmbKategori->currentText();
        QString yeniAciklama = txtAciklama->toPlainText().trimmed();

        if (yeniBaslik.isEmpty()) {
            mesajGoster(dialog, QMessageBox::Warning, "Hata", "Başlık boş bırakılamaz!");
            return;
        }
        bool ok2;
        double yeniFiyat = yeniFiyatStr.toDouble(&ok2);
        if (!ok2 || yeniFiyat <= 0) {
            mesajGoster(dialog, QMessageBox::Warning, "Hata", "Geçerli bir fiyat giriniz!");
            return;
        }

        // Değiştirilen özellikleri metin formatına dönüştür
        QStringList ozellikList;
        for (auto it = ozellikEditleri.begin(); it != ozellikEditleri.end(); ++it) {
            if (!it.value()->text().isEmpty()) {
                ozellikList << it.key() + ": " + it.value()->text();
            }
        }
        QString yeniOzelliklerStr = ozellikList.join(" | ");

        QSqlQuery guncelle(DatabaseManager::getInstance()->getDatabase());
        guncelle.prepare("UPDATE Ilan SET baslik = :b, fiyat = :f, kategori = :k, "
                         "aciklama = :a, stokAdedi = :stok, "
                         "foto1 = :f1, foto2 = :f2, foto3 = :f3, foto4 = :f4, foto5 = :f5, "
                         "ozellikler = :ozel "
                         "WHERE ilanNo = :id");
        guncelle.bindValue(":b",    yeniBaslik);
        guncelle.bindValue(":f",    yeniFiyat);
        guncelle.bindValue(":k",    yeniKategori);
        guncelle.bindValue(":a",    yeniAciklama);
        guncelle.bindValue(":stok", spinStok->value());
        guncelle.bindValue(":f1",   secilenFotolar[0]);
        guncelle.bindValue(":f2",   secilenFotolar[1]);
        guncelle.bindValue(":f3",   secilenFotolar[2]);
        guncelle.bindValue(":f4",   secilenFotolar[3]);
        guncelle.bindValue(":f5",   secilenFotolar[4]);
        guncelle.bindValue(":ozel", yeniOzelliklerStr);
        guncelle.bindValue(":id",   ilanNo);

        if (guncelle.exec()) {
            mesajGoster(dialog, QMessageBox::Information, "Başarılı", "İlan başarıyla güncellendi!");
            dialog->accept();
        } else {
            mesajGoster(dialog, QMessageBox::Critical, "Hata",
                        "Güncelleme başarısız!\n" + guncelle.lastError().text());
        }
    });

    connect(dialog, &QDialog::accepted, this, &Profil::profilIlanlariniYukle);
    dialog->exec();
}

// ──────────────────────────────────────────────────────────────
// İLAN SİL — sahiplik kontrolü
// ──────────────────────────────────────────────────────────────
void Profil::on_btnIlanSil_clicked() {
    QListWidgetItem *seciliItem = ui->listProfilIlanlar->currentItem();
    if (!seciliItem) {
        mesajGoster(this, QMessageBox::Warning, "Uyarı", "Lütfen önce silinecek ilanı seçin!");
        return;
    }

    // Sahiplik kontrolü
    int ilanSahibiId = seciliItem->data(Qt::UserRole + 1).toInt();
    if (ilanSahibiId != aktifKullaniciId) {
        mesajGoster(this, QMessageBox::Warning, "Yetki Hatası",
                    "Bu ilan size ait değil!\n"
                    "Yalnızca kendi eklediğiniz ilanları silebilirsiniz.");
        return;
    }

    const QString stil =
        "QMessageBox { background-color: #ffffff; }"
        "QLabel { color: #000000; font-size: 11pt; font-weight: bold; }"
        "QPushButton { color: #000000; background-color: #e1e1e1; border: 1px solid #adadad; "
        "padding: 5px; min-width: 80px; border-radius: 4px; }";

    QMessageBox onay(this);
    onay.setWindowTitle("Onay");
    onay.setText("Bu ilanı silmek istediğinize emin misiniz?");
    onay.setIcon(QMessageBox::Question);
    QPushButton *evetButonu = onay.addButton("Evet",  QMessageBox::YesRole);
    onay.addButton("Hayır", QMessageBox::NoRole);
    onay.setStyleSheet(stil);
    onay.exec();

    if (onay.clickedButton() == evetButonu) {
        int id = seciliItem->data(Qt::UserRole).toInt();
        QSqlQuery query(DatabaseManager::getInstance()->getDatabase());
        query.prepare("DELETE FROM Ilan WHERE ilanNo = :id");
        query.bindValue(":id", id);

        if (query.exec()) {
            mesajGoster(this, QMessageBox::Information, "Başarılı", "İlan başarıyla silindi.");
            profilIlanlariniYukle();
        } else {
            mesajGoster(this, QMessageBox::Critical, "Hata",
                        "Silme işlemi başarısız!\n" + query.lastError().text());
            qDebug() << "Silme hatası:" << query.lastError().text();
        }
    }
}

// ──────────────────────────────────────────────────────────────
// ŞİFRE DEĞİŞTİR
// ──────────────────────────────────────────────────────────────
void Profil::on_btnSifreDegistir_clicked() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Şifre Değiştir");
    dialog->setMinimumWidth(380);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setStyleSheet(
        "QDialog { background-color: #f9fafb; }"
        "QLineEdit {"
        "  background-color: white; color: #000000;"
        "  border: 1px solid #d1d5db; border-radius: 6px; padding: 6px; font-size: 10pt; }"
        "QLabel { color: #000000; font-weight: bold; font-size: 10pt; }");

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->setSpacing(12);
    layout->setContentsMargins(20, 20, 20, 20);

    layout->addWidget(new QLabel("Mevcut Şifre:"));
    QLineEdit *txtMevcut = new QLineEdit();
    txtMevcut->setEchoMode(QLineEdit::Password);
    layout->addWidget(txtMevcut);

    layout->addWidget(new QLabel("Yeni Şifre:"));
    QLineEdit *txtYeni = new QLineEdit();
    txtYeni->setEchoMode(QLineEdit::Password);
    layout->addWidget(txtYeni);

    layout->addWidget(new QLabel("Yeni Şifre (Tekrar):"));
    QLineEdit *txtYeniTekrar = new QLineEdit();
    txtYeniTekrar->setEchoMode(QLineEdit::Password);
    layout->addWidget(txtYeniTekrar);

    QHBoxLayout *butonLayout = new QHBoxLayout();
    QPushButton *btnKaydet = new QPushButton("Kaydet");
    QPushButton *btnIptal  = new QPushButton("Iptal");
    btnKaydet->setMinimumHeight(38);
    btnIptal->setMinimumHeight(38);
    btnKaydet->setStyleSheet(
        "QPushButton { background-color: #0078D7; color: white; font-weight: bold; border-radius: 7px; }"
        "QPushButton:hover { background-color: #005a9e; }");
    btnIptal->setStyleSheet(
        "QPushButton { background-color: #9ca3af; color: white; font-weight: bold; border-radius: 7px; }"
        "QPushButton:hover { background-color: #6b7280; }");
    butonLayout->addWidget(btnKaydet);
    butonLayout->addWidget(btnIptal);
    layout->addLayout(butonLayout);

    connect(btnIptal, &QPushButton::clicked, dialog, &QDialog::reject);

    connect(btnKaydet, &QPushButton::clicked, dialog, [=]() {
        QString mevcut     = txtMevcut->text();
        QString yeni       = txtYeni->text();
        QString yeniTekrar = txtYeniTekrar->text();

        if (mevcut.isEmpty() || yeni.isEmpty() || yeniTekrar.isEmpty()) {
            mesajGoster(dialog, QMessageBox::Warning, "Uyarı", "Tüm alanları doldurunuz!");
            return;
        }
        if (yeni != yeniTekrar) {
            mesajGoster(dialog, QMessageBox::Warning, "Uyarı", "Yeni şifreler eşleşmiyor!");
            return;
        }
        if (yeni.length() < 6) {
            mesajGoster(dialog, QMessageBox::Warning, "Uyarı", "Yeni şifre en az 6 karakter olmalıdır!");
            return;
        }

        QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();

        QSqlQuery kontrol(db);
        kontrol.prepare("SELECT 1 FROM Kullanici WHERE kullaniciId = :id AND sifre = :sifre");
        kontrol.bindValue(":id",    aktifKullaniciId);
        kontrol.bindValue(":sifre", mevcut);

        if (!kontrol.exec() || !kontrol.next()) {
            mesajGoster(dialog, QMessageBox::Warning, "Hata", "Mevcut şifre yanlış!");
            return;
        }

        QSqlQuery guncelle(db);
        guncelle.prepare("UPDATE Kullanici SET sifre = :yeni WHERE kullaniciId = :id");
        guncelle.bindValue(":yeni", yeni);
        guncelle.bindValue(":id",   aktifKullaniciId);

        if (guncelle.exec()) {
            mesajGoster(dialog, QMessageBox::Information, "Başarılı", "Şifreniz başarıyla değiştirildi!");
            dialog->accept();
        } else {
            mesajGoster(dialog, QMessageBox::Critical, "Hata",
                        "Şifre güncellenemedi!\n" + guncelle.lastError().text());
        }
    });

    dialog->exec();
}

void Profil::favoriIlanlariniYukle() {
    ui->listFavoriler->clear();

    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    if (!db.isOpen()) db.open();

    QSqlQuery query(db);
    query.prepare(
        "SELECT i.ilanNo, i.baslik, i.fiyat, i.kategori "
        "FROM Favoriler f "
        "JOIN Ilan i ON f.ilanNo = i.ilanNo "
        "WHERE f.kullaniciId = :uid "
        "ORDER BY i.ilanNo DESC");
    query.bindValue(":uid", aktifKullaniciId);

    if (!query.exec()) {
        qDebug() << "Favori yükleme hatası:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        int     ilanNo   = query.value("ilanNo").toInt();
        QString baslik   = query.value("baslik").toString();
        QString fiyat    = query.value("fiyat").toString();
        QString kategori = query.value("kategori").toString();

        QString metin = baslik + "  —  " + fiyat + " TL\n★  Kategori: " + kategori;

        QListWidgetItem *item = new QListWidgetItem(metin);
        item->setData(Qt::UserRole, ilanNo);
        item->setForeground(QBrush(QColor("#d97706")));
        ui->listFavoriler->addItem(item);
    }
}

void Profil::on_btnFavorilerim_clicked() {
    bool favGoster = !ui->listFavoriler->isVisible();

    ui->listFavoriler->setVisible(favGoster);
    ui->listProfilIlanlar->setVisible(!favGoster);
    ui->btnIlanDuzenle->setVisible(!favGoster);
    ui->btnIlanSil->setVisible(!favGoster);
    ui->btnFavoridenCikar->setVisible(favGoster);
    ui->lblIlanBaslik->setText(favGoster ? "Favorilerim" : "İlanlarım");
    ui->btnFavorilerim->setText(favGoster ? "← İlanlarıma Dön" : "★ Favorilerim");

    if (favGoster)
        favoriIlanlariniYukle();
}

void Profil::on_btnFavoridenCikar_clicked() {
    QListWidgetItem *secili = ui->listFavoriler->currentItem();
    if (!secili) {
        mesajGoster(this, QMessageBox::Warning, "Uyarı",
                    "Lütfen önce çıkarmak istediğiniz ilanı seçin!");
        return;
    }

    int ilanNo = secili->data(Qt::UserRole).toInt();

    QSqlQuery query(DatabaseManager::getInstance()->getDatabase());
    query.prepare("DELETE FROM Favoriler WHERE kullaniciId = :uid AND ilanNo = :ilan");
    query.bindValue(":uid",  aktifKullaniciId);
    query.bindValue(":ilan", ilanNo);

    if (query.exec()) {
        mesajGoster(this, QMessageBox::Information, "Başarılı", "İlan favorilerden çıkarıldı.");
        favoriIlanlariniYukle();
    } else {
        mesajGoster(this, QMessageBox::Critical, "Hata",
                    "İşlem başarısız!\n" + query.lastError().text());
    }
}

void Profil::on_btnGeri_clicked() {
    this->close();
}
