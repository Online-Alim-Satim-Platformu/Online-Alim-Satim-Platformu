#include "profil.h"
#include "ui_profil.h"
#include "databasemanager.h"
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

Profil::Profil(QWidget *parent) : QWidget(parent), ui(new Ui::Profil) {
    ui->setupUi(this);
    kullaniciBilgileriniYukle();
    profilIlanlariniYukle();
}

Profil::~Profil() {
    delete ui;
}

void Profil::kullaniciBilgileriniYukle() {
    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    QSqlQuery query(db);

    if (query.exec("SELECT kullaniciAdi, email FROM Kullanici LIMIT 1")) {
        if (query.next()) {
            ui->lblAdSoyad->setText(query.value("kullaniciAdi").toString());
            ui->lblEmail->setText(query.value("email").toString());
        } else {
            ui->lblAdSoyad->setText("Berat");
            ui->lblEmail->setText("berat@example.com");
        }
    } else {
        qDebug() << "Kullanıcı bilgisi hatası:" << query.lastError().text();
    }
}

void Profil::profilIlanlariniYukle() {
    ui->listProfilIlanlar->clear();

    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    if (!db.isOpen()) db.open();

    QSqlQuery query(db);
    if (query.exec("SELECT ilanNo, baslik, fiyat FROM Ilan")) {
        while (query.next()) {
            QListWidgetItem *item = new QListWidgetItem();
            item->setText(query.value("baslik").toString() + " - " +
                          query.value("fiyat").toString() + " TL");
            item->setData(Qt::UserRole, query.value("ilanNo").toInt());
            ui->listProfilIlanlar->addItem(item);
        }
    } else {
        qDebug() << "İlan yükleme hatası:" << query.lastError().text();
    }
}

// ──────────────────────────────────────────────────────────────
// İLAN DÜZENLE — seçili ilanın bilgilerini dolu gelen popup
// ──────────────────────────────────────────────────────────────
void Profil::on_btnIlanDuzenle_clicked() {
    QListWidgetItem *secili = ui->listProfilIlanlar->currentItem();
    if (!secili) {
        QMessageBox::warning(this, "Uyarı", "Lütfen önce düzenlemek istediğiniz ilanı seçin!");
        return;
    }

    int ilanNo = secili->data(Qt::UserRole).toInt();

    // Mevcut ilan bilgilerini veritabanından çek
    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT baslik, fiyat, kategori, aciklama FROM Ilan WHERE ilanNo = :id");
    query.bindValue(":id", ilanNo);

    if (!query.exec() || !query.next()) {
        QMessageBox::critical(this, "Hata", "İlan bilgileri yüklenemedi.");
        return;
    }

    QString mevcutBaslik   = query.value("baslik").toString();
    QString mevcutFiyat    = query.value("fiyat").toString();
    QString mevcutKategori = query.value("kategori").toString();
    QString mevcutAciklama = query.value("aciklama").toString();

    // ── Düzenleme Popup'ı ──
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("İlanı Düzenle");
    dialog->setMinimumWidth(420);
    dialog->setStyleSheet("background-color: #f9fafb; color: #000000;");
    dialog->setAttribute(Qt::WA_DeleteOnClose);

    QString inputStyle = "QLineEdit, QTextEdit, QComboBox {"
                         "  background-color: white;"
                         "  color: #000000;"
                         "  border: 1px solid #d1d5db;"
                         "  border-radius: 6px;"
                         "  padding: 6px;"
                         "  font-size: 10pt;"
                         "}"
                         "QLabel { color: #000000; font-weight: bold; }";
    dialog->setStyleSheet(dialog->styleSheet() + inputStyle);

    QVBoxLayout *anaLayout = new QVBoxLayout(dialog);
    anaLayout->setSpacing(12);
    anaLayout->setContentsMargins(20, 20, 20, 20);

    // Başlık
    QLabel *lblBaslik = new QLabel("Başlık:");
    QLineEdit *txtBaslik = new QLineEdit(mevcutBaslik);
    anaLayout->addWidget(lblBaslik);
    anaLayout->addWidget(txtBaslik);

    // Fiyat
    QLabel *lblFiyat = new QLabel("Fiyat (TL):");
    QLineEdit *txtFiyat = new QLineEdit(mevcutFiyat);
    txtFiyat->setPlaceholderText("Örn: 1500");
    anaLayout->addWidget(lblFiyat);
    anaLayout->addWidget(txtFiyat);

    // Kategori
    QLabel *lblKategori = new QLabel("Kategori:");
    QComboBox *cmbKategori = new QComboBox();
    cmbKategori->addItems({"Emlak", "Vasıta", "Elektronik", "Giyim"});
    // Mevcut kategoriyi seç
    int idx = cmbKategori->findText(mevcutKategori);
    if (idx >= 0) cmbKategori->setCurrentIndex(idx);
    cmbKategori->setStyleSheet("QComboBox { background-color: white; color: #000000; "
                               "border: 1px solid #d1d5db; border-radius: 6px; padding: 6px; }"
                               "QComboBox QAbstractItemView { background-color: white; color: #000000; }");
    anaLayout->addWidget(lblKategori);
    anaLayout->addWidget(cmbKategori);

    // Açıklama
    QLabel *lblAciklama = new QLabel("Açıklama:");
    QTextEdit *txtAciklama = new QTextEdit(mevcutAciklama);
    txtAciklama->setMinimumHeight(90);
    anaLayout->addWidget(lblAciklama);
    anaLayout->addWidget(txtAciklama);

    // Kaydet / İptal butonları
    QHBoxLayout *butonLayout = new QHBoxLayout();
    QPushButton *btnKaydet = new QPushButton("💾 Kaydet");
    QPushButton *btnIptal  = new QPushButton("✖ İptal");

    btnKaydet->setMinimumHeight(38);
    btnIptal->setMinimumHeight(38);

    btnKaydet->setStyleSheet("QPushButton { background-color: #0078D7; color: white; "
                             "font-weight: bold; border-radius: 7px; }"
                             "QPushButton:hover { background-color: #005a9e; }");
    btnIptal->setStyleSheet("QPushButton { background-color: #9ca3af; color: white; "
                            "font-weight: bold; border-radius: 7px; }"
                            "QPushButton:hover { background-color: #6b7280; }");

    butonLayout->addWidget(btnKaydet);
    butonLayout->addWidget(btnIptal);
    anaLayout->addLayout(butonLayout);

    connect(btnIptal, &QPushButton::clicked, dialog, &QDialog::reject);

    // ── Kaydet basıldığında veritabanını güncelle ──
    connect(btnKaydet, &QPushButton::clicked, dialog, [=]() {
        QString yeniBaslik   = txtBaslik->text().trimmed();
        QString yeniFiyatStr = txtFiyat->text().trimmed();
        QString yeniKategori = cmbKategori->currentText();
        QString yeniAciklama = txtAciklama->toPlainText().trimmed();

        // Boşluk kontrolü
        if (yeniBaslik.isEmpty()) {
            QMessageBox::warning(dialog, "Hata", "Başlık boş bırakılamaz!");
            return;
        }
        bool ok;
        double yeniFiyat = yeniFiyatStr.toDouble(&ok);
        if (!ok || yeniFiyat <= 0) {
            QMessageBox::warning(dialog, "Hata", "Geçerli bir fiyat giriniz!");
            return;
        }

        // Güncelleme sorgusu
        QSqlQuery guncelle(DatabaseManager::getInstance()->getDatabase());
        guncelle.prepare("UPDATE Ilan SET baslik = :b, fiyat = :f, kategori = :k, aciklama = :a "
                         "WHERE ilanNo = :id");
        guncelle.bindValue(":b",  yeniBaslik);
        guncelle.bindValue(":f",  yeniFiyat);
        guncelle.bindValue(":k",  yeniKategori);
        guncelle.bindValue(":a",  yeniAciklama);
        guncelle.bindValue(":id", ilanNo);

        if (guncelle.exec()) {
            QMessageBox::information(dialog, "Başarılı", "İlan başarıyla güncellendi!");
            dialog->accept();
        } else {
            QMessageBox::critical(dialog, "Hata", "Güncelleme başarısız!\n" + guncelle.lastError().text());
        }
    });

    // Dialog kapanınca listeyi yenile
    connect(dialog, &QDialog::accepted, this, &Profil::profilIlanlariniYukle);

    dialog->exec();
}

