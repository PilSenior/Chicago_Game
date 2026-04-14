# Chicago Game - Detaylı Program Açıklaması

## 📚 Programa Genel Bakış

Bu program, "Chicago" adında bir zar oyunu simulatörüdür. İnsan oyuncu ile bilgisayar arasında 11 turdan oluşan bir oyun oynanır. Her turda hedef sayı artar (1. tur'da hedef 2, 2. tur'da hedef 3, vb.) ve oyuncular zar atarak bu hedefe ulaşmaya çalışırlar.

---

## 🔧 Kod Geliştirme Adımları

### ADIM 1: Gerekli Kütüphaneleri Ekleme

```c
#include <stdio.h>      // Ekran çıkışı ve giriş işlemleri için
#include <stdlib.h>     // Rastgele sayı üretimi için (rand() fonksiyonu)
#include <time.h>       // Zaman bazlı rasgele sayı üretimi için (seed uretimi)
```

**Neden bu kütüphaneler lazım?**
- `stdio.h`: Kullanıcıyla iletişim (printf ve scanf)
- `stdlib.h`: Rastgele sayılar (rand())
- `time.h`: Her çalışmada farklı rastgele sayılar (time(NULL))

---

### ADIM 2: Fonksiyon Prototipi Tanımlaması

```c
int roll_a_dice(void);
int play_user(int target);
int play_computer(int target);
void scoresheet(int comp_total, int user_total);
int calculate_score(int dice1, int dice2);
```

**Neden prototip lazım?**
- Derleyiciye fonksiyonların varlığını önceden bildirmek
- main() fonksiyonu bu fonksiyonları kullanacağı için
- Parametreleri ve dönüş tiplerini tanımlamak

---

## 📋 Fonksiyonlar Detaylı Açıklaması

### 1️⃣ roll_a_dice() - Zar Atma Fonksiyonu

```c
int roll_a_dice()
{
    return (rand() % 6) + 1;
}
```

**Fonksiyonun Amacı:**
- 1 ile 6 arasında rastgele bir sayı üretmek (gerçek zar gibi)

**Mantık Açıklaması:**
- `rand()`: Rastgele bir sayı üretir (0 ile RAND_MAX arasında)
- `% 6`: Sayıyı 6'ya bölerek kalanını alır (0, 1, 2, 3, 4, 5)
- `+ 1`: 1 ekleyerek sonucu 1-6 aralığına çevirir

**Örnek:**
- rand() = 12 ise → 12 % 6 = 0 → 0 + 1 = **1**
- rand() = 15 ise → 15 % 6 = 3 → 3 + 1 = **4**

---

### 2️⃣ calculate_score() - Skor Hesaplama Fonksiyonu

```c
int calculate_score(int dice1, int dice2)
{
    return dice1 + dice2;
}
```

**Fonksiyonun Amacı:**
- İki zarın toplamını hesaplamak

**Parametreler:**
- `dice1`: Birinci zarın değeri
- `dice2`: İkinci zarın değeri

**Dönüş Değeri:** İki zarın toplamı (2 ile 12 arasında)

**Neden ayrı bir fonksiyon?**
- Kodu daha okunur hale getirmek
- Aynı işlemi birden fazla yerde kullanacağımız için

---

### 3️⃣ play_user() - Kullanıcı Oyunu Fonksiyonu

