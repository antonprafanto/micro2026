# Pertemuan 6: Sensor Jarak & Interrupt Basics

## Mata Kuliah Mikrokontroller - Prodi Informatika Unmul

> **"See Without Eyes — Measure Distance with Sound Waves!"** 📏

---

## 📋 Informasi Pertemuan

- **Durasi**: 3 × 50 menit (150 menit)
- **Tipe**: Teori + Praktikum Hardware
- **Prerequisites**: Pertemuan 1-5 (GPIO, Serial, DHT22, Error Handling)
- **Deliverable**: Video demo parking sensor + buzzer warning + screenshot Serial Monitor
- **Batas Waktu**: 1 minggu setelah pertemuan

---

## 🎯 Tujuan Pembelajaran

Setelah pertemuan ini, mahasiswa mampu:

1. **Memahami** prinsip kerja sensor ultrasonic HC-SR04 (sonar)
2. **Menghitung** jarak berdasarkan waktu tempuh gelombang suara
3. **Menggunakan** `pulseIn()` untuk mengukur durasi echo
4. **Memahami** konsep interrupt vs polling
5. **Menggunakan** `attachInterrupt()` dan ISR pada ESP32
6. **Mengimplementasikan** parking sensor dengan buzzer dan LED indikator

---

## 📖 Outline Materi

### **Bagian 1: Teori Sensor Jarak & Interrupt (60 menit)**

1. Prinsip Sonar & Gelombang Ultrasonik
2. Sensor Ultrasonic HC-SR04
3. Rumus Perhitungan Jarak
4. Fungsi `pulseIn()`
5. Sensor PIR HC-SR501 (Deteksi Gerakan)
6. Interrupt Basics: Polling vs Interrupt
7. `attachInterrupt()` & ISR (Interrupt Service Routine)
8. Rules ISR & Volatile Variables

### **Bagian 2: Persiapan Hardware (15 menit)**

9. Wiring HC-SR04 + Voltage Divider (PENTING!)
10. Wiring Buzzer & LED Indikator

### **Bagian 3: Praktikum Hardware (75 menit)**

11. Praktikum 1: Baca Jarak Dasar
12. Praktikum 2: Parking Sensor (Buzzer + LED)
13. Praktikum 3: Interrupt Demo dengan Button

---

# BAGIAN 1: TEORI SENSOR JARAK & INTERRUPT (60 menit)

## 1️⃣ Prinsip Sonar & Gelombang Ultrasonik

### **Apa itu Sonar?**

> **Sonar** (Sound Navigation and Ranging) = Teknik mengukur jarak menggunakan **gelombang suara**. Prinsip yang sama digunakan oleh kelelawar, lumba-lumba, dan kapal selam!

### **Cara Kerja Sonar**

```
Sensor                      Objek
  │                           │
  │  1. Kirim gelombang ──►   │
  │                           │  ← Gelombang memantul
  │  ◄── 2. Terima pantulan   │
  │                           │
  │  3. Hitung waktu tempuh   │
  │     Jarak = (waktu × kecepatan) / 2
```

### **Gelombang Ultrasonik**

| Jenis Suara | Frekuensi | Contoh |
|---|---|---|
| **Infrasonik** | < 20 Hz | Gempa, gajah |
| **Suara manusia** | 20 Hz - 20 kHz | Bicara, musik |
| **Ultrasonik** | > 20 kHz | **HC-SR04 (40 kHz)**, kelelawar |

> 💡 **Ultrasonik** berada di atas batas pendengaran manusia (>20 kHz), jadi kamu **tidak akan mendengar** suara yang dipancarkan sensor!

### **Kecepatan Suara di Udara**

```
Kecepatan suara = 343 m/s (pada 20°C, tekanan normal)
                = 34.300 cm/s
                = 0,0343 cm/µs
                ≈ 0,034 cm/µs  (dibulatkan, untuk perhitungan)
```

> 📌 **Fun Fact**: Kecepatan suara dipengaruhi suhu. Pada 0°C, kecepatan suara = 331 m/s. Pada 40°C = 355 m/s. Untuk course ini, kita pakai **343 m/s** (suhu ruangan ~20°C).

---

## 2️⃣ Sensor Ultrasonic HC-SR04

### **Apa itu HC-SR04?**

> **HC-SR04** adalah sensor jarak ultrasonik yang mengukur jarak dengan cara memancarkan gelombang ultrasonik 40 kHz dan mengukur waktu pantulannya.

### **Fisik HC-SR04**

```
     ┌──────────────────────┐
     │  ┌─────┐  ┌─────┐   │
     │  │  T  │  │  R  │   │  T = Transmitter (pemancar)
     │  │     │  │     │   │  R = Receiver (penerima)
     │  └─────┘  └─────┘   │
     │                      │
     │  HC-SR04             │
     └──┬──┬──┬──┬──────────┘
        │  │  │  │
       VCC Trig Echo GND
        │  │   │   │
       5V  │   │  GND
           │   │
        GPIO5  GPIO18
               (via voltage divider!)
```

