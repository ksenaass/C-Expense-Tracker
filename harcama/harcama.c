#include <stdio.h>   // Temel giriş/çıkış işlemleri (printf, scanf) için
#include <stdlib.h>  // Dosya işlemleri için
#include <string.h>  // Metinleri birleştirmek ve parçalamak için
#include <windows.h> // Açılır pencere (pop-up) gösterebilmek için
#include <time.h>    // Otomatik tarih almak için

// Harcama bilgilerini bir arada tutacağımız şablon
typedef struct {
    char tarih[15];
    char kategori[30];
    char aciklama[50];
    float tutar;
} Harcama;

// Analiz yaparken kategorilerin toplamını tutacağımız şablon
typedef struct {
    char isim[30];
    float toplamTutar;
} Kategori;

// 1. İŞLEM: YENİ HARCAMA EKLEME
void harcamaEkle() {
    Harcama h; // 'h' adında bir harcama kutusu oluşturduk
    
    // Verileri kaydedeceğimiz dosyayı "ekleme" (a) modunda açıyoruz
    FILE *dosya = fopen("harcamalar.csv", "a");

    if (dosya == NULL) { // Dosya açılamazsa ekrana pop-up hata mesajı ver
        MessageBox(NULL, "Dosya acilamadi!", "Hata", MB_ICONERROR | MB_OK);
        return;
    }

    // O anki tarihi bilgisayardan otomatik alıp h.tarih içine yazıyoruz
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(h.tarih, "%02d-%02d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    // Siyah ekranda kullanıcıdan bilgileri istiyoruz
    printf("\nKategori (Orn: Egitim, Market): ");
    scanf("%s", h.kategori);
    
    printf("Aciklama (Bosluk yerine _ kullanin): ");
    scanf("%s", h.aciklama);
    
    printf("Tutar: ");
    if (scanf("%f", &h.tutar) != 1) { // Kullanıcı sayı yerine harf girerse uyar
        MessageBox(NULL, "Lutfen sadece sayi girin!", "Hata", MB_ICONERROR | MB_OK);
        while(getchar() != '\n'); // Hatalı girişi temizle
        fclose(dosya);
        return;
    }

    // Bilgileri aralarında virgül olacak şekilde dosyaya yaz ve dosyayı kapat
    fprintf(dosya, "%s,%s,%s,%.2f\n", h.tarih, h.kategori, h.aciklama, h.tutar);
    fclose(dosya);
    
    // İşlem bitince ekrana başarılı olduğuna dair pop-up çıkar
    MessageBox(NULL, "Harcama basariyla kaydedildi!", "Basarili", MB_ICONINFORMATION | MB_OK);
}

// 2. İŞLEM: HARCAMALARI AÇILIR PENCEREDE LİSTELEME
void harcamalariListele() {
    char satir[150]; // Dosyadan okunacak her bir satırı tutacak geçici alan
    
    // Pop-up ekranında göstereceğimiz ana metin (Başlıkları hazır ekledik)
    char liste[2048] = "TARIH\t\tKATEGORI\tACIKLAMA\tTUTAR\n--------------------------------------------------------------\n";
    
    // Dosyayı "okuma" (r) modunda açıyoruz
    FILE *dosya = fopen("harcamalar.csv", "r");
    
    if (dosya == NULL) {
        MessageBox(NULL, "Henuz hic harcama kaydi yok.", "Bilgi", MB_ICONINFORMATION | MB_OK);
        return;
    }

    // Dosyayı satır satır okuyup sonuna gelene kadar dön
    while (fgets(satir, sizeof(satir), dosya) != NULL) {
        // Okunan satırdaki virgülleri bulup boşluğa (TAB) çevir ki güzel görünsün
        for(int i = 0; satir[i] != '\0'; i++) {
            if(satir[i] == ',') satir[i] = '\t';
        }
        // Düzenlenen satırı, ana listemizin sonuna ekle (strcat = metin birleştir)
        strcat(liste, satir); 
    }
    fclose(dosya);

    // Hazırladığımız uzun listeyi ekranda pop-up olarak göster
    MessageBox(NULL, liste, "Tum Harcamalar", MB_OK);
}

// 3. İŞLEM: KATEGORİLERE GÖRE TOPLAM HARCAMA HESAPLAMA
void butceAnalizi() {
    FILE *dosya = fopen("harcamalar.csv", "r");
    if (dosya == NULL) {
        MessageBox(NULL, "Analiz edilecek veri bulunamadi.", "Bilgi", MB_ICONINFORMATION | MB_OK);
        return;
    }

    char satir[150];
    Kategori kategoriler[20]; // En fazla 20 farklı kategori tutacak liste
    int kategoriSayisi = 0;   // Şu an listede kaç kategori var?
    float genelToplam = 0;

    while (fgets(satir, sizeof(satir), dosya) != NULL) {
        satir[strcspn(satir, "\n")] = 0; // Alt satıra geçme işaretini temizle
        
        // Satırı virgüllerden bölerek parçalara ayır
        char *tarih = strtok(satir, ",");
        char *kategori = strtok(NULL, ",");
        char *aciklama = strtok(NULL, ",");
        char *tutar_str = strtok(NULL, ",");

        if(kategori && tutar_str) {
            float tutar = atof(tutar_str); // Metin olan tutarı sayıya çevir
            genelToplam += tutar;
            
            // Bu kategori daha önce listeye eklenmiş mi diye bak
            int bulundu = 0;
            for(int i = 0; i < kategoriSayisi; i++) {
                if(strcmp(kategoriler[i].isim, kategori) == 0) {
                    kategoriler[i].toplamTutar += tutar; // Varsa sadece parasını ekle
                    bulundu = 1;
                    break;
                }
            }
            
            // Eğer kategori listede yoksa, yeni olarak listeye ekle
            if(!bulundu && kategoriSayisi < 20) {
                strcpy(kategoriler[kategoriSayisi].isim, kategori);
                kategoriler[kategoriSayisi].toplamTutar = tutar;
                kategoriSayisi++;
            }
        }
    }
    fclose(dosya);

    // Sonuçları pop-up ekranında göstermek için bir metin hazırlıyoruz
    char rapor[1024] = "--- KATEGORI BAZLI BUTCE ANALIZI ---\n\n";
    char gecici[100]; // Her kategoriyi tek tek yazmak için geçici metin kutusu
    
    for(int i = 0; i < kategoriSayisi; i++) {
        // "Market: 150 TL" şeklinde metin oluştur ve rapora ekle
        sprintf(gecici, "%s:\t %.2f TL\n", kategoriler[i].isim, kategoriler[i].toplamTutar);
        strcat(rapor, gecici);
    }
    
    // En alta genel toplamı ekle
    sprintf(gecici, "\n----------------------------------\nGENEL TOPLAM:\t %.2f TL", genelToplam);
    strcat(rapor, gecici);

    // Hazırlanan raporu açılır pencerede göster
    MessageBox(NULL, rapor, "Analiz Raporu", MB_OK);
}

// ANA PROGRAM
int main() {
    int secim;

    while (1) {
        printf("\n=== Kisisel Harcama Takipcisi ===\n");
        printf("1. Yeni Harcama Ekle\n");
        printf("2. Tüm Harcamalari Listele (Pop-up)\n");
        printf("3. Butce Analizi Raporu (Pop-up)\n");
        printf("0. Cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &secim);

        if (secim == 0) {
            MessageBox(NULL, "Program kapatiliyor...", "Cikis", MB_ICONINFORMATION | MB_OK);
            break; 
        }
        else if (secim == 1) { harcamaEkle(); } 
        else if (secim == 2) { harcamalariListele(); }
        else if (secim == 3) { butceAnalizi(); }
        else {
            MessageBox(NULL, "Yanlis bir sayi girdiniz!", "Uyari", MB_ICONWARNING | MB_OK);
        }
    }

    return 0;
}
