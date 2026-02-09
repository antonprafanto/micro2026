# 🔒 Lab Safety Guide - Laboratorium Mikrokontroller ESP32

## Panduan Keselamatan untuk Mahasiswa Informatika

> **PENTING**: Dokumen ini WAJIB dibaca sebelum praktikum pertama!

---

## ⚠️ Mengapa Lab Safety Penting?

Meskipun kita bekerja dengan voltage rendah (3.3V-5V), **elektronika tetap memiliki risiko**:

- Komponen bisa **terbakar** jika salah pasang
- **Short circuit** bisa merusak ESP32 (harga Rp 60.000!)
- **Kapasitor** bisa meledak jika polaritas terbalik
- **Bau/asap** dari komponen terbakar bisa mengganggu kesehatan

**Prinsip Utama**: _"Safety First, Experiment Second"_ ✅

---

## 📋 Checklist Sebelum Praktikum

Sebelum SETIAP praktikum, pastikan:

- [ ] Membaca materi praktikum terlebih dahulu
- [ ] Memahami circuit diagram yang akan dibuat
- [ ] Menyiapkan komponen yang dibutuhkan
- [ ] Breadboard dan workspace dalam keadaan bersih
- [ ] Laptop battery cukup (min 50%)
- [ ] ESP32 tidak terhubung ke USB saat memasang komponen

---

## 🔌 Aturan Dasar Kelistrikan

### 1. **Voltage & Current Basics**

- **ESP32**: bekerja di **3.3V** logic (BUKAN 5V seperti Arduino Uno!)
- **USB Port**: menyuplai **5V** ke ESP32
- **GPIO Max Current**: 12mA per pin, 40mA total
- **LED**: butuh resistor pembatas arus (220Ω - 1kΩ)

### 2. **Yang BOLEH dilakukan**:

✅ Gunakan breadboard untuk prototyping  
✅ Gunakan resistor untuk LED (minimal 220Ω)  
✅ Hubungkan sensor ke 3.3V atau 5V (sesuai datasheet)  
✅ Cabut USB sebelum ubah wiring  
✅ Test dengan multimeter jika ragu

### 3. **Yang DILARANG KERAS**:

❌ **JANGAN** hubungkan VCC langsung ke GND (short circuit!)  
❌ **JANGAN** hubungkan GPIO langsung ke 5V (max 3.6V!)  
❌ **JANGAN** pasang LED tanpa resistor  
❌ **JANGAN** pasang komponen saat ESP32 nyala (powered)  
❌ **JANGAN** paksa komponen jika tidak pas di breadboard  
❌ **JANGAN** hubungkan ESP32 ke AC 220V tanpa proper circuit

---

## 🛠️ Panduan Penggunaan Komponen

### 1. **Breadboard 101**

```
Breadboard Layout:
┌─────────────────────────────────────┐
│ [-] [-] [-] [-] [-] [-] [-] [-]      │ ← Power Rail (-)
│ [+] [+] [+] [+] [+] [+] [+] [+]      │ ← Power Rail (+)
│                                      │
│  a  b  c  d  e   f  g  h  i  j       │
│ [ ][ ][ ][ ][ ] [ ][ ][ ][ ][ ]  1   │
│ [ ][ ][ ][ ][ ] [ ][ ][ ][ ][ ]  2   │ ← Terminal strips
│       ...                            │   (vertikal terhubung)
└─────────────────────────────────────┘
```

**Aturan**:

- **Power rails** (atas/bawah): terhubung **horizontal** sepanjang breadboard
- **Terminal strips** (tengah): terhubung **vertikal** dalam 1 kolom (a-e atau f-j)
- **Gap tengah**: untuk memasang IC (ESP32 tidak dipasang di breadboard, tapi dihubungkan dengan jumper)

### 2. **LED (Light Emitting Diode)**

**Polaritas**:

- **Kaki panjang**: Anode (+) → hubungkan ke GPIO (via resistor)
- **Kaki pendek**: Cathode (-) → hubungkan ke GND

**Resistor Pembatas**:

```
GPIO ----[Resistor 220Ω]----[LED]---- GND
```

**Perhitungan**:

- Voltage GPIO: 3.3V
- LED voltage drop: ~2V
- LED current: 10-20mA (safe: 10mA)
- Resistor: (3.3V - 2V) / 0.01A = 130Ω → gunakan 220Ω (lebih safe)

**Yang SALAH**:

```
❌ GPIO ----[LED]---- GND  (tanpa resistor, LED terbakar!)
❌ GND ----[LED]----[Resistor]---- GPIO  (polaritas terbalik!)
```

### 3. **Resistor**

**Color Code** (4 pita):
| Warna | Nilai |
|-------|-------|
| Hitam | 0 |
| Coklat| 1 |
| Merah | 2 |
| Oranye| 3 |
| Kuning| 4 |
| Hijau | 5 |
| Biru | 6 |
| Ungu | 7 |
| Abu | 8 |
| Putih | 9 |

