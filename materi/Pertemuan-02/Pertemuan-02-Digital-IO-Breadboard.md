# Pertemuan 2: Digital I/O & Breadboard Basics

## Mata Kuliah Mikrokontroller - Prodi Informatika Unmul

> **"From One LED to Many - Mastering Digital Control!"** 💡

---

## 📋 Informasi Pertemuan

- **Durasi**: 3 × 50 menit (150 menit)
- **Tipe**: Teori + Praktikum Wokwi
- **Prerequisites**: Sudah selesai Pertemuan 1 (Blink LED onboard)
- **Deliverable**: Traffic Light simulation (screenshot + link Wokwi)
- **Batas Waktu**: 1 minggu setelah pertemuan

---

## 🎯 Tujuan Pembelajaran

Setelah pertemuan ini, mahasiswa mampu:

1. **Memahami** konsep GPIO (General Purpose Input/Output)
2. **Membedakan** digital HIGH vs LOW, input vs output
3. **Menggunakan** breadboard untuk prototyping circuit
4. **Mengimplementasikan** external LED dengan wiring yang benar
5. **Membaca** input dari push button
6. **Membuat** multiple LED pattern (traffic light)
7. **Menerapkan** pull-up resistor dan debouncing dasar

---

## 📖 Outline Materi

### **Bagian 1: Teori GPIO & Digital I/O (50 menit)**

1. Konsep GPIO (General Purpose Input/Output)
2. Digital Signal: HIGH vs LOW
3. pinMode(), digitalWrite(), digitalRead()
4. Pull-up dan Pull-down Resistor
5. Debouncing untuk Button

### **Bagian 2: Breadboard & Wiring (30 menit)**

6. Anatomi Breadboard
7. Wiring Best Practices
8. LED Basics (Review + Wiring)
9. Push Button Wiring

### **Bagian 3: Praktikum Wokwi (70 menit)**

10. External LED Blink
11. Button Control LED
12. Multiple LED Pattern
13. **Project**: Traffic Light Simulation

---

# BAGIAN 1: TEORI GPIO & DIGITAL I/O (50 menit)

## 1️⃣ Konsep GPIO (General Purpose Input/Output)

### **Apa itu GPIO?**

> **GPIO** adalah **pin yang bisa diprogram** untuk fungsi berbeda: baca sensor (input) atau kontrol aktuator (output).

### **Analogi GPIO = Pintu Rumah**

Bayangkan GPIO seperti **pintu rumah yang bisa 2 arah**:

- **OUTPUT Mode**: Pintu untuk **keluar** (ESP32 kirim signal keluar)
  - Contoh: Nyalakan LED, bunyikan buzzer, gerakkan motor
- **INPUT Mode**: Pintu untuk **masuk** (ESP32 terima signal dari luar)
  - Contoh: Baca button, baca sensor suhu, deteksi gerakan

**Satu GPIO** bisa jadi **INPUT atau OUTPUT**, tergantung kita set di program!

---

### **GPIO di ESP32**

ESP32 punya **34 GPIO pins**:

- GPIO0, GPIO1, GPIO2, ..., GPIO39
- Sebagian besar bisa jadi **INPUT atau OUTPUT**
- Beberapa **input-only** (GPIO34-39)
- **JANGAN pakai** GPIO6-11 (flash memory!)

**Voltage Level**:

- HIGH = **3.3V** (logic 1)
- LOW = **0V / GND** (logic 0)

⚠️ **PENTING**: ESP32 logic = **3.3V**, BUKAN 5V seperti Arduino Uno!

---

## 2️⃣ Digital Signal: HIGH vs LOW

### **Apa itu Digital Signal?**

Signal yang hanya punya **2 kemungkinan nilai**:

1. **HIGH** (tinggi) = 3.3V = Logic 1 = ON = TRUE
2. **LOW** (rendah) = 0V = Logic 0 = OFF = FALSE

### **Visualisasi Digital Signal**

