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

    this->setStyleSheet("background-color: white;");

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
        "WHERE ilanNo = ?"
        );

    query.addBindValue(m_ilanNo);

    if (query.exec() && query.next()) {

        QString baslik =
            query.value("baslik").toString();

        QString fiyat =
            query.value("fiyat").toString();

        QString kategori =
            query.value("kategori").toString();

        QString aciklama =
            query.value("aciklama").toString();

        QString stok =
            query.value("stokAdedi").toString();

        QString fotoYolu =
            query.value("fotografYolu").toString();

        ui->lblBaslik->setText(
            baslik.toUpper()
            );

        if (!fotoYolu.isEmpty()) {

            QPixmap pix(fotoYolu);

            if (!pix.isNull()) {

                ui->lblFoto->setPixmap(
                    pix.scaled(
                        ui->lblFoto->size(),
                        Qt::KeepAspectRatio,
                        Qt::SmoothTransformation
                        )
                    );

            } else {

                ui->lblFoto->setText(
                    "Resim Bulunamadi"
                    );
            }

        } else {

            ui->lblFoto->setText(
                "Fotograf Yok"
                );
        }

        QString detay =
            "<b>Ilan Basligi:</b> " + baslik +
            "<br><br><b>Fiyat:</b> " + fiyat + " TL" +
            "<br><br><b>Kategori:</b> " + kategori +
            "<br><br><b>Stok Adedi:</b> " + stok;

        ui->lblDetaylar->setText(detay);

        ui->txtAciklama->setText(aciklama);

        ui->txtAciklama->setReadOnly(true);

    } else {

        qDebug() << "Veri cekme hatasi:"
                 << query.lastError().text();

        QMessageBox::critical(
            this,
            "Hata",
            "Ilan bilgileri yuklenemedi!"
            );
    }
}

void IlanDetay::on_btnAnasayfa_clicked()
{
    this->close();
}

void IlanDetay::on_btnFavori_clicked()
{
    QMessageBox::information(
        this,
        "Basarili",
        "Ilan favorilere eklendi!"
        );
}
