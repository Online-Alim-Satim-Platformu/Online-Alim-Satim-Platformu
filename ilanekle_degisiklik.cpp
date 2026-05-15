// ============================================================
// Bu dosya SNIPPET'tir — ilanekle.cpp'nin TAMAMI DEĞİL.
// Aşağıdaki adımları kendi ilanekle.cpp dosyana uygula.
// ============================================================

// ── ADIM 1: En üste şu include'u ekle ──
#include "session.h"


// ── ADIM 2: Ilan tablosuna INSERT yapan sorguyu bul ──
// (genellikle btnKaydet veya btnIlanEkle'nin clicked sinyalinde)
// Mevcut INSERT sorgunda "kullaniciId" sütununu ekle.

// ÖNCE (örnek):
query.prepare("INSERT INTO Ilan (baslik, fiyat, kategori, aciklama, fotografYolu, stokAdedi) "
              "VALUES (:baslik, :fiyat, :kategori, :aciklama, :foto, :stok)");

// SONRA — kullaniciId eklendi:
query.prepare("INSERT INTO Ilan (baslik, fiyat, kategori, aciklama, fotografYolu, stokAdedi, kullaniciId) "
              "VALUES (:baslik, :fiyat, :kategori, :aciklama, :foto, :stok, :kulId)");

// ── ADIM 3: bindValue satırlarının arasına bunu ekle ──
query.bindValue(":kulId", aktifKullaniciId);


// ── ADIM 4 (isteğe bağlı): Ilan tablosunda kullaniciId sütunu yoksa ──
// SQLite için veritabanını açan yerde bir kez çalıştır:
QSqlQuery alter(db);
alter.exec("ALTER TABLE Ilan ADD COLUMN kullaniciId INTEGER DEFAULT 0");
// Not: Bu satır sütun zaten varsa hata verir ama sessizce geçer, sorun olmaz.
