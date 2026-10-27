# 💰 Kişisel Harcama Takipçisi

C programlama dili ile geliştirilmiş, harcamalarınızı kaydeden ve **Windows açılır pencereleri (Pop-up)** kullanarak raporlar sunan basit ve kullanışlı bir bütçe takip uygulamasıdır.

## 🌟 Özellikler

- **Yeni Harcama Ekleme:** Kategori, açıklama ve tutar girerek hızlıca harcama ekleyebilirsiniz. Tarih, bilgisayarınızdan otomatik olarak çekilir.
- **Açılır Pencere (Pop-up) ile Listeleme:** Kaydedilen tüm harcamalar, düzenli bir tablo halinde Windows mesaj penceresinde gösterilir.
- **Kategori Bazlı Analiz:** Hangi kategoriye (Market, Eğitim, Fatura vb.) toplam ne kadar harcadığınızı hesaplar ve genel toplam ile birlikte pop-up raporu olarak sunar.
- **Kalıcı Veri Saklama:** Verileriniz `harcamalar.csv` adlı Excel ile de uyumlu bir dosyada güvenle saklanır.

## ⚙️ Gereksinimler

- **İşletim Sistemi:** Windows (Program `windows.h` kütüphanesini kullandığı için Windows ortamında çalışır).
- **Derleyici:** Herhangi bir C derleyicisi (GCC, MinGW, Dev-C++ vb.).

## 🚀 Kurulum ve Çalıştırma

1. Proje dosyalarını bilgisayarınıza indirin veya `harcama_takip.c` adında bir dosya oluşturup kodu içine yapıştırın.
2. Terminal (Komut İstemcisi) açın ve dosyanın bulunduğu dizine gidin.
3. Kodu derlemek için şu komutu çalıştırın:
   ```bash
   gcc harcama_takip.c -o harcama_takip.exe
