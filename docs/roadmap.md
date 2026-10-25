# Yol Haritası

Geliştirme küçük ve test edilebilir aşamalara ayrılmıştır. Her aşamanın bir **çıktısı** ve bir
**test ölçütü** vardır. Bir aşama, test ölçütü sağlanmadan tamamlanmış sayılmaz.

Kurallar için bkz. [game-design.md](game-design.md).

---

## Aşama 0 — Hazırlık

- [x] GitHub deposunun oluşturulması
- [x] README, .gitignore ve belge klasörünün eklenmesi
- [x] Oyun tasarım belgesinin kesin kurallarla doldurulması
- [ ] Unreal Engine 5 alt sürümünün belirlenmesi
- [ ] Git LFS kurulumu ve `.uasset`/`.umap` takibi
- [ ] Açık kararlardan ilk prototip için gerekenlerin kesinleştirilmesi

**Test:** Depo klonlanabiliyor, belgeler eksiksiz okunabiliyor.

---

## Aşama 1 — Boş Proje ve Ağ Temeli

- [ ] UE5 C++ projesinin oluşturulması
- [ ] Dedicated (ayrılmış) sunucu derlemesi
- [ ] İki istemcinin aynı sunucuya bağlanması

**Test:** Bir sunucu ve iki istemci aynı haritada birbirini görüyor.

---

## Aşama 2 — Karakter Hareketi ve Kamera

- [ ] Sunucu otoriter karakter hareketi
- [ ] FPS ve TPS kamera

**Test:** İki istemcide hareket senkron; istemcinin hızı değiştirmesi sunucu tarafından engelleniyor.

---

## Aşama 3 — Silah ve Hasar

- [ ] Tek bir silah ile ateş etme
- [ ] Sunucu tarafında isabet ve hasar hesabı
- [ ] Ölüm ve anında yeniden doğma

**Test:** Hasar yalnızca sunucuda hesaplanıyor; ölen oyuncu anında yeniden doğuyor.

---

## Aşama 4 — Kalıcı Hesap ve Karakter

- [ ] Hesap başına tek karakter
- [ ] Karakter verilerinin veritabanına kaydedilmesi

**Test:** Oyuncu çıkıp tekrar girdiğinde karakteri aynı durumda; ikinci karakter oluşturulamıyor.

---

## Aşama 5 — Seviye ve Bonuslar

- [ ] XP ve seviye 1–60
- [ ] Seviye başına hasar, savunma, hız ve isabet bonusları

**Test:** 60. seviyede bonuslar +%35 / +%30 / +%10 / +%20 değerlerine eşit (birim testi).

---

## Aşama 6 — Envanter ve Ekipman

- [ ] Benzersiz kimlikli eşyalar
- [ ] Silah ve zırh parçalarının kuşanılması
- [ ] Zırh kaliteleri (Ranger → Titanium)

**Test:** Eşyalar kimlikleriyle kalıcı; seviye şartı olmadan kuşanılabiliyor.

---

## Aşama 7 — Geliştirme Sistemi

- [ ] +0…+7 geliştirme
- [ ] Kategoriye özel kartlar
- [ ] Başarısızlıkta eşyanın, kartın ve ücretin yok olması

**Test:** Yanlış kategori kartı reddediliyor; başarısızlıkta eşya siliniyor; sonuç yalnızca sunucuda belirleniyor.

---

## Aşama 8 — FRONTIER ve Tek Kışla

- [ ] CITADEL güvenli bölgesi
- [ ] PvP kapalı ortak dünya
- [ ] Bir K1 kışlası: yapay zekâ askerler ve yeniden doğma

**Test:** FRONTIER'da oyuncular birbirine hasar veremiyor; kışla temizlenince yeniden doğuyor.

---

## Aşama 9 — Kışla Sandığı ve Dağıtım

- [ ] Katkı takibi
- [ ] Tek ortak sandık
- [ ] Klan deposuna veya zar sistemiyle dağıtım
- [ ] Eşyaların +0 çıkması

**Test:** Sandığı en fazla katkı veren takım alıyor; birden fazla takım aynı kışlada savaşabiliyor.

---

## Aşama 10 — Merkezi Market

- [ ] Markete eşya satma
- [ ] Yalnızca stoktaki gerçek eşyaların satın alınması
- [ ] Sistem fiyatları

**Test:** Stok sıfırken satın alma reddediliyor; satılan eşya aynı kimlik ve geliştirme seviyesiyle geri alınıyor.

---

## Aşama 11 — Partiler ve WARZONE 7v7

- [ ] En fazla 7 kişilik parti
- [ ] 7v7 bölge hakimiyeti
- [ ] PvP K/D ve onur sıralaması

**Test:** 14 oyunculu maç tamamlanıyor; yapay zekâ öldürmeleri K/D'ye eklenmiyor; ölümde eşya kaybı yok.

---

## Aşama 12 — Klanlar

- [ ] En fazla 21 üye
- [ ] Klan deposu, yetkiler ve işlem kayıtları

**Test:** 22. üye eklenemiyor; depo işlemleri kayıtlara yazılıyor.

---

## Aşama 13 — Kışlaların Tamamı ve +7 Kartı

- [ ] 35 kışla (K1–K7)
- [ ] K7'de %0,5 ihtimalli +7 kartı

**Test:** Simülasyonda +7 kartı yalnızca K7'den ve yaklaşık %0,5 oranında çıkıyor.

---

## Aşama 14 — Araçlar ve Garaj

- [ ] Geliştirilebilir araçlar
- [ ] Garaj sistemi

**Test:** Araç garajda saklanıyor ve geliştirmesi kalıcı.

---

## Aşama 15 — Denge Testleri

- [ ] Seviye 60 +7 Titanium oyuncu ile 3 seviye 10 oyuncu arasındaki karşılaşmalar
- [ ] Ekonomi ve geliştirme oranlarının ayarlanması

**Test:** Güçlü oyuncu çoğunlukla kazanıyor, koordineli üç oyuncu da kazanabiliyor.