### **Pin HC-SR04**

| Pin | Fungsi | Hubungkan ke |
|-----|--------|-------------|
| **VCC** | Power supply | ESP32 **VIN (5V)** ⚠️ Harus 5V! |
| **Trig** | Trigger input | ESP32 GPIO (output) |
| **Echo** | Echo output | ESP32 GPIO **via voltage divider** ⚠️ |
| **GND** | Ground | ESP32 GND |

### **Spesifikasi HC-SR04**

| Parameter | Nilai |
|---|---|
| **Tegangan Kerja** | 5V DC |
| **Arus Operasi** | 15 mA |
| **Frekuensi Ultrasonik** | 40 kHz |
| **Range Jarak** | 2 cm - 400 cm (4 meter) |
| **Akurasi** | ±3 mm |
| **Sudut Pengukuran** | ~15° (cone) |
| **Trigger Pulse** | 10 µs (minimum) |

> ⚠️ **PENTING**: HC-SR04 butuh **tegangan 5V** untuk berfungsi! Jika dihubungkan ke 3.3V, sensor mungkin tidak bekerja atau memberikan data yang tidak akurat.

---

### **Cara Kerja HC-SR04 — Step by Step**

```
              10µs pulse
ESP32 ──────►  Trig
               │
               ▼
HC-SR04     Kirim 8 burst ultrasonik (40 kHz)
               │
               │ ─── gelombang ke objek ──► │
               │                             │ pantul
               │ ◄── gelombang kembali ──── │
               │
               ▼
HC-SR04     Echo pin → HIGH selama gelombang travel
               │
               ▼          durasi HIGH
ESP32 ◄──── Echo  ════════════════════
                   │←──── pulseIn() ────►│
```

**Langkah detail:**

1. ESP32 kirim **HIGH** ke pin **Trig** selama **10 µs** (trigger pulse)
2. HC-SR04 memancarkan **8 burst** gelombang ultrasonik 40 kHz
3. Gelombang menuju objek, memantul, dan kembali ke receiver
4. HC-SR04 men-set pin **Echo** ke **HIGH** selama waktu perjalanan pulang-pergi
5. ESP32 mengukur **durasi HIGH** pada pin Echo menggunakan `pulseIn()`
6. ESP32 menghitung **jarak** dari durasi tersebut

---

## 3️⃣ Rumus Perhitungan Jarak

### **Rumus Dasar**

```
Jarak (cm) = (Durasi × Kecepatan Suara) / 2

Dimana:
- Durasi    = waktu Echo HIGH (µs) → dari pulseIn()
- Kecepatan = 0.034 cm/µs  (kecepatan suara di udara)
- Dibagi 2  = karena gelombang pergi DAN kembali (round-trip)
```

### **Dalam Kode C++**

```cpp
// Kirim trigger pulse 10µs
digitalWrite(TRIG_PIN, LOW);
delayMicroseconds(2);
digitalWrite(TRIG_PIN, HIGH);
delayMicroseconds(10);
digitalWrite(TRIG_PIN, LOW);

// Baca durasi echo
long duration = pulseIn(ECHO_PIN, HIGH);

// Hitung jarak
float distance = (duration * 0.034) / 2.0;  // dalam cm
```

### **Contoh Perhitungan**

```
Objek berjarak 25 cm:

Waktu pergi = 25 / 0.034 = 735 µs
Waktu pulang = 735 µs
Total (round-trip) = 1.470 µs

pulseIn() return: 1470 µs
Jarak = (1470 × 0.034) / 2 = 24.99 cm ≈ 25 cm ✅
```

### **Table Durasi vs Jarak**

| Durasi Echo (µs) | Jarak (cm) | Keterangan |
|---|---|---|
| 116 | 2 cm | Minimum range |
| 580 | 10 cm | Sangat dekat |
| 1.175 | 20 cm | Dekat |
| 2.938 | 50 cm | Sedang |
| 5.875 | 100 cm (1m) | Jauh |
| 23.500 | 400 cm (4m) | Maximum range |

---

## 4️⃣ Fungsi `pulseIn()`

### **Apa itu `pulseIn()`?**

> `pulseIn(pin, value)` mengukur **durasi** suatu pulse (HIGH atau LOW) pada pin tertentu, dalam satuan **mikro-detik (µs)**.

### **Syntax**

```cpp
long duration = pulseIn(pin, value);
long duration = pulseIn(pin, value, timeout);
```

| Parameter | Tipe | Keterangan |
|---|---|---|
| `pin` | int | Pin yang dibaca |
| `value` | int | `HIGH` atau `LOW` — pulse mana yang diukur |
| `timeout` | unsigned long | (Opsional) Timeout dalam µs. Default: 1.000.000 µs (1 detik) |
| **Return** | unsigned long | Durasi pulse dalam µs, atau **0** jika timeout |

