# Oyun Tasarım Belgesi (GDD)

Bu belge WARFRONT'un **kesinleşmiş** oyun kurallarını içerir. Sayısal değerleri veya ayrıntıları henüz
belirlenmemiş konular kesin karar olarak yazılmaz; bunlar
[Dengeleme ve Açık Kararlar](#11-dengeleme-ve-açık-kararlar) bölümünde toplanır.

---

## 1. Genel Bakış

| Başlık | Karar |
|--------|-------|
| Oyun adı | WARFRONT |
| Tür | Modern askeri FPS/TPS + RPG ilerleme sistemi |
| Dünyalar | **FRONTIER** (ortak açık dünya, PvE) ve **WARZONE** (PvP) |
| Karakter | Hesap başına yalnızca **bir** kalıcı karakter |
| Maksimum seviye | **60** |
| Görev sistemi | **Yok** |
| Oyun motoru | Unreal Engine 5 (C++ ve Blueprints) |
| Mimari | Sunucu otoriter çok oyunculu |

---

## 2. Karakter ve İlerleme

### 2.1 Kalıcı Karakter

- Her hesabın yalnızca bir kalıcı karakteri vardır.
- Karakter seviyesi, envanteri ve ilerlemesi sunucuda kalıcı olarak saklanır.

### 2.2 Seviye Bonusları

Karakter her seviyede şu dört özellikte bonus kazanır: **hasar, savunma, hareket hızı ve mermi isabeti**.

60. seviyede ulaşılacak hedef toplam bonuslar:

| Özellik | 60. seviyede hedef bonus |
|---------|--------------------------|
| Hasar | +%35 |
| Savunma | +%30 |
| Hareket hızı | +%10 |
| Mermi isabeti | +%20 |

### 2.3 Seviye Atlama Zorluğu

| Seviye aralığı | Zorluk |
|----------------|--------|
| 1–10 | Kolay |
| 10–25 | Orta |
| 25–45 | Zor |
| 45–55 | Çok zor |
| 55–60 | En zor |

### 2.4 Ekipman ve Seviye

- Ekipman kullanımı için **seviye şartı yoktur**. Her oyuncu her ekipmanı kullanabilir.

### 2.5 Görevler

- Oyunda **görev sistemi yoktur**. İlerleme; kışlalar, PvP ve ekipman geliştirme üzerinden sağlanır.

---

## 3. Dünya 1 — FRONTIER (PvE)

### 3.1 Genel Kurallar

- Bütün oyuncuların bulunduğu **ortak açık dünyadır**.
- **PvP kapalıdır.**
- Merkezde güvenli şehir **CITADEL** bulunur.

### 3.2 Kışlalar

Toplam **35** kışla vardır:

| Kademe | Kışla sayısı |
|--------|--------------|
| K1 | 8 |
| K2 | 7 |
| K3 | 6 |
| K4 | 5 |
| K5 | 4 |
| K6 | 3 |
| K7 | 2 |
| **Toplam** | **35** |

- Kışlalar **tarafsızdır**: hiçbir klana ait olmaz.
- Kışlalar tamamlandıktan sonra **yeniden doğar**.
- Kışlalar özel oturumlara (instance) **ayrılmaz**. Herkes aynı fiziksel kışlaya katılabilir.

### 3.3 Kışla Ödülleri

- Tamamlanan her kışladan **yalnızca bir ortak sandık** çıkar.
- Sandığı **en fazla katkı sağlayan takım** kazanır.
- Sandık içeriğinin dağıtımı:
  - **Klan baskını:** eşyalar **klan deposuna** gider.
  - **Bağımsız parti:** eşyalar **zar sistemiyle** oyunculara dağıtılır.
- Kışladan çıkan bütün silah ve zırhlar **+0** seviyesindedir.
- **+7 geliştirme kartı** yalnızca **K7** kışlalarından çıkar. Her ana ödül yuvasında çıkma ihtimali **%0,5**'tir.

### 3.4 Kışla Tablosu

Her kışlanın asker sayısı ve yeniden doğma süresi, mevcut tasarım kararlarına göre ayrı bir tabloda
belirlenecektir (bkz. [Açık Kararlar](#11-dengeleme-ve-açık-kararlar)).

---

## 4. Dünya 2 — WARZONE (PvP)

### 4.1 Genel Kurallar

- PvP savaşları en fazla **7 kişilik partilerle** oynanır.
- Klan üyeliği **zorunlu değildir**.
- Oyuncular istedikleri kişilerle parti kurabilir.

### 4.2 İlk Mod: 7v7 Bölge Hakimiyeti

- İlk oynanabilir mod **7v7 bölge hakimiyetidir**.
- Ölen oyuncu **anında yeniden doğar**.
- PvP ölümünde **eşya kaybı yoktur**.

### 4.3 İstatistik ve Sıralama

- Yapay zekâ öldürmeleri PvP **K/D oranına dahil edilmez**.
- **PvP onur sıralaması** diğer istatistiklerden ayrı tutulur.

---

## 5. Ekipman ve Geliştirme

### 5.1 Geliştirilebilir Ekipman

- Silahlar, kask, yelek, pantolon, ayakkabı ve diğer geliştirilebilir ekipmanlar **+0 ile +7** arasında
  geliştirilebilir.

### 5.2 Zırh Kaliteleri

| Sıra | Kalite | Malzeme |
|------|--------|---------|
| 1 | Ranger | Deri |
| 2 | Vanguard | Bronz |
| 3 | Phantom | Gümüş |
| 4 | Imperial | Altın |
| 5 | Titanium | Titanyum |

- Zırhın **kalitesi** ve **geliştirme seviyesi** uzaktan görsel olarak ayırt edilebilir.

### 5.3 Geliştirme Kartları

- Geliştirme kartları **ekipman kategorisine özeldir**. Örneğin bir silah kartı zırhta kullanılamaz.
- Geliştirme **başarısız olursa**:
  - Geliştirilen eşya **tamamen yok olur**.
  - Kart ve geliştirme ücreti **tüketilir**.

### 5.4 Güç Dengesi Hedefi

- Seviye 60 ve tam **+7 Titanium** ekipmanlı bir oyuncu, **üç adet seviye 10 ve başlangıç ekipmanlı**
  oyuncuya karşı güçlü olmalıdır.
- Buna rağmen **koordineli üç oyuncunun kazanması mümkün** olmalıdır.
- Bu denge **oyun testleriyle doğrulanacaktır**.

---

## 6. Ekonomi

### 6.1 Merkezi Market

- Oyuncular arasında **pazar kurmak yoktur**.
- Bir **merkezi market** bulunur.
- Oyuncular eşyalarını markete satar.
- Market **yalnızca oyuncuların sattığı gerçek eşyaları** stoklar ve yeniden satar. Market yoktan eşya üretmez.
- Alış ve satış fiyatlarını **sistem belirler**.
- Bir ürünün stoğu **sıfırsa satın alınamaz**.

### 6.2 Eşya Bütünlüğü

- Markete satılan ve marketten alınan eşyaların **geliştirme seviyesi** ve **benzersiz kimliği** korunur.

### 6.3 Sunucu Doğrulaması

- Market, envanter ve geliştirme işlemleri **sunucu tarafından doğrulanır**. İstemci bu işlemlerin
  sonucunu belirleyemez.

---

## 7. Klanlar

- Klanlar en fazla **21 üyelidir**.
- Klan üyeliği PvP veya kışlalar için **zorunlu değildir**.
- Her klanın şunları olacaktır:
  - **Klan deposu**
  - **Yetki sistemi**
  - **İşlem kayıtları**

---

## 8. Araçlar

- Araçlar **geliştirilebilir**.
- Bir **garaj sistemi** bulunacaktır.

---

## 9. Teknik Gereksinimler

- Hedef oyun motoru: **Unreal Engine 5**
- Diller: **C++ ve Blueprints**
- **Sunucu otoriter** çok oyunculu mimari
- **Kalıcı** hesap, envanter, ekonomi ve ilerleme verileri
- Ayrıntılar: [technical.md](technical.md)

---

## 10. Kapsam Dışı

Aşağıdakiler kesin kararlar gereği oyunda **bulunmaz**:

- Hesap başına birden fazla karakter
- Görev sistemi
- Ekipman için seviye şartı
- FRONTIER'da PvP
- Klanlara ait kışlalar ve özel kışla oturumları
- Oyuncular arası pazar veya doğrudan ticaret pazarı
- PvP ölümünde eşya kaybı

---

## 11. Dengeleme ve Açık Kararlar

Bu bölümdeki konular **henüz kesinleşmemiştir**. Değerler belirlendikçe ilgili bölüme taşınacaktır.

### 11.1 İlerleme

- [ ] Seviye başına bonusların dağılımı: 60. seviyedeki hedefe doğrusal mı yoksa eğri ile mi ulaşılacak?
- [ ] Seviye başına gereken deneyim puanı (XP) değerleri.
- [ ] Zorluk aralıklarının sınır seviyeleri (10, 25, 45 ve 55. seviyeler hangi aralığa dahil?).
- [ ] Deneyim kaynakları ve oranları (kışla, PvP vb.).
- [ ] FPS/TPS kamera seçimi: oyuncu serbestçe mi değiştirecek, yoksa duruma göre mi?

### 11.2 Kışlalar

- [ ] Her kışlanın asker sayısı ve yeniden doğma süresi (ayrı tablo).
- [ ] Kışla kademelerine (K1–K7) giriş için seviye önerisi veya şartı olacak mı?
- [ ] Katkının nasıl ölçüleceği (hasar, öldürme, iyileştirme vb.) ve eşitlik durumunda kazanan.
- [ ] Sandık içeriği ve ana ödül yuvası sayısı.
- [ ] K1–K6'dan çıkan geliştirme kartlarının türleri ve ihtimalleri.
- [ ] Zar sisteminin kuralları (ihtiyaç/açgözlülük, otomatik dağıtım vb.).
- [ ] Klan üyeleri ile klansız oyuncuların aynı takımda olması durumunda sandığın nereye gideceği.

### 11.3 Ekipman ve Geliştirme

- [ ] Her seviye (+1…+7) için geliştirme başarı oranları ve ücretleri.
- [ ] Hangi kartın hangi seviyeye geliştirdiği (+7 kartı dışındakiler).
- [ ] Zırh kalitelerinin ve geliştirme seviyelerinin istatistik değerleri.
- [ ] "Diğer geliştirilebilir ekipmanlar"ın tam listesi.
- [ ] Kalite ve seviyenin görsel olarak nasıl gösterileceği (renk, efekt, parlama vb.).
- [ ] Başlangıç ekipmanının içeriği.

### 11.4 PvP

- [ ] 7v7 bölge hakimiyeti kuralları: bölge sayısı, puan, maç süresi, kazanma koşulu.
- [ ] Eşleştirme kuralları (seviye/ekipman farkı, parti büyüklüğü).
- [ ] Onur sıralamasının hesaplanması ve ödülleri.
- [ ] Yeniden doğma noktaları ve doğma koruması.

### 11.5 Ekonomi

- [ ] Sistem fiyatlarının belirlenme formülü (stok, talep, kalite ve geliştirme seviyesine göre).
- [ ] Para birimi ve para kaynakları.
- [ ] Market stoğu için üst sınır olacak mı?

### 11.6 Klanlar ve Araçlar

- [ ] Klan rol ve yetki seviyeleri.
- [ ] Klan deposu kapasitesi.
- [ ] Araç türleri, geliştirme kuralları ve garaj kapasitesi.
- [ ] Araçların FRONTIER ve WARZONE'da kullanımı.

### 11.7 Denge Testleri

- [ ] "Seviye 60 +7 Titanium oyuncuya karşı 3 seviye 10 oyuncu" senaryosu için test yöntemi ve başarı ölçütü
  (örneğin kazanma oranı aralığı).