```c
int play_user(int target)
{
    int roll_no = 1;           // 1., 2. veya 3. atış mı?
    int dice1, dice2;          // İki zarın değerleri
    int hits = 0;              // Hedefi kaç kez peş peşe vurduk?
    char choice = 'Y';         // Kullanıcı tekrar atmak istiyor mu?

    while (roll_no <= 3 && choice != 'N' && choice != 'n')
    {
        // Zar atılıyor
        dice1 = roll_a_dice();
        dice2 = roll_a_dice();
        printf("You got [Dice 1]: %d [Dice 2]: %d\n", dice1, dice2);

        // Hedefi vurduk mu?
        int is_hit = (calculate_score(dice1, dice2) == target);

        if (is_hit)
        {
            hits++;  // Hedefi vurduk, sayıyı artır
        }
        else if (!is_hit)
        {
            hits = 0;  // ❌ ÖNEMLI: Hedefi kaçırdık, seri bozuluyor, her şey sıfırlanır!
        }

        // O atışın sonucunu göster
        int round_total = hits * target;  // Toplam skor (hitler × hedef)
        int roll_score = is_hit ? target : 0;  // Bu atışın puanı
        printf("Your score: %d Total score: %d\n", roll_score, round_total);

        // 3. atıştan sonra sorma, sadece 1. ve 2. atıştan sonra sor
        if (roll_no < 3)
        {
            do
            {
                printf("Shall I roll for you again (Y/N)? ");
                scanf(" %c", &choice);
                if (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
                    printf("Invalid input, Try Again!\n");
            } while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');
        }
        roll_no++;
    }

    // Eğer en az bir hit varsa, hitler × hedef döndür. Yoksa 0 döndür
    return (hits > 0) ? hits * target : 0;
}
```

**Fonksiyonun Amacı:**
Kullanıcının bir turda kaç puan kazanacağını belirlemek (maksimum 3 zar atış)

**Değişkenler:**
| Değişken | Türü | Amaç |
|----------|------|------|
| `roll_no` | int | Kaçıncı atış olduğunu takip et (1, 2 veya 3) |
| `dice1, dice2` | int | Her atışta zarların değerleri |
| `hits` | int | **SERI VURU SAYISI**: Hedefi peş peşe kaç kez vurttuk? |
| `choice` | char | Kullanıcı Y(evet) veya N(hayır) girişi |
| `is_hit` | int | Bu atış hedefe ulaştı mı? (true/false) |
| `round_total` | int | Turun toplam puanı (hits × target) |
| `roll_score` | int | Bu atışın puanı |

**Seri Vuru Sistemi (Cascade System):**
```
Örnek 1: Target = 5
Atış 1: 2+3=5 ✓ Hedefi vurduk! hits=1 → puan=1×5=5
Atış 2: 2+3=5 ✓ Tekrar vurduk! hits=2 → puan=2×5=10
Atış 3: 1+3=4 ✗ KAÇIRDIK! hits=0 → TOPLAM PUAN=0

❌ ÖNEMLİ KURAL:
Bir atışta ıskalarsak, önceki tüm hitler geçersiz olur!
Bu nedenle hits = 0 yapılır.
```

**Dönüş Değeri:**
- En az 1 hit varsa: `hits × target`
- Hit yoksa: `0`

---

### 4️⃣ play_computer() - Bilgisayar Oyunu Fonksiyonu

```c
int play_computer(int target)
{
    int roll_no = 1;
    int dice1, dice2;
    int sum = target - 1;      // Başlangıç: hedefi tutmayan bir sayı
    int hits = 0;
    int round_total = 0;
    int roll_score;

    // sum == target - 1 olduğu sürece devam et
    // Yani: Hedefi VURANA KADAR zar at!
    while (roll_no <= 3 && sum == target - 1)
    {
        dice1 = roll_a_dice();
        dice2 = roll_a_dice();
        sum = dice1 + dice2;

        // İlk atış mesajı vs diğer atışlar için farklı mesaj
        if (roll_no == 1)
        {
            printf("I rolled them and I got\n");
        }
        else
        {
            printf("Rolled again!\n");
        }
        printf("[Dice 1]: %d [Dice 2]: %d\n", dice1, dice2);

        // Hedef tuttu mu? (Ternary operator (? :) kullanılmış)
        int is_hit = (calculate_score(dice1, dice2) == target) ? 1 : 0;

        if (is_hit)
            hits++;
        else
            hits = 0;  // Yine aynı seri bozukluğu kuralı
        
        round_total = hits * target;
        roll_score = is_hit ? target : 0;
        roll_no++;
    }
    printf("My score: %d Total score: %d\n", roll_score, round_total);
    return round_total;
}
```