### **Cara Kerja**

```
Signal: ─────┐          ┌──────────
             │  HIGH    │
             └──────────┘
             │←── pulseIn() ──►│
             menunggu    mengukur
             HIGH mulai  durasi HIGH
```

1. `pulseIn()` **menunggu** sampai pin berubah ke `value` (HIGH)
2. Mulai **mengukur** durasi
3. Berhenti saat pin berubah ke **!value** (LOW)
4. **Return** durasi dalam µs

### **Timeout & Error Handling**

```cpp
long duration = pulseIn(ECHO_PIN, HIGH, 30000);  // Timeout 30ms (~5 meter)

if (duration == 0) {
  Serial.println("❌ Timeout! Tidak ada pantulan (objek terlalu jauh atau tidak ada?)");
  return -1;  // Indikator error
}

float distance = (duration * 0.034) / 2.0;
```

> ⚠️ **PENTING**: `pulseIn()` adalah **blocking function** — program berhenti sampai pulse selesai atau timeout. Untuk aplikasi yang butuh responsif (multi-tasking), pertimbangkan interrupt-based approach.

---

## 5️⃣ Sensor PIR HC-SR501 (Deteksi Gerakan)

### **Apa itu PIR?**

> **PIR** (Passive Infrared) sensor mendeteksi **perubahan radiasi infrared** yang dipancarkan oleh makhluk hidup (manusia, hewan). Sensor ini **tidak** memancarkan apapun — hanya "mendengar" perubahan IR.

### **Prinsip Kerja**

```
        ┌─────────────┐
        │  Fresnel     │  ← Lensa untuk fokuskan IR
        │  Lens        │
        │ ┌───┐ ┌───┐ │
        │ │ A │ │ B │ │  ← 2 sensor IR (pyroelectric)
        │ └───┘ └───┘ │
        └─────────────┘

Idle:    Sensor A = Sensor B = sama → LOW
Motion:  IR bergerak → A ≠ B → HIGH (motion detected!)
```

### **Spesifikasi HC-SR501**

| Parameter | Nilai |
|---|---|
| Tegangan Kerja | 4.5V - 20V (biasanya 5V) |
| Output | 3.3V HIGH / 0V LOW ✅ (aman untuk ESP32!) |
| Range Deteksi | ~3-7 meter (adjustable) |
| Sudut Deteksi | ~120° |
| Delay Time | 0.3s - 5 menit (adjustable via knob) |
| Trigger Mode | Single / Repeatable (jumper) |

> ✅ **Good News**: Output PIR HC-SR501 adalah **3.3V** — bisa langsung dihubungkan ke GPIO ESP32 **tanpa** voltage divider!

### **Adjustment Knobs**

```
HC-SR501 (tampak belakang):
┌──────────────────────┐
│  [Sensitivity]        │  ← Putar: jangkauan deteksi (CW = lebih jauh)
│  [Time Delay]         │  ← Putar: durasi output HIGH (CW = lebih lama)
│  [Jumper: H/L]        │  ← H = repeatable trigger, L = single trigger
└──────────────────────┘
```

### **Wiring PIR ke ESP32**

| PIR Pin | ESP32 | Keterangan |
|---|---|---|
| VCC | VIN (5V) | Power supply |
| OUT | GPIO4 | Output signal (3.3V) — langsung tanpa divider |
| GND | GND | Ground |

---

## 6️⃣ Interrupt Basics: Polling vs Interrupt

### **Masalah dengan Polling**

**Polling** = program terus-menerus **bertanya** apakah ada event:

```cpp
// Polling: bertanya terus-menerus
void loop() {
  int state = digitalRead(BUTTON_PIN);  // "Ada event?"
  if (state == LOW) {
    Serial.println("Button pressed!");   // Proses event
  }
  // ... kode lain yang butuh waktu lama ...
  delay(1000);  // ← Event bisa TERLEWAT di sini!
}
```

**Masalah Polling:**

- ❌ **Boros CPU**: terus menerus check, meskipun tidak ada event
- ❌ **Bisa miss event**: jika ada `delay()` atau kode lama, event bisa terlewat
- ❌ **Tidak responsif**: delay antara check bisa lama

---

### **Solusi: Interrupt**

**Interrupt** = hardware yang memberitahu CPU **saat event terjadi**, tanpa perlu ditanya:

```cpp
// Interrupt: hardware laporkan event otomatis
volatile bool buttonPressed = false;

// ISR: dipanggil OTOMATIS saat button ditekan
void IRAM_ATTR buttonISR() {
  buttonPressed = true;
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);
}

void loop() {
  if (buttonPressed) {
    Serial.println("Button pressed!");
    buttonPressed = false;
  }
  // ... kode lain yang butuh waktu lama ...
  delay(1000);  // ← Event TIDAK terlewat! ISR tetap dipanggil!
}
```