```
Voltage (V)
  3.3V  ─┐     ┌─────┐     ┌─
         │     │     │     │
         │     │     │     │
  0V   ──┴─────┴─────┴─────┴───> Time
        HIGH  LOW   HIGH  LOW
        ON    OFF   ON    OFF
```

### **Bedanya dengan Analog**

| Aspek           | Digital            | Analog                  |
| --------------- | ------------------ | ----------------------- |
| **Nilai**       | 2 nilai (0 atau 1) | Infinite nilai (0-3.3V) |
| **Contoh**      | Switch ON/OFF      | Volume knob (0-100%)    |
| **ESP32 Read**  | `digitalRead()`    | `analogRead()`          |
| **ESP32 Write** | `digitalWrite()`   | `analogWrite()` / PWM   |

---

## 3️⃣ pinMode(), digitalWrite(), digitalRead()

### **A. pinMode() - Set Mode GPIO**

**Fungsi**: Menentukan GPIO sebagai INPUT atau OUTPUT

**Syntax**:

```cpp
pinMode(pin, mode);
```

**Parameter**:

- `pin`: GPIO number (contoh: 2, 15, 16)
- `mode`:
  - `OUTPUT` → GPIO untuk kirim signal (LED, buzzer)
  - `INPUT` → GPIO untuk terima signal (button, sensor)
  - `INPUT_PULLUP` → INPUT dengan internal pull-up resistor

**Contoh**:

```cpp
pinMode(2, OUTPUT);       // GPIO2 sebagai output (untuk LED)
pinMode(15, INPUT);       // GPIO15 sebagai input (untuk button)
pinMode(16, INPUT_PULLUP); // GPIO16 sebagai input dengan pull-up
```

**Kapan pakai?**: Di `setup()`, sebelum pakai GPIO!

---

### **B. digitalWrite() - Kirim Signal (OUTPUT)**

**Fungsi**: Set GPIO ke HIGH (3.3V) atau LOW (0V)

**Syntax**:

```cpp
digitalWrite(pin, value);
```

**Parameter**:

- `pin`: GPIO number
- `value`:
  - `HIGH` atau `1` → Set ke 3.3V (LED ON)
  - `LOW` atau `0` → Set ke 0V (LED OFF)

**Contoh**:

```cpp
digitalWrite(2, HIGH);  // GPIO2 = 3.3V (LED ON)
delay(1000);
digitalWrite(2, LOW);   // GPIO2 = 0V (LED OFF)
```

**Use Case**: Kontrol LED, buzzer, relay, motor (via driver)

---

### **C. digitalRead() - Baca Signal (INPUT)**

**Fungsi**: Baca status GPIO (HIGH atau LOW)

**Syntax**:

```cpp
int value = digitalRead(pin);
```

**Return**:

- `HIGH` (atau `1`) → Pin terdeteksi 3.3V
- `LOW` (atau `0`) → Pin terdeteksi 0V

**Contoh**:

```cpp
int buttonState = digitalRead(15);  // Baca GPIO15

if (buttonState == HIGH) {
  Serial.println("Button PRESSED!");
} else {
  Serial.println("Button NOT pressed");
}
```

**Use Case**: Baca button, switch, sensor digital (PIR, limit switch)

---

### **Flow Decision: INPUT or OUTPUT?**

```
┌─────────────────────────────────────┐
│ Apakah GPIO untuk KONTROL sesuatu?  │
│ (LED, buzzer, motor, relay)         │
└───────────┬─────────────────────────┘
            │
     ┌──────┴──────┐
     │    YES      │     NO
     ▼             ▼
  OUTPUT        INPUT
  (kirim)      (terima)
     │             │
     ▼             ▼
digitalWrite()  digitalRead()
```

---

## 4️⃣ Pull-up dan Pull-down Resistor

### **Problem: Floating Input**

Ketika button **TIDAK ditekan**, GPIO input tidak terhubung ke apa-apa = **floating**:

- Bisa baca HIGH, bisa LOW (random!)
- Tidak stabil, nilai berubah-ubah