**Fonksiyonun Amacı:**
Bilgisayarın bir turda kaç puan kazanacağını belirlemek

**Bilgisayar Stratejisi Analizi:**

```c
while (roll_no <= 3 && sum == target - 1)
```

- **sum = target - 1**: Başlangıçta hedefi tutmayan bir değer
- **sum == target - 1 KADAR DÖNGÜYÜ SÜRDÜRMEKTİR**
- Yani: **Bilgisayar hedefi VURDUĞU ANDA DURUR!**

**Örnek:**
```
Target = 5, İlk sum = 4
Atış 1: 2+3=5 → sum=5 (==target-1 değil!) → Döngü durur
Bilgisayar pek çok ama sadece hedefi vurdu!
```

**Vs Kullanıcı (seçme özgürlüğü var):**
```
Kullanıcı: Hedefi vurduğu halde tekrar atmayı tercih edebilir
```

---

### 5️⃣ scoresheet() - Skor Kartı Fonksiyonu

```c
void scoresheet(int comp_total, int user_total)
{
    printf("=============================\n");
    printf("My score    Your score\n");
    printf("%d           %d\n", comp_total, user_total);
}
```

**Fonksiyonun Amacı:**
Geçerli Toplam Skorları görsel olarak göstermek

**Parametreler:**
- `comp_total`: Bilgisayarın toplam puanı (tüm turların toplamı)
- `user_total`: Kullanıcının toplam puanı (tüm turların toplamı)

**Neden void?**
- Sadece ekrana yazdırır, bir değer döndürmez

---

## 🎮 main() Fonksiyonu - Oyun Mantığı

### BÖLÜM 1: Değişkenlerin Tanımlanması

```c
int n;                    // Oynanacak tur sayısı (1-11)
int user_total = 0;       // Kullanıcının toplam puanı
int comp_total = 0;       // Bilgisayarın toplam puanı

// İlk karşılaşma (Kimlerin başlayacağını belirlemek için)
int user_start_d1, user_start_d2;    // Kullanıcının ilk zarları
int comp_start_d1, comp_start_d2;    // Bilgisayarın ilk zarları
int user_start_sum;                  // Kullanıcının ilk toplamı
int comp_start_sum;                  // Bilgisayarın ilk toplamı

// Tur sonuçları
int user_round_score;     // O turdaki kullanıcı puanı
int comp_round_score;     // O turdaki bilgisayar puanı
int round = 1;            // Kaçıncı turda olduğumuz
int user_starts;          // Kullanıcı mı başlayacak? (1=evet/0=hayır)

srand((unsigned int)time(NULL));  // Rastgele sayı üreticisini başlat
```

**srand() Açıklaması:**
- Her program çalışmasında farklı rastgele sayılar üretmek için
- `time(NULL)`: Sistem saatinin saniye sayısını alır
- Bu "seed" olarak kullanılır (kaynak)

---

### BÖLÜM 2: Oyuncu Seçimi (Do-While Döngüsü)

```c
do
{
    comp_start_d1 = roll_a_dice();
    comp_start_d2 = roll_a_dice();
    user_start_d1 = roll_a_dice();
    user_start_d2 = roll_a_dice();

    comp_start_sum = comp_start_d1 + comp_start_d2;
    user_start_sum = user_start_d1 + user_start_d2;

    printf("I have rolled the dice and got %d and %d!\n", comp_start_d1, comp_start_d2);
    printf("I have rolled the dice for you, and you got %d and %d!\n", user_start_d1, user_start_d2);
} while (comp_start_sum == user_start_sum);  // Eşitse tekrar at

user_starts = (user_start_sum > comp_start_sum);  // Kimi tutarsa haklı başlar
```

**Neden Do-While?**
- En az bir kere zarları atmak gerekir (post-test)
- Eğer eşit olursa tekrar atmak gerekir