### **Analogi: Polling vs Interrupt**

| Aspek | Polling (Bertanya Terus) | Interrupt (Diberi Tahu) |
|---|---|---|
| **Analogi** | Cek HP tiap 5 menit: "ada pesan?" | Notifikasi bunyi saat pesan masuk |
| **CPU Usage** | Boros (selalu cek) | Efisien (cek hanya saat ada event) |
| **Responsivitas** | Bisa miss event | **Tidak pernah miss** |
| **Complexity** | Simple (sequential) | Sedikit lebih kompleks (ISR rules) |
| **Best For** | Sensor yang perlu baca rutin | Event yang jarang tapi penting |

---

## 7️⃣ `attachInterrupt()` & ISR

### **Syntax `attachInterrupt()`**

```cpp
attachInterrupt(digitalPinToInterrupt(pin), ISR_function, mode);
```

| Parameter | Keterangan |
|---|---|
| `digitalPinToInterrupt(pin)` | Konversi GPIO number ke interrupt number |
| `ISR_function` | Nama fungsi ISR yang akan dipanggil |
| `mode` | Kapan interrupt di-trigger |

### **Interrupt Modes**

| Mode | Trigger Saat |
|---|---|
| `RISING` | Signal berubah dari **LOW → HIGH** ↑ |
| `FALLING` | Signal berubah dari **HIGH → LOW** ↓ |
| `CHANGE` | Signal berubah (**apapun** perubahannya) |
| `LOW` | Signal sedang **LOW** |
| `HIGH` | Signal sedang **HIGH** (ESP32 only) |

### **Diagram Mode**

```
Signal: ─────┐          ┌──────────
             │          │
             └──────────┘

         FALLING↓   RISING↑
              │         │
           Trigger   Trigger
```

### **Contoh Lengkap**

```cpp
#define BUTTON_PIN  4
volatile int pressCount = 0;

// ISR: HARUS cepat, JANGAN pakai delay() atau Serial!
void IRAM_ATTR onButtonPress() {
  pressCount++;     // Increment counter (cepat!)
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Attach interrupt: saat button ditekan (FALLING edge)
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onButtonPress, FALLING);
}

void loop() {
  Serial.printf("Button pressed %d times\n", pressCount);
  delay(1000);
}
```

### **ESP32 Interrupt Pins**

> ✅ Di ESP32, **hampir semua GPIO** bisa digunakan untuk interrupt (GPIO 0-39). Ini berbeda dari Arduino Uno yang hanya punya 2 interrupt pin (D2, D3)!

**Pengecualian**: GPIO 6-11 (flash memory) — jangan dipakai.

---

## 8️⃣ Rules ISR & Volatile Variables

### **Rules untuk ISR (WAJIB diikuti!)**

ISR (Interrupt Service Routine) dijalankan di luar alur normal program. Ada aturan ketat:

| ✅ BOLEH | ❌ DILARANG |
|---|---|
| Set variable (`flag = true`) | `delay()` / `delayMicroseconds()` |
| Increment counter (`count++`) | `Serial.print()` / `Serial.println()` |
| Baca/tulis GPIO (`digitalWrite()`) | Operasi yang lama/blocking |
| `millis()` (aman di ESP32 untuk debounce) | `yield()` atau `vTaskDelay()` |
| Set flag untuk "process later" | Alokasi memory (`new`, `malloc`) |

### **Mengapa `IRAM_ATTR`?**

```cpp
void IRAM_ATTR myISR() {   // ← IRAM_ATTR penting!
  // ... code ISR ...
}
```

**`IRAM_ATTR`** menempatkan fungsi ISR di **IRAM** (Internal RAM) ESP32, bukan di Flash memory. Ini penting karena:

- ISR harus dijalankan **secepat mungkin**
- Akses Flash memory **lebih lambat** dari IRAM
- Jika ISR di Flash, bisa terjadi **crash** karena Flash cache miss

> ⚠️ **Selalu gunakan `IRAM_ATTR` untuk ISR di ESP32!** Tanpa ini, program bisa crash kapan saja.

### **Volatile Variables**

```cpp
volatile bool motionDetected = false;   // ← HARUS volatile!
volatile int  counter = 0;              // ← HARUS volatile!
```

**Mengapa `volatile`?**

- Compiler biasanya **mengoptimasi** variable yang "tampaknya" tidak berubah di loop
- Tapi ISR berjalan di luar alur normal — compiler tidak tahu bahwa ISR bisa mengubah variable!
- `volatile` memberitahu compiler: "**Jangan optimasi** variable ini — nilainya bisa berubah kapan saja dari luar!"

