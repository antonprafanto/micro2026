# Pertemuan 1: Pengenalan Embedded Systems & ESP32 + Lab Safety

## Mata Kuliah Mikrokontroller - Prodi Informatika Unmul

> **"Your First Step into IoT World!"** 🚀

---

## 📋 Informasi Pertemuan

- **Durasi**: 3 × 50 menit (150 menit)
- **Tipe**: Teori + Lab Safety + Praktikum
- **Deliverable**: Screenshot Blink LED + Lab Safety Quiz (score min 80%)
- **Batas Waktu**: 1 minggu setelah pertemuan

---

## 🎯 Tujuan Pembelajaran

Setelah pertemuan ini, mahasiswa mampu:

1. **Memahami** konsep dasar embedded systems dan contoh aplikasinya
2. **Menjelaskan** perbedaan mikrokontroller (Arduino, ESP8266, ESP32)
3. **Mengenal** arsitektur dan keunggulan ESP32
4. **Menerapkan** prosedur lab safety untuk elektronika dasar
5. **Menggunakan** Arduino IDE untuk programming ESP32
6. **Mengimplementasikan** program "Blink LED" pertama

---

## 📖 Outline Materi

### **Bagian 1: Teori (60 menit)**

1. Apa itu Embedded Systems?
2. Mengenal Mikrokontroller
3. Kenapa ESP32?
4. Arsitektur ESP32
5. Arduino IDE vs ESP-IDF vs MicroPython
6. Komponen Elektronika Dasar

### **Bagian 2: Lab Safety (30 menit)**

7. Safety Rules untuk Elektronika
8. Pengenalan Breadboard
9. Komponen Safety

### **Bagian 3: Praktikum (60 menit)**

10. Setup Arduino IDE
11. Install ESP32 Board Support
12. Upload Program Blink Pertama
13. Troubleshooting Common Errors

---

# BAGIAN 1: TEORI (60 menit)

## 1️⃣ Apa itu Embedded Systems?

### **Definisi**

> **Embedded System** adalah sistem komputer khusus yang dirancang untuk melakukan **satu atau beberapa fungsi spesifik**, biasanya sebagai bagian dari sistem yang lebih besar.

### **Perbedaan dengan Komputer Biasa**

| Aspek        | Komputer PC/Laptop                    | Embedded System                       |
| ------------ | ------------------------------------- | ------------------------------------- |
| **Fungsi**   | General purpose (bisa untuk apa saja) | Specific purpose (fungsi tertentu)    |
| **OS**       | Windows, macOS, Linux (kompleks)      | Bare metal atau RTOS (minimal)        |
| **Performa** | High (GHz, multi-core, GB RAM)        | Cukup untuk tugasnya (MHz, KB-MB RAM) |
| **Power**    | 50-100W (butuh listrik)               | 0.1-5W (bisa battery)                 |
| **Cost**     | Rp 5jt - 30jt                         | Rp 10rb - 500rb                       |
| **Contoh**   | Desktop, laptop                       | Kulkas, AC, smartwatch, drone         |

### **Contoh Embedded Systems di Sekitar Kita**

#### 🏠 **Di Rumah**:

- **Kulkas**: Thermostat mengatur suhu otomatis
- **Rice Cooker**: Timer dan temperature control
- **AC Remote**: Infrared transmitter dengan microcontroller
- **Smart TV**: Media player dengan embedded Linux
- **Washing Machine**: Kontrol motor, timer, sensor level air

#### 📱 **Di Smartphone**:

- **Kamera**: Image signal processor (ISP)
- **Charging Circuit**: Battery management system
- **Fingerprint Sensor**: Secure processor
- **NFC Chip**: Contactless payment

#### 🚗 **Di Kendaraan**:

- **Engine Control Unit (ECU)**: Kontrol injeksi bahan bakar
- **ABS System**: Anti-lock braking
- **Airbag Controller**: Crash detection
- **Dashboard**: Display instrument cluster

#### 🏭 **Di Industri**:

- **PLC (Programmable Logic Controller)**: Automation factory
- **Temperature Logger**: Monitoring cold chain
- **Access Control**: RFID door lock
- **CCTV**: Video processing & network

### **Mengapa Embedded Systems Penting?**

✅ Ada di **miliaran perangkat** di dunia  
✅ Market besar (IoT diproyeksikan **41.6 miliar devices** di 2025)  
✅ **Career opportunity**: Embedded engineer, IoT developer, firmware engineer  
✅ **Foundation** untuk IoT, Robotics, Automotive, Smart City

---

## 2️⃣ Mengenal Mikrokontroller

### **Apa itu Mikrokontroller?**

> Mikrokontroller adalah **komputer mini dalam satu chip** yang berisi CPU, memory, dan I/O peripheral.

### **Analogi Mudah**

Bayangkan mikrokontroller seperti **otak robot**:

- **CPU** = Otak yang berpikir
- **Memory** = Ingatan (RAM untuk kerja, Flash untuk program)
- **GPIO** = Tangan & kaki (untuk interaksi dengan dunia luar)
- **Program** = Instruksi yang diajarkan

### **Perbandingan Mikrokontroller Populer**

