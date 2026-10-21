#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h> 

// Harcama modeli
typedef struct {
    char tarih[15];
    char kategori[30];
    char aciklama[50];
    float tutar;
} Harcama;

// Analiz icin kullanılacak model
typedef struct {
    char isim[30];
    float toplamTutar;
} Kategori;

void harcamaEkle() {
    Harcama h;
    FILE *dosya = fopen("harcamalar.csv", "a");

    if (dosya == NULL) {
        MessageBox(NULL, "Dosya acilamadi!", "Hata", MB_ICONERROR | MB_OK);
        return;
    }

    // Tarihi bilgisayardan otomatik cekme islemi
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(h.tarih, "%02d-%02d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    
    printf("\nKategori (Orn: Egitim, Evcil_Hayvan, Teknoloji): ");
    scanf("%s", h.kategori);
    printf("Aciklama (Bosluk yerine _ kullanin): ");
    scanf("%s", h.aciklama);
    printf("Tutar: ");
    
    // Tutar kismina yanlislikla harf girilmesini engelleyen hata kontrolu
    if (scanf("%f", &h.tutar) != 1) {
        MessageBox(NULL, "Gecersiz tutar! Lutfen sadece sayi girin.", "Hata", MB_ICONERROR | MB_OK);
        while(getchar() != '\n'); // Hatali girisi temizle
        fclose(dosya);
        return;
    }

    fprintf(dosya, "%s,%s,%s,%.2f\n", h.tarih, h.kategori, h.aciklama, h.tutar);
    fclose(dosya);
    
    MessageBox(NULL, "Harcama basariyla sisteme islendi!", "Basarili", MB_ICONINFORMATION | MB_OK);
}

void harcamalariListele() {
    char satir[150];
    char liste[2048] = "TARIH\t\tKATEGORI\tACIKLAMA\tTUTAR\n----------------------------------------------------------------------\n";
    FILE *dosya = fopen("harcamalar.csv", "r");
    
    if (dosya == NULL) {
        MessageBox(NULL, "Henuz hic harcama kaydi yok.", "Bilgi", MB_ICONINFORMATION | MB_OK);
        return;
    }

    while (fgets(satir, sizeof(satir), dosya) != NULL) {
        for(int i = 0; satir[i] != '\0'; i++) {
            if(satir[i] == ',') satir[i] = '\t';
        }
        strcat(liste, satir); 
    }
    fclose(dosya);
    MessageBox(NULL, liste, "Tum Harcamalar", MB_OK);
}

// YENI OZELLIK: Kategori bazli toplam harcama hesaplayici
void butceAnalizi() {
    FILE *dosya = fopen("harcamalar.csv", "r");
    if (dosya == NULL) {
        MessageBox(NULL, "Analiz edilecek veri bulunamadi.", "Bilgi", MB_ICONINFORMATION | MB_OK);
        return;
    }

    char satir[150];
    Kategori kategoriler[20]; // Maksimum 20 farkli kategori tutan sabit dizi
    int kategoriSayisi = 0;
    float genelToplam = 0;

    while (fgets(satir, sizeof(satir), dosya) != NULL) {
        satir[strcspn(satir, "\n")] = 0;
        
        char *tarih = strtok(satir, ",");
        char *kategori = strtok(NULL, ",");
        char *aciklama = strtok(NULL, ",");
        char *tutar_str = strtok(NULL, ",");

        if(kategori && tutar_str) {
            float tutar = atof(tutar_str);
            genelToplam += tutar;
            
            // Bu kategori daha once eklendi mi diye diziyi kontrol et
            int bulundu = 0;
            for(int i = 0; i < kategoriSayisi; i++) {
                if(strcmp(kategoriler[i].isim, kategori) == 0) {
                    kategoriler[i].toplamTutar += tutar;
                    bulundu = 1;
                    break;
                }
            }
            
            // Kategori ilk kez goruluyorsa diziye yeni kayit olarak ekle
            if(!bulundu && kategoriSayisi < 20) {
                strcpy(kategoriler[kategoriSayisi].isim, kategori);
                kategoriler[kategoriSayisi].toplamTutar = tutar;
                kategoriSayisi++;
            }
        }
    }
    fclose(dosya);

    // Sonuclari pop-up ekrani icin hazirla
    char rapor[1024] = "--- KATEGORI BAZLI BUTCE ANALIZI ---\n\n";
    char gecici[100];
    for(int i = 0; i < kategoriSayisi; i++) {
        sprintf(gecici, "%s:\t %.2f TL\n", kategoriler[i].isim, kategoriler[i].toplamTutar);
        strcat(rapor, gecici);
    }
    sprintf(gecici, "\n----------------------------------\nGENEL TOPLAM:\t %.2f TL", genelToplam);
    strcat(rapor, gecici);

    MessageBox(NULL, rapor, "Analiz Raporu", MB_OK);
}

int main() {
    int secim;

    while (1) {
        printf("\n=== Kisisel Harcama Takipcisi ===\n");
        printf("1. Yeni Harcama Ekle (Otomatik Tarihli)\n");
        printf("2. Tüm Harcamalari Listele\n");
        printf("3. Butce Analizi Raporu \n");
        printf("0. Cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &secim);

        if (secim == 0) {
            MessageBox(NULL, "Programdan cikiliyor. Iyi gunler!", "Cikis", MB_ICONINFORMATION | MB_OK);
            break; 
        }

        if (secim == 1) {
            harcamaEkle();
        } 
        else if (secim == 2) {
            harcamalariListele();
        }
        else if (secim == 3) {
            butceAnalizi();
        }
        else {
            MessageBox(NULL, "Gecersiz secim yaptiniz!", "Uyari", MB_ICONWARNING | MB_OK);
        }
    }

    return 0;
}