**Contoh**: 220Ω

- Merah (2), Merah (2), Coklat (×10), Gold (±5%)

**Tidak ada polaritas**, bisa dipasang bolak-balik!

### 4. **Push Button**

**Wiring dengan Internal Pull-up**:

```
Button ----[GPIO]
           |
          GND
```

**Code**:

```cpp
pinMode(BUTTON_PIN, INPUT_PULLUP); // Enable internal pull-up
int state = digitalRead(BUTTON_PIN); // LOW = pressed, HIGH = released
```

### 5. **Sensor DHT22**

**Pinout**:

1. VCC → 3.3V atau 5V
2. Data → GPIO (dengan pull-up resistor 10kΩ)
3. NC (not connected)
4. GND → GND

**Wiring**:

```
DHT22 Pin 1 (VCC) ---- 3.3V
DHT22 Pin 2 (Data) ---- GPIO15 (+ pull-up 10kΩ ke VCC)
DHT22 Pin 4 (GND) ---- GND
```

### 6. **Sensor HC-SR04 (Ultrasonic)**

**PENTING**: HC-SR04 butuh **5V** untuk VCC!

**Wiring**:

```
HC-SR04 VCC ---- 5V (dari ESP32 VIN atau USB)
HC-SR04 Trig ---- GPIO5
HC-SR04 Echo ---- GPIO18 (atau via voltage divider jika perlu 3.3V)
HC-SR04 GND ---- GND
```

⚠️ **Catatan**: Echo pin mengeluarkan 5V, tapi GPIO ESP32 toleran hingga 3.6V. Untuk aman, gunakan **voltage divider** (resistor 1kΩ + 2kΩ).

### 7. **OLED Display (SSD1306)**

**I2C Pinout**:

- VCC → 3.3V
- GND → GND
- SCL → GPIO22 (default I2C clock)
- SDA → GPIO21 (default I2C data)

**Address**: Biasanya 0x3C atau 0x3D (gunakan I2C scanner untuk cek)

---

## 🚨 Troubleshooting & Emergency

### **Jika Ada Asap/Bau Terbakar**:

1. ⚡ **CABUT USB IMMEDIATELY!**
2. 🚫 **JANGAN SENTUH** komponen (bisa panas!)
3. 🔍 **Identifikasi** komponen yang terbakar
4. 📢 **Lapor** ke dosen/asisten lab
5. ✅ **Check wiring** sebelum power kembali

### **Jika ESP32 Tidak Terdeteksi**:

1. Check driver CH340/CP2102 sudah terinstall
2. Check kabel USB (coba kabel lain)
3. Check port selection di Arduino IDE
4. Tekan tombol **BOOT** saat upload
5. Coba board lain (mungkin ESP32 rusak)

### **Jika Sensor Tidak Terbaca**:

1. Check wiring: VCC, GND, Data pin
2. Check library sudah terinstall
3. Check GPIO pin benar
4. Test dengan multimeter (VCC = 3.3V/5V, GND = 0V)
5. Coba sensor lain (mungkin rusak)

### **Jika LED Tidak Menyala**:

1. Check polaritas (kaki panjang ke resistor, pendek ke GND)
2. Check resistor terpasang
3. Check GPIO sudah `pinMode(OUTPUT)`
4. Test LED dengan battery 3V (untuk test apakah LED rusak)

---

## 🔋 Power Supply Guidelines

### **Sumber Power**:

1. **USB Port Laptop**: 5V, max ~500mA (cukup untuk ESP32 + beberapa sensor)
2. **Power Bank**: 5V, ideal untuk mobile/field testing
3. **Adaptor 5V**: Gunakan yang ada output USB atau hubungkan ke VIN pin
4. **Battery**: LiPo 3.7V atau 2x AA battery (3V) via VIN

### **Perhitungan Konsumsi**:

| Komponen                | Konsumsi Arus                |
| ----------------------- | ---------------------------- |
| ESP32 (active, WiFi ON) | ~160mA                       |
| ESP32 (deep sleep)      | ~10µA                        |
| LED (10mA each)         | 10mA × jumlah LED            |
| DHT22                   | ~2.5mA                       |
| HC-SR04                 | ~15mA                        |
| OLED                    | ~20mA                        |
| Servo SG90              | ~100-500mA (tergantung load) |

**Contoh**:

- ESP32 + 3 LED + DHT22 + OLED = 160 + 30 + 2.5 + 20 = **212.5mA**
- USB port (500mA) → **AMAN** ✅
- Jika tambah servo → **BUTUH EXTERNAL POWER** ⚠️

### **External Power untuk Actuator Besar**:

Jika menggunakan motor DC, servo, atau relay banyak:

1. Gunakan **external power supply** terpisah (5V/12V sesuai komponen)
2. **Sambungkan GND** ESP32 dengan GND external power (common ground!)
3. **JANGAN** hubungkan VCC ESP32 dengan VCC external power

```
[5V Adaptor] ----+---- Motor VCC
                 |
                GND ---- Motor GND ---- ESP32 GND

[USB/ESP32] ---- GPIO ---- Motor Driver Signal
```

---

## 🧰 Tools & Best Practices

### **Tools yang Berguna** (opsional tapi recommended):

1. **Multimeter**: Untuk ukur voltage, current, continuity
2. **Wire Stripper**: Untuk jumper wire custom
3. **Tweezers**: Untuk ambil komponen kecil dari breadboard
4. **Label Maker**: Untuk labeling komponen/kit

### **Wiring Best Practices**:

1. **Color Coding**:
   - Merah: VCC/3.3V/5V
   - Hitam/Coklat: GND
   - Warna lain: Signal/GPIO
2. **Rapi**: Hindari wiring yang crossing/messy
3. **Short Wire**: Gunakan jumper sepanjang yang dibutuhkan saja
4. **Dokumentasi**: Foto circuit sebelum disassemble

### **Code Best Practices**:

1. **Test Incremental**: Jangan langsung code kompleks, test step-by-step
2. **Serial Debug**: Gunakan `Serial.println()` untuk debug
3. **Comment**: Tulis comment untuk wiring pinout
   ```cpp
   #define LED_PIN 2    // Onboard LED
   #define DHT_PIN 15   // DHT22 data pin
   ```
4. **Backup Code**: Save code sebelum experiment

---

## 📦 Lab Equipment Care

### **Komponen Storage**:

1. **Pisahkan** komponen berdasarkan jenis (LED, resistor, sensor)
2. **Label** dengan jelas
3. **Anti-Static Bag** untuk IC/ESP32 (jika ada)
4. **Breadboard**: Bersihkan setelah praktikum, jangan tinggal komponen

### **ESP32 Care**:

1. **Jangan** cabut dengan paksa saat upload (bisa corrupt firmware)
2. **Avoid** static discharge (sentuh grounded metal sebelum pegang ESP32)
3. **Store** dalam box anti-static atau ziplock
4. **Label** ESP32 dengan nama (jika shared)

### **General Lab Rules**:

1. ✅ Datang tepat waktu
2. ✅ Workspace bersih sebelum & sesudah praktikum
3. ✅ Report komponen rusak/hilang ke asisten
4. ✅ No food/drink di dekat workspace
5. ✅ Matikan lampu & AC saat keluar lab (yang terakhir)

---

## ✅ Lab Safety Quiz (WAJIB)

Sebelum praktikum pertama, kerjakan quiz ini di e-learning:

**Sample Questions**:

1. Berapa voltage logic ESP32?
   - a) 5V
   - b) 3.3V ✅
   - c) 12V
   - d) 220V

2. Apa yang harus dilakukan jika ada asap dari komponen?
   - a) Semprot dengan air
   - b) Tiup untuk memadamkan
   - c) Cabut power segera ✅
   - d) Terus diamati

3. Berapa nilai resistor minimum untuk LED dengan GPIO 3.3V?
   - a) 0Ω (tidak perlu)
   - b) 100Ω
   - c) 220Ω ✅
   - d) 10kΩ

4. Kaki mana dari LED yang dihubungkan ke GPIO?
   - a) Kaki pendek
   - b) Kaki panjang ✅
   - c) Bebas
   - d) Keduanya

5. Apa yang dimaksud dengan short circuit?
   - a) VCC terhubung langsung ke GND ✅
   - b) LED tidak menyala
   - c) Cable terlalu pendek
   - d) Resistor terlalu besar

**Passing Score**: 80% (min 4/5 benar)

---

## 📞 Emergency Contact

Jika ada masalah SERIUS (komponen meledak, terbakar, luka):

1. **Asisten Lab**: [Nomor/Email]
2. **Dosen Pengampu**: [Nomor/Email]
3. **Lab Manager**: [Nomor/Email]
4. **Emergency Kampus**: [Nomor]

---

## 🎓 Final Notes

> _"An hour of planning can save you days of debugging."_

**Remember**:

- 🧠 **Think before you connect**
- 👀 **Double-check wiring**
- ⚡ **Power off before changes**
- 📚 **Read datasheet when in doubt**
- 🤝 **Ask if unsure**

**Lab safety bukan untuk menakuti, tapi untuk melindungi Anda dan peralatan!**

Selamat praktikum, stay safe, dan have fun! 🚀

---

**Terakhir diupdate**: Februari 2026  
**Revisi**: 1.0  
**Untuk**: Mata Kuliah Mikrokontroller - Prodi Informatika Unmul