```cpp
// TANPA volatile (BUG! compiler mungkin optimasi):
bool flag = false;

void IRAM_ATTR myISR() {
  flag = true;     // Set di ISR
}

void loop() {
  if (flag) {       // ❌ Compiler mungkin SKIP pengecekan ini
    // ...          //    karena "flag tidak pernah diubah di loop()"
  }
}

// DENGAN volatile (BENAR!):
volatile bool flag = false;

void IRAM_ATTR myISR() {
  flag = true;     // Set di ISR
}

void loop() {
  if (flag) {       // ✅ Compiler SELALU baca ulang dari memory
    // ...
    flag = false;
  }
}
```

### **Pola ISR yang Benar**

```cpp
// ISR hanya set flag — CEPAT!
volatile bool eventFlag = false;

void IRAM_ATTR myISR() {
  eventFlag = true;   // Hanya set flag, JANGAN proses di sini
}

void loop() {
  if (eventFlag) {
    eventFlag = false;

    // ✅ Proses event di SINI (di loop, bukan di ISR)
    Serial.println("Event terjadi!");
    // ... aksi lainnya ...
  }
}
```

---

# BAGIAN 2: PERSIAPAN HARDWARE (15 menit)

## 9️⃣ Wiring HC-SR04 + Voltage Divider

### **⚠️ PERINGATAN PENTING: VOLTAGE LEVELS**

| Komponen | VCC | Signal Output | ESP32 Max |
|---|---|---|---|
| **HC-SR04** | **5V** | Echo = **5V** | GPIO max **3.6V** |
| **ESP32** | 3.3V | GPIO = 3.3V | — |

> 🚨 **BAHAYA!** Pin Echo HC-SR04 mengeluarkan sinyal **5V**. Jika langsung dihubungkan ke GPIO ESP32 (max 3.6V), bisa **merusak ESP32**!

### **Solusi: Voltage Divider**

Gunakan 2 resistor untuk menurunkan 5V → 3.33V:

```
                    HC-SR04
                   Echo Pin
                      │
                      │ (5V signal)
                      │
                  ┌───┤
                  │   │
              [R1=1kΩ]│
                  │   │
                  ├───┴──────────► ESP32 GPIO18
                  │                (3.33V ✅)
              [R2=2kΩ]
                  │
                  │
                 GND
```

**Perhitungan:**

```
Vout = Vin × R2 / (R1 + R2)
Vout = 5V × 2kΩ / (1kΩ + 2kΩ)
Vout = 5V × 2/3
Vout = 3.33V ✅ (di bawah 3.6V limit ESP32)
```

> 💡 **Tidak punya resistor 2kΩ?** Kamu bisa pakai **2 resistor 1kΩ seri** (= 2kΩ). Atau gunakan kombinasi 1kΩ + 2.2kΩ (Vout = 3.44V, masih aman).

### **Tabel Wiring Lengkap**

| HC-SR04 Pin | Hubungkan ke | Keterangan |
|---|---|---|
| VCC | ESP32 **VIN** | ⚠️ Harus 5V! Bukan 3V3! |
| Trig | ESP32 **GPIO5** | Trigger pulse (3.3V output OK) |
| Echo | **Voltage divider** → **GPIO18** | 5V → 3.33V via R1=1kΩ, R2=2kΩ |
| GND | ESP32 **GND** | Ground bersama |

### **Wiring Buzzer**

| Buzzer Pin | Hubungkan ke | Keterangan |
|---|---|---|
| (+) Positive | ESP32 **GPIO19** | Active buzzer — langsung berbunyi saat HIGH |
| (-) Negative | ESP32 **GND** | Ground |

> 📌 **Active Buzzer vs Passive Buzzer**:
> - **Active buzzer**: Sudah punya oscillator internal, langsung bunyi saat diberi tegangan. Kontrol dengan `digitalWrite()`.
> - **Passive buzzer**: Perlu sinyal PWM/tone untuk berbunyi. Bisa menghasilkan nada berbeda. Kontrol dengan `tone()`.
> 
> Kit starter kita menggunakan **active buzzer** — cukup ON/OFF saja!

### **Wiring LED Indikator (3 LED)**

| LED | ESP32 GPIO | Resistor | Keterangan |
|-----|-----------|----------|------------|
| LED Hijau (Aman) | **GPIO15** | 220Ω | Jarak > 50cm |
| LED Kuning (Waspada) | **GPIO16** | 220Ω | Jarak 20-50cm |
| LED Merah (Bahaya) | **GPIO17** | 220Ω | Jarak < 20cm |

---

## 🔗 Diagram Wiring Lengkap