**Mantık:**
```
Eğer Kullanıcı > Bilgisayar    → user_starts = 1 (true)
Eğer Bilgisayar > Kullanıcı    → user_starts = 0 (false)
```

---

### BÖLÜM 3: Tur Sayısını Alma

```c
do
{
    printf("How many rounds would you like to play? ");
    scanf("%d", &n);

    if (n < 1 || n > 11)
    {
        printf("%d is an invalid number of rounds...\n", n);
    }
} while (n < 1 || n > 11);  // Geçerli giri kadar döngüyü sürüt
```

**Chicago Oyunu Kuralı:**
- Minimum 2 (2+2=4) ile Maksimum 12 (11+1=12) toplamı olmak için
- 1 ile 11 tur oynanabilir

---

### BÖLÜM 4: Ana Oyun Döngüsü (While)

```c
while (round <= n)
{
    int target = round + 1;  // Target her turda 1 artar
                             // Tur 1: target=2
                             // Tur 2: target=3
                             // ...
                             // Tur 11: target=12

    if (user_starts)  // Kullanıcı mı başlayacak?
    {
        // SENARYO A: Kullanıcı → Bilgisayar
        printf("\nRound %d -- Your Turn: (Target = %d)\n", round, target);
        user_round_score = play_user(target);
        user_total += user_round_score;  // Toplam puana ekle

        printf("\nRound %d -- My Turn: (Target = %d)\n", round, target);
        comp_round_score = play_computer(target);
        comp_total += comp_round_score;   // Toplam puana ekle
    }
    else
    {
        // SENARYO B: Bilgisayar → Kullanıcı
        printf("\nRound %d -- My Turn: (Target = %d)\n", round, target);
        comp_round_score = play_computer(target);
        comp_total += comp_round_score;

        printf("\nRound %d -- Your Turn: (Target = %d)\n", round, target);
        user_round_score = play_user(target);
        user_total += user_round_score;
    }

    printf("\nOur scoresheet after round %d:\n", round);
    scoresheet(comp_total, user_total);

    round++;
}
```

**Her Turun Akışı:**
```
1. Target belirlenir (round + 1)
2. Başlayan oyuncu belirlenir
3. Birinci oyuncu oynar → puanı toplam'a eklenir
4. İkinci oyuncu oynar → puanı toplam'a eklenir
5. Skorlar gösterilir
6. Bir sonraki tura geçilir
```

**Why += Operatörü?**
```c
user_total += user_round_score;
// Eşdeğer: user_total = user_total + user_round_score;
```

---

### BÖLÜM 5: Oyun Sonu ve Kazanan Açıklaması

```c
printf("\n");
if (user_total > comp_total)
{
    printf("YOU ARE THE WINNER!!\n");
}
else if (comp_total > user_total)
{
    printf("I AM THE WINNER!!\n");
}
else
{
    printf("NO WINNER FOR THIS GAME!\n");  // Beraberlik
}

return 0;  // Program başarıyla tamamlandı
```

---

## 📊 Örnek Oyun Senaryosu

```
BAŞLANGIÇ: Oyuncu seçimi
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Bilgisayar zarı: 3 + 2 = 5
Kullanıcı zarı:  4 + 4 = 8
Kullanıcı kazanır, başlar.

Tur sayısı: 3 (3 tur oynanacak)

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
TUR 1 - TARGET = 2
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Kullanıcının Sırası (Target=2):
  Atış 1: 1+1=2 ✓ hits=1 puan=2
  Tekrar at mı? Y
  Atış 2: 2+2=4 ✗ KACIRDIK! hits=0 puan=0
  Tekrar at mı? N
  → Bu turdaki puan = 0 (son atış kaçtığı için)
  user_total = 0 + 0 = 0

Bilgisayarın Sırası (Target=2):
  Atış 1: 2+2=4 ✗ Hedefi tutmadı, tekrar at
  Atış 2: 1+1=2 ✓ HEDEFI VURDU! Durur.
  hits=1 puan=2
  → Bu turdaki puan = 2
  comp_total = 0 + 2 = 2

Scoresheet: Bilgisayar=2, Kullanıcı=0

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
TUR 2 - TARGET = 3
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

[Aynı mantık tekrarlanır...]

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
TUR 3 - TARGET = 4
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

[Aynı mantık tekrarlanır...]

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
OYUN SONU
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Final: Bilgisayar=8, Kullanıcı=7

KAZANAN: I AM THE WINNER!!
```

