# Pertemuan 5: Sensor Suhu & Kelembaban (DHT22)

## Mata Kuliah Mikrokontroller - Prodi Informatika Unmul

> **"Feel the Environment — Your ESP32 Can Sense Temperature & Humidity!"** 🌡️

---

## 📋 Informasi Pertemuan

- **Durasi**: 3 × 50 menit (150 menit)
- **Tipe**: Teori + Praktikum Hardware
- **Prerequisites**: Pertemuan 1-4 (GPIO, Digital/Analog I/O, PWM, Serial Communication)
- **Deliverable**: Video demo sistem monitoring suhu + LED indikator + screenshot Serial Monitor
- **Batas Waktu**: 1 minggu setelah pertemuan

---

## 🎯 Tujuan Pembelajaran

Setelah pertemuan ini, mahasiswa mampu:

1. **Memahami** perbedaan sensor analog dan sensor digital
2. **Menjelaskan** cara kerja sensor DHT22 dan protokol komunikasi 1-Wire
3. **Menginstalasi** dan menggunakan library Adafruit DHT Sensor
4. **Membaca** data suhu dan kelembaban dari DHT22 via ESP32
5. **Menerapkan** error handling (`isnan()`) untuk pembacaan sensor
6. **Mengimplementasikan** LED indikator berdasarkan rentang suhu

---

## 📖 Outline Materi

### **Bagian 1: Teori Sensor Suhu & Kelembaban (50 menit)**

1. Sensor Analog vs Sensor Digital
2. Mengenal DHT22 (AM2302)
3. DHT22 vs DHT11: Perbandingan
4. Protokol Komunikasi 1-Wire (Single-Bus)
5. Cara Membaca Datasheet Sensor
6. Error Handling pada Sensor Digital

### **Bagian 2: Persiapan Hardware & Library (20 menit)**

7. Instalasi Library Adafruit DHT
8. Wiring DHT22 ke ESP32
9. Pull-up Resistor: Mengapa Dibutuhkan?

### **Bagian 3: Praktikum Hardware (80 menit)**

10. Praktikum 1: Baca Suhu & Kelembaban Dasar
11. Praktikum 2: Error Handling + Output Terformat
12. Praktikum 3: LED Indikator Suhu (3 Warna)
13. Project Akhir: Sistem Monitoring Lengkap

---

# BAGIAN 1: TEORI SENSOR SUHU & KELEMBABAN (50 menit)

## 1️⃣ Sensor Analog vs Sensor Digital

### **Review: Jenis Sensor**

Sensor bisa dikategorikan berdasarkan **output signal**:

| Aspek | Sensor Analog | Sensor Digital |
|---|---|---|
| **Output** | Tegangan analog (0V-3.3V) | Data digital (bit 0 dan 1) |
| **Membaca** | `analogRead()` → nilai 0-4095 | Library khusus → nilai langsung |
| **Contoh** | Potensiometer, LDR, LM35 | DHT22, DS18B20, BMP280 |
| **Akurasi** | Tergantung ADC (12-bit di ESP32) | Sudah dikalibrasi di IC sensor |
| **Noise** | Rentan noise di kabel panjang | Tahan noise (data digital) |
| **Konversi** | Manual: voltage → suhu (rumus) | Langsung: panggil `readTemperature()` |

---

### **Contoh Sensor Analog: LM35**

```
Sensor LM35:
- Output: 10mV per °C
- Range: 0°C - 150°C
- Contoh: 28°C → output 280mV (0.28V)
- Perlu rumus manual: suhu = (voltage / 0.01)
```

**Masalah sensor analog:**

- ❌ Noise dari kabel panjang
- ❌ Akurasi terbatas oleh resolusi ADC
- ❌ Tidak bisa baca kelembaban (cuma suhu)

---

### **Contoh Sensor Digital: DHT22**

```
Sensor DHT22:
- Output: Data digital via protokol 1-Wire
- Range Suhu: -40°C sampai +80°C
- Range Kelembaban: 0% - 100% RH
- Hasil langsung: suhu = 28.50°C, kelembaban = 65.0%
- Sudah dikalibrasi di pabrik!
```

**Keunggulan sensor digital:**

- ✅ Data sudah dikalibrasi dan akurat
- ✅ Tahan noise (transmisi digital)
- ✅ Bisa baca 2 data sekaligus (suhu + kelembaban)
- ✅ Mudah dipakai (tinggal panggil library)

---

## 2️⃣ Mengenal DHT22 (AM2302)

### **Apa itu DHT22?**

> **DHT22** (juga dikenal sebagai **AM2302**) adalah sensor digital yang mampu mengukur **suhu** dan **kelembaban udara** sekaligus dalam satu komponen.

### **Fisik DHT22**

```
          ┌─────────────┐
          │             │
          │    DHT22    │
          │   ┌─────┐   │
          │   │ IC   │   │
          │   └─────┘   │
          │             │
          └──┬──┬──┬──┬─┘
             │  │  │  │
            (1)(2)(3)(4)
             │  │  │  │
            VCC DATA NC GND
             │  │     │
            3V3 │    GND
                │
           GPIO + Pull-up 10kΩ
```

**Pin DHT22 (4 pin):**