**Solusi**: Pull-up atau Pull-down resistor!

---

### **A. Pull-up Resistor**

Resistor yang **"tarik" voltage ke HIGH** (3.3V) saat button tidak ditekan.

**Wiring**:

```
       3.3V
        │
       [R] 10kΩ (pull-up resistor)
        │
        ├─────── GPIO (INPUT)
        │
     [Button]
        │
       GND
```

**Logic**:

- Button **NOT pressed**: R tarik GPIO ke 3.3V → `digitalRead()` = **HIGH**
- Button **PRESSED**: GPIO terhubung ke GND → `digitalRead()` = **LOW**

**Code**:

```cpp
pinMode(15, INPUT_PULLUP);  // Enable internal pull-up

int state = digitalRead(15);
if (state == LOW) {
  // Button PRESSED (karena pull-up, pressed = LOW)
}
```

**Keuntungan**: ESP32 punya **internal pull-up**, tidak perlu resistor eksternal!

---

### **B. Pull-down Resistor**

Resistor yang **"tarik" voltage ke LOW** (GND) saat button tidak ditekan.

**Wiring**:

```
       3.3V
        │
     [Button]
        │
        ├─────── GPIO (INPUT)
        │
       [R] 10kΩ (pull-down resistor)
        │
       GND
```

**Logic**:

- Button **NOT pressed**: R tarik GPIO ke GND → `digitalRead()` = **LOW**
- Button **PRESSED**: GPIO terhubung ke 3.3V → `digitalRead()` = **HIGH**

**Note**: ESP32 **TIDAK punya** internal pull-down yang reliable. Lebih baik pakai pull-up!

---

### **Comparison Table**

| Aspek                       | Pull-up                 | Pull-down          |
| --------------------------- | ----------------------- | ------------------ |
| Default state (not pressed) | HIGH                    | LOW                |
| Pressed state               | LOW                     | HIGH               |
| Internal support di ESP32   | ✅ YES                  | ❌ NO (unreliable) |
| Wiring external resistor    | Opsional (ada internal) | Required           |
| **Recommendation**          | **USE THIS!**           | Avoid              |

**Best Practice**: Pakai `INPUT_PULLUP` untuk button! Simpel dan reliable.

---

## 5️⃣ Debouncing untuk Button

### **Problem: Button Bounce**

Button mekanik **tidak perfect**:

- Saat ditekan, contact metal **bounce** (loncat-loncat)
- Dalam 10-50ms, bisa terbaca pressed-released-pressed berkali-kali
- Program baca sebagai **multiple press**!

**Visualisasi**:

```
Physical Press: ─┐              ┌─
                 │ Pressed      │
                 └──────────────┘

Electrical Signal: ─┐┌┐┌─┐┌─────┌─
                    ││││ ││      │  ← Bounce!
                    └┘└┘ └┘      └─

Program Reads:  PRESS PRESS PRESS PRESS (4× dalam 1 press!)
```

---

### **Solution 1: Hardware Debouncing**

Tambah **capacitor** parallel dengan button (0.1μF - 1μF).

**Cons**: Butuh komponen tambahan.

---

### **Solution 2: Software Debouncing (Recommended)**

Tambah **delay** setelah detect button press.

**Simple Debounce**:

```cpp
int buttonState = digitalRead(BUTTON_PIN);

if (buttonState == LOW) {  // Pressed (pull-up)
  delay(50);  // Wait 50ms untuk bounce selesai

  // Baca lagi untuk confirm
  if (digitalRead(BUTTON_PIN) == LOW) {
    // Confirmed press!
    Serial.println("Button pressed");

    // Do action
    digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // Toggle LED

    // Wait until released
    while (digitalRead(BUTTON_PIN) == LOW) {
      delay(10);
    }
  }
}
```

---

### **Solution 3: State-based Debouncing (Advanced)**

Track button state dan timestamp.