```
ESP32 DevKit V1
┌──────────────────────────────┐
│                              │
│  VIN (5V) ──────────────────►│ HC-SR04 VCC
│                              │
│  GPIO5 (output) ────────────►│ HC-SR04 Trig
│                              │
│  GPIO18 (input) ◄──┐        │
│                     │        │
│               ┌─[1kΩ]─┐     │  Voltage Divider:
│               │        │     │  HC-SR04 Echo (5V)
│            HC-SR04   [2kΩ]   │  → 1kΩ → junction → GPIO18 (3.33V)
│            Echo Pin    │     │  → 2kΩ → GND
│               │       GND   │
│               └────────┘     │
│                              │
│  GND ──────────────────────►│ HC-SR04 GND
│                              │
│  GPIO19 ──── [Buzzer +] ──── GND (Buzzer -)
│                              │
│  GPIO15 ──── [220Ω] ──── [LED Hijau]  ──── GND
│  GPIO16 ──── [220Ω] ──── [LED Kuning] ──── GND
│  GPIO17 ──── [220Ω] ──── [LED Merah]  ──── GND
│                              │
└──────────────────────────────┘
```

> ⚠️ **Before Power ON Checklist:**
>
> - [ ] HC-SR04 VCC → **VIN (5V)**, BUKAN 3V3
> - [ ] Echo melalui **voltage divider** (1kΩ + 2kΩ) → GPIO18
> - [ ] Trig langsung ke GPIO5
> - [ ] Buzzer polaritas benar (+ ke GPIO19, - ke GND)
> - [ ] 3 LED dengan resistor 220Ω
> - [ ] **Tidak ada** VCC langsung ke GND

---

# BAGIAN 3: PRAKTIKUM HARDWARE (75 menit)

## ⚙️ Persiapan Praktikum

### **Hardware yang Dibutuhkan**

| Komponen | Qty | Keterangan |
|---|---|---|
| ESP32 DevKit V1 | 1 | Board mikrokontroller |
| Kabel USB Micro | 1 | Programming & power |
| HC-SR04 Ultrasonic | 1 | Sensor jarak |
| Resistor 1kΩ | 1 | Voltage divider (R1) |
| Resistor 2kΩ (atau 2×1kΩ) | 1 | Voltage divider (R2) |
| Buzzer Active | 1 | Alarm parking |
| LED Hijau, Kuning, Merah | 3 | Indikator jarak |
| Resistor 220Ω | 3 | Current limiting LED |
| Breadboard | 1 | Prototyping |
| Jumper Wire M-M | ~15 | Koneksi |

### **Software**

- ✅ Arduino IDE 2.x
- ✅ ESP32 Board Support
- ✅ **Tidak perlu library tambahan** — HC-SR04 hanya butuh `pulseIn()` (built-in)

---

## 📟 Praktikum 1: Baca Jarak Dasar

### **Tujuan**: Mengukur jarak dengan HC-SR04 dan menampilkan di Serial Monitor

---

### **Code:**

```cpp
/*
 * Praktikum 6.1: Baca Jarak Dasar
 * HC-SR04 → Serial Monitor
 */

// ── Pin Definitions ────────────────────────────
#define TRIG_PIN    5       // Trigger → GPIO5
#define ECHO_PIN    18      // Echo → GPIO18 (via voltage divider!)

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.println("================================");
  Serial.println("  Praktikum 6.1: Baca Jarak");
  Serial.println("  HC-SR04 Ultrasonic Sensor");
  Serial.println("================================");
  Serial.println();
  delay(1000);
}

// ── Fungsi Baca Jarak ──────────────────────────
float readDistance() {
  // Kirim trigger pulse (10µs)
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Baca durasi echo (timeout 30ms ≈ 5 meter)
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  // Timeout check
  if (duration == 0) {
    return -1;  // Error: tidak ada pantulan
  }

  // Hitung jarak (cm)
  float distance = (duration * 0.034) / 2.0;
  return distance;
}

void loop() {
  float jarak = readDistance();

  if (jarak < 0) {
    Serial.println("❌ Error: tidak ada pantulan (objek terlalu jauh?)");
  } else {
    Serial.printf("📏 Jarak: %.1f cm\n", jarak);
  }

  delay(200);  // Update 5x per detik
}
```

### **Expected Output:**

```
================================
  Praktikum 6.1: Baca Jarak
  HC-SR04 Ultrasonic Sensor
================================

📏 Jarak: 45.2 cm
📏 Jarak: 44.8 cm
📏 Jarak: 15.3 cm
📏 Jarak: 5.1 cm
```

### **Langkah Praktikum:**

1. Pasang wiring HC-SR04 (JANGAN lupa voltage divider di Echo!)
2. Upload code
3. Buka Serial Monitor (115200)
4. Dekatkan tangan ke sensor → jarak berkurang
5. Jauhkan tangan → jarak bertambah
6. Test batas: sangat dekat (<2cm) dan sangat jauh (>4m)

---

## 📟 Praktikum 2: Parking Sensor (Buzzer + LED)

### **Tujuan**: Membuat parking sensor — buzzer beep semakin cepat saat objek semakin dekat

**Logika Parking Sensor:**