// ──────────────────────────────────────────────────────────────
// İLAN SİL
// ──────────────────────────────────────────────────────────────
void Profil::on_btnIlanSil_clicked() {
    QListWidgetItem *seciliItem = ui->listProfilIlanlar->currentItem();
    if (!seciliItem) {
        QMessageBox::warning(this, "Uyarı", "Lütfen önce silinecek ilanı seçin!");
        return;
    }

    QString stil = "QMessageBox { background-color: #ffffff; }"
                   "QLabel { color: #000000; font-size: 11pt; font-weight: bold; }"
                   "QPushButton { color: #000000; background-color: #e1e1e1; border: 1px solid #adadad; "
                   "padding: 5px; min-width: 80px; border-radius: 4px; }";

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Onay");
    msgBox.setText("Bu ilanı silmek istediğinize emin misiniz?");
    msgBox.setIcon(QMessageBox::Question);
    QPushButton *evetButonu  = msgBox.addButton("Evet",  QMessageBox::YesRole);
    msgBox.addButton("Hayır", QMessageBox::NoRole);
    msgBox.setStyleSheet(stil);
    msgBox.exec();

    if (msgBox.clickedButton() == evetButonu) {
        int id = seciliItem->data(Qt::UserRole).toInt();
        QSqlQuery query(DatabaseManager::getInstance()->getDatabase());
        query.prepare("DELETE FROM Ilan WHERE ilanNo = :id");
        query.bindValue(":id", id);

        if (query.exec()) {
            QMessageBox infoBox(this);
            infoBox.setWindowTitle("Başarılı");
            infoBox.setText("İlan başarıyla silindi.");
            infoBox.setIcon(QMessageBox::Information);
            infoBox.addButton("Tamam", QMessageBox::AcceptRole);
            infoBox.setStyleSheet(stil);
            infoBox.exec();
            profilIlanlariniYukle();
        } else {
            qDebug() << "Silme hatası:" << query.lastError().text();
        }
    }
}

void Profil::on_btnSifreDegistir_clicked() {
    QMessageBox::information(this, "Bilgi", "Şifre değiştirme fonksiyonu yakında aktif edilecek.");
}

void Profil::on_btnGeri_clicked() {
    this->close();
}