```cpp
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int buttonState = HIGH;
int lastButtonReading = HIGH;

void loop() {
  int reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonReading) {
    lastDebounceTime = millis();  // Reset timer
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Stable reading untuk >50ms
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        // Button pressed action
        Serial.println("Button pressed (debounced)");
      }
    }
  }

  lastButtonReading = reading;
}
```

**Keuntungan**: Non-blocking (program tetap jalan), lebih robust.

---

# BAGIAN 2: BREADBOARD & WIRING (30 menit)

## 6️⃣ Anatomi Breadboard

### **Apa itu Breadboard?**

> **Breadboard** adalah papan untuk **prototyping circuit** tanpa soldering.

Lubang-lubang terhubung secara internal, bisa colok komponen dan wire.

---

### **Struktur Breadboard**

```
┌──────────────────────────────────────────────────┐
│  (-)  [─][─][─][─][─][─][─][─][─][─][─][─]  (-) │ ← Power Rail (GND)
│  (+)  [─][─][─][─][─][─][─][─][─][─][─][─]  (+) │ ← Power Rail (VCC)
├──────────────────────────────────────────────────┤
│       a   b   c   d   e   f   g   h   i   j      │
│   1  [│] [│] [│] [│] [│] [│] [│] [│] [│] [│]     │
│   2  [│] [│] [│] [│] [│] [│] [│] [│] [│] [│]     │ ← Terminal Strips
│   3  [│] [│] [│] [│] [│] [│] [│] [│] [│] [│]     │   (vertikal terhubung)
│   4  [│] [│] [│] [│] [│] [│] [│] [│] [│] [│]     │
│  ...                                             │
│  30  [│] [│] [│] [│] [│] [│] [│] [│] [│] [│]     │
├──────────────────────────────────────────────────┤
│  (+)  [─][─][─][─][─][─][─][─][─][─][─][─]  (+) │ ← Power Rail (VCC)
│  (-)  [─][─][─][─][─][─][─][─][─][─][─][─]  (-) │ ← Power Rail (GND)
└──────────────────────────────────────────────────┘
```

---

### **Koneksi Internal**

#### **1. Power Rails** (atas & bawah):

- Terhubung **HORIZONTAL** (sepanjang breadboard)
- (+) rail: untuk VCC (3.3V atau 5V)
- (-) rail: untuk GND
- ⚠️ **Tidak terhubung** kiri-kanan (perlu jumper jika ingin connect)

#### **2. Terminal Strips** (tengah):

- Terhubung **VERTICAL** dalam 1 kolom (a-b-c-d-e atau f-g-h-i-j)
- **GAP di tengah**: untuk IC (tapi ESP32 tidak ditaruh di breadboard, pakai jumper)
- Setiap row (1, 2, 3, ...) terpisah

---

### **Cara Pakai Breadboard**

1. **Hubungkan Power Rails**:

```
ESP32 3V3 ──jumper─> Breadboard (+) rail
ESP32 GND ──jumper─> Breadboard (-) rail
```

2. **Komponen Ambil Power dari Rails**:

```
LED Anode ──resistor─> (+) rail (3.3V)
LED Cathode ──────────> (-) rail (GND)
```

3. **Horizontal untuk Power, Vertical untuk Signal**:

- Power: pakai power rails (horizontal)
- Signal (GPIO): pakai terminal strips (vertical)

---

## 7️⃣ Wiring Best Practices

### **Color Coding** (Sangat Penting!)

| Warna              | Fungsi             | Keterangan           |
| ------------------ | ------------------ | -------------------- |
| **Merah**          | VCC / 3.3V / 5V    | Power positive       |
| **Hitam / Coklat** | GND                | Ground               |
| **Kuning**         | Signal / GPIO      | Data line            |
| **Hijau / Biru**   | Special (I2C, SPI) | SDA, SCL, MOSI, MISO |
| **Oranye / Putih** | Signal alternatif  | Multi-function GPIO  |

**Benefit**: Mudah troubleshoot, cepat trace wiring!

---

### **Wiring Tips**

✅ **DO**:

- Potong jumper wire **sepanjang yang dibutuhkan** (tidak terlalu panjang)
- Wiring **rapi** (hindari crossing/tumpang tindih)
- Test **satu komponen dulu** sebelum tambah komponen baru
- Foto circuit **sebelum disassemble** (untuk dokumentasi)

❌ **DON'T**:

- Kabel terlalu panjang dan berantakan
- Crossing wire berlebihan (susah trace)
- Langsung semua komponen (susah debug kalau error)

---

### **Before Power ON Checklist** (WAJIB!)

Sebelum hubungkan ESP32 ke USB, cek:

- [ ] Tidak ada VCC terhubung langsung ke GND (short circuit!)
- [ ] LED punya resistor pembatas arus (220Ω - 1kΩ)
- [ ] Polaritas LED benar (panjang=anode, pendek=cathode)
- [ ] Wiring sudah sesuai diagram
- [ ] Tidak ada wire longgar/lepas

---

## 8️⃣ LED Basics (Review + Wiring)

### **External LED vs Onboard LED**

| Aspek        | Onboard LED (P01)            | External LED (P02)         |
| ------------ | ---------------------------- | -------------------------- |
| **Location** | Di ESP32 board               | Di breadboard              |
| **Wiring**   | Tidak perlu (sudah built-in) | Perlu wire ke breadboard   |
| **Resistor** | Sudah ada di board           | **Harus tambah** resistor! |
| **GPIO**     | GPIO2 (fixed)                | Bebas pilih GPIO           |

---

### **Wiring External LED**

**Diagram**:

```
ESP32 GPIO ──┐
             │
            [R] 220Ω (resistor)
             │
            [LED] ← Anode (kaki panjang)
             │
            GND ← Cathode (kaki pendek)
```

**Wiring Steps di Wokwi**:

1. Add LED component
2. Add resistor 220Ω
3. Connect:
   - ESP32 GPIO → Resistor pin 1
   - Resistor pin 2 → LED anode (panjang / merah)
   - LED cathode (pendek / hitam) → GND

---

### **Mengapa Perlu Resistor?**

LED tanpa resistor = **Tarik arus berlebih** = **Terbakar**! 🔥

**Ohm's Law**: R = V / I

- V = Vsupply - Vled = 3.3V - 2V = 1.3V
- I = 10mA (LED safe current) = 0.01A
- R = 1.3V / 0.01A = **130Ω**

Karena resistor 130Ω jarang, pakai **220Ω** (lebih aman, LED agak redup) atau **330Ω**.

---

## 9️⃣ Push Button Wiring

### **Button with Internal Pull-up** (Recommended)

**Wiring**:

```
Button pin 1 ─── GPIO (INPUT_PULLUP)
Button pin 2 ─── GND
```

**Code**:

```cpp
pinMode(BUTTON_PIN, INPUT_PULLUP);

if (digitalRead(BUTTON_PIN) == LOW) {
  // Button PRESSED (pull-up = pressed is LOW)
}
```

**Keuntungan**: Simpel, tidak perlu resistor eksternal!

---

### **Button Logic (Pull-up)**

| Kondisi         | Voltage di GPIO         | `digitalRead()` |
| --------------- | ----------------------- | --------------- |
| **NOT pressed** | 3.3V (pull-up resistor) | **HIGH**        |
| **PRESSED**     | 0V (terhubung ke GND)   | **LOW**         |

⚠️ **PENTING**: Dengan pull-up, button pressed = **LOW** (kebalikan dari intuisi!)

---

# BAGIAN 3: PRAKTIKUM WOKWI (70 menit)

## 🌐 Praktikum 1: External LED Blink

### **Tujuan**: Menambah LED eksternal di breadboard Wokwi

---

### **Step 1: Buat Project Baru**

1. Login ke Wokwi
2. Click "New Project" → "ESP32"
3. Rename project: `P02_External_LED_[Nama]`

---

### **Step 2: Add Components**

1. Click tombol **"+"** di simulation area
2. Add komponen:
   - **LED** (Red LED)
   - **Resistor** (220 ohm)