| Jarak | LED | Buzzer | Keterangan |
|-------|-----|--------|------------|
| > 50 cm | 🟢 Hijau | OFF | Aman |
| 20-50 cm | 🟡 Kuning | Beep lambat (500ms) | Waspada |
| 10-20 cm | 🔴 Merah | Beep sedang (200ms) | Dekat! |
| < 10 cm | 🔴 Merah (blink) | Beep cepat (80ms) | Bahaya! |

---

### **Code:**

```cpp
/*
 * Praktikum 6.2: Parking Sensor
 * HC-SR04 + Buzzer + LED Indikator
 */

#define TRIG_PIN    5
#define ECHO_PIN    18
#define BUZZER_PIN  19
#define LED_GREEN   15
#define LED_YELLOW  16
#define LED_RED     17

float readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return -1;
  return (duration * 0.034) / 2.0;
}

void allLEDsOff() {
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  // Matikan semua
  digitalWrite(BUZZER_PIN, LOW);
  allLEDsOff();

  delay(200);
  Serial.println("\n");
  Serial.println("╔═══════════════════════════════════╗");
  Serial.println("║   🅿️ ESP32 Parking Sensor         ║");
  Serial.println("║   Pertemuan 6 - Mikrokontroller   ║");
  Serial.println("╚═══════════════════════════════════╝");
  Serial.println();
  Serial.println("✅ Sistem siap! Monitoring jarak...\n");
}

void loop() {
  float jarak = readDistance();

  allLEDsOff();
  digitalWrite(BUZZER_PIN, LOW);

  if (jarak < 0) {
    // Error — tidak ada pantulan
    Serial.println("⚠️ Out of range");
    delay(500);
    return;
  }

  // Tampilkan jarak
  Serial.printf("📏 Jarak: %5.1f cm  │  ", jarak);

  if (jarak > 50) {
    // ── AMAN ──
    digitalWrite(LED_GREEN, HIGH);
    Serial.println("🟢 AMAN");
    delay(200);

  } else if (jarak > 20) {
    // ── WASPADA ──
    digitalWrite(LED_YELLOW, HIGH);
    Serial.println("🟡 WASPADA");
    // Beep lambat
    digitalWrite(BUZZER_PIN, HIGH);
    delay(50);
    digitalWrite(BUZZER_PIN, LOW);
    delay(450);

  } else if (jarak > 10) {
    // ── DEKAT ──
    digitalWrite(LED_RED, HIGH);
    Serial.println("🔴 DEKAT!");
    // Beep sedang
    digitalWrite(BUZZER_PIN, HIGH);
    delay(50);
    digitalWrite(BUZZER_PIN, LOW);
    delay(150);

  } else {
    // ── BAHAYA ──
    Serial.println("🔴 BAHAYA!!!");
    // Beep cepat + LED merah blink
    for (int i = 0; i < 3; i++) {
      digitalWrite(LED_RED, HIGH);
      digitalWrite(BUZZER_PIN, HIGH);
      delay(40);
      digitalWrite(LED_RED, LOW);
      digitalWrite(BUZZER_PIN, LOW);
      delay(40);
    }
  }
}
```

### **Cara Test Parking Sensor:**

1. Upload code → Buka Serial Monitor
2. **Aman**: Tidak ada objek di depan sensor → LED hijau, buzzer OFF
3. **Waspada**: Dekatkan tangan ~30cm → LED kuning, buzzer beep lambat
4. **Dekat**: Dekatkan tangan ~15cm → LED merah, buzzer beep sedang
5. **Bahaya**: Dekatkan tangan <10cm → LED merah blink, buzzer beep cepat

---

## 📟 Praktikum 3: Interrupt Demo dengan Button

### **Tujuan**: Memahami interrupt — button press menghentikan/memulai monitoring jarak

---

### **Komponen Tambahan**

| Komponen | GPIO | Keterangan |
|---|---|---|
| Push Button | GPIO4 | Dengan internal pull-up |

### **Code:**

```cpp
/*
 * Praktikum 6.3: Interrupt Demo
 * Button interrupt untuk toggle monitoring ON/OFF
 */

#define TRIG_PIN    5
#define ECHO_PIN    18
#define BUTTON_PIN  4

// ── Volatile variables (diubah oleh ISR) ─────
volatile bool toggleFlag = false;

// ── Non-volatile ─────────────────────────────
bool monitoringOn = true;
unsigned long lastDebounceTime = 0;
const unsigned long DEBOUNCE_DELAY = 200;  // 200ms debounce

// ── ISR: dipanggil saat button ditekan ───────
void IRAM_ATTR onButtonPress() {
  toggleFlag = true;   // Set flag saja! Proses di loop()
}

float readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return -1;
  return (duration * 0.034) / 2.0;
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Attach interrupt pada FALLING edge (button press)
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onButtonPress, FALLING);

  delay(200);
  Serial.println("\n");
  Serial.println("╔═══════════════════════════════════╗");
  Serial.println("║   Interrupt Demo - Button Toggle   ║");
  Serial.println("║   Tekan button untuk ON/OFF        ║");
  Serial.println("╚═══════════════════════════════════╝");
  Serial.println();
  Serial.println("Monitoring: ON\n");
}

void loop() {
  // ── Handle interrupt flag ────────────────
  if (toggleFlag) {
    // Software debounce
    if (millis() - lastDebounceTime > DEBOUNCE_DELAY) {
      lastDebounceTime = millis();
      monitoringOn = !monitoringOn;  // Toggle
      Serial.printf("\n>>> Monitoring: %s <<<\n\n", monitoringOn ? "ON" : "OFF");
    }
    toggleFlag = false;
  }

  // ── Monitoring jarak ─────────────────────
  if (monitoringOn) {
    float jarak = readDistance();
    if (jarak < 0) {
      Serial.println("⚠️ Out of range");
    } else {
      Serial.printf("📏 Jarak: %.1f cm\n", jarak);
    }
  }

  delay(200);
}
```

