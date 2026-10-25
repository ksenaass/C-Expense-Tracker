# Kişisel Harcama Takipçisi
C'de dosyalama mantığını pratik etmek için yazılan basit ama kullanışlı bir harcama takip programı. Uygulama arka planda terminalde çalışıyor ama sonuçları ve uyarıları direkt Windows pop-up'ları (MessageBox) ile ekrana veriyor.

Girdiğiniz her harcamayı bir CSV dosyasına kaydediyor, böylece programı kapatsanız bile verileriniz kaybolmuyor. Üstelik harcamaları kategorilerine (Eğitim, Teknoloji, Abonelikler vb.) ayırarak toplam ne kadar harcadığınızı da tek tuşla özetleyebiliyor.

## Neler Yaptım?
* **Kalıcı Kayıt:** Harcamalar anında `harcamalar.csv` dosyasına yazılıyor (isterseniz Excel ile de açıp bakabilirsiniz).
* **Otomatik Tarih:** `time.h` kütüphanesini ekledim, bu sayede tarihi elle girmeye gerek kalmıyor; bilgisayarın saatinden o anı kendi çekiyor.
* **Bütçe Analizi:** Verileri sadece alt alta listelemek yerine, kategorileri gruplayıp (Örn: Eğitime şu kadar, Teknolojiye bu kadar) genel bir rapor sunan bir analiz fonksiyonu bulunuyor.
* **Görsel Arayüz Ufaklıkları:** Tamamen siyah ekrana bakmamak için `windows.h` kullandım, uyarılar ve raporlar ekrana açılır pencere olarak geliyor.

## Nasıl Çalıştırabilirsiniz?

Projeyi bilgisayarınıza indirdikten sonra, terminalde kodun bulunduğu klasöre gidip şu komutla derleyebilirsiniz:

gcc harcama.c -o harcama