Components akan muncul di simulation area.

---

### **Step 3: Wiring**

**Target Circuit**:

```
ESP32 GPIO15 → Resistor → LED Anode → LED Cathode → GND
```

**Cara Wiring di Wokwi**:

1. **Click GPIO15** di ESP32 board
2. **Drag** ke **resistor pin 1** (salah satu ujung resistor)
3. **Click resistor pin 2** (ujung satunya)
4. **Drag** ke **LED anode** (kaki panjang, biasanya merah di Wokwi)
5. **Click LED cathode** (kaki pendek, biasanya hitam)
6. **Drag** ke **GND** di ESP32

Wire akan otomatis terbentuk!

---

### **Step 4: Upload Code**

```cpp
/*
 * Praktikum 2.1: External LED Blink
 * GPIO: 15
 */

#define LED_PIN 15  // External LED di GPIO15

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("External LED Blink");
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED ON");
  delay(1000);

  digitalWrite(LED_PIN, LOW);
  Serial.println("LED OFF");
  delay(1000);
}
```

---

### **Step 5: Run & Verify**

1. Click **Play** ▶️
2. **Verify**:
   - LED merah di breadboard berkedip ON-OFF
   - Serial Monitor menampilkan output

**Selamat! External LED pertama Anda!** 🎉

---

## 🔘 Praktikum 2: Button Control LED

### **Tujuan**: Kontrol LED dengan push button

---

### **Wiring**:

```
ESP32 GPIO15 → Resistor 220Ω → LED → GND
ESP32 GPIO4  → Button pin 1
Button pin 2 → GND
```

**Di Wokwi**:

1. Keep LED dari praktikum 1
2. Add: **Push button**
3. Wire:
   - Button pin 1 → ESP32 GPIO4
   - Button pin 2 → GND

---

### **Code**:

```cpp
/*
 * Praktikum 2.2: Button Control LED
 */

#define LED_PIN 15
#define BUTTON_PIN 4

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Internal pull-up

  Serial.begin(115200);
  Serial.println("Button Control LED");
  Serial.println("Press button to toggle LED");
}

void loop() {
  // Baca button state
  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW) {  // Pressed (pull-up)
    Serial.println("Button PRESSED - LED ON");
    digitalWrite(LED_PIN, HIGH);
  } else {
    Serial.println("Button RELEASED - LED OFF");
    digitalWrite(LED_PIN, LOW);
  }

  delay(100);  // Small delay untuk stability
}
```

---

### **Test**:

1. Run simulation
2. **Click button** di Wokwi (dengan mouse)
3. **Verify**: LED ON saat button ditekan, OFF saat dilepas

---

## 🚦 Praktikum 3: Multiple LED - Traffic Light!

### **Tujuan**: Project akhir - simulasi lampu lalu lintas

---

### **Wiring 3 LED**:

```
GPIO15 → Resistor → LED Merah  → GND
GPIO16 → Resistor → LED Kuning → GND
GPIO17 → Resistor → LED Hijau  → GND
```

**Di Wokwi**:

1. Add 3× LED (merah, kuning, hijau)
2. Add 3× Resistor 220Ω
3. Wire sesuai diagram

---

### **Code - Traffic Light Simulation**:

```cpp
/*
 * ================================================
 * PROJECT: TRAFFIC LIGHT SIMULATION
 * ================================================
 *
 * Simulasi lampu lalu lintas dengan 3 LED:
 * - Merah: 5 detik
 * - Kuning: 2 detik
 * - Hijau: 5 detik
 * Loop repeat!
 */

// Pin definitions
#define RED_LED    15
#define YELLOW_LED 16
#define GREEN_LED  17

void setup() {
  // Set semua LED sebagai OUTPUT
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  Serial.begin(115200);
  Serial.println("=== TRAFFIC LIGHT SIMULATION ===");
  Serial.println("Red (5s) → Yellow (2s) → Green (5s)");
  Serial.println();
}

void loop() {
  // STATE 1: RED LIGHT (Stop!)
  Serial.println("🔴 RED - STOP!");
  digitalWrite(RED_LED, HIGH);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  delay(5000);  // 5 detik

  // STATE 2: YELLOW LIGHT (Get Ready!)
  Serial.println("🟡 YELLOW - GET READY!");
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  delay(2000);  // 2 detik

  // STATE 3: GREEN LIGHT (Go!)
  Serial.println("🟢 GREEN - GO!");
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  delay(5000);  // 5 detik

  Serial.println("--- Repeat ---\n");
  // Loop akan repeat dari awal
}
```

