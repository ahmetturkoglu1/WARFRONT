# Teknik Notlar

## Motor ve Araçlar

- **Oyun motoru:** Unreal Engine 5 (_alt sürüm belirlenecek_)
- **Programlama dili:** C++ ve Blueprints
- **Mimari:** Sunucu otoriter çok oyunculu
- **Sürüm kontrolü:** Git + GitHub

## Büyük Dosyalar

Unreal Engine varlıkları (`.uasset`, `.umap`) büyük ikili dosyalardır. Proje oluşturulmadan önce
[Git LFS](https://git-lfs.com/) kurulması ve bu dosya türlerinin LFS ile takip edilmesi önerilir.

## Dal (Branch) Stratejisi

- `main` — kararlı sürüm
- Özellik geliştirmeleri için ayrı dallar açılır ve `main`'e birleştirilir.

## Kod Standartları

Unreal Engine'in resmi [kodlama standardı](https://dev.epicgames.com/documentation/en-us/unreal-engine/epic-cplusplus-coding-standard-for-unreal-engine) takip edilecektir.
