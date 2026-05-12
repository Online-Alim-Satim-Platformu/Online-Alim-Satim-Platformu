#include "ilandetay.h"
#include "ui_ilandetay.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>

IlanDetay::IlanDetay(int ilanNo, QWidget *parent) :
    QWidget(parent), ui(new Ui::IlanDetay), m_ilanNo(ilanNo)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: white;");

    // Açılışta verileri yükle
    ilanBilgileriniYukle();
}

IlanDetay::~IlanDetay() {
    delete ui;
}

void IlanDetay::ilanBilgileriniYukle() {
    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    QSqlQuery query(db);

    // İlan ve Satıcı bilgilerini birleştirerek çekiyoruz
    query.prepare("SELECT i.baslik, i.fiyat, i.durum, i.aciklama, i.fotografYolu, "
                  "u.kullaniciAdi, u.email FROM Ilan i "
                  "JOIN KULLANICI u ON i.saticiID = u.kullaniciID "
                  "WHERE i.ilanNo = :id");
    query.bindValue(":id", m_ilanNo);

    if (query.exec() && query.next()) {
        // 1. BAŞLIK AYARI
        ui->lblBaslik->setText(query.value("baslik").toString().toUpper());

        // 2. FOTOĞRAF YÜKLEME
        QString fotoYolu = query.value("fotografYolu").toString();
        if (!fotoYolu.isEmpty()) {
            QPixmap pix(fotoYolu);
            if(!pix.isNull()) {
                ui->lblFoto->setPixmap(pix.scaled(ui->lblFoto->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            } else {
                ui->lblFoto->setText("Resim Bulunamadı");
            }
        }

        // 3. DETAYLAR (Sadece başlıklar siyah ve kalın)
        QString detayHtml = QString(
            "<p><b style='color:black;'>İLAN:</b> %1</p>"
            "<p><b style='color:black;'>FİYAT:</b> <span style='color:green;'>%2 TL</span></p>"
            "<p><b style='color:black;'>DURUM:</b> %3</p>"
        ).arg(query.value("baslik").toString()).arg(query.value("fiyat").toString()).arg(query.value("durum").toString());
        ui->lblDetaylar->setText(detayHtml);

        // 4. SATICI BİLGİLERİ (Sadece başlıklar siyah ve kalın)
        ui->lblSaticiBilgi->setText(QString("<b style='color:black;'>Satıcı:</b> %1<br><b style='color:black;'>E-Posta:</b> %2")
                                    .arg(query.value("kullaniciAdi").toString())
                                    .arg(query.value("email").toString()));

        // 5. AÇIKLAMA
        ui->txtAciklama->setText(query.value("aciklama").toString());
        ui->txtAciklama->setReadOnly(true);

    } else {
        qDebug() << "Veri çekme hatası:" << query.lastError().text();
    }
}

// BUTON FONKSİYONLARI
void IlanDetay::on_btnAnasayfa_clicked() {
    this->close(); // Pencereyi kapatır ve Anasayfaya döner
}

void IlanDetay::on_btnFavori_clicked() {
    // Favori ekleme işlemi veritabanına burada kaydedilebilir
    QMessageBox::information(this, "Başarılı", "İlan favorilerinize eklendi!");
}