---

## 🎯 Temel Konseptler

### 1. Seri Vuru Sistemi (Cascade Hits)
```
Kurallar:
✓ Hedefi vursan → hits++
✗ Hedefi kaçırsan → hits = 0 (SERİ BOZULUR!)
Skor = hits × target
```

### 2. Pre-Test vs Post-Test Döngüler

**Pre-Test (while):**
```c
while (roll_no <= 3 && choice != 'N')  // Before executing
{
    // Body
}
```
- Koşul yanlışsa hiç çalışmaz

**Post-Test (do-while):**
```c
do
{
    // Body (at least once!)
} while (condition);
```
- En az bir kere çalışır

### 3. Ternary Operator (`? :`)
```c
int roll_score = is_hit ? target : 0;
// Eğer is_hit doğruysa: target
// Eğer is_hit yanlışsa: 0
```

### 4. Rastgele Sayı Üretimi
```c
srand(time(NULL));     // Seed'i ayarla
int random = rand();   // 0 ile RAND_MAX arasında sayı üret
```

---

## 🔍 Kritik Değişken Davranışları

### hits Değişkeni - En Önemli!
```
BAŞLANGICI: hits = 0
PEŞPEŞE VURA VURA: hits++, hits++, hits++...
KAÇIRSAN: hits = 0 (HER ŞEY SIFIRLANıR!)
PUAN: hits × target
```

### choice Değişkeni
```
Y/y: Devam et, bir sonraki atış
N/n: Dur, bu turu bitir
Başlangıç: 'Y' (döngünün en az bir kere çalışması için)
```

### target Değişkemi
```
Tur 1: 2 (1+1)
Tur 2: 3 (2+1)
Tur 3: 4 (3+1)
...
Tur 11: 12 (11+1)

Max Toplam: 2+3+4+5+6+7+8+9+10+11+12 = 77
```

---

## 📝 Kod Yazma Kuralları (Bu Projede Kullanılan)

1. **Fonksiyon prototipi** önce tanımla
2. **Basit fonksiyonları** ihtiyacına göre oluştur
3. **Validasyon döngüsü** kullanıcı girişi için
4. **Anlamlı değişken isimleri** kullan (roll_no, comp_start_d1, vb.)
5. **Yorumlar** yazılmasında bile önemli kodu açıkla

---

## 🚀 Program Çalıştırma Adımları

```bash
# Derleme
gcc main.c -o chicago_game

# Çalıştırma
./chicago_game

# Örnek Input:
# Zar atışından sonra: Y (devam et)
# Tur sayısı: 5
```

---

## 📌 Özet

| Konu | Açıklama |
|------|----------|
| **Amaç** | İnsan vs Bilgisayar zar oyunu |
| **Turlar** | 1-11 arası |
| **Her turda target** | round + 1 |
| **Max puan/tur** | (turlar × target) |
| **Önemli kural** | Kaçırırsan → hits=0 → puan=0 |
| **Bilgisayar strateji** | Hedefi vurduğu anda dur |
| **Kullanıcı strateji** | Seçme özgürlüğü |
| **Kazanan** | En yüksek toplam puan |

---

## 💡 Öğrenilen Konseptler

✅ Fonksiyon yazma ve kullanma  
✅ Döngüler (while, do-while)  
✅ Koşul ifadeleri (if-else)  
✅ Rastgele sayı üretimi  
✅ Değişken türleri (int, char)  
✅ Ternary operator (? :)  
✅ Girdi/Çıktı işlemleri (scanf, printf)  
✅ Oyun mantığı tasarlama  