### **Langkah Praktikum:**

1. Tambah push button: satu ujung ke GPIO4, ujung lain ke GND
2. Upload code → Buka Serial Monitor
3. Jarak ditampilkan terus-menerus (monitoring ON)
4. **Tekan button** → monitoring OFF (jarak berhenti update)
5. **Tekan lagi** → monitoring ON kembali
6. **Perhatikan**: meskipun ada `delay(200)` di loop, button press **TIDAK PERNAH TERLEWAT** karena interrupt!

> 💡 **Key Takeaway**: Interrupt memastikan event penting (button press) selalu terdeteksi, bahkan saat program sedang melakukan hal lain!

---

# 🏆 Project Akhir: Parking Sensor Lengkap

## **File**: `P06_Parking_Sensor.ino`

Project akhir menggabungkan semua yang dipelajari:

- ✅ HC-SR04 mengukur jarak
- ✅ Voltage divider untuk safety
- ✅ 3 LED indikator (hijau/kuning/merah)
- ✅ Buzzer beep rate berubah sesuai jarak
- ✅ Error handling (out of range)
- ✅ Serial output terformat

**Lihat file kode lengkap di**: `code/P06_Parking_Sensor.ino`

---

## 🌟 Challenge (Opsional — Bonus Poin!)

### **Challenge: PIR Motion Detection + Interrupt**

Tambah sensor PIR dengan interrupt:

- PIR mendeteksi gerakan → trigger ISR → set flag
- Counter gerakan (volatile)
- Serial menu: view stats, reset, toggle alarm
- Kombinasi: alarm jika ada gerakan DAN jarak dekat

**Lihat file kode lengkap di**: `code/P06_Challenge_PIR_Interrupt.ino`

---

## 📚 Konsep Penting — Ringkasan

### **HC-SR04**

| Fungsi/Rumus | Kegunaan |
|---|---|
| `pulseIn(ECHO, HIGH)` | Baca durasi echo (µs) |
| `distance = (duration × 0.034) / 2` | Hitung jarak (cm) |
| Trigger: 10µs HIGH pulse | Mulai pengukuran |
| Timeout: `pulseIn(pin, HIGH, 30000)` | Max 30ms (~5m) |

### **Interrupt**

| Fungsi | Kegunaan |
|---|---|
| `attachInterrupt(pin, ISR, mode)` | Daftarkan fungsi interrupt |
| `digitalPinToInterrupt(pin)` | Konversi GPIO → interrupt number |
| `IRAM_ATTR` | Tempatkan ISR di IRAM (wajib di ESP32) |
| `volatile` | Variable yang diubah di ISR |
| `RISING / FALLING / CHANGE` | Kapan interrupt trigger |
| `detachInterrupt(pin)` | Hapus interrupt |

### **Safety**

| Aturan | Keterangan |
|---|---|
| HC-SR04 VCC = **5V (VIN)** | Jangan pakai 3.3V! |
| Echo → **voltage divider** | 5V → 3.33V (1kΩ+2kΩ) |
| ISR harus cepat | No delay, no Serial |
| Selalu pakai `volatile` | Untuk variable yang diubah ISR |

---

## 🔗 Referensi

- [Random Nerd Tutorials — ESP32 HC-SR04](https://randomnerdtutorials.com/esp32-hc-sr04-ultrasonic-arduino/)
- [HC-SR04 Datasheet](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf)
- [Arduino pulseIn() Reference](https://www.arduino.cc/reference/en/language/functions/advanced-io/pulsein/)
- [ESP32 Interrupt Tutorial](https://randomnerdtutorials.com/esp32-external-wake-up-deep-sleep/)
- [Arduino attachInterrupt() Reference](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)

---

**Next**: Pertemuan 7 — Display LCD/OLED & Review 📺

---

**Materi ini dibuat untuk**: Mata Kuliah Mikrokontroller — Prodi Informatika Unmul
