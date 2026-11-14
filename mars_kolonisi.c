#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    // Durum degiskenleri
    int saglik = 100, enerji = 100, oksijen = 100;
    int su, yedekParca, modulHasari = 0;
    int kilitMuhurlu = 0;
    int gun = 1, tur = 0;

    // Zorluga gore degisen degerler
    int firtinaSure, firtinaHasar, suEsikYuksek, suEsikDusuk;

    // Diger degiskenler
    char seviye, komut, sifre, tahmin;
    int gecerli, turHarca, zar, esik, i;
    int miktar, artik, kullanilan, uretilen;
    int parca, onarilan;
    int carpan, kayip, esik1;
    int hasarTur, kayipSaglik, kayipOksijen;
    int deneme, puan;

    srand(time(NULL));

    printf("--- MARS KOLONISI YASAM DESTEK SIMULATORU ---\n");

    // Zorluk secimi
    do
    {
        printf("Zorluk sec (K: Kolay, N: Normal, Z: Zor): ");
        scanf(" %c", &seviye);
        gecerli = 1;

        switch (seviye)
        {
        case 'k':
        case 'K':
            su = 40;
            yedekParca = 3;
            firtinaSure = 3;
            firtinaHasar = 5;
            suEsikYuksek = 60;
            suEsikDusuk = 30;
            printf("Kolay secildi.\n");
            break;
        case 'n':
        case 'N':
            su = 30;
            yedekParca = 2;
            firtinaSure = 5;
            firtinaHasar = 8;
            suEsikYuksek = 50;
            suEsikDusuk = 20;
            printf("Normal secildi.\n");
            break;
        case 'z':
        case 'Z':
            su = 20;
            yedekParca = 2;
            firtinaSure = 7;
            firtinaHasar = 12;
            suEsikYuksek = 40;
            suEsikDusuk = 10;
            printf("Zor secildi.\n");
            break;
        default:
            gecerli = 0;
            printf("Gecersiz seviye! Tekrar gir.\n");
        }
    } while (gecerli == 0);

    printf("Komutlar: G O T D U K H Q\n");

    // Ana oyun dongusu
    do
    {
        turHarca = 0;
        printf("\n[Gun %d - Tur %d] Komut: ", gun, tur);
        scanf(" %c", &komut);

        switch (komut)
        {
        case 'g':
        case 'G':
            if (enerji < 15)
            {
                printf("Enerji yetersiz! Komut iptal.\n");
                break;
            }
            turHarca = 1;
            enerji = enerji - 15;
            oksijen = oksijen - 10;

            // Yaralanma kontrolu
            zar = rand() % 100;
            if (zar < 10 || modulHasari > 70)
            {
                saglik = saglik - 10;
                printf("Zar: %d / Esik: 10 -> YARALANDIN (Saglik -10)\n", zar);
            }
            else
            {
                printf("Zar: %d / Esik: 10 -> YARALANMADIN\n", zar);
            }

            // Su bulma kontrolu
            if (enerji > 40 && oksijen > 30)
            {
                esik = suEsikYuksek;
            }
            else
            {
                esik = suEsikDusuk;
            }
            zar = rand() % 100;
            if (zar < esik)
            {
                su = su + 5;
                printf("Zar: %d / Esik: %d -> BASARILI, 5 su bulundu\n", zar, esik);
            }
            else
            {
                printf("Zar: %d / Esik: %d -> Su bulunamadi\n", zar, esik);

                // Yedek parca bulma kontrolu
                zar = rand() % 100;
                if (zar < 30)
                {
                    yedekParca = yedekParca + 1;
                    printf("Zar: %d / Esik: 30 -> BASARILI, 1 yedek parca bulundu\n", zar);
                }
                else
                {
                    printf("Zar: %d / Esik: 30 -> BASARISIZ, eli bos donuldun\n", zar);
                }
            }
            break;

        case 'o':
        case 'O':
            if (enerji < 10)
            {
                printf("Enerji yetersiz! Komut iptal.\n");
                break;
            }
            printf("Suyun: %d. Kac su kullanilsin? ", su);
            miktar = 0;
            scanf("%d", &miktar);
            if (miktar > su || miktar < 2)
            {
                printf("Gecersiz miktar! Komut iptal.\n");
                break;
            }
            turHarca = 1;
            enerji = enerji - 10;
            artik = miktar % 2;
            kullanilan = miktar - artik;
            uretilen = kullanilan / 2 * 3;
            su = su - kullanilan;
            oksijen = oksijen + uretilen;
            printf("%d su kullanildi, %d oksijen uretildi. Artik su: %d\n", kullanilan, uretilen, artik);
            break;

        case 't':
        case 'T':
            if (yedekParca <= 0)
            {
                printf("Yedek parca yok, tamir yapilamaz!\n");
                break;
            }
            if (enerji < 10)
            {
                printf("Enerji yetersiz! Komut iptal.\n");
                break;
            }
            if (modulHasari == 0)
            {
                printf("Hasar yok, tamire gerek yok.\n");
                break;
            }

            if (modulHasari <= 30)
            {
                printf("Hasar: HAFIF\n");
                parca = 1;
                onarilan = 15;
            }
            else if (modulHasari <= 70)
            {
                printf("Hasar: ORTA\n");
                parca = 2;
                onarilan = 30;
            }
            else
            {
                printf("Hasar: AGIR\n");
                parca = 3;
                onarilan = 40;
            }

            if (yedekParca < parca)
            {
                printf("Yeterli yedek parca yok! Komut iptal.\n");
                break;
            }
            turHarca = 1;
            enerji = enerji - 10;
            yedekParca = yedekParca - parca;
            modulHasari = modulHasari - onarilan;
            printf("%d parca harcandi, %d hasar onarildi.\n", parca, onarilan);
            break;

        case 'd':
        case 'D':
            printf("\n--- DURUM RAPORU ---\n");
            printf("Gun: %d  Tur: %d\n", gun, tur);
            printf("Saglik: %d  Enerji: %d  Oksijen: %d\n", saglik, enerji, oksijen);
            printf("Su: %d  Yedek Parca: %d  Modul Hasari: %d\n", su, yedekParca, modulHasari);
            printf("Hava kilidi muhurlu mu (0/1): %d\n", kilitMuhurlu);

            if (oksijen < 25)
            {
                printf("UYARI: Oksijen kritik!\n");
            }
            if (saglik < 30)
            {
                printf("UYARI: Saglik kritik!\n");
            }
            if (modulHasari > 70)
            {
                printf("UYARI: Modul hasari kritik!\n");
            }
            if (oksijen >= 25 && saglik >= 30 && modulHasari <= 70)
            {
                printf("TUM SISTEMLER NORMAL\n");
            }
            break;

        case 'u':
        case 'U':
            turHarca = 1;
            enerji = enerji + 25;
            if (oksijen >= 20)
            {
                if (saglik < 100)
                {
                    saglik = saglik + 10;
                    printf("Dinlendin: Enerji +25, Saglik +10\n");
                }
                else
                {
                    printf("Dinlendin: Enerji +25 (saglik zaten dolu)\n");
                }
            }
            else
            {
                saglik = saglik - 5;
                printf("Oksijen cok az! Saglik -5\n");
            }
            oksijen = oksijen - 5;
            break;

        case 'k':
        case 'K':
            turHarca = 1;
            hasarTur = 0;
            kayipSaglik = 0;
            kayipOksijen = 0;
            printf("KUM FIRTINASI basladi (%d tur)\n", firtinaSure);

            for (i = 1; i <= firtinaSure; i++)
            {
                // Cift turlarda hasar 2 kat
                carpan = 1;
                if (i % 2 == 0)
                {
                    carpan = 2;
                }

                // Modul zayifsa firtina daha tehlikeli
                esik1 = 25;
                if (modulHasari > 50)
                {
                    esik1 = 35;
                }

                zar = rand() % 100;
                if (zar < esik1)
                {
                    kayip = firtinaHasar * carpan;
                    saglik = saglik - kayip;
                    kayipSaglik = kayipSaglik + kayip;
                    hasarTur = hasarTur + 1;
                    printf("Tur %d - Zar: %d / Esik: %d -> CAN KAYBI (-%d)\n", i, zar, esik1, kayip);
                }
                else if (zar < esik1 + 25)
                {
                    if (kilitMuhurlu == 1)
                    {
                        printf("Tur %d - Zar: %d / Esik: %d -> Oksijen sizintisi, kilit muhurlu, atlandi\n", i, zar, esik1 + 25);
                        continue;
                    }
                    kayip = 8 * carpan;
                    oksijen = oksijen - kayip;
                    kayipOksijen = kayipOksijen + kayip;
                    hasarTur = hasarTur + 1;
                    printf("Tur %d - Zar: %d / Esik: %d -> OKSIJEN SIZINTISI (-%d)\n", i, zar, esik1 + 25, kayip);
                }
                else if (zar < esik1 + 45)
                {
                    kayip = firtinaHasar * carpan;
                    modulHasari = modulHasari + kayip;
                    hasarTur = hasarTur + 1;
                    printf("Tur %d - Zar: %d / Esik: %d -> MODUL HASARI (+%d)\n", i, zar, esik1 + 45, kayip);
                }
                else
                {
                    printf("Tur %d - Zar: %d / Esik: %d -> Korundun, zarar yok\n", i, zar, esik1 + 45);
                }

                if (saglik <= 0 || oksijen <= 0)
                {
                    printf("Kritik seviye! Firtina bitirildi.\n");
                    break;
                }
            }
            printf("FIRTINA OZETI: %d turda hasar alindi, %d saglik ve %d oksijen kaybedildi.\n", hasarTur, kayipSaglik, kayipOksijen);
            break;

        case 'h':
        case 'H':
            if (kilitMuhurlu == 1)
            {
                printf("Hava kilidi zaten muhurlu.\n");
                break;
            }
            if (enerji < 15)
            {
                printf("Enerji yetersiz! (en az 15 gerekli)\n");
                break;
            }
            turHarca = 1;
            sifre = 'A' + (gun % 26);
            deneme = 0;
            printf("IPUCU: Sifre, alfabede A harfinden bugunun gun sayisi kadar ilerideki harftir.\n");

            do
            {
                printf("Deneme %d/3 - Harf gir: ", deneme + 1);
                scanf(" %c", &tahmin);
                if (tahmin >= 'a' && tahmin <= 'z')
                {
                    tahmin = tahmin - 'a' + 'A';
                }
                deneme = deneme + 1;
                if (tahmin != sifre)
                {
                    enerji = enerji - 5;
                    if (tahmin < sifre)
                    {
                        printf("Yanlis! Ileri git (Enerji -5)\n");
                    }
                    else
                    {
                        printf("Yanlis! Geri git (Enerji -5)\n");
                    }
                }
            } while (tahmin != sifre && deneme < 3);

            if (tahmin == sifre)
            {
                kilitMuhurlu = 1;
                printf("DOGRU! Hava kilidi muhurlendi.\n");
            }
            else
            {
                modulHasari = modulHasari + 20;
                printf("3 deneme bitti! Modul hasari +20\n");
            }
            break;

        case 'q':
        case 'Q':
            printf("Cikis yapiliyor...\n");
            break;

        default:
            printf("Tanimsiz komut! (tur harcanmadi)\n");
        }

        // Zaman akisi
        if (turHarca == 1)
        {
            tur = tur + 1;
            if (tur % 3 == 0)
            {
                gun = gun + 1;
                oksijen = oksijen - 8;
                printf("\n*** Yeni gun basladi: Gun %d (Oksijen -8) ***\n", gun);
                if (modulHasari > 70)
                {
                    saglik = saglik - 5;
                    printf("Modul hasari yuksek, Saglik -5\n");
                }
            }
        }

        // Sinirlandirma (0-100)
        if (saglik < 0)
        {
            saglik = 0;
        }
        if (saglik > 100)
        {
            saglik = 100;
        }
        if (enerji < 0)
        {
            enerji = 0;
        }
        if (enerji > 100)
        {
            enerji = 100;
        }
        if (oksijen < 0)
        {
            oksijen = 0;
        }
        if (oksijen > 100)
        {
            oksijen = 100;
        }
        if (modulHasari < 0)
        {
            modulHasari = 0;
        }
        if (modulHasari > 100)
        {
            modulHasari = 100;
        }

    } 

    while (komut != 'q' && komut != 'Q' && saglik > 0 && oksijen > 0 && gun <= 15);

    // Oyun sonu
    printf("\n=============================\n");
    if (saglik <= 0 || oksijen <= 0)
    {
        printf("OYUNU KAYBETTIN!\n");
    }
    else if (gun > 15)
    {
        printf("TEBRIKLER! Kurtarma ekibi geldi, OYUNU KAZANDIN!\n");
        gun = 15;
    }
    else
    {
        printf("Oyundan cikildi.\n");
    }

    puan = (gun * 100) + saglik + oksijen - modulHasari;

    printf("--- SONUC RAPORU ---\n");
    printf("Hayatta kalinan gun: %d\n", gun);
    printf("Toplam tur: %d\n", tur);
    printf("Saglik: %d  Enerji: %d  Oksijen: %d\n", saglik, enerji, oksijen);
    printf("Su: %d  Yedek Parca: %d  Modul Hasari: %d\n", su, yedekParca, modulHasari);
    printf("PUAN: %d\n", puan);
    printf("=============================\n");

    return 0;
}