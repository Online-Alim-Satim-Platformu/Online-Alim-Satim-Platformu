#include "ilandetay.h"
#include "ui_ilandetay.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>

IlanDetay::IlanDetay(int ilanNo, QWidget *parent)
    : QWidget(parent),
    ui(new Ui::IlanDetay),
    m_ilanNo(ilanNo)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:white;");

    ui->lblBaslik->setStyleSheet(
        "font-size: 22px;"
        "font-weight: bold;"
        "color: #222222;"
        "padding: 10px;"
        "border-bottom: 2px solid #cccccc;"
        );

    ui->lblAciklamaBaslik->setStyleSheet(
        "font-size: 14px;"
        "font-weight: bold;"
        "color: #333333;"
        "padding: 4px;"
        );

    ilanBilgileriniYukle();
}

IlanDetay::~IlanDetay()
{
    delete ui;
}

void IlanDetay::ilanBilgileriniYukle()
{
    QSqlDatabase db =
        DatabaseManager::getInstance()->getDatabase();
    QSqlQuery query(db);
    query.prepare(
        "SELECT baslik, fiyat, kategori, "
        "aciklama, stokAdedi, fotografYolu "
        "FROM Ilan "
        "WHERE ilanNo=?"
        );
    query.addBindValue(m_ilanNo);

    if(query.exec() && query.next())
    {
        QString baslik   = query.value("baslik").toString();
        QString fiyat    = query.value("fiyat").toString();
        QString kategori = query.value("kategori").toString();
        QString aciklama = query.value("aciklama").toString();
        QString stok     = query.value("stokAdedi").toString();
        QString foto     = query.value("fotografYolu").toString();

        // En üstte ilan adını yaz
        ui->lblBaslik->setText(baslik.toUpper());

        // Fotoğraf
        if(!foto.isEmpty())
        {
            QPixmap pix(foto);
            if(!pix.isNull())
            {
                ui->lblFoto->setPixmap(
                    pix.scaled(
                        ui->lblFoto->size(),
                        Qt::KeepAspectRatio,
                        Qt::SmoothTransformation
                        )
                    );
            }
            else
            {
                ui->lblFoto->setText("Resim bulunamadi");
            }
        }

        // Sağ üstteki detay bilgileri
        QString detay =
            "<b>Fiyat:</b> "         + fiyat    + " TL" +
            "<br><br><b>Kategori:</b> " + kategori +
            "<br><br><b>Stok:</b> "     + stok;

        ui->lblDetaylar->setText(detay);

        // "İlan Detayı" başlığını güncelle
        ui->lblAciklamaBaslik->setText("İlan Detayı");

        // Açıklama kutusuna yaz
        ui->txtAciklama->clear();
        if(aciklama.isEmpty())
            ui->txtAciklama->setPlaceholderText("Açıklama girilmemiş.");
        else
            ui->txtAciklama->setPlainText(aciklama);

        ui->txtAciklama->setReadOnly(true);

        qDebug() << "ACIKLAMA:" << aciklama;
        qDebug() << "FIYAT:"    << fiyat;
        qDebug() << "KATEGORI:" << kategori;
    }
    else
    {
        QMessageBox::critical(
            this,
            "Hata",
            query.lastError().text()
            );
        qDebug() << query.lastError().text();
    }
}

void IlanDetay::on_btnAnasayfa_clicked()
{
    close();
}

void IlanDetay::on_btnFavori_clicked()
{
    QMessageBox::information(
        this,
        "Basarili",
        "Favorilere eklendi"
        );
}