| Fitur         | Arduino Uno          | ESP8266              | **ESP32**                  |
| ------------- | -------------------- | -------------------- | -------------------------- |
| **Chip**      | ATmega328P           | ESP8266              | ESP32                      |
| **CPU**       | 16 MHz (single core) | 80 MHz (single core) | **240 MHz (dual core)** 🚀 |
| **RAM**       | 2 KB                 | 80 KB                | **520 KB**                 |
| **Flash**     | 32 KB                | 4 MB                 | **4-16 MB**                |
| **WiFi**      | ❌                   | ✅ 2.4 GHz           | ✅ 2.4 GHz                 |
| **Bluetooth** | ❌                   | ❌                   | ✅ **BT Classic + BLE**    |
| **GPIO Pins** | 14                   | 11                   | **34 pins**                |
| **ADC**       | 10-bit (6 channel)   | 10-bit (1 channel)   | **12-bit (18 channel)**    |
| **PWM**       | 6                    | 4                    | **16 channel**             |
| **Harga**     | ~Rp 70k              | ~Rp 30k              | **~Rp 60k**                |
| **Best For**  | Belajar dasar        | WiFi project simple  | **IoT kompleks**           |

### **Kenapa Kita Pilih ESP32?**

✅ **Powerful**: Dual-core 240 MHz (48× lebih cepat dari Arduino Uno!)  
✅ **Wireless Built-in**: WiFi + Bluetooth (tidak perlu module tambahan)  
✅ **Banyak GPIO**: 34 pins (cukup untuk project kompleks)  
✅ **Affordable**: Harga terjangkau (~Rp 60.000)  
✅ **Large Community**: Banyak tutorial, library, forum support  
✅ **Arduino Compatible**: Bisa pakai Arduino IDE (mudah untuk pemula)  
✅ **Future-Proof**: Sudah support IoT, ML on edge (TensorFlow Lite)

---

## 3️⃣ Arsitektur ESP32

### **ESP32 Block Diagram (Simplified)**

```
┌─────────────────────────────────────────────────────────┐
│                      ESP32 SoC                          │
│                                                         │
│  ┌──────────────┐          ┌──────────────┐            │
│  │  CPU Core 0  │          │  CPU Core 1  │            │
│  │  (240 MHz)   │          │  (240 MHz)   │            │
│  └──────────────┘          └──────────────┘            │
│         │                          │                    │
│         └──────────┬───────────────┘                    │
│                    │                                    │
│         ┌──────────▼──────────┐                         │
│         │   Memory             │                         │
│         │  - 520 KB RAM        │                         │
│         │  - 4 MB Flash        │                         │
│         └──────────┬──────────┘                         │
│                    │                                    │
│    ┌───────────────┴───────────────┐                    │
│    │      Peripherals              │                    │
│    │  - 34× GPIO                   │                    │
│    │  - 18× ADC (12-bit)           │                    │
│    │  - 16× PWM                    │                    │
│    │  - 3× UART, 2× I2C, 4× SPI    │                    │
│    │  - WiFi 802.11 b/g/n          │                    │
│    │  - Bluetooth Classic + BLE    │                    │
│    │  - Touch Sensor (10 pin)      │                    │
│    └───────────────────────────────┘                    │
└─────────────────────────────────────────────────────────┘
```

### **Penjelasan Komponen Utama**

#### **1. Dual-Core CPU (240 MHz)**

- **2 core** independen yang bisa jalan parallel
- Core 0: biasanya untuk WiFi/Bluetooth
- Core 1: untuk aplikasi user (default di Arduino)
- Bisa multi-tasking (baca sensor sambil kirim WiFi)

#### **2. Memory**

- **RAM (520 KB)**: Tempat program berjalan & data temporary
- **Flash (4 MB)**: Tempat menyimpan program (seperti "hard disk")
- **PSRAM (opsional)**: Tambahan RAM eksternal hingga 8 MB

#### **3. GPIO (General Purpose Input/Output)**

- **34 pins** yang bisa diprogram sebagai input atau output
- Bisa baca sensor (input) atau kontrol LED/motor (output)
- Voltage: **3.3V logic** (PENTING! Bukan 5V seperti Arduino Uno)

#### **4. ADC (Analog-to-Digital Converter)**

- **18 channel**, resolusi **12-bit** (0-4095)
- Untuk baca sensor analog (potensiometer, LDR, soil moisture, dll)
- Input voltage range: 0V - 3.3V

#### **5. PWM (Pulse Width Modulation)**

- **16 channel** independen
- Untuk kontrol kecepatan motor, brightness LED, servo
- Frequency configurable (hingga 40 MHz)

#### **6. Communication Protocols**

- **UART (3×)**: Serial communication (GPS, debug, dll)
- **I2C (2×)**: Untuk sensor (OLED, RTC, MPU6050)
- **SPI (4×)**: High-speed (SD card, display TFT)

#### **7. Wireless**

- **WiFi 802.11 b/g/n (2.4 GHz)**: Internet connectivity
- **Bluetooth Classic**: Audio streaming, SPP (serial)
- **BLE (Bluetooth Low Energy)**: Sensor, wearable, beacon

