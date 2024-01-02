#include <iostream>
#include <iomanip>
#include <locale>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Urun {
    string ad;
    double fiyat;
    int stokAdedi;
};

void firmaHakkinda() {
    system("cls");
    wcout << L"MTG SOFTWORKS 2023 Yilinda Kurulmus Yeni Teknolojileri Takip Eden Inovatif Bir Yazilim Sirketidir." << endl;
    wcout << L"Firma Sahibi: Mesut Taha Güven" << endl;
}

void alisverisBasla(vector<Urun>& urunler, double& toplamFiyat) {
    system("cls");

    int secim;
    int adet;
    char devamEt;

    do {
        wcout << L"\n1-) Cep Telefonu -----> 30000TL\n"
            << L"2-) Bilgisayar -----> 50000TL\n"
            << L"3-) Televizyon -----> 42500TL\n"
            << L"4-) Klavye -----> 1000TL\n"
            << L"5-) Mouse -----> 650TL\n"
            << L"6-) Sepeti Sıfırla\n"
            << L"0-) Geri Dön\n";
        wcout << L"Secim yapin: ";
        cin >> secim;

        if (secim == 6) {
            toplamFiyat = 0.0;
            urunler.clear();
            wcout << L"Sepet sifirlandi." << endl;
            continue;
        }
        else if (secim == 0) {
            break;
        }
        else if (secim < 1 || secim > 5) {
            wcout << L"Gecersiz secim! Lutfen tekrar deneyin." << endl;
            continue;
        }

        int urunIndex = secim - 1;

        wcout << L"Adet girin: ";
        cin >> adet;

        if (adet <= 0 || adet > urunler[urunIndex].stokAdedi) {
            wcout << L"Geçersiz adet! Lutfen uygun bir adet girin." << endl;
            continue;
        }

        toplamFiyat += adet * urunler[urunIndex].fiyat;
        urunler[urunIndex].stokAdedi -= adet;

        wcout << L"Toplam Fiyat: " << fixed << setprecision(2) << toplamFiyat << L" TL" << endl;

        wcout << L"\nAlisverise devam etmek istiyor musunuz? (e/h): ";
        cin >> devamEt;
        if (devamEt != 'e' && devamEt != 'E') {
            system("cls");
            break;
        }

    } while (true);
}

void taksitlendir(double toplamTutar, string dosyaAdi) {
    int taksitSayisi;
    double taksitTutari;
    string aylar[] = { "Ocak", "Subat", "Mart", "Nisan", "Mayis", "Haziran", "Temmuz", "Agustos", "Eylul", "Ekim", "Kasim", "Aralik" };

    wcout << L"Taksitlendirme islemi baslatiliyor..." << endl;

    wcout << L"Taksit Sayisi (0-36): ";
    cin >> taksitSayisi;

    if (taksitSayisi < 0 || taksitSayisi > 36) {
        wcout << L"Geçersiz taksit sayisi! Lutfen 0 ile 36 arasinda bir deger girin." << endl;
        return;
    }

    taksitTutari = toplamTutar / taksitSayisi;

    ofstream dosya(dosyaAdi);
    if (dosya.is_open()) {
        dosya << "Sepetteki Toplam Tutar: " << fixed << setprecision(2) << toplamTutar << " TL" << endl;

        for (int i = 0; i < taksitSayisi; ++i) {
            dosya << aylar[i % 12].c_str() << " Taksit: " << fixed << setprecision(2) << taksitTutari << " TL" << endl;
        }

        dosya.close();
        wcout << L"Taksit bilgileri " << "taksit.txt" << " dosyasina yazdirildi." << endl;
    }
    else {
        wcout << L"Dosya acilamadi!" << endl;
    }

    // Ekrana yazdırma
    wcout << L"\nSepetteki Toplam Tutar: " << fixed << setprecision(2) << toplamTutar << L" TL" << endl;

    for (int i = 0; i < taksitSayisi; ++i) {
        wcout << aylar[i % 12].c_str() << " Taksit: " << fixed << setprecision(2) << taksitTutari << L" TL" << endl;
    }
}

void yazdir(double toplamFiyat) {
    system("cls");
    wcout << L"Toplam Tutar: " << fixed << setprecision(2) << toplamFiyat << L" TL" << endl;
}

int main() {
    setlocale(LC_ALL, "turkish");

    int secim;
    char devamEt;
    double toplamFiyat = 0.0;
    vector<Urun> urunler = {
        {"Cep Telefonu", 30000.0, 10},
        {"Bilgisayar", 50000.0, 15},
        {"Televizyon", 42500.0, 20},
        {"Klavye", 1000.0, 30},
        {"Mouse", 650.0, 25}
    };

    do {
        wcout << L"\nMTG SOFTWORKS BILISIM HOSGELDINIZ\n";
        wcout << L"-------------------------------------------------\n";
        wcout << L"Lutfen bir islem seciniz:\n";
        wcout << L"1-) Firma Hakkinda\n2-) Alis Veris\n3-) Cikis\n";

        wcout << L"Secim yapin: ";
        cin >> secim;

        switch (secim) {
        case 1:
            firmaHakkinda();
            break;
        case 2:
            do {
                wcout << L"\nAlisveris Menusu:\n";
                wcout << L"1-) Alisverise Basla\n"
                    << L"2-) Taksitlendir\n"
                    << L"3-) Yazdir\n"
                    << L"0-) Geri Don\n";
                wcout << L"Secim yapin: ";
                cin >> secim;

                switch (secim) {
                case 1:
                    alisverisBasla(urunler, toplamFiyat);
                    break;
                case 2:
                    taksitlendir(toplamFiyat, "taksit.txt");
                    break;
                case 3:
                    yazdir(toplamFiyat);
                    break;
                case 0:
                    break;
                default:
                    wcout << L"Gecersiz secim! Lutfen tekrar deneyin." << endl;
                    break;
                }

                if (secim != 0) {
                    wcout << L"\nDevam etmek istiyor musunuz? (e/h): ";
                    cin >> devamEt;
                    if (devamEt != 'e' && devamEt != 'E') {
                        break;
                    }
                }

            } while (secim != 0);
            break;
        case 3:
            wcout << L"Programdan cikiliyor..." << endl;
            break;
        default:
            wcout << L"Gecersiz secim! Lutfen tekrar deneyin." << endl;
            break;
        }

    } while (secim != 3);

    return 0;
}