---

### **Test & Verify**:

1. Run simulation
2. **Observe**: LED berubah sesuai pattern:
   - Merah 5s → Kuning 2s → Hijau 5s → Repeat
3. **Serial Monitor**: Menampilkan state saat ini

---

### **Challenge (Opsional - Bonus!)**:

#### **Challenge 1: Button untuk Start/Stop**

Tambah button: tekan untuk start, tekan lagi untuk stop traffic light.

#### **Challenge 2: Pedestrian Button**

Tambah button pedestrian: saat ditekan, traffic light paksa ke merah untuk kasih jalan pejalan kaki.

#### **Challenge 3: Night Mode**

Lampu kuning berkedip saja (simulasi malam hari).

---

## 📤 Deliverable Pertemuan 2

### **Yang Harus Dikumpulkan**:

#### **1. Screenshot Wokwi Traffic Light** ✅

Screenshot harus menunjukkan:

- ✓ Wiring 3 LED dengan resistor (circuit diagram jelas)
- ✓ Simulation running (salah satu LED menyala)
- ✓ Code editor dengan full code
- ✓ Serial Monitor dengan output state

**File naming**: `P02_TrafficLight_[NIM]_[Nama].png`

---

#### **2. Link Wokwi Project** 🔗

- Save project dengan nama: `P02_TrafficLight_[NIM]_[Nama]`
- Click **Share** → Copy link
- Test link (buka di incognito mode)

---

#### **3. Video Demo** 📹 (Opsional tapi Recommended)

- Screen recording Wokwi simulation (10-30 detik)
- Tunjukkan 1 cycle lengkap (Merah → Kuning → Hijau)
- Upload ke Google Drive / YouTube (unlisted)

---

#### **4. (Bonus) Challenge** 🌟

Jika mengerjakan challenge:

- Screenshot challenge project
- Link Wokwi challenge
- Penjelasan modifikasi

**Bonus**: +15% dari nilai deliverable!

---

## 📊 Grading Criteria

| Kriteria                                    | Bobot |
| ------------------------------------------- | ----- |
| Wiring benar (3 LED + resistor + ESP32)     | 30%   |
| Code lengkap & simulation jalan             | 30%   |
| Traffic light pattern sesuai (timing benar) | 25%   |
| Screenshot & link Wokwi valid               | 10%   |
| Ketepatan waktu submit                      | 5%    |
| **Bonus**: Challenge                        | +15%  |

**Total maksimal**: 115%

---

## 🎓 Rangkuman Pertemuan 2

### **Konsep yang Dipelajari**:

✅ **GPIO**: General Purpose Input/Output (bisa IN atau OUT)  
✅ **Digital I/O**: HIGH (3.3V) vs LOW (0V)  
✅ **pinMode()**: Set GPIO sebagai INPUT atau OUTPUT  
✅ **digitalWrite()**: Kirim signal HIGH/LOW ke GPIO  
✅ **digitalRead()**: Baca signal dari GPIO  
✅ **Pull-up Resistor**: Stabilkan input button (internal di ESP32!)  
✅ **Breadboard**: Prototyping tanpa solder  
✅ **Multiple LED**: Kontrol banyak output bersamaan

### **Skills yang Didapat**:

✅ Wiring external LED dengan resistor  
✅ Baca input dari push button  
✅ Kontrol multiple LED untuk pattern  
✅ Debug circuit dengan visual di Wokwi  
✅ State machine sederhana (traffic light states)