#### **8. Touch Sensor**

- **10 GPIO** punya capacitive touch sensing
- Bisa buat touch button tanpa physical button!

---

## 4️⃣ ESP32 DevKit Board (Yang Kita Pakai)

### **Pinout ESP32 DevKit V1 (NodeMCU-32S)**

```
                         ┌─────┐
                         │ USB │
                         └──┬──┘
    ┌──────────────────────┴──────────────────────┐
    │                                              │
EN  │ (RST)                                  (3V3) │ 3.3V
VP  │ (GPIO36) ADC1_0                       (GND)  │ GND
VN  │ (GPIO39) ADC1_3                       (GPIO15)│ D15
D34 │ (GPIO34) ADC1_6                       (GPIO2) │ D2  (LED_BUILTIN)
D35 │ (GPIO35) ADC1_7                       (GPIO0) │ D0  (BOOT)
D32 │ (GPIO32) ADC1_4, TOUCH9              (GPIO4) │ D4
D33 │ (GPIO33) ADC1_5, TOUCH8              (GPIO16)│ D16
D25 │ (GPIO25) ADC2_8, DAC1                (GPIO17)│ D17
D26 │ (GPIO26) ADC2_9, DAC2                (GPIO5) │ D5  (SPI_SS)
D27 │ (GPIO27) ADC2_7, TOUCH7              (GPIO18)│ D18 (SPI_SCK)
D14 │ (GPIO14) ADC2_6, TOUCH6              (GPIO19)│ D19 (SPI_MISO)
D12 │ (GPIO12) ADC2_5, TOUCH5              (GPIO21)│ D21 (I2C_SDA)
GND │                                       (RX0)  │ GPIO3
D13 │ (GPIO13) ADC2_4, TOUCH4              (TX0)  │ GPIO1
D9  │ (GPIO9)  FLASH                       (GPIO22)│ D22 (I2C_SCL)
D10 │ (GPIO10) FLASH                       (GPIO23)│ D23 (SPI_MOSI)
D11 │ (GPIO11) FLASH                        (GND)  │ GND
VIN │ (5V from USB)                         (3V3)  │ 3.3V
    │                                              │
    └──────────────────────────────────────────────┘
```

### **Pin Penting yang Sering Dipakai**

| Pin           | Fungsi       | Keterangan                               |
| ------------- | ------------ | ---------------------------------------- |
| **GPIO2**     | LED_BUILTIN  | LED onboard (untuk test blink)           |
| **GPIO21**    | I2C_SDA      | Untuk OLED, sensor I2C                   |
| **GPIO22**    | I2C_SCL      | Untuk OLED, sensor I2C                   |
| **GPIO15**    | General GPIO | Aman untuk LED, button                   |
| **GPIO32-39** | ADC only     | Untuk sensor analog (potensiometer, LDR) |
| **GND**       | Ground       | Common ground (hitam)                    |
| **3V3**       | Power 3.3V   | VCC untuk sensor 3.3V (merah)            |
| **VIN**       | Power 5V     | Input dari USB, atau output 5V           |

### **Pin yang HARUS HATI-HATI (JANGAN Dipakai Sembarangan)**

| Pin          | Warning              | Mengapa?                                              |
| ------------ | -------------------- | ----------------------------------------------------- |
| **GPIO6-11** | ⚠️ **JANGAN PAKAI!** | Terhubung ke Flash memory internal, bisa brick ESP32! |
| **GPIO0**    | ⚠️ Hati-hati         | BOOT button, harus HIGH saat boot                     |
| **GPIO1, 3** | ⚠️ Hindari           | TX0/RX0 untuk serial debugging                        |
| **GPIO12**   | ⚠️ Check voltage     | Boot fail jika HIGH saat boot                         |

---

## 5️⃣ Arduino IDE vs ESP-IDF vs MicroPython

### **Comparison**

| Aspek                 | Arduino IDE                  | ESP-IDF                | MicroPython                  |
| --------------------- | ---------------------------- | ---------------------- | ---------------------------- |
| **Bahasa**            | C/C++ (simplified)           | C/C++ (advanced)       | Python                       |
| **Difficulty**        | ⭐ (Beginner)                | ⭐⭐⭐⭐⭐ (Expert)    | ⭐⭐ (Easy)                  |
| **Library**           | Banyak (Arduino ecosystem)   | Advanced, low-level    | Growing                      |
| **Performance**       | Good (compiled)              | Best (optimized)       | Slower (interpreted)         |
| **Development Speed** | Fast                         | Slow                   | Very Fast                    |
| **Use Case**          | Prototyping, learning, hobby | Production, commercial | Rapid prototyping, education |
| **Best For**          | **Kita (pemula!)**           | Professional dev       | Python lovers                |

### **Kenapa Kita Pakai Arduino IDE?**

✅ **Beginner-Friendly**: Syntax simple, banyak example code  
✅ **Large Community**: Banyak tutorial, forum, Q&A  
✅ **Rich Libraries**: Ribuan library siap pakai  
✅ **Cross-Platform**: Windows, Mac, Linux  
✅ **Quick Prototyping**: Upload code dalam hitungan detik

