# Mars Kolonisi Yaşam Destek Simülatörü

C diliyle yazılmış, metin tabanlı ve tek karakterli komutlarla kontrol edilen bir hayatta kalma oyunu. Oyuncu, Mars'taki küçük bir araştırma istasyonunda tek başına kalmış bir mühendisi yönetir ve kurtarma ekibi gelene kadar **15 gün** hayatta kalmaya çalışır.

Proje, "Algoritma ve Programlama" dersi ödevi kapsamında geliştirilmiştir. Yalnızca C'nin temel yapıları kullanılmıştır: değişkenler, aritmetik ve mantıksal operatörler, `if – else if – else`, `switch – case`, `for` ve `do – while`. Fonksiyon, dizi ve struct kullanılmamıştır.

## İçindekiler

- [Özellikler](#özellikler)
- [Gereksinimler](#gereksinimler)
- [Derleme ve Çalıştırma](#derleme-ve-çalıştırma)
- [Nasıl Oynanır](#nasıl-oynanır)
- [Komutlar](#komutlar)
- [Zorluk Seviyeleri](#zorluk-seviyeleri)
- [Oyun Kuralları](#oyun-kuralları)
- [Örnek Çıktı](#örnek-çıktı)
- [Kodda Kullanılan C Yapıları](#kodda-kullanılan-c-yapıları)
- [Proje Yapısı](#proje-yapısı)

## Özellikler

- Büyük/küçük harf duyarsız komut sistemi (`g` ve `G` aynı işlemi yapar)
- Üç zorluk seviyesi: Kolay, Normal, Zor
- Sağlık, enerji, oksijen, su, yedek parça, modül hasarı, hava kilidi, gün ve tur takibi
- Rastgele olaylar: her zar ve eşik değeri ekrana yazdırılır (`Zar: 37 / Esik: 45 -> BASARILI` biçiminde)
- `for` döngüsüyle simüle edilen kum fırtınası
- `do – while` döngüsüyle çalışan, sınırlı denemeli hava kilidi şifresi
- Oyun sonunda sonuç raporu ve puan hesabı

## Gereksinimler

- Bir C derleyicisi (örneğin GCC)
- Standart C kütüphaneleri: `stdio.h`, `stdlib.h`, `time.h`

## Derleme ve Çalıştırma

```bash
gcc mars_kolonisi_basit.c -o mars
./mars
```

Windows'ta çalıştırmak için:

```bash
gcc mars_kolonisi_basit.c -o mars.exe
mars.exe
```

> Konsol karakter kodlaması sorunlarını önlemek için program çıktısında Türkçe karakter kullanılmamıştır.

## Nasıl Oynanır

1. Program başlayınca zorluk seviyesini seçin (`K`, `N` veya `Z`). Geçersiz girişte seçim tekrar istenir.
2. `[Gun X - Tur Y] Komut:` satırında bir komut harfi girin ve Enter'a basın.
3. Sağlık veya oksijen 0'a düşmeden 15. günü tamamlamaya çalışın.
4. Oyun bittiğinde (kazanma, kaybetme veya `Q` ile çıkış) sonuç raporu gösterilir.

## Komutlar

| Komut | İşlev | Maliyet |
|:-----:|-------|---------|
| `G` | **Keşif görevi.** Su veya yedek parça bulma şansı vardır, yaralanma riski taşır. | Enerji -15, Oksijen -10 |
| `O` | **Oksijen üret.** Girilen su miktarı oksijene dönüşür (2 su = 3 oksijen). Tek sayıda su girilirse 1 birim artık olarak depoda kalır. | Enerji -10 |
| `T` | **Tamir.** Yedek parça harcanarak modül hasarı azaltılır. | Enerji -10 |
| `D` | **Durum raporu.** Tüm değerler ve kritik uyarılar gösterilir. Tur harcamaz. | Yok |
| `U` | **Uyu / dinlen.** Enerji ve sağlık artar, oksijen tüketimi devam eder. | Oksijen -5 |
| `K` | **Kum fırtınası.** Fırtına tur tur simüle edilir. | Rastgele olaylar |
| `H` | **Hava kilidi şifresi.** Doğru şifre girilirse hava kilidi mühürlenir. | Her yanlış denemede Enerji -5 |
| `Q` | **Çıkış.** Oyunu bitirir ve sonuç raporunu gösterir. | Yok |

Tanımsız bir komut girildiğinde uyarı verilir ve tur harcanmaz. Enerjisi yetersiz olan komut iptal edilir ve tur harcamaz.

### Keşif (G)

- Yaralanma koşulu: `zar < 10 || modulHasari > 70` (sağlık -10)
- Su bulma eşiği, `enerji > 40 && oksijen > 30` ise yüksek, değilse düşüktür.
- Üç olası sonuç vardır: 5 birim su bulma, 1 yedek parça bulma veya eli boş dönme.

### Tamir (T)

Hasar seviyesine göre üç kademe vardır:

| Hasar | Kademe | Harcanan parça | Onarılan hasar |
|:-----:|--------|:--------------:|:--------------:|
| 0 – 30 | Hafif | 1 | 15 |
| 31 – 70 | Orta | 2 | 30 |
| 71 – 100 | Ağır | 3 | 40 |

### Kum Fırtınası (K)

- Fırtınanın süresi zorluk seviyesine göre belirlenir.
- Her turda can kaybı, oksijen sızıntısı, modül hasarı veya korunma olaylarından biri gerçekleşir.
- Çift numaralı turlarda rüzgar şiddetlenir ve hasar iki katına çıkar.
- Hava kilidi mühürlüyse oksijen sızıntısı olayı o tur için atlanır.
- Sağlık veya oksijen 0'a düşerse fırtına anında sonlanır.
- Fırtına sonunda özet yazdırılır: hasar alınan tur sayısı, kaybedilen sağlık ve oksijen.

### Hava Kilidi Şifresi (H)

- Şifre, İngiliz alfabesinden tek bir büyük harftir. Küçük harf girişi de kabul edilir.
- Şifre sabit değildir, günden türetilir: `'A' + (gun % 26)`. Birinci gün şifre `B`, ikinci gün `C` olur.
- En fazla **3 deneme** hakkı vardır. Her yanlış denemede enerji 5 azalır ve "ileri git" veya "geri git" ipucu verilir.
- Doğru şifrede hava kilidi mühürlenir. 3 deneme de başarısız olursa modül hasarı 20 artar.
- Hava kilidi mühürlendikten sonra tekrar `H` girilemez.

## Zorluk Seviyeleri

| Seviye | Başlangıç suyu | Yedek parça | Fırtına süresi | Fırtına hasarı | Su bulma eşiği (yüksek / düşük) |
|--------|:--------------:|:-----------:|:--------------:|:--------------:|:-------------------------------:|
| Kolay (`K`) | 150 | 3 | 3 tur | 5 | 60 / 30 |
| Normal (`N`) | 140 | 2 | 5 tur | 8 | 50 / 20 |
| Zor (`Z`) | 130 | 2 | 7 tur | 12 | 40 / 10 |

## Oyun Kuralları

**Başlangıç değerleri:** Sağlık 100, enerji 100, oksijen 100, modül hasarı 0, hava kilidi mühürsüz, gün 1, tur 0.

**Zaman akışı:**
- Her geçerli komut tur sayacını 1 artırır (`D`, `Q`, tanımsız ve iptal edilen komutlar hariç).
- Her 3 turda bir (`tur % 3 == 0`) yeni gün başlar.
- Gün başında oksijen 8 azalır. Modül hasarı 70'in üzerindeyse ek olarak 5 sağlık kaybedilir.

**Sınırlandırma:** Sağlık, enerji, oksijen ve modül hasarı her komuttan sonra 0 ile 100 arasında tutulur.

**Oyun sonu:**
- Sağlık veya oksijen 0'a düşerse oyun **kaybedilir**.
- 15. gün tamamlanırsa kurtarma ekibi gelir ve oyun **kazanılır**.
- `Q` ile çıkıldığında da sonuç raporu yazdırılır.

**Puan hesabı:**

```text
Puan = (gun x 100) + saglik + oksijen - modulHasari
```

## Örnek Çıktı

```text
--- MARS KOLONISI YASAM DESTEK SIMULATORU ---
Zorluk sec (K: Kolay, N: Normal, Z: Zor): x
Gecersiz seviye! Tekrar gir.
Zorluk sec (K: Kolay, N: Normal, Z: Zor): k
Kolay secildi.
Komutlar: G O T D U K H Q

[Gun 1 - Tur 0] Komut: b
Tanimsiz komut! (tur harcanmadi)

[Gun 1 - Tur 0] Komut: g
Zar: 88 / Esik: 10 -> YARALANMADIN
Zar: 23 / Esik: 60 -> BASARILI, 5 su bulundu

[Gun 2 - Tur 3] Komut: o
Suyun: 155. Kac su kullanilsin? 12
12 su kullanildi, 18 oksijen uretildi. Artik su: 0

[Gun 2 - Tur 5] Komut: k
KUM FIRTINASI basladi (3 tur)
Tur 1 - Zar: 11 / Esik: 25 -> CAN KAYBI (-5)
Tur 2 - Zar: 99 / Esik: 70 -> Korundun, zarar yok
Tur 3 - Zar: 70 / Esik: 70 -> Korundun, zarar yok
FIRTINA OZETI: 1 turda hasar alindi, 5 saglik ve 0 oksijen kaybedildi.
```

Oyun sonunda şuna benzer bir sonuç raporu yazdırılır:

```text
=============================
TEBRIKLER! Kurtarma ekibi geldi, OYUNU KAZANDIN!
--- SONUC RAPORU ---
Hayatta kalinan gun: 15
Toplam tur: 45
Saglik: 100  Enerji: 100  Oksijen: 50
Su: 0  Yedek Parca: 3  Modul Hasari: 0
PUAN: 1650
=============================
```

## Kodda Kullanılan C Yapıları

| Yapı | Kullanıldığı yer |
|------|------------------|
| `switch – case` (fall-through ile) | Zorluk seçimi ve komut yönetimi (`case 'g': case 'G':`) |
| `if – else if – else` | Tamir kademeleri, oyun sonu kontrolü |
| İç içe `if` | Dinlenmede oksijene göre sağlık kontrolü |
| `for` döngüsü | Kum fırtınası simülasyonu |
| `break` ve `continue` | Fırtınayı erken bitirme, mühürlü kilitte oksijen sızıntısını atlama |
| `do – while` döngüsü | Ana komut döngüsü, zorluk seçimi, hava kilidi şifresi |
| Aritmetik operatörler (`+ - * / %`) | Kaynak hesapları, artık su, çift tur ve gün kontrolü, şifre harfi |
| Mantıksal operatörler (`&& \|\|`) | Yaralanma, su eşiği, durum raporu, döngü koşulları |
| `rand()` ve `srand(time(NULL))` | Rastgele olaylar |

## Proje Yapısı

```text
.
├── mars_kolonisi_basit.c   # Oyunun tüm kaynak kodu
└── README.md
```

## Hazırlayan

Ad Soyad: ........................

Öğrenci No: ........................
