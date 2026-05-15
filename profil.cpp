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
// TÜM İLANLAR — herkes görür, sahiplik bilgisiyle
//   Qt::UserRole   = ilanNo
//   Qt::UserRole+1 = ilanSahibiId  (düzenle/sil kontrolü için)
// ──────────────────────────────────────────────────────────────
void Profil::profilIlanlariniYukle() {
    ui->listProfilIlanlar->clear();

    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    if (!db.isOpen()) db.open();

    QSqlQuery query(db);
    bool ok = query.exec(
        "SELECT i.ilanNo, i.baslik, i.fiyat, i.kullaniciId, k.kullaniciAdi "
        "FROM Ilan i "
        "LEFT JOIN Kullanici k ON i.kullaniciId = k.kullaniciId "
        "ORDER BY i.ilanNo DESC");

    if (!ok) {
        qDebug() << "İlan yükleme hatası:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        int     ilanNo       = query.value("ilanNo").toInt();
        QString baslik       = query.value("baslik").toString();
        QString fiyat        = query.value("fiyat").toString();
        int     ilanSahibiId = query.value("kullaniciId").toInt();
        QString ekleyen      = query.value("kullaniciAdi").toString();
        bool    benimIlanim  = (ilanSahibiId == aktifKullaniciId);

        QString metin = baslik + "  —  " + fiyat + " TL\n";
        if (benimIlanim) {
            metin += "✏  Sizin ilanınız";
        } else {
            metin += "👤 Ekleyen: " + (ekleyen.isEmpty() ? "Bilinmiyor" : ekleyen);
        }

        QListWidgetItem *item = new QListWidgetItem(metin);
        item->setData(Qt::UserRole,     ilanNo);
        item->setData(Qt::UserRole + 1, ilanSahibiId);

        // Renk: kendi ilanın yeşil, başkasının gri
        if (benimIlanim) {
            item->setForeground(QBrush(QColor("#1a7f37")));
        } else {
            item->setForeground(QBrush(QColor("#555555")));
        }

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
    query.prepare("SELECT baslik, fiyat, kategori, aciklama, fotografYolu "
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
    QString secilenFoto    = query.value("fotografYolu").toString();

    // ── Düzenleme Popup'ı ──
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("İlanı Düzenle");
    dialog->setMinimumWidth(440);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setStyleSheet(
        "QDialog { background-color: #f9fafb; }"
        "QLineEdit, QTextEdit, QComboBox {"
        "  background-color: white; color: #000000;"
        "  border: 1px solid #d1d5db; border-radius: 6px; padding: 6px; font-size: 10pt; }"
        "QLabel { color: #000000; font-weight: bold; font-size: 10pt; }");

    QVBoxLayout *anaLayout = new QVBoxLayout(dialog);
    anaLayout->setSpacing(12);
    anaLayout->setContentsMargins(20, 20, 20, 20);

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

    anaLayout->addWidget(new QLabel("Açıklama:"));
    QTextEdit *txtAciklama = new QTextEdit(mevcutAciklama);
    txtAciklama->setMinimumHeight(90);
    anaLayout->addWidget(txtAciklama);

    // Fotoğraf seç
    anaLayout->addWidget(new QLabel("Fotoğraf:"));
    QHBoxLayout *fotoLayout = new QHBoxLayout();
    QLabel *lblFotoYolu = new QLabel(secilenFoto.isEmpty() ? "(Fotoğraf seçilmedi)" : secilenFoto);
    lblFotoYolu->setStyleSheet("font-weight: normal; color: #555555; font-size: 9pt;");
    lblFotoYolu->setWordWrap(true);

    QPushButton *btnFotoSec = new QPushButton("📁 Fotoğraf Seç");
    btnFotoSec->setMinimumHeight(34);
    btnFotoSec->setStyleSheet(
        "QPushButton { background-color: #6366f1; color: white; font-weight: bold; border-radius: 6px; }"
        "QPushButton:hover { background-color: #4f46e5; }");
    fotoLayout->addWidget(lblFotoYolu, 1);
    fotoLayout->addWidget(btnFotoSec);
    anaLayout->addLayout(fotoLayout);

    connect(btnFotoSec, &QPushButton::clicked, dialog, [&secilenFoto, lblFotoYolu, dialog]() {
        QString dosya = QFileDialog::getOpenFileName(
            dialog, "Fotoğraf Seç", "",
            "Resim Dosyaları (*.png *.jpg *.jpeg *.bmp *.gif)");
        if (!dosya.isEmpty()) {
            secilenFoto = dosya;
            lblFotoYolu->setText(dosya);
        }
    });

    // Kaydet / İptal
    QHBoxLayout *butonLayout = new QHBoxLayout();
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
    anaLayout->addLayout(butonLayout);

    connect(btnIptal, &QPushButton::clicked, dialog, &QDialog::reject);

    connect(btnKaydet, &QPushButton::clicked, dialog, [=, &secilenFoto]() mutable {
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

        QSqlQuery guncelle(DatabaseManager::getInstance()->getDatabase());
        guncelle.prepare("UPDATE Ilan SET baslik = :b, fiyat = :f, kategori = :k, "
                         "aciklama = :a, fotografYolu = :foto WHERE ilanNo = :id");
        guncelle.bindValue(":b",    yeniBaslik);
        guncelle.bindValue(":f",    yeniFiyat);
        guncelle.bindValue(":k",    yeniKategori);
        guncelle.bindValue(":a",    yeniAciklama);
        guncelle.bindValue(":foto", secilenFoto);
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
    mesajGoster(this, QMessageBox::Information, "Bilgi",
                "Şifre değiştirme fonksiyonu yakında aktif edilecek.");
}

void Profil::on_btnGeri_clicked() {
    this->close();
}