---

## 6️⃣ Komponen Elektronika Dasar

> **Penting untuk Mahasiswa Informatika!** Kita akan belajar elektronika dari nol.

### **A. Resistor (Penghambat Arus)**

#### **Fungsi**:

- Membatasi arus listrik
- Protect LED dari terbakar
- Pull-up / pull-down untuk button

#### **Satuan**: Ohm (Ω)

| Nilai | Simbol | Kegunaan Umum         |
| ----- | ------ | --------------------- |
| 220 Ω | 220R   | LED current limiting  |
| 1 kΩ  | 1K     | General purpose       |
| 10 kΩ | 10K    | Pull-up/down resistor |

#### **Color Code (Resistor 4 Pita)**

```
┌───────────────────────────────────────┐
│  [Pita 1] [Pita 2] [Multiplier] [Toleransi] │
│     ↓        ↓          ↓          ↓     │
│   Digit1   Digit2     ×10^n      ±%      │
└───────────────────────────────────────┘

Contoh: Merah-Merah-Coklat-Gold
  = 2 2 ×10 ±5%
  = 220Ω ±5%
```

**Color Table**:

- Hitam: 0
- Coklat: 1
- **Merah: 2** ← (22 × 10 = 220Ω untuk LED)
- Oranye: 3
- Kuning: 4
- Hijau: 5
- Biru: 6
- Ungu: 7
- Abu: 8
- Putih: 9

**Toleransi**:

- Gold: ±5%
- Silver: ±10%

#### **Tidak Ada Polaritas**: Boleh dipasang bolak-balik!

---

### **B. LED (Light Emitting Diode)**

#### **Fungsi**: Memancarkan cahaya saat dialiri arus

#### **Mengenal Polaritas LED**

```
       ┌────┐
       │    │  ← Kaki PANJANG (Anode, +)
       │LED │
       │    │  ← Kaki PENDEK (Cathode, -)
       └────┘
```

✅ **Kaki PANJANG** → **Anode (+)** → Hubungkan ke GPIO (via resistor)  
❌ **Kaki PENDEK** → **Cathode (-)** → Hubungkan ke GND

#### **Wiring LED yang Benar**

```
ESP32 GPIO ----[Resistor 220Ω]----[LED]---- GND
              (pembatas arus)    (Anode) (Cathode)
```

#### **SALAH (LED akan terbakar!)** ❌

```
ESP32 GPIO ----[LED]---- GND  (tanpa resistor!)
```

#### **Mengapa Perlu Resistor?**

Perhitungan sederhana:

- GPIO ESP32: 3.3V
- LED voltage drop: ~2V
- LED safe current: 10-20mA (kita pakai 10mA agar aman)

**Ohm's Law**: R = V / I

- R = (3.3V - 2V) / 0.01A = 130Ω

Karena resistor 130Ω jarang, kita pakai **220Ω** (lebih aman, LED agak kurang terang).

---

### **C. Push Button**

#### **Fungsi**: Input digital (pressed atau not pressed)

#### **Wiring dengan Internal Pull-Up** (Recommended)

```
        ┌──────┐
Button──┤      ├── GPIO (INPUT_PULLUP)
        └──┬───┘
           │
          GND
```

**Code**:

```cpp
pinMode(BUTTON_PIN, INPUT_PULLUP);
int state = digitalRead(BUTTON_PIN);
// LOW = pressed, HIGH = released (karena pull-up)
```

**Keuntungan**: Tidak butuh resistor eksternal!

---

### **D. Breadboard (Papan Prototyping)**

#### **Anatomy Breadboard**

```
Power Rails (terhubung horizontal):
┌─────────────────────────────────────┐
│ [-][-][-][-][-][-][-][-][-][-]      │ ← Negative (GND)
│ [+][+][+][+][+][+][+][+][+][+]      │ ← Positive (VCC)
├─────────────────────────────────────┤
│                                     │
│  a  b  c  d  e      f  g  h  i  j   │
│ [ ][ ][ ][ ][ ] │ [ ][ ][ ][ ][ ] 1 │
│ [ ][ ][ ][ ][ ] │ [ ][ ][ ][ ][ ] 2 │ ← Terminal strips
│ [ ][ ][ ][ ][ ] │ [ ][ ][ ][ ][ ] 3 │   (terhubung vertikal)
│       ...                           │
└─────────────────────────────────────┘
```

**Aturan Penting**:

1. **Power rails** (atas/bawah): Terhubung **horizontal**
2. **Terminal strips** (tengah): Terhubung **vertikal** dalam 1 kolom (a-e atau f-j)
3. **Gap di tengah**: Untuk IC (ESP32 tidak dipasang di breadboard, pakai jumper)

---

# BAGIAN 2: LAB SAFETY (30 menit)

## ⚠️ Mengapa Lab Safety Penting?

Meskipun kita bekerja dengan voltage rendah (3.3V-5V), tetap ada risiko:

- Komponen bisa **terbakar** jika salah pasang
- ESP32 rusak = **Rp 60.000** hilang!
- Short circuit bisa **merusak port USB laptop**