### **Next Week Preview** (Pertemuan 3):

- Analog I/O & PWM
- LED dimmer (kontrol brightness)
- Potensiometer sensor
- Breathing LED effect
- Project: LED brightness control 🌟

---

## 📚 Referensi & Bahan Bacaan

### **Tutorial Wokwi**:

- [Wokwi ESP32 Guide](https://docs.wokwi.com/guides/esp32)
- [Wokwi LED Tutorial](https://docs.wokwi.com/parts/wokwi-led)
- [Wokwi Button Tutorial](https://docs.wokwi.com/parts/wokwi-pushbutton)

### **Konsep GPIO**:

- [ESP32 GPIO Explained](https://randomnerdtutorials.com/esp32-pinout-reference-gpios/)
- [Digital I/O Arduino](https://www.arduino.cc/reference/en/language/functions/digital-io/)

### **Video** (Indonesian):

- Search YouTube: "ESP32 LED Button Indonesia"
- Channel: Indobot, Kelas Robot

---

## ❓ FAQ

**Q: Apakah resistor 220Ω harus exact, atau boleh 330Ω atau 470Ω?**  
A: Boleh! Range 220Ω - 1kΩ aman untuk LED. Makin besar resistor, LED makin redup (tapi lebih aman).

**Q: Di Wokwi, LED tidak menyala. Kenapa?**  
A: Check wiring: (1) Resistor terhubung? (2) Polaritas LED benar? (3) Code `pinMode(OUTPUT)` sudah? (4) Reset simulation.

**Q: Button saya tidak berfungsi di Wokwi. Kenapa?**  
A: (1) Check wiring button ke GPIO & GND. (2) Pastikan pakai `INPUT_PULLUP`. (3) Logic: pressed = LOW (bukan HIGH).

**Q: Boleh tidak pakai Wokwi, langsung hardware ESP32 fisik?**  
A: Boleh, tapi untuk Pertemuan 2, **submission harus Wokwi** (untuk konsistensi penilaian). Hardware boleh untuk latihan tambahan.

**Q: Traffic light saya timing-nya beda (misal Merah 3s, Hijau 7s). Apakah masalah?**  
A: Tidak masalah! Boleh modifikasi timing, asal pattern-nya benar (Merah → Kuning → Hijau → Repeat). Tapi jika mau ikut standar: Merah 5s, Kuning 2s, Hijau 5s.

---

## 🆘 Troubleshooting

### **LED di Wokwi tidak menyala**:

- [ ] Check wiring (GPIO → Resistor → LED → GND)
- [ ] Polaritas LED: anode (panjang) ke resistor, cathode (pendek) ke GND
- [ ] Code: `pinMode(LED_PIN, OUTPUT)` sudah ada?
- [ ] Code: `digitalWrite(LED_PIN, HIGH)` sudah dipanggil?
- [ ] Reset simulation (click Reset button)

### **Button tidak merespon**:

- [ ] Wiring: Button pin 1 → GPIO, pin 2 → GND
- [ ] Code: `pinMode(BUTTON_PIN, INPUT_PULLUP)` sudah ada?
- [ ] Logic benar: dengan pull-up, pressed = LOW
- [ ] Coba click button di simulation (tidak perlu keyboard)

### **Traffic light tidak berubah**:

- [ ] Check semua 3 LED terhubung ke GPIO berbeda (15, 16, 17)
- [ ] Code: semua 3 LED sudah `pinMode(OUTPUT)`?
- [ ] Logic state: pastikan hanya 1 LED ON di tiap state
- [ ] Serial Monitor: apakah output menunjukkan state berubah?

---

<div align="center">

**🎉 Selamat! Anda Telah Menguasai Digital I/O!**

**Next**: Pertemuan 3 - Analog I/O & PWM

---

_"One LED, Two LEDs, Three LEDs... Soon IoT!"_ 🚀

**Mata Kuliah Mikrokontroller - Prodi Informatika Unmul**

</div>
