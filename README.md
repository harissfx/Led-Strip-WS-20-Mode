
# 🌈 Arduino WS2812B LED Strip - Multi Mode Effects

Proyek Arduino untuk mengontrol LED Strip WS2812B dengan 20 efek visual yang keren dan menarik. Cocok untuk dekorasi, project DIY, atau belajar pemrograman Arduino.

![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

## ✨ Fitur

- **20 Mode Efek Visual** yang berbeda dan keren
- **Auto Mode Change** - berganti otomatis setiap 15 detik
- **Manual Mode Switch** - ganti mode dengan tombol
- **Customizable** - mudah dimodifikasi dan dikembangkan
- **Serial Monitor** - info mode aktif real-time
- **Optimized** - dirancang untuk 11 LED (bisa disesuaikan)

## 🎨 Daftar Efek

| No | Nama Efek | Deskripsi |
|---|---|---|
| 0 | Color Wipe | Mengisi LED berurutan dengan warna merah |
| 1 | Rainbow | Seluruh strip menampilkan warna pelangi |
| 2 | Rainbow Cycle | Pelangi yang bergerak sepanjang strip |
| 3 | Theater Chase | Efek lampu teater klasik |
| 4 | Fade In Out | Warna merah yang memudar masuk/keluar |
| 5 | Color Bounce | Warna kuning memantul dari ujung ke ujung |
| 6 | Sparkle | LED berkedip acak seperti bintang |
| 7 | Fire Effect | Simulasi api yang realistis |
| 8 | Meteor Rain | Efek hujan meteor dengan trail |
| 9 | Twinkle | LED berkelip-kelip acak |
| 10 | Running Lights | Cahaya bergerak seperti ombak |
| 11 | Color Chase | Warna cyan mengejar sepanjang strip |
| 12 | Breathing Effect | Efek bernapas lembut warna hijau |
| 13 | Police Strobe | Simulasi lampu polisi merah-biru |
| 14 | Rainbow Pulse | Pelangi yang berdenyut |
| 15 | Larson Scanner | Efek KITT dari Knight Rider |
| 16 | Color Waves | Gelombang warna yang mengalir |
| 17 | Random Burst | Ledakan warna acak |
| 18 | Dual Color Chase | Dua warna saling kejar |
| 19 | Stroboscope | Efek strobo putih |

## 🛠️ Hardware yang Dibutuhkan

- Arduino (Uno/Nano/Mega/dll)
- LED Strip WS2812B (11 LED atau sesuaikan)
- Power Supply 5V (minimal 2A untuk 11 LED)
- Push Button (opsional, untuk ganti mode manual)
- Resistor 10kΩ (untuk pull-up button, opsional jika pakai INPUT_PULLUP)
- Kabel jumper
- Breadboard (opsional)

## 📐 Wiring Diagram

```
Arduino          WS2812B LED Strip
  5V    -------> VCC (5V)
  GND   -------> GND
  D6    -------> DIN (Data In)

Arduino          Push Button (Opsional)
  D2    -------> Button Terminal 1
  GND   -------> Button Terminal 2
```

### Catatan Penting:
- Gunakan power supply eksternal untuk LED strip (jangan dari Arduino!)
- Hubungkan GND Arduino dengan GND power supply
- Untuk strip panjang (>30 LED), gunakan kapasitor 1000µF di jalur power
- Tambahkan resistor 330Ω antara pin D6 Arduino dan DIN LED strip

## 📦 Library yang Dibutuhkan

Install library berikut melalui Arduino IDE Library Manager:

```
Adafruit NeoPixel by Adafruit
```

**Cara Install:**
1. Buka Arduino IDE
2. Pergi ke `Sketch` → `Include Library` → `Manage Libraries`
3. Cari "Adafruit NeoPixel"
4. Klik `Install`

## 🚀 Cara Menggunakan

### 1. Upload Kode

```bash
# Clone repository (jika dari Git)
git clone <repository-url>

# Atau download file .ino dan buka di Arduino IDE
```

### 2. Konfigurasi

Edit bagian konfigurasi di awal kode sesuai kebutuhan:

```cpp
#define LED_PIN     6      // Pin data LED strip
#define LED_COUNT   11     // Jumlah LED di strip Anda
#define BRIGHTNESS  100    // Kecerahan (0-255)
#define BUTTON_PIN  2      // Pin tombol (opsional)
```

### 3. Upload ke Arduino

1. Hubungkan Arduino ke komputer via USB
2. Pilih board dan port yang sesuai di Arduino IDE
3. Klik tombol `Upload` (→)
4. Tunggu hingga upload selesai

### 4. Monitoring

Buka Serial Monitor (`Ctrl + Shift + M`) dengan baud rate **9600** untuk melihat mode aktif.

## ⚙️ Kustomisasi

### Mengubah Kecepatan Pergantian Mode

```cpp
const long modeInterval = 15000;  // 15 detik
// Ubah menjadi:
const long modeInterval = 30000;  // 30 detik
```

### Menonaktifkan Auto Mode

Hapus atau comment bagian ini di `loop()`:

```cpp
// if (millis() - lastModeChange > modeInterval) {
//   currentMode = (currentMode + 1) % totalModes;
//   lastModeChange = millis();
// }
```

### Menambah Efek Baru

1. Buat fungsi efek baru:

```cpp
void myCustomEffect() {
  // Kode efek Anda
  for(int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 255, 0, 255);  // Magenta
    strip.show();
    delay(50);
  }
}
```

2. Tambahkan ke `totalModes`:

```cpp
const int totalModes = 21;  // Tambah 1
```

3. Tambahkan case di `runMode()`:

```cpp
case 20: myCustomEffect(); break;
```

### Mengubah Warna Efek

Contoh mengubah warna Color Wipe dari merah ke biru:

```cpp
// Sebelum:
case 0: colorWipe(strip.Color(255, 0, 0), 100); break;

// Sesudah:
case 0: colorWipe(strip.Color(0, 0, 255), 100); break;
```

Format warna: `strip.Color(Red, Green, Blue)` dengan nilai 0-255.

## 🎯 Tips & Trik

### Hemat Daya
```cpp
strip.setBrightness(50);  // Kurangi brightness
```

### Efek Lebih Cepat/Lambat
Ubah parameter `wait` atau `delay` di setiap fungsi efek.

### Mode Random
Tambahkan di `loop()`:

```cpp
currentMode = random(0, totalModes);
```

### Kombinasi Efek
Buat fungsi yang menggabungkan beberapa efek:

```cpp
void comboEffect() {
  sparkle(255, 255, 255, 30);
  fadeInOut(255, 0, 0, 5);
}
```

## 📊 Konsumsi Daya

Estimasi konsumsi daya (untuk 11 LED):

| Brightness | Arus per LED | Total (11 LED) |
|-----------|--------------|----------------|
| 100% (255) | ~60mA | ~660mA |
| 50% (128) | ~30mA | ~330mA |
| 25% (64) | ~15mA | ~165mA |

**Rekomendasi:** Gunakan power supply minimal 2A untuk keamanan.

## 🐛 Troubleshooting

### LED Tidak Menyala
- ✅ Cek koneksi power supply
- ✅ Pastikan GND Arduino dan power supply terhubung
- ✅ Periksa pin data (default D6)
- ✅ Cek apakah LED strip sudah terhubung dengan benar (perhatikan arah: DIN bukan DOUT)

### Warna Tidak Sesuai
```cpp
// Coba ubah di setup():
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);
// Atau:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
```

### LED Berkedip/Glitch
- Tambahkan kapasitor 1000µF di jalur power
- Tambahkan resistor 330Ω di jalur data
- Gunakan kabel data yang lebih pendek

### Tombol Tidak Berfungsi
- Pastikan pin button benar (default D2)
- Cek koneksi button ke GND
- Pastikan menggunakan `INPUT_PULLUP`

## 📚 Referensi

- [Adafruit NeoPixel Library](https://github.com/adafruit/Adafruit_NeoPixel)
- [WS2812B Datasheet](https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf)
- [Arduino Reference](https://www.arduino.cc/reference/en/)

## 🤝 Kontribusi

Kontribusi selalu welcome! Silakan:

1. Fork repository ini
2. Buat branch fitur (`git checkout -b fitur-baru`)
3. Commit perubahan (`git commit -m 'Tambah fitur baru'`)
4. Push ke branch (`git push origin fitur-baru`)
5. Buat Pull Request

## 📝 To-Do List

- [ ] Tambah kontrol via Serial Command
- [ ] Integrasi dengan sensor suara
- [ ] Mode musik reaktif
- [ ] Simpan mode terakhir ke EEPROM
- [ ] Web interface via ESP8266/ESP32
- [ ] Kontrol via Bluetooth/WiFi

## 📄 Lisensi

Project ini menggunakan lisensi MIT. Lihat file `LICENSE` untuk detail.

## 👨‍💻 Author

Dibuat dengan ❤️ untuk komunitas Arduino Indonesia

---

**⭐ Jika project ini membantu, jangan lupa kasih star!**

**💬 Ada pertanyaan? Buka issue di GitHub!**

## 📸 Gallery

```
Mode 1: Rainbow           Mode 7: Fire Effect       Mode 15: Larson Scanner
████████████              🔥🔥🔥🔥🔥🔥🔥           ●→→→○○○○○○○

Mode 13: Police Strobe    Mode 8: Meteor Rain      Mode 6: Sparkle
🔴🔴🔴🔴🔴🔵🔵🔵🔵🔵          ☄️→→→→○○○○○○          ✨○○✨○○○✨○○
```


---

**Happy Coding! 🚀**
```