**Prinsip**: _"Safety First, Experiment Second!"_

---

## 🔒 Safety Rules Utama

### **1. Voltage & Current**

| Item        | Voltage | Aman?                                       |
| ----------- | ------- | ------------------------------------------- |
| ESP32 Logic | 3.3V    | ✅ Sangat aman                              |
| USB Port    | 5V      | ✅ Aman                                     |
| GPIO Max    | 3.6V    | ⚠️ Limit (jangan lebih!)                    |
| Listrik PLN | 220V AC | ❌ **BERBAHAYA!** Jangan hubungkan langsung |

**GOLDEN RULE**: **JANGAN** hubungkan ESP32 langsung ke 220V AC!

---

### **2. Yang BOLEH Dilakukan** ✅

✅ Gunakan breadboard untuk prototyping  
✅ Gunakan resistor 220Ω-1kΩ untuk LED  
✅ Hubungkan sensor ke 3.3V atau 5V (cek datasheet dulu)  
✅ **Cabut USB** sebelum ubah wiring  
✅ Tanya jika ragu

---

### **3. Yang DILARANG KERAS** ❌

❌ **JANGAN** hubungkan VCC ke GND directly (short circuit!)  
❌ **JANGAN** hubungkan GPIO ke 5V (max 3.6V!)  
❌ **JANGAN** pasang LED tanpa resistor  
❌ **JANGAN** pasang komponen saat ESP32 nyala (powered ON)  
❌ **JANGAN** paksa komponen jika tidak pas di breadboard

---

### **4. Jika Ada Asap/Bau Terbakar** 🚨

1. ⚡ **CABUT USB SEGERA!**
2. 🚫 **JANGAN SENTUH** komponen (bisa panas!)
3. 📢 **LAPOR** ke dosen/asisten
4. 🔍 Identifikasi komponen yang terbakar
5. ✅ Check wiring sebelum power kembali

---

## 🧰 Tips Wiring

### **Color Coding (Best Practice)**:

- **Merah**: VCC / 3.3V / 5V (power)
- **Hitam/Coklat**: GND (ground)
- **Warna lain**: Signal (GPIO, data)

### **Before Power ON Checklist**:

- [ ] Cek polaritas LED (panjang ke resistor, pendek ke GND)
- [ ] Cek tidak ada VCC terhubung langsung ke GND
- [ ] Cek resistor terpasang untuk LED
- [ ] Cek wiring sesuai diagram

---

# BAGIAN 3: PRAKTIKUM (60 menit)

## 🌐 Praktikum dengan Wokwi Simulator

> **Untuk Pertemuan 1, kita akan menggunakan Wokwi simulator online!**  
> **Keuntungan**: Tidak perlu hardware fisik, bisa praktik di mana saja, tidak ada risiko komponen rusak!

### **Apa itu Wokwi?**

**Wokwi** adalah **ESP32 simulator online** yang berjalan di browser. Kita bisa:

- ✅ Coding ESP32 langsung di browser
- ✅ Simulate circuit (LED, button, sensor, dll)
- ✅ Lihat hasil real-time (LED menyala, serial monitor, dll)
- ✅ Share project dengan link (untuk submission)
- ✅ **100% Gratis** untuk basic features