| Pin | Nama | Fungsi | Hubungkan ke |
|-----|------|--------|-------------|
| 1 | VCC | Power supply | ESP32 **3V3** |
| 2 | DATA | Data signal (1-Wire) | ESP32 GPIO + pull-up 10kΩ ke 3V3 |
| 3 | NC | Not Connected | Tidak dipakai |
| 4 | GND | Ground | ESP32 **GND** |

> ⚠️ **PERHATIAN**: Beberapa modul DHT22 hanya punya **3 pin** (VCC, DATA, GND) karena pin NC sudah dihilangkan dan resistor pull-up **sudah terpasang** di dalam modul. Cek modul kamu — jika ada 3 pin, kamu **tidak** perlu tambah resistor pull-up eksternal!

---

### **Spesifikasi Teknis DHT22**

| Parameter | Nilai |
|---|---|
| **Tegangan Kerja** | 3.3V - 5V |
| **Range Suhu** | -40°C s/d +80°C |
| **Akurasi Suhu** | ±0.5°C |
| **Resolusi Suhu** | 0.1°C |
| **Range Kelembaban** | 0% - 100% RH |
| **Akurasi Kelembaban** | ±2-5% RH |
| **Resolusi Kelembaban** | 0.1% RH |
| **Sampling Period** | Min. 2 detik antar pembacaan |
| **Arus Operasi** | 1-1.5 mA (saat membaca), 40-50 µA (standby) |
| **Protokol** | Single-bus (1-Wire proprietary) |

> 📌 **Sampling Period 2 Detik**: DHT22 membutuhkan **minimal 2 detik** antar setiap pembacaan. Jika kamu baca terlalu cepat (misal setiap 500ms), sensor akan **mengembalikan data lama** atau **error**! Ini alasan kenapa kita pakai `delay(2000)` di kode.

---

## 3️⃣ DHT22 vs DHT11: Perbandingan

| Parameter | DHT11 | **DHT22** |
|---|---|---|
| **Harga** | ~Rp 10.000 | ~Rp 35.000 |
| **Range Suhu** | 0°C - 50°C | **-40°C s/d +80°C** ✅ |
| **Akurasi Suhu** | ±2°C | **±0.5°C** ✅ |
| **Range Kelembaban** | 20% - 90% | **0% - 100%** ✅ |
| **Akurasi Kelembaban** | ±5% | **±2-5%** ✅ |
| **Resolusi** | Integer (1°C) | **0.1°C** ✅ |
| **Sampling Rate** | 1 detik | **2 detik** |
| **Warna** | Biru | Putih |
| **Best For** | Budget ketat, penggunaan indoor | Akurasi tinggi, range luas |

### **Kapan Pakai DHT11?**

- ✅ Budget terbatas (murah 3× lipat)
- ✅ Tidak butuh akurasi tinggi (misalnya hanya untuk indikator "panas/dingin")
- ✅ Hanya butuh monitoring indoor (ruangan AC, 20-35°C)

### **Kapan Pakai DHT22?**

- ✅ Butuh akurasi tinggi (lab, data logging)
- ✅ Monitoring outdoor (suhu bisa minus atau >50°C)
- ✅ Butuh resolusi desimal (28.5°C, bukan cuma 28°C atau 29°C)
- ✅ Kelembaban range luas (greenhouse, server room)

> 💡 **Di course ini kita pakai DHT22** karena akurasi lebih tinggi dan resolusi desimal — cocok untuk belajar sensor digital dengan data yang lebih detail.

---

## 4️⃣ Protokol Komunikasi 1-Wire (Single-Bus)

### **Mengapa Disebut "1-Wire"?**

DHT22 berkomunikasi dengan ESP32 hanya menggunakan **1 kabel data**. Tidak ada clock terpisah seperti I2C atau SPI.

> ⚠️ **Catatan Penting**: Protokol "1-Wire" di DHT22 **BUKAN** protokol Dallas 1-Wire (yang dipakai DS18B20). Ini adalah protokol **proprietary** milik sensor DHT — nama "1-Wire" hanya merujuk bahwa komunikasi lewat **satu kabel data**, bukan standar jaringan Dallas.

---

### **Cara Kerja Komunikasi DHT22**

Proses pembacaan data dari DHT22 terdiri dari 3 tahap:

```
  ESP32 (Host)               DHT22 (Sensor)
      │                          │
      │  1. START SIGNAL         │
      │  ──── LOW 1ms ────►     │  ESP32 tarik DATA LOW minimal 1ms
      │  ──── HIGH ────►        │  ESP32 lepas DATA (HIGH via pull-up)
      │                          │
      │  2. RESPONSE SIGNAL      │
      │  ◄──── LOW 80µs ────    │  DHT22 tarik LOW 80µs
      │  ◄──── HIGH 80µs ────   │  DHT22 tarik HIGH 80µs
      │                          │
      │  3. DATA (40 bit)        │
      │  ◄──── 40 bits ────     │  DHT22 kirim 40 bit data
      │                          │
```

### **Format Data 40 Bit**

DHT22 mengirim total **40 bit** (5 byte) data:

