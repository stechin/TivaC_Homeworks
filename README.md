# PC Kontrollü Tiva C Veri Toplama ve LCD Yönetim Sistemi

Bu proje, **Tiva C TM4C123GH6PM** mikrodenetleyicisi ile C# (Windows Forms) tabanlı bir PC arayüzü arasında Full-Duplex haberleşme sağlayan bir gömülü sistem uygulamasıdır.

## Proje Özellikleri
- **Çift Yönlü Haberleşme:** UART protokolü üzerinden PC'den Tiva'ya komut, Tiva'dan PC'ye sensör verisi aktarımı.
- **LCD Kontrolü:** PC üzerinden gönderilen saat ve metin verilerinin 2x16 LCD ekrana yazdırılması.
- **Sensör Okuma:** PTC sensörü ile ortam sıcaklık değişiminin 12-bit ADC ile okunması.
- **Durum İzleme:** Kart üzerindeki buton durumunun ve ADC verilerinin C# arayüzünde anlık grafiksel takibi.
- **Zaman Senkronizasyonu:** PC saatinin mikrodenetleyiciye aktarılması ve Timer kesmesi ile yürütülmesi.

## Donanım Listesi
- Tiva C Series TM4C123GH6PM LaunchPad
- 2x16 LCD Ekran (HD44780 Sürücülü)
- PTC Sıcaklık Sensörü (ve 10k Direnç)
- 10k Potansiyometre (LCD Kontrastı için)
- Jumper Kablolar ve Breadboard

## Pin Bağlantı Şeması

| Bileşen | Tiva C Pin | Açıklama |
| :--- | :--- | :--- |
| **LCD RS** | PB0 | Register Select |
| **LCD E** | PB1 | Enable |
| **LCD D4-D7**| PB4-PB7 | 4-bit Veri Yolu |
| **ADC Giriş**| PE3 | Gerilim Bölücü (PTC + Direnç) |
| **Buton** | PF4 | Dahili SW1 Butonu |
| **UART RX** | PA0 | PC'den Veri Alma (Dahili) |
| **UART TX** | PA1 | PC'ye Veri Gönderme (Dahili) |

---
*Bu proje Sakarya Üniversitesi Elektrik-Elektronik Mühendisliği bölümü İleri Mikroişlemciler dersi kapsamında geliştirilmiştir.*