**Website**: [https://wokwi.com](https://wokwi.com)

---

### **Langkah 1: Buat Akun Wokwi (Gratis)**

1. Buka browser, kunjungi: [https://wokwi.com](https://wokwi.com)
2. Klik **Sign Up** (pojok kanan atas)
3. Pilih metode sign up:
   - **Google Account** (recommended - cepat)
   - **GitHub Account** (jika punya)
   - **Email** (perlu verifikasi email)
4. Setelah login, Anda akan masuk ke dashboard Wokwi

**Note**: Akun gratis sudah cukup untuk course ini!

---

### **Langkah 2: Buat Project ESP32 Baru**

1. Di dashboard Wokwi, klik **"New Project"**
2. Pilih template: **"ESP32"**
3. Akan muncul:
   - **Code Editor** (kiri): Tempat nulis code C++
   - **Simulation Area** (tengah/kanan): ESP32 board virtual
   - **Serial Monitor** (bawah): Output serial

**Default Code**: Wokwi sudah include code blink LED sederhana!

---

### **Langkah 3: Pahami Interface Wokwi**

#### **A. Code Editor (Panel Kiri)**

```
├── sketch.ino         ← Main code file (seperti Arduino IDE)
├── diagram.json       ← Circuit diagram (auto-generated)
└── libraries.txt      ← Dependencies (jika perlu library tambahan)
```

Click `sketch.ino` untuk edit code.

#### **B. Simulation Area (Panel Tengah/Kanan)**

- ESP32 board virtual ditampilkan
- **LED biru kecil** di board = GPIO 2 (LED_BUILTIN)
- Bisa klik component untuk interact (misal: button)

#### **C. Control Buttons (Atas)**

| Button        | Fungsi                                   |
| ------------- | ---------------------------------------- |
| ▶️ **Play**   | Start simulation                         |
| ⏸️ **Pause**  | Pause simulation                         |
| 🔄 **Reset**  | Restart ESP32 (seperti tekan RST button) |
| 📊 **Serial** | Buka serial monitor                      |
| 🔗 **Share**  | Generate link untuk sharing              |
| 💾 **Save**   | Save project (login required)            |

#### **D. Serial Monitor (Panel Bawah)**

- Klik icon **"Serial Monitor"** untuk buka
- Menampilkan output dari `Serial.println()`
- Bisa kirim input ke ESP32 (untuk pertemuan mendatang)

---

### **Langkah 4: Jalankan Simulasi Pertama**

1. **Test Default Code**:
   - Klik tombol **Play** ▶️
   - Lihat LED biru di ESP32 board → akan berkedip!
   - Buka Serial Monitor → akan muncul output

2. **Pause & Reset**:
   - Klik **Pause** ⏸️ → simulation berhenti
   - Klik **Reset** 🔄 → simulation restart dari awal
   - Klik **Play** ▶️ lagi → simulation lanjut

**Selamat! Anda sudah menjalankan ESP32 pertama kali!** 🎉

---

### **Langkah 5: Tutorial Fitur Wokwi**

#### **Zoom & Navigate**:

- **Zoom In/Out**: Mouse scroll wheel atau pinch (touchpad)
- **Pan**: Click & drag di simulation area

#### **Inspect Component**:

- **Hover** mouse di atas ESP32 board
- Akan muncul pin labels (GPIO2, VCC, GND, dll)
- Berguna untuk tahu pin mana yang mana

#### **Add Component** (Untuk Pertemuan Mendatang):

- Klik tombol **"+"** di sebelah ESP32
- Pilih component: LED, Button, Resistor, Sensor, dll
- Drag & drop ke simulation area
- Connect dengan wire (click pin → drag → click target pin)

**Note**: Untuk Pertemuan 1, kita pakai LED onboard saja (tidak perlu add component).

---

### **Langkah 6: Understand Wokwi Pinout**

Di Wokwi, ESP32 board menampilkan pin labels yang jelas:

- **GPIO2**: LED_BUILTIN (built-in blue LED)
- **3V3**: Power 3.3V
- **GND**: Ground
- **VIN**: Power input (5V from USB)
- **GPIO0-39**: General purpose I/O pins

**Visual**: Hover mouse di atas pin untuk lihat label!

---

### **Referensi Pinout ESP32** (Untuk Dipelajari)

Untuk pinout detail ESP32 DevKit V1, lihat gambar di:

- [ESP32 Pinout Reference - Random Nerd Tutorials](https://randomnerdtutorials.com/esp32-pinout-reference-gpios/)
- [ESP32 DevKit V1 Pinout - Wokwi Docs](https://docs.wokwi.com/parts/wokwi-esp32-devkit-v1)

**Print & tempelkan** di meja belajar Anda untuk referensi cepat!

---

## 🎨 (Optional) Setup Arduino IDE untuk Physical Hardware

> **Bagian ini OPSIONAL untuk Pertemuan 1!**  
> Jika Anda sudah punya ESP32 fisik dan ingin coba, ikuti steps ini.  
> **Namun, untuk Pertemuan 1, submission harus pakai Wokwi.**

<details>
<summary>Click untuk expand: Arduino IDE Setup (Optional)</summary>

### **Langkah 1: Download & Install Arduino IDE**

1. Kunjungi: [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)
2. Download **Arduino IDE 2.x** (versi terbaru)
3. Install seperti biasa

### **Langkah 2: Install Driver CH340**

(Sama seperti section sebelumnya - lihat di archive jika perlu)

### **Langkah 3: Install ESP32 Board Support**

1. Arduino IDE → File → Preferences
2. Additional Boards Manager URLs:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Tools → Board → Boards Manager → Search "esp32" → Install

### **Langkah 4: Upload ke ESP32 Fisik**

1. Hubungkan ESP32 via USB
2. Tools → Board → ESP32 Dev Module
3. Tools → Port → Pilih COM port
4. Upload code
5. Tekan BOOT button jika stuck "Connecting..."

</details>

---

## 🚀 Upload Program Blink di Wokwi!

### **Program Blink Klasik**

```cpp
/*
 * Program: Blink LED Onboard ESP32
 * Deskripsi: LED onboard (GPIO 2) akan berkedip ON-OFF setiap 1 detik
 *
 * Hardware:
 * - ESP32 DevKit V1 (Wokwi simulation)
 * - LED onboard di GPIO 2 (sudah built-in di board)
 *
 * Wiring: Tidak perlu wiring, LED sudah onboard!
 */

// Define pin LED onboard
#define LED_BUILTIN 2  // GPIO 2 adalah LED onboard di ESP32

// Fungsi setup: jalan 1x saat ESP32 boot
void setup() {
  // Set GPIO 2 sebagai OUTPUT (untuk kontrol LED)
  pinMode(LED_BUILTIN, OUTPUT);

  // (Opsional) Buka serial monitor untuk debugging
  Serial.begin(115200);
  Serial.println("ESP32 Blink Program Started!");
}

// Fungsi loop: jalan terus-menerus (infinite loop)
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // LED ON (HIGH = 3.3V)
  Serial.println("LED ON");
  delay(1000);                      // Tunggu 1000ms = 1 detik

  digitalWrite(LED_BUILTIN, LOW);   // LED OFF (LOW = 0V)
  Serial.println("LED OFF");
  delay(1000);                      // Tunggu 1 detik

  // Loop akan repeat dari awal
}
```

---

### **Cara Upload di Wokwi**

1. **Copy Code**:
   - Select SEMUA code di atas (Ctrl+A atau Command+A)
   - Copy (Ctrl+C atau Command+C)

2. **Paste ke Wokwi**:
   - Di Wokwi Code Editor (panel kiri)
   - Click `sketch.ino`
   - Select semua code yang ada (Ctrl+A)
   - Paste code baru (Ctrl+V) - akan replace code lama

3. **Run Simulation**:
   - Klik tombol **Play** ▶️ di atas
   - **Observe**:
     - LED biru di ESP32 board akan berkedip!
     - Serial Monitor akan menampilkan "LED ON" / "LED OFF"

4. **Buka Serial Monitor** (jika belum terbuka):
   - Klik icon **Serial Monitor** di bawah
   - Output akan muncul:
     ```
     ESP32 Blink Program Started!
     LED ON
     LED OFF
     LED ON
     LED OFF
     ...
     ```

**Selamat! LED pertama Anda sudah berkedip!** 🎉

---

### **Save Project Wokwi**

**PENTING**: Save project agar tidak hilang!

1. Klik tombol **Save** 💾 (pojok kanan atas)
2. Beri nama project:
   ```
   P01_Blink_LED_[NIM]_[Nama]
   ```
   Contoh: `P01_Blink_LED_2111001_Anton`
3. Klik **Save**

**Project tersimpan** di akun Wokwi Anda!

---

### **Share Project (Untuk Submission)**

1. Klik tombol **Share** 🔗
2. Copy link yang muncul (format: `https://wokwi.com/projects/xxxxx`)
3. **Test link**:
   - Paste di tab browser baru
   - Pastikan bisa dibuka (untuk verify submission nanti)

**Save link ini** untuk submission deliverable!

---

## 🎯 Modifikasi & Eksperimen

### **Challenge 1: Ubah Kecepatan Blink**

Coba ubah `delay(1000)` menjadi:

- `delay(500)` → Blink lebih cepat (2× per detik)
- `delay(2000)` → Blink lebih lambat (1× per 2 detik)
- `delay(100)` → Super cepat!

**Upload lagi** dan lihat perbedaannya.

---

### **Challenge 2: Blink Pattern**

Buat pattern: ON 2 detik, OFF 0.5 detik

```cpp
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);  // ON selama 2 detik

  digitalWrite(LED_BUILTIN, LOW);
  delay(500);   // OFF selama 0.5 detik
}
```

---

### **Challenge 3: SOS Morse Code**

SOS dalam Morse: `··· −−− ···` (3 short, 3 long, 3 short)

```cpp
void loop() {
  // S (3× short blink)
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }

  delay(500);  // Pause antara S dan O

  // O (3× long blink)
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(600);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }

  delay(500);  // Pause antara O dan S

  // S (3× short blink)
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }

  delay(2000);  // Pause sebelum repeat
}
```

---

## 🐞 Troubleshooting Common Errors

### **Error 1: "Board not found" atau "Port not found"**

**Penyebab**:

- Driver belum terinstall
- Kabel USB rusak (coba kabel lain)
- Port USB laptop bermasalah

**Solusi**:

1. Install driver CH340 atau CP2102
2. Coba USB port lain
3. Restart Arduino IDE
4. Restart laptop

---

### **Error 2: "Failed to connect to ESP32"**

**Penyebab**:

- ESP32 tidak masuk mode programming

**Solusi**:

1. **Metode 1** (Manual BOOT):
   - Tekan dan tahan tombol **BOOT**
   - Klik **Upload**
   - Tunggu muncul "Connecting..."
   - Lepas tombol BOOT saat muncul "Writing at 0x..."

2. **Metode 2** (Restart ESP32):
   - Cabut USB
   - Tunggu 5 detik
   - Hubungkan lagi
   - Upload lagi

---

### **Error 3: "Sketch too big"**

**Penyebab**:

- Partition scheme salah

**Solusi**:

- Tools → Partition Scheme → "No OTA (2MB APP)"

---

### **Error 4: LED Tidak Berkedip**

**Penyebab**:

- Upload sebenarnya gagal (tapi tidak error)
- LED rusak (jarang)

**Solusi**:

1. Buka Serial Monitor, cek apakah ada output
2. Jika ada output tapi LED tidak berkedip → LED rusak (ganti board atau gunakan external LED)
3. Upload program lagi dengan tekan BOOT

---

## 📤 Deliverable Pertemuan 1

### **Yang Harus Dikumpulkan** (via e-learning):

#### **1. Screenshot Wokwi Simulator** ✅

Ambil screenshot yang menunjukkan:

- ✓ Code editor dengan full code visible (panel kiri)
- ✓ ESP32 simulation dengan LED menyala/mati (panel kanan)
- ✓ Serial Monitor dengan output "LED ON" / "LED OFF" (panel bawah)
- ✓ **Seluruh window Wokwi** terlihat (jangan crop terlalu ketat)

**File naming**: `P01_Screenshot_[NIM]_[Nama].png`  
**Contoh**: `P01_Screenshot_2111001_AntonPrafanto.png`

---

#### **2. Link Wokwi Project (Public)** 🔗

- Save project Wokwi Anda dengan nama:  
  `P01_Blink_LED_[NIM]_[Nama]`
- Klik tombol **Share** 🔗
- Copy link public project
- **Test link** di browser incognito (pastikan bisa dibuka orang lain!)

**Format submissi link**: Paste di form e-learning atau dalam file submission.

**Contoh link**: `https://wokwi.com/projects/123456789012345`

---

#### **3. (Opsional) Jika Mengerjakan Challenge** 🌟

Jika sudah mengerjakan challenge (SOS Morse atau modifikasi lain):

- Screenshot challenge project
- Link Wokwi challenge project
- Penjelasan singkat modifikasi yang dibuat

**Bonus points**: +10% dari nilai deliverable!

---

### **Template Submission**

Gunakan template di file: `P01_Template_Submission.md`

**Checklist sebelum submit**:

- [ ] Screenshot Wokwi jelas dan tidak blur
- [ ] Link Wokwi sudah di-test (bisa dibuka)
- [ ] Nama file sesuai format
- [ ] Submit **SEBELUM DEADLINE** (1 minggu setelah pertemuan)

---

### **Grading Criteria**

| Kriteria                          | Bobot |
| --------------------------------- | ----- |
| Screenshot & Link Wokwi berfungsi | 40%   |
| Code lengkap dan simulation jalan | 30%   |
| Penjelasan (jika diminta)         | 20%   |
| Ketepatan waktu submit            | 10%   |
| **Bonus**: Challenge              | +10%  |

**Total maksimal**: 110% (jika mengerjakan challenge)

---

## 🎓 Rangkuman & Poin Penting

### **Apa yang Sudah Kita Pelajari:**

✅ **Embedded Systems**: Komputer spesifik untuk fungsi tertentu, ada di mana-mana  
✅ **Mikrokontroller**: Otak mini dalam chip (CPU + memory + I/O)  
✅ **ESP32**: Powerful, WiFi+BT, affordable (~Rp 60k), banyak GPIO  
✅ **Arduino IDE**: Tool untuk programming ESP32 dengan mudah  
✅ **Lab Safety**: JANGAN short circuit, JANGAN LED tanpa resistor, CABUT USB sebelum ubah wiring  
✅ **Blink LED**: Program pertama, foundation dari semua project IoT!

### **Next Week Preview** (Pertemuan 2):

- Digital I/O lebih lanjut
- External LED dengan breadboard
- Push button input
- **Project**: Traffic light simulation 🚦

---

## 📚 Referensi & Bahan Bacaan

### **Official Documentation**:

1. [ESP32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)
2. [Arduino ESP32 GitHub](https://github.com/espressif/arduino-esp32)
3. [Arduino Language Reference](https://www.arduino.cc/reference/en/)

### **Tutorial**:

1. [Random Nerd Tutorials - ESP32](https://randomnerdtutorials.com/getting-started-with-esp32/)
2. [Last Minute Engineers](https://lastminuteengineers.com/electronics/esp32-projects/)

### **Video** (Indonesian):

1. Search YouTube: "ESP32 Arduino IDE Indonesia"
2. Channel: Kelas Robot, Indobot

---

## ❓ FAQ

**Q: Apakah ESP32 saya rusak jika upload gagal berkali-kali?**  
A: Belum tentu! Coba tekan BOOT saat upload. 99% kasus, ESP32 tidak rusak, hanya perlu proper upload procedure.

**Q: Boleh tidak pakai resistor untuk LED onboard?**  
A: LED onboard sudah ada resistor built-in di PCB, jadi aman. Tapi untuk external LED, WAJIB pakai resistor!

**Q: Kalau saya pakai MacBook, apakah sama?**  
A: Ya, Arduino IDE sama di semua OS. Driver mungkin beda, tapi prinsipnya sama.

**Q: Apakah ESP32 bisa diprogram pakai bahasa lain?**  
A: Bisa! ESP-IDF (C/C++), MicroPython (Python), Lua. Tapi untuk course ini, kita fokus Arduino C/C++.

---

## 💬 Diskusi & Tanya Jawab

Jika ada pertanyaan:

1. **Forum kelas** (Discord/WhatsApp group)
2. **Office hours** dosen
3. **Asisten lab**

**Jangan malu bertanya!** Tidak ada pertanyaan bodoh, yang bodoh adalah tidak bertanya. 😊

---

<div align="center">

**Selamat! Anda Telah Menyelesaikan Pertemuan 1!** 🎉

**Next**: Pertemuan 2 - Digital I/O & Breadboard Basics

---

_"From Blink to IoT, One Step at a Time!"_ 🚀

**Mata Kuliah Mikrokontroller - Prodi Informatika Unmul**

</div>