```
Byte 1: Kelembaban (integer part, high byte)
Byte 2: Kelembaban (decimal part, low byte)
Byte 3: Suhu (integer part, high byte)
Byte 4: Suhu (decimal part, low byte)
Byte 5: Checksum (sum of byte 1-4, low 8 bit)
```

**Contoh Raw Data:**

```
Data diterima: 02 8C 01 5E 27

Byte 1-2: 0x028C = 652  → Kelembaban = 652 / 10 = 65.2%
Byte 3-4: 0x015E = 350  → Suhu = 350 / 10 = 35.0°C
Byte 5:   0x27   = 39   → Checksum = (02 + 8C + 01 + 5E) & 0xFF = 0x27 ✓
```

### **Encoding Bit "0" dan "1"**

DHT22 membedakan bit 0 dan bit 1 berdasarkan **durasi HIGH signal**:

```
Bit "0":  LOW 50µs → HIGH 26-28µs (pendek → bit 0)
Bit "1":  LOW 50µs → HIGH 70µs    (panjang → bit 1)
```

> 💡 **Untungnya** kita tidak perlu mengimplementasikan semua timing ini secara manual. Library **Adafruit DHT** mengurus semua timing dan parsing data secara otomatis!

---

### **Checksum: Error Detection**

Byte 5 digunakan sebagai checksum untuk mendeteksi error:

```
Checksum valid jika:
  Byte5 == (Byte1 + Byte2 + Byte3 + Byte4) & 0xFF

Jika checksum TIDAK valid → data korup → library return NaN
```

Ini penting karena noise elektromagnetik bisa mengganggu transmisi data, terutama jika kabel data terlalu panjang (>10 meter).

---

## 5️⃣ Cara Membaca Datasheet Sensor

### **Mengapa Datasheet Penting?**

> **Datasheet** adalah dokumen resmi dari manufacturer yang berisi semua spesifikasi teknis komponen. Sebagai engineer, kamu **harus** bisa membaca datasheet!

### **Informasi Penting di Datasheet DHT22:**

| Section | Informasi | Contoh DHT22 |
|---|---|---|
| **Electrical Characteristics** | Tegangan, arus | 3.3V-5V, 1-1.5mA |
| **Measuring Range** | Range pengukuran | -40°C s/d 80°C |
| **Accuracy** | Akurasi | ±0.5°C |
| **Timing Diagram** | Timing komunikasi | Start signal, response, data |
| **Pinout** | Urutan pin | VCC, DATA, NC, GND |
| **Application Circuit** | Rangkaian contoh | Pull-up resistor 10kΩ |

### **Tips Membaca Datasheet:**

1. **Baca section "Absolute Maximum Ratings"** → Jangan melebihi batas ini!
2. **Cek "Application Circuit"** → Ikuti rangkaian yang direkomendasikan
3. **Perhatikan "Typical" vs "Maximum"** → Nilai typical adalah kondisi normal
4. **Cek "Sampling Period"** → Interval minimum antar pembacaan

**Link Datasheet DHT22:**

- [Sparkfun DHT22 Datasheet (PDF)](https://www.sparkfun.com/datasheets/Sensors/Temperature/DHT22.pdf)

---

## 6️⃣ Error Handling pada Sensor Digital

### **Mengapa Perlu Error Handling?**

Sensor bisa gagal membaca karena berbagai alasan:

| Penyebab | Gejala | Solusi |
|---|---|---|
| **Kabel putus/lepas** | Return `NaN` | Cek wiring |
| **Baca terlalu cepat** | Return data lama | Interval min 2 detik |
| **Checksum error** | Return `NaN` | Cek noise, pendekkan kabel |
| **Tegangan tidak stabil** | Data tidak konsisten | Cek power supply |
| **Pin salah** | Selalu `NaN` | Cek pin definition |

---

### **Fungsi `isnan()` — Is Not A Number**

Ketika sensor gagal, library DHT mengembalikan **NaN** (Not a Number). Kita harus cek ini sebelum menggunakan data!

```cpp
float suhu = dht.readTemperature();
float kelembaban = dht.readHumidity();

// ⚠️ SELALU cek NaN sebelum pakai data!
if (isnan(suhu) || isnan(kelembaban)) {
  Serial.println("❌ Error: Gagal membaca sensor DHT22!");
  Serial.println("   Cek wiring: VCC→3V3, DATA→GPIO+pullup, GND→GND");
  return;  // Skip loop ini, coba lagi di iterasi berikutnya
}

// ✅ Data valid, aman digunakan
Serial.printf("Suhu: %.1f°C, Kelembaban: %.1f%%\n", suhu, kelembaban);
```

> 💡 **Best Practice**: SELALU cek `isnan()` sebelum memproses data sensor. Tanpa pengecekan ini, program bisa crash atau menampilkan data yang salah!

---

### **Pola Error Handling yang Robust**

```cpp
int failCount = 0;
const int MAX_RETRIES = 3;

void readSensor() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    failCount++;
    Serial.printf("⚠️ Pembacaan gagal! (attempt %d/%d)\n", failCount, MAX_RETRIES);

    if (failCount >= MAX_RETRIES) {
      Serial.println("❌ Sensor error berulang! Cek hardware!");
      // Bisa tambah: matikan LED, set flag error, dll.
    }
    return;
  }

  // Reset counter jika berhasil
  failCount = 0;

  // Proses data...
  Serial.printf("✅ Suhu: %.1f°C | Kelembaban: %.1f%%\n", t, h);
}
```

---

# BAGIAN 2: PERSIAPAN HARDWARE & LIBRARY (20 menit)

## 7️⃣ Instalasi Library Adafruit DHT

### **Mengapa Butuh Library?**

Komunikasi dengan DHT22 membutuhkan timing yang sangat presisi (dalam satuan **mikro-detik**). Menulis kode timing manual sangat rumit dan mudah error. Library **Adafruit DHT** mengurus semua ini!

### **Library yang Dibutuhkan (2 Library)**

| Library | Author | Fungsi |
|---|---|---|
| **DHT sensor library** | Adafruit | Membaca data DHT11/DHT22 |
| **Adafruit Unified Sensor** | Adafruit | Dependency (abstract sensor interface) |

### **Cara Install via Arduino IDE Library Manager**

1. Buka **Arduino IDE 2.x**
2. Klik menu **Sketch** → **Include Library** → **Manage Libraries...**
3. Di kolom pencarian, ketik: **`DHT sensor library`**
4. Cari yang by **Adafruit** → Klik **Install**
5. Jika muncul dialog "Install dependencies?" → Klik **Install All** (ini akan otomatis install `Adafruit Unified Sensor`)

```
┌──────────────────────────────────────────────────────┐
│  Library Manager                                      │
├──────────────────────────────────────────────────────┤
│  Search: [DHT sensor library          ] 🔍           │
│                                                       │
│  DHT sensor library           by Adafruit     v1.4.6 │
│  ├── Reads DHT11, DHT22, AM2302, AM2301             │
│  └── [INSTALL]  ← Klik ini!                         │
│                                                       │
│  ⚠️ Dependencies required:                           │
│  ├── Adafruit Unified Sensor                         │
│  └── [Install All]  ← Klik ini!                     │
└──────────────────────────────────────────────────────┘
```

### **Verifikasi Instalasi**

Setelah install, cek apakah library terinstall:

```
Sketch → Include Library → cari "DHT"
Jika muncul "DHT sensor library" → ✅ Berhasil!
```

Atau di code, tambahkan:

```cpp
#include <DHT.h>         // Library utama
// Jika compile tanpa error → library terinstall! ✅
```

---

## 8️⃣ Wiring DHT22 ke ESP32

### **Diagram Wiring**

```
                    ┌─────────────┐
                    │   DHT22     │
                    │  ┌───────┐  │
                    │  │  IC   │  │
                    │  └───────┘  │
                    └─┬──┬──┬──┬─┘
                      │  │  │  │
                     (1)(2)(3)(4)
                      │  │  │  │
                     VCC DATA NC GND
                      │  │     │
                      │  │     │
    ESP32 3V3 ────────┘  │     └──────── ESP32 GND
                         │
                    ┌────┴────┐
                    │         │
              ESP32 GPIO4     │
                              │
                    Pull-up Resistor 10kΩ
                              │
                    ESP32 3V3 ─┘
```

### **Tabel Wiring DHT22**

| DHT22 Pin | ESP32 Pin | Keterangan |
|-----------|-----------|------------|
| Pin 1 (VCC) | **3V3** | Power supply 3.3V |
| Pin 2 (DATA) | **GPIO4** | Data signal + pull-up 10kΩ ke 3V3 |
| Pin 3 (NC) | — | Tidak dihubungkan |
| Pin 4 (GND) | **GND** | Ground |

### **Wiring LED Indikator (3 LED)**

| LED | ESP32 GPIO | Resistor | Keterangan |
|-----|-----------|----------|------------|
| LED Biru (Dingin) | **GPIO15** | 220Ω | Nyala jika suhu < 25°C |
| LED Hijau (Normal) | **GPIO16** | 220Ω | Nyala jika suhu 25-30°C |
| LED Merah (Panas) | **GPIO17** | 220Ω | Nyala jika suhu > 30°C |

### **Diagram Wiring Lengkap (DHT22 + 3 LED)**

```
ESP32 DevKit V1
┌──────────────────────┐
│                      │
│  3V3 ──────────┬────►│ DHT22 VCC (Pin 1)
│                │     │
│                │  ┌──►│ Pull-up 10kΩ (satu ujung ke 3V3)
│                │  │  │
│  GPIO4  ───────┼──┤──►│ DHT22 DATA (Pin 2)
│                │  │  │
│                └──┘  │  (Pull-up 10kΩ antara DATA dan 3V3)
│                      │
│  GND   ─────────────►│ DHT22 GND (Pin 4)
│                      │
│  GPIO15 ──── [220Ω] ──── [LED Biru]  ──── GND
│  GPIO16 ──── [220Ω] ──── [LED Hijau] ──── GND
│  GPIO17 ──── [220Ω] ──── [LED Merah] ──── GND
│                      │
└──────────────────────┘
```

> ⚠️ **Catatan Wiring**:
>
> 1. **Cabut USB** dari ESP32 sebelum memasang/mengubah wiring!
> 2. LED: Kaki panjang (Anode) ke resistor, kaki pendek (Cathode) ke GND
> 3. Jika menggunakan **modul DHT22 3-pin**, pull-up resistor sudah built-in — tidak perlu tambah eksternal
> 4. Pastikan tidak ada kabel yang lepas atau short circuit sebelum power ON

---

## 9️⃣ Pull-up Resistor: Mengapa Dibutuhkan?

### **Masalah "Floating Pin"**

Pin DATA DHT22 adalah **open-drain** — sensor hanya bisa menarik kabel ke LOW (0V), tapi **tidak bisa mendorong** ke HIGH (3.3V). Tanpa pull-up resistor:

```
Tanpa Pull-up:
DATA pin "mengambang" (floating) saat idle
→ ESP32 baca nilai random (kadang HIGH, kadang LOW)
→ Komunikasi gagal!
```

### **Dengan Pull-up Resistor:**

```
Dengan Pull-up 10kΩ:
3V3 ──── [10kΩ] ──── DATA pin
                      │
                   (idle = HIGH, sensor tarik = LOW)

- Idle: resistor "menarik" DATA ke HIGH (3.3V) ✅
- Sensor aktif: sensor tarik DATA ke LOW (0V) ✅
- Transisi jelas: HIGH ↔ LOW ✅
```

### **Mengapa 10kΩ?**

- Terlalu kecil (220Ω): arus terlalu besar saat LOW → boros energi, sensor kepanasan
- Terlalu besar (100kΩ): transisi HIGH→LOW terlalu lambat → timing error
- **10kΩ**: pas — arus cukup kecil (0.33mA), transisi cukup cepat

> 💡 **Tip**: Jika kamu pakai **modul DHT22** (bukan sensor standalone), biasanya sudah ada resistor pull-up 10kΩ terpasang di PCB modul. Cek dulu sebelum menambahkan resistor tambahan (double pull-up bisa menyebabkan masalah)!

---

# BAGIAN 3: PRAKTIKUM HARDWARE (80 menit)

## ⚙️ Persiapan Praktikum

### **Hardware yang Dibutuhkan**

| Komponen | Qty | Keterangan |
|---|---|---|
| ESP32 DevKit V1 | 1 | Board mikrokontroller |
| Kabel USB Micro | 1 | Untuk programming & power |
| Sensor DHT22 | 1 | Sensor suhu & kelembaban |
| Breadboard | 1 | Untuk prototyping |
| Resistor 10kΩ | 1 | Pull-up untuk DHT22 (jika bukan modul) |
| LED Biru | 1 | Indikator suhu dingin |
| LED Hijau | 1 | Indikator suhu normal |
| LED Merah | 1 | Indikator suhu panas |
| Resistor 220Ω | 3 | Current limiting untuk LED |
| Jumper Wire M-M | ~10 | Untuk koneksi |

### **Software yang Dibutuhkan**

- ✅ Arduino IDE 2.x (terinstall)
- ✅ ESP32 Board Support (terinstall)
- ✅ Library DHT sensor library (Adafruit) — **install sekarang jika belum!**
- ✅ Library Adafruit Unified Sensor — **install sekarang jika belum!**

---

### **Before Power ON Checklist** ⚠️

Sebelum hubungkan USB ke ESP32, pastikan:

- [ ] DHT22 VCC → 3V3 (BUKAN 5V — meskipun sensor support 5V, lebih aman pakai 3.3V di ESP32)
- [ ] DHT22 DATA → GPIO4 (dengan pull-up 10kΩ ke 3V3)
- [ ] DHT22 GND → GND
- [ ] LED Biru: GPIO15 → 220Ω → LED Anode → LED Cathode → GND
- [ ] LED Hijau: GPIO16 → 220Ω → LED Anode → LED Cathode → GND
- [ ] LED Merah: GPIO17 → 220Ω → LED Anode → LED Cathode → GND
- [ ] Tidak ada kabel yang short circuit (VCC ke GND)

---

## 📟 Praktikum 1: Baca Suhu & Kelembaban Dasar

### **Tujuan**: Membaca data sensor DHT22 dan menampilkan di Serial Monitor

---

### **Code:**

```cpp
/*
 * Praktikum 5.1: Baca Suhu & Kelembaban Dasar
 * Membaca DHT22 dan menampilkan data di Serial Monitor
 */

#include <DHT.h>          // Library DHT sensor (Adafruit)

// ── Pin & Sensor Type ────────────────────────────────
#define DHT_PIN   4        // DHT22 DATA pin ke GPIO4
#define DHT_TYPE  DHT22    // Tipe sensor: DHT22 (AM2302)

// Buat objek DHT
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();  // Inisialisasi sensor DHT22

  Serial.println("================================");
  Serial.println("  Praktikum 5.1: Baca DHT22");
  Serial.println("  Sensor Suhu & Kelembaban");
  Serial.println("================================");
  Serial.println();

  // Tunggu sensor siap (2 detik)
  Serial.println("Menunggu sensor siap...");
  delay(2000);
  Serial.println("Sensor siap! Mulai membaca...\n");
}

void loop() {
  // Baca data dari DHT22
  float suhu = dht.readTemperature();       // Celsius (default)
  float kelembaban = dht.readHumidity();    // Persen (%)

  // Tampilkan di Serial Monitor
  Serial.print("Suhu: ");
  Serial.print(suhu, 1);       // 1 desimal
  Serial.print(" °C  |  ");
  Serial.print("Kelembaban: ");
  Serial.print(kelembaban, 1);  // 1 desimal
  Serial.println(" %");

  // Tunggu 2 detik (minimum sampling period DHT22)
  delay(2000);
}
```

### **Expected Output:**

```
================================
  Praktikum 5.1: Baca DHT22
  Sensor Suhu & Kelembaban
================================

Menunggu sensor siap...
Sensor siap! Mulai membaca...

Suhu: 28.5 °C  |  Kelembaban: 65.2 %
Suhu: 28.6 °C  |  Kelembaban: 65.0 %
Suhu: 28.5 °C  |  Kelembaban: 64.8 %
```

### **Langkah Praktikum:**

1. Pastikan wiring DHT22 sudah benar (lihat Section 8)
2. Buka Arduino IDE → Paste code di atas
3. Pilih Board: **ESP32 Dev Module**
4. Pilih Port: COM yang benar
5. Upload code
6. Buka **Serial Monitor** → set baud rate **115200**
7. Lihat output suhu dan kelembaban

### **Apa yang Terjadi Jika Sensor Tidak Terhubung?**

Jika DHT22 tidak terhubung atau wiring salah:

```
Suhu: nan °C  |  Kelembaban: nan %
Suhu: nan °C  |  Kelembaban: nan %
```

**`nan`** = **Not a Number** — artinya pembacaan sensor gagal. Ini akan kita tangani di Praktikum 2!

---

## 📟 Praktikum 2: Error Handling + Output Terformat

### **Tujuan**: Menambah error handling dan format output yang lebih informatif

---

### **Code:**

```cpp
/*
 * Praktikum 5.2: Error Handling + Output Terformat
 * DHT22 dengan pengecekan NaN dan Serial.printf()
 */

#include <DHT.h>

#define DHT_PIN   4
#define DHT_TYPE  DHT22

DHT dht(DHT_PIN, DHT_TYPE);

int readCount = 0;    // Counter pembacaan berhasil
int failCount = 0;    // Counter pembacaan gagal

void setup() {
  Serial.begin(115200);
  dht.begin();

  delay(200);
  Serial.println("\n");
  Serial.println("╔══════════════════════════════════╗");
  Serial.println("║  DHT22 Sensor Monitor            ║");
  Serial.println("║  Pertemuan 5: Suhu & Kelembaban  ║");
  Serial.println("║  Mikrokontroller - Informatika   ║");
  Serial.println("╚══════════════════════════════════╝");
  Serial.println();

  Serial.printf("Sensor Pin : GPIO%d\n", DHT_PIN);
  Serial.printf("Sensor Type: DHT22 (AM2302)\n");
  Serial.printf("Interval   : 2 detik\n");
  Serial.println();

  Serial.println("Menunggu sensor siap (2 detik)...");
  delay(2000);
  Serial.println("✅ Sensor siap!\n");
}

void loop() {
  // Baca sensor
  float t = dht.readTemperature();    // Celsius
  float h = dht.readHumidity();       // Persen

  // ⚠️ Error Handling: cek apakah pembacaan valid
  if (isnan(t) || isnan(h)) {
    failCount++;
    Serial.printf("❌ Pembacaan #%d GAGAL! (total gagal: %d)\n",
                  readCount + failCount, failCount);
    Serial.println("   → Cek wiring: VCC→3V3, DATA→GPIO4+pullup, GND→GND");

    if (failCount >= 5) {
      Serial.println("⚠️ WARNING: 5x gagal berturut-turut!");
      Serial.println("   → Pastikan sensor terhubung dengan benar");
      Serial.println("   → Cek apakah pull-up resistor 10kΩ terpasang");
    }

    delay(2000);
    return;  // Skip, coba lagi di loop berikutnya
  }

  // Reset fail counter jika berhasil
  failCount = 0;
  readCount++;

  // Hitung Heat Index (indeks panas yang dirasakan)
  float heatIndex = dht.computeHeatIndex(t, h, false); // false = Celsius

  // Tampilkan data terformat
  Serial.println("┌─── Sensor Reading ─────────────────┐");
  Serial.printf("│ #%d                                  \n", readCount);
  Serial.printf("│ Suhu         : %.1f °C              \n", t);
  Serial.printf("│ Kelembaban   : %.1f %%              \n", h);
  Serial.printf("│ Heat Index   : %.1f °C              \n", heatIndex);
  Serial.printf("│ Uptime       : %lu detik            \n", millis() / 1000);
  Serial.println("└─────────────────────────────────────┘");
  Serial.println();

  delay(2000);
}
```

### **Expected Output (Berhasil):**

```
╔══════════════════════════════════╗
║  DHT22 Sensor Monitor            ║
║  Pertemuan 5: Suhu & Kelembaban  ║
║  Mikrokontroller - Informatika   ║
╚══════════════════════════════════╝

Sensor Pin : GPIO4
Sensor Type: DHT22 (AM2302)
Interval   : 2 detik

Menunggu sensor siap (2 detik)...
✅ Sensor siap!

┌─── Sensor Reading ─────────────────┐
│ #1
│ Suhu         : 28.5 °C
│ Kelembaban   : 65.2 %
│ Heat Index   : 30.1 °C
│ Uptime       : 4 detik
└─────────────────────────────────────┘
```

### **Expected Output (Error):**

```
❌ Pembacaan #1 GAGAL! (total gagal: 1)
   → Cek wiring: VCC→3V3, DATA→GPIO4+pullup, GND→GND
❌ Pembacaan #2 GAGAL! (total gagal: 2)
   → Cek wiring: VCC→3V3, DATA→GPIO4+pullup, GND→GND
```

### **Langkah Praktikum:**

1. Upload code Praktikum 2
2. Buka Serial Monitor (115200)
3. Verify output terformat dengan box border
4. **TEST ERROR**: Cabut kabel DATA DHT22 → lihat pesan error muncul
5. **TEST RECOVERY**: Pasang kembali kabel DATA → lihat pembacaan kembali normal

> 💡 **Bonus Pengetahuan**: `dht.computeHeatIndex()` menghitung **Heat Index** — suhu yang "dirasakan" tubuh manusia, yang dipengaruhi oleh kelembaban. Suhu 30°C dengan kelembaban 80% terasa seperti 35°C!

---

## 📟 Praktikum 3: LED Indikator Suhu (3 Warna)

### **Tujuan**: Menampilkan status suhu menggunakan 3 LED berwarna

**Logika LED:**

| Kondisi | LED yang Menyala | Keterangan |
|---------|-----------------|------------|
| Suhu < 25°C | 🔵 LED Biru | Dingin |
| 25°C ≤ Suhu ≤ 30°C | 🟢 LED Hijau | Normal |
| Suhu > 30°C | 🔴 LED Merah | Panas |

---

### **Code:**

```cpp
/*
 * Praktikum 5.3: LED Indikator Suhu
 * LED berubah warna berdasarkan suhu yang dibaca DHT22
 */

#include <DHT.h>

// ── Pin Definitions ────────────────────────────
#define DHT_PIN     4       // DHT22 DATA pin
#define DHT_TYPE    DHT22

#define LED_BLUE    15      // LED Biru  (Dingin)  < 25°C
#define LED_GREEN   16      // LED Hijau (Normal)  25-30°C
#define LED_RED     17      // LED Merah (Panas)   > 30°C

// ── Threshold Suhu ─────────────────────────────
#define TEMP_COLD   25.0    // Di bawah ini = Dingin
#define TEMP_HOT    30.0    // Di atas ini  = Panas

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Set LED pins sebagai output
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  // Matikan semua LED saat start
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);

  // Splash screen
  delay(200);
  Serial.println("\n");
  Serial.println("╔════════════════════════════════════╗");
  Serial.println("║  DHT22 + LED Indikator Suhu        ║");
  Serial.println("║  Pertemuan 5 - Mikrokontroller      ║");
  Serial.println("╚════════════════════════════════════╝");
  Serial.println();
  Serial.printf("DHT22 Pin  : GPIO%d\n", DHT_PIN);
  Serial.printf("LED Biru   : GPIO%d (< %.0f°C)\n", LED_BLUE, TEMP_COLD);
  Serial.printf("LED Hijau  : GPIO%d (%.0f-%.0f°C)\n", LED_GREEN, TEMP_COLD, TEMP_HOT);
  Serial.printf("LED Merah  : GPIO%d (> %.0f°C)\n", LED_RED, TEMP_HOT);
  Serial.println();

  // Test semua LED (nyalakan 1 per 1)
  Serial.println("Testing LED...");
  testAllLEDs();
  Serial.println("✅ LED test selesai!\n");

  // Tunggu sensor siap
  Serial.println("Menunggu sensor DHT22 siap...");
  delay(2000);
  Serial.println("✅ Sistem siap! Monitoring dimulai...\n");
}

// ─────────────────────────────────────────────────
// FUNCTION: testAllLEDs
// Test semua LED saat startup
// ─────────────────────────────────────────────────
void testAllLEDs() {
  Serial.println("  🔵 LED Biru...");
  digitalWrite(LED_BLUE, HIGH);
  delay(500);
  digitalWrite(LED_BLUE, LOW);

  Serial.println("  🟢 LED Hijau...");
  digitalWrite(LED_GREEN, HIGH);
  delay(500);
  digitalWrite(LED_GREEN, LOW);

  Serial.println("  🔴 LED Merah...");
  digitalWrite(LED_RED, HIGH);
  delay(500);
  digitalWrite(LED_RED, LOW);
}

// ─────────────────────────────────────────────────
// FUNCTION: updateLEDs
// Nyalakan LED sesuai suhu, matikan yang lain
// ─────────────────────────────────────────────────
void updateLEDs(float suhu) {
  // Matikan semua LED dulu
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);

  // Nyalakan LED sesuai range suhu
  if (suhu < TEMP_COLD) {
    digitalWrite(LED_BLUE, HIGH);
    Serial.printf("  Status: 🔵 DINGIN (< %.0f°C)\n", TEMP_COLD);
  } else if (suhu > TEMP_HOT) {
    digitalWrite(LED_RED, HIGH);
    Serial.printf("  Status: 🔴 PANAS (> %.0f°C)\n", TEMP_HOT);
  } else {
    digitalWrite(LED_GREEN, HIGH);
    Serial.printf("  Status: 🟢 NORMAL (%.0f-%.0f°C)\n", TEMP_COLD, TEMP_HOT);
  }
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  // Error handling
  if (isnan(t) || isnan(h)) {
    Serial.println("❌ Error membaca sensor!");

    // Blink semua LED sebagai indikator error
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, HIGH);
    delay(200);
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);

    delay(2000);
    return;
  }

  // Tampilkan data
  Serial.println("┌─── Monitor Suhu ─────────────────┐");
  Serial.printf("│ Suhu       : %.1f °C              \n", t);
  Serial.printf("│ Kelembaban : %.1f %%              \n", h);

  // Update LED berdasarkan suhu
  updateLEDs(t);

  Serial.println("└───────────────────────────────────┘");
  Serial.println();

  delay(2000);
}
```

### **Cara Test LED Indikator:**

Karena suhu ruangan biasanya 25-30°C (LED Hijau menyala), kamu bisa test LED lain dengan cara:

1. **Test LED Merah (>30°C)**: Pegang sensor DHT22 dengan tangan → suhu naik karena panas tubuh
2. **Test LED Biru (<25°C)**: Letakkan es batu dekat sensor → suhu turun
3. **Test Error**: Cabut kabel DATA → semua LED blink sebagai indikator error

---

# 🏆 Project Akhir: Sistem Monitoring Suhu Lengkap

## **File**: `P05_DHT22_LED_Indicator.ino`

Project akhir menggabungkan semua yang dipelajari:

- ✅ Membaca sensor DHT22 (suhu + kelembaban)
- ✅ Error handling robust (dengan retry counter)
- ✅ LED indikator 3 warna
- ✅ Serial output terformat dengan statistik
- ✅ LED test saat startup

**Lihat file kode lengkap di**: `code/P05_DHT22_LED_Indicator.ino`

---

## 🌟 Challenge (Opsional — Bonus Poin!)

### **Challenge: DHT22 Statistics Monitor**

Tambahkan fitur tracking statistik:

- Simpan pembacaan terakhir (rolling window 10 data)
- Hitung MIN, MAX, AVERAGE suhu dan kelembaban
- Serial Menu interaktif:
  - `1` → Baca sensor sekarang
  - `2` → Tampilkan statistik (min/max/avg)
  - `3` → Reset statistik
  - `4` → Set alarm threshold

**Lihat file kode lengkap di**: `code/P05_Challenge_DHT22_Stats.ino`

---

## 📚 Konsep Penting — Ringkasan

### **Sensor DHT22**

| Fungsi | Kegunaan |
|---|---|
| `#include <DHT.h>` | Include library DHT |
| `DHT dht(PIN, TYPE)` | Buat objek sensor |
| `dht.begin()` | Inisialisasi sensor |
| `dht.readTemperature()` | Baca suhu (°C) |
| `dht.readHumidity()` | Baca kelembaban (%) |
| `dht.computeHeatIndex(t, h, false)` | Hitung heat index (°C) |

---

### **Error Handling**

| Fungsi | Kegunaan |
|---|---|
| `isnan(value)` | Cek apakah value = NaN (Not a Number) |
| Return `NaN` | Sensor gagal membaca (wiring error, dll) |
| Retry counter | Hitung error berturut-turut |

---

### **LED Control**

| Fungsi | Kegunaan |
|---|---|
| `pinMode(pin, OUTPUT)` | Set pin sebagai output |
| `digitalWrite(pin, HIGH)` | Nyalakan LED |
| `digitalWrite(pin, LOW)` | Matikan LED |

---

### **Best Practices Sensor**

1. ✅ **Selalu** cek `isnan()` sebelum pakai data sensor
2. ✅ **Minimum** 2 detik interval antara pembacaan DHT22
3. ✅ **Gunakan** pull-up resistor 10kΩ (atau gunakan modul yang sudah punya built-in)
4. ✅ **Test** semua LED saat startup (visual confirmation)
5. ✅ **Cabut USB** sebelum ubah wiring
6. ❌ **Jangan** baca sensor terlalu cepat (<2 detik)

---

## 🔗 Referensi

- [Adafruit DHT Sensor Library (GitHub)](https://github.com/adafruit/DHT-sensor-library)
- [Random Nerd Tutorials — ESP32 with DHT22](https://randomnerdtutorials.com/esp32-dht11-dht22-temperature-humidity-sensor-arduino-ide/)
- [DHT22 Datasheet (PDF)](https://www.sparkfun.com/datasheets/Sensors/Temperature/DHT22.pdf)
- [Arduino Serial Reference](https://www.arduino.cc/reference/en/language/functions/communication/serial/)

---

**Next**: Pertemuan 6 — Sensor Jarak & Interrupt Basics 📏

---

**Materi ini dibuat untuk**: Mata Kuliah Mikrokontroller — Prodi Informatika Unmul
