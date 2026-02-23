# Pertemuan 3: Analog I/O & PWM

## Mata Kuliah Mikrokontroller - Prodi Informatika Unmul

> **"From ON/OFF to Smooth Control - The Power of PWM!"** ⚡

---

## 📋 Informasi Pertemuan

- **Durasi**: 3 × 50 menit (150 menit)
- **Tipe**: Teori + Praktikum Wokwi
- **Prerequisites**: Pertemuan 1-2 (GPIO, Digital I/O)
- **Deliverable**: LED Dimmer dengan Potensiometer (screenshot + link Wokwi)
- **Batas Waktu**: 1 minggu setelah pertemuan

---

## 🎯 Tujuan Pembelajaran

Setelah pertemuan ini, mahasiswa mampu:

1. **Memahami** perbedaan analog vs digital
2. **Menggunakan** ADC (Analog-to-Digital Converter) untuk baca sensor
3. **Mengimplementasikan** PWM (Pulse Width Modulation) untuk kontrol LED brightness
4. **Membaca** nilai dari potensiometer (sensor analog)
5. **Mengontrol** LED brightness secara smooth (0-100%)
6. **Membuat** project LED dimmer interaktif

---

## 📖 Outline Materi

### **Bagian 1: Teori Analog I/O (50 menit)**

1. Analog vs Digital Signal
2. ADC (Analog-to-Digital Converter)
3. `analogRead()` di ESP32
4. PWM (Pulse Width Modulation)
5. `analogWrite()` vs `ledcWrite()`
6. Potensiometer Basics

### **Bagian 2: Konsep PWM Mendalam (40 menit)**

7. Duty Cycle Explained
8. PWM Frequency
9. LED Dimming dengan PWM
10. ESP32 LEDC (LED Controller)

### **Bagian 3: Praktikum Wokwi (60 menit)**

11. Baca Potensiometer (ADC Input)
12. LED Dimmer dengan PWM
13. **Project**: Interactive LED Brightness Control
14. Challenge: RGB LED Color Mixer

---

# BAGIAN 1: TEORI ANALOG I/O (50 menit)

## 1️⃣ Analog vs Digital Signal

### **Review: Digital Signal**

Digital = **2 nilai** (HIGH atau LOW):

```
Voltage
3.3V  ─┐   ┌───  ← HIGH
      │   │
0V  ──┴───┴────  ← LOW
```

**Contoh**: Button (pressed/not pressed), LED (on/off)

---

### **Analog Signal**

Analog = **infinite nilai** dalam range tertentu (0V - 3.3V):

```
Voltage
3.3V  ─────────────────
      ∿∿∿ (wave)
      │ │ │ │ │
0V  ──┴─┴─┴─┴─┴────
```

**Contoh**:

- Suara (mikrofon): 0-3.3V (volume bervariasi)
- Cahaya (LDR): 0-3.3V (terang-gelap-mid)
- Suhu (sensor analog): 0-3.3V (dingin-hangat-panas)
- Potensiometer: 0-3.3V (rotasi knob)

---

### **Perbandingan**

| Aspek             | Digital                          | Analog                                        |
| ----------------- | -------------------------------- | --------------------------------------------- |
| **Nilai**         | 2 (LOW/HIGH)                     | Infinite (0-3.3V)                             |
| **Contoh Sensor** | Button, PIR motion, limit switch | Potensiometer, LDR, thermistor, soil moisture |
| **ESP32 Read**    | `digitalRead()`                  | `analogRead()`                                |
| **Precision**     | 1-bit (0 atau 1)                 | **12-bit** (0-4095 di ESP32)                  |
| **Use Case**      | ON/OFF control                   | Measurement, smooth control                   |

---

### **Real-World Examples**

#### **Digital** (Diskrit):

- 💡 **Lampu kamar**: ON atau OFF
- 🚪 **Pintu**: Terbuka atau Tertutup
- 🔴 **Traffic light**: Merah, Kuning, atau Hijau (state diskrit)

#### **Analog** (Continuous):

- 🔆 **Brightness control**: 0% - 100% (smooth)
- 🎚️ **Volume speaker**: Pelan - Keras (gradual)
- 🌡️ **Suhu ruangan**: 20°C, 21.5°C, 22.3°C, ...

---

## 2️⃣ ADC (Analog-to-Digital Converter)

### **Apa itu ADC?**

> **ADC** = Circuit yang mengubah **voltage analog** (0-3.3V) menjadi **angka digital** (0-4095) yang bisa dibaca komputer.

### **Analogi ADC = Penggaris**

Bayangkan ADC seperti **penggaris** untuk mengukur voltage:

- Voltage analog = Panjang benda (continuous)
- ADC = Penggaris dengan skala (diskrit, misal mm)
- Output = Angka hasil ukur (misal: 15mm)

**ESP32** punya **penggaris 12-bit** = bisa ukur **4096 tingkat** (0-4095)!

---

### **ADC di ESP32**

**Spesifikasi**:

- **Resolution**: 12-bit (0 - 4095)
- **Voltage Range**: 0V - 3.3V
- **Channels**: 18 channel (GPIO32-39, GPIO25-27, GPIO32-33, GPIO14-15, GPIO12-13, GPIO2, GPIO0, GPIO4)
- **ADC1**: 8 channel (GPIO32-39) - **Recommended** (tidak conflict dengan WiFi)
- **ADC2**: 10 channel - **Avoid** (conflict dengan WiFi!)

**Formula Konversi**:

```
Voltage = (ADC_Value / 4095) × 3.3V

Example:
- ADC Value = 0    → 0V (GND)
- ADC Value = 2048 → 1.65V (setengah)
- ADC Value = 4095 → 3.3V (max)
```

---

### **GPIO ADC Pins** (Safe to Use)

| GPIO       | ADC Channel | Note               |
| ---------- | ----------- | ------------------ |
| **GPIO32** | ADC1_4      | ✅ Recommended     |
| **GPIO33** | ADC1_5      | ✅ Recommended     |
| **GPIO34** | ADC1_6      | ✅ Input only      |
| **GPIO35** | ADC1_7      | ✅ Input only      |
| **GPIO36** | ADC1_0      | ✅ Input only (VP) |
| **GPIO39** | ADC1_3      | ✅ Input only (VN) |

**Best Practice**: Pakai **GPIO32 atau GPIO33** untuk ADC (bisa INPUT/OUTPUT).

---

## 3️⃣ `analogRead()` di ESP32

### **Fungsi**

Baca nilai analog dari GPIO (return integer 0-4095).

### **Syntax**

```cpp
int value = analogRead(pin);
```

**Parameter**:

- `pin`: GPIO number yang punya ADC (32, 33, 34, 35, 36, 39)

**Return**:

- Integer **0 - 4095** (12-bit resolution)

---

### **Contoh**

```cpp
#define POT_PIN 34  // Potensiometer di GPIO34 (ADC1_6)

void setup() {
  Serial.begin(115200);
  // Tidak perlu pinMode untuk ADC!
}

void loop() {
  int potValue = analogRead(POT_PIN);  // 0-4095

  // Konversi ke voltage
  float voltage = (potValue / 4095.0) * 3.3;

  // Konversi ke percentage
  int percentage = map(potValue, 0, 4095, 0, 100);

  Serial.print("ADC: ");
  Serial.print(potValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage);
  Serial.print("V | Percentage: ");
  Serial.print(percentage);
  Serial.println("%");

  delay(500);
}
```

**Output**:

```
ADC: 2048 | Voltage: 1.65V | Percentage: 50%
ADC: 3072 | Voltage: 2.48V | Percentage: 75%
ADC: 4095 | Voltage: 3.30V | Percentage: 100%
```

---

### **Helper Function: `map()`**

`map()` = Scale nilai dari range tertentu ke range lain.

**Syntax**:

```cpp
long map(long value, long fromLow, long fromHigh, long toLow, long toHigh);
```

**Example**:

```cpp
// Scale ADC (0-4095) to LED brightness (0-255)
int brightness = map(potValue, 0, 4095, 0, 255);

// Scale ADC (0-4095) to servo angle (0-180)
int angle = map(potValue, 0, 4095, 0, 180);

// Scale ADC (0-4095) to percentage (0-100)
int percent = map(potValue, 0, 4095, 0, 100);
```

**Note**: `map()` does **linear scaling** (proportional).

---

## 4️⃣ PWM (Pulse Width Modulation)

### **Problem: Digital Output hanya HIGH/LOW**

Dengan `digitalWrite()`, LED hanya bisa **ON (100%)** atau **OFF (0%)**.

**Bagaimana cara membuat LED 50% brightness?** 🤔

---

### **Solution: PWM!**

> **PWM** = Technically HIGH/LOW sangat cepat, tapi **mata manusia** melihatnya sebagai **brightness di antaranya**!

### **Visualisasi PWM**

```
100% Duty Cycle (Always ON):
3.3V  ████████████████████████  ← LED terang penuh

50% Duty Cycle (Half ON, Half OFF):
3.3V  ████░░░░████░░░░████░░░░  ← LED setengah terang
      ON  OFF ON  OFF ON  OFF

25% Duty Cycle:
3.3V  ██░░░░░░██░░░░░░██░░░░░░  ← LED redup
      ON OFF  ON OFF  ON OFF

0% Duty Cycle (Always OFF):
0V    ░░░░░░░░░░░░░░░░░░░░░░░░  ← LED mati
```

**Mata manusia** tidak bisa deteksi ON-OFF di speed tinggi (> 100 Hz) = melihat sebagai **brightness average**!

---

### **PWM Parameters**

#### **1. Duty Cycle**

Persentase waktu signal ON dalam 1 periode.

- **100% duty cycle** = Always ON = Full brightness
- **50% duty cycle** = Half ON, half OFF = Half brightness
- **0% duty cycle** = Always OFF = No light

**Formula**:

```
Duty Cycle (%) = (ON Time / Period) × 100%
```

---

#### **2. Frequency**

Berapa kali cycle dalam 1 detik (Hz).

- **Low frequency** (< 100 Hz): LED berkedip (mata bisa deteksi)
- **High frequency** (> 1000 Hz): LED smooth (mata tidak deteksi kedip)

**ESP32 default**: 5000 Hz (5 kHz) = Sangat smooth!

---

### **PWM Use Cases**

| Application         | Control     | Range                  |
| ------------------- | ----------- | ---------------------- |
| **LED Dimmer**      | Brightness  | 0% - 100%              |
| **Motor Speed**     | RPM         | Slow - Fast            |
| **Servo Angle**     | Position    | 0° - 180°              |
| **Buzzer Tone**     | Frequency   | Low pitch - High pitch |
| **Heating Element** | Temperature | Cool - Hot             |

---

## 5️⃣ `analogWrite()` vs `ledcWrite()`

### **Arduino Classic: `analogWrite()`**

Di Arduino Uno/Nano:

```cpp
analogWrite(pin, value);  // value: 0-255 (8-bit)
```

**Note**: ESP32 **TIDAK SUPPORT** `analogWrite()`! 🚫

---

### **ESP32: `ledcWrite()` via LEDC**

ESP32 pakai **LEDC (LED Controller)** peripheral = hardware PWM yang powerful!

**Setup 3-step**:

1. **Configure channel**: Set frequency & resolution
2. **Attach pin**: Hubungkan GPIO ke channel
3. **Write value**: Set duty cycle

---

### **ESP32 LEDC Example**

```cpp
#define LED_PIN 15
#define PWM_CHANNEL 0    // Channel 0-15 (ESP32 punya 16 channel!)
#define PWM_FREQ 5000    // 5 kHz
#define PWM_RESOLUTION 8 // 8-bit (0-255)

void setup() {
  // 1. Setup PWM (NEW API: combines setup + attach)
  ledcAttach(LED_PIN, PWM_FREQ, PWM_RESOLUTION);
}

void loop() {
  // 2. Write duty cycle to pin directly (0-255 untuk 8-bit)
  ledcWrite(LED_PIN, 255);  // 100% brightness
  delay(1000);

  ledcWrite(LED_PIN, 128);  // 50% brightness
  delay(1000);

  ledcWrite(LED_PIN, 64);   // 25% brightness
  delay(1000);

  ledcWrite(LED_PIN, 0);    // 0% (OFF)
  delay(1000);
}
```

---

### **LEDC Functions Explained**

#### **1. `ledcSetup(channel, freq, resolution)`**

Configure PWM channel.

**Parameters**:

- `channel`: 0-15 (ESP32 punya 16 channel PWM independen!)
- `freq`: Frequency in Hz (recommended: 5000 untuk LED)
- `resolution`: Bit depth:
  - 8-bit: 0-255 (sama seperti Arduino)
  - 10-bit: 0-1023
  - 12-bit: 0-4095
  - 16-bit: 0-65535

**Return**: Actual frequency (might be slightly different)

---

#### **2. `ledcAttachPin(pin, channel)`**

Hubungkan GPIO pin ke PWM channel.

**Parameters**:

- `pin`: GPIO number (hampir semua GPIO bisa PWM!)
- `channel`: Channel yang sudah di-setup (0-15)

---

#### **3. `ledcWrite(channel, value)`**

Set duty cycle value.

**Parameters**:

- `channel`: Channel number (0-15)
- `value`: 0 - max (tergantung resolution)
  - 8-bit: 0-255
  - 10-bit: 0-1023
  - 12-bit: 0-4095

---

### **Resolution Comparison**

| Resolution | Range   | Steps | Best For                      |
| ---------- | ------- | ----- | ----------------------------- |
| **8-bit**  | 0-255   | 256   | ✅ LED dimming (cukup smooth) |
| **10-bit** | 0-1023  | 1024  | Servo control                 |
| **12-bit** | 0-4095  | 4096  | High-precision control        |
| **16-bit** | 0-65535 | 65536 | Audio, ultra-smooth           |

**Recommendation**: Pakai **8-bit** untuk LED (simple & cukup!).

---

## 6️⃣ Potensiometer Basics

### **Apa itu Potensiometer?**

> **Potensiometer** (Pot) = **Variable resistor** yang bisa diubah dengan putar knob.

Fungsi: Kontrol voltage (0V - 3.3V) secara manual.

---

### **Anatomi Potensiometer**

Pot punya **3 pin**:

```
        ┌─────────┐
        │  Knob   │ ← Rotatable
        └────┬────┘
             │
        ┌────┴────┐
       Pin1 Pin2 Pin3
        │    │    │
       VCC  OUT  GND
```

---

### **Pin Configuration**

| Pin                   | Connect To     | Voltage         |
| --------------------- | -------------- | --------------- |
| **Pin 1** (VCC)       | 3.3V           | Fixed 3.3V      |
| **Pin 2** (Wiper/OUT) | GPIO (ADC pin) | Variable 0-3.3V |
| **Pin 3** (GND)       | GND            | Fixed 0V        |

**How it works**:

- Knob **full CCW** (counter-clockwise): Pin2 = 0V (GND)
- Knob **middle**: Pin2 = 1.65V (half)
- Knob **full CW** (clockwise): Pin2 = 3.3V (VCC)

---

### **Wiring Potensiometer**

```
Pot Pin 1 (VCC)  ─── ESP32 3.3V
Pot Pin 2 (OUT)  ─── ESP32 GPIO34 (ADC pin)
Pot Pin 3 (GND)  ─── ESP32 GND
```

**Di Wokwi**:

1. Add component: "Potentiometer"
2. Wire:
   - Pot VCC → ESP32 3V3
   - Pot SIG (signal/wiper) → ESP32 GPIO34
   - Pot GND → ESP32 GND

---

### **Read Potensiometer**

```cpp
#define POT_PIN 34

void setup() {
  Serial.begin(115200);
}

void loop() {
  int potValue = analogRead(POT_PIN);  // 0-4095

  Serial.print("Pot Value: ");
  Serial.println(potValue);

  delay(100);
}
```

**Test di Wokwi**: Drag knob potensiometer, lihat nilai berubah di serial monitor!

---

## 7️⃣ Duty Cycle Explained

### **Mathematical Definition**

```
Duty Cycle (%) = (Pulse Width / Period) × 100%

Example:
Period = 1ms
Pulse Width = 0.5ms
Duty Cycle = (0.5 / 1) × 100% = 50%
```

---

### **Visual Examples**

```
Period = 10ms, Frequency = 100Hz

10% Duty Cycle:
│█│░░░░░░░░░│█│░░░░░░░░░│  ← 1ms ON, 9ms OFF
 1ms  9ms    1ms  9ms

50% Duty Cycle:
│█████│░░░░░│█████│░░░░░│  ← 5ms ON, 5ms OFF
 5ms   5ms   5ms   5ms

90% Duty Cycle:
│█████████│░│█████████│░│  ← 9ms ON, 1ms OFF
   9ms   1ms   9ms   1ms
```

---

### **Brightness vs Duty Cycle**

| Duty Cycle | LED Brightness | Visual           |
| ---------- | -------------- | ---------------- |
| 0%         | OFF            | ░░░░░░░░░░░░░░░░ |
| 25%        | Redup          | ██░░░░ (faint)   |
| 50%        | Setengah       | ████░░ (medium)  |
| 75%        | Terang         | ██████ (bright)  |
| 100%       | Maksimal       | ████████ (full)  |

---

## 8️⃣ PWM Frequency

### **Frequency vs Periode**

```
Frequency (Hz) = 1 / Period (seconds)

Examples:
- 1 Hz = 1 cycle per second = Period 1s
- 100 Hz = 100 cycles per second = Period 10ms
- 5000 Hz = 5000 cycles per second = Period 0.2ms
```

---

### **Frequency Effect on LED**

| Frequency    | Effect                                   | Recommendation                 |
| ------------ | ---------------------------------------- | ------------------------------ |
| **1 Hz**     | Visible blinking (ON-OFF setiap 1 detik) | ❌ Terlalu lambat              |
| **50 Hz**    | Slight flicker (masih deteksi kedip)     | ❌ Kurang smooth               |
| **100 Hz**   | Barely visible flicker                   | ⚠️ Batas minimum               |
| **500 Hz**   | Smooth (mata sudah tidak deteksi)        | ✅ OK                          |
| **5000 Hz**  | Very smooth                              | ✅ **Recommended!**            |
| **10000 Hz** | Ultra smooth                             | ✅ OK (tapi tidak perlu lebih) |

**Best Practice**: Pakai **5000 Hz (5 kHz)** untuk LED dimming!

---

# BAGIAN 3: PRAKTIKUM WOKWI (60 menit)

## 🌐 Praktikum 1: Baca Potensiometer

### **Tujuan**: Membaca nilai analog dari potensiometer dan tampilkan di serial monitor

---

### **Wiring**:

```
Potensiometer:
  VCC → ESP32 3V3
  SIG → ESP32 GPIO34 (ADC pin)
  GND → ESP32 GND
```

---

### **Code**:

```cpp
/*
 * Praktikum 3.1: Baca Potensiometer (ADC)
 */

#define POT_PIN 34  // GPIO34 (ADC1_6)

void setup() {
  Serial.begin(115200);
  Serial.println("Potensiometer ADC Reader");
  Serial.println("Turn the knob to see values change!");
}

void loop() {
  // Baca ADC value (0-4095)
  int potValue = analogRead(POT_PIN);

  // Konversi ke voltage (0-3.3V)
  float voltage = (potValue / 4095.0) * 3.3;

  // Konversi ke percentage (0-100%)
  int percentage = map(potValue, 0, 4095, 0, 100);

  // Print ke serial monitor
  Serial.print("ADC: ");
  Serial.print(potValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 2);  // 2 decimal places
  Serial.print("V | Percentage: ");
  Serial.print(percentage);
  Serial.println("%");

  delay(100);  // Update 10× per detik
}
```

---

### **Test di Wokwi**:

1. Run simulation
2. **Drag knob** potensiometer (mouse)
3. Observe serial monitor:
   - Knob kiri penuh → ADC ~0, Voltage ~0V, 0%
   - Knob tengah → ADC ~2048, Voltage ~1.65V, 50%
   - Knob kanan penuh → ADC ~4095, Voltage ~3.3V, 100%

---

## 💡 Praktikum 2: LED Dimmer dengan PWM

### **Tujuan**: Control Brightness LED dengan PWM (duty cycle 0-100%)

---

### **Wiring**:

```
GPIO15 → Resistor 220Ω → LED → GND
```

---

### **Code**:

```cpp
/*
 * Praktikum 3.2: LED Dimmer (PWM)
 */

#define LED_PIN 15
#define PWM_CHANNEL 0
#define PWM_FREQ 5000     // 5 kHz
#define PWM_RESOLUTION 8  // 8-bit (0-255)

void setup() {
  // Setup PWM (NEW API)
  ledcAttach(LED_PIN, PWM_FREQ, PWM_RESOLUTION);

  Serial.begin(115200);
  Serial.println("LED Brightness Fading");
}

void loop() {
  // Fade UP (0 → 255)
  for (int brightness = 0; brightness <= 255; brightness++) {
    ledcWrite(LED_PIN, brightness);
    Serial.print("Brightness: ");
    Serial.println(brightness);
    delay(10);  // 10ms per step = 2.55s total
  }

  delay(500);  // Pause at max

  // Fade DOWN (255 → 0)
  for (int brightness = 255; brightness >= 0; brightness--) {
    ledcWrite(LED_PIN, brightness);
    Serial.print("Brightness: ");
    Serial.println(brightness);
    delay(10);
  }

  delay(500);  // Pause at min
}
```

---

### **Test di Wokwi**:

- Run simulation
- **Observe**: LED **breathing effect** (fade in → fade out → repeat)
- Serial monitor: Brightness value 0-255

---

## 🎚️ Praktikum 3: Interactive LED Dimmer (PROJECT UTAMA!)

### **Tujuan**: Kontrol LED brightness dengan potensiometer (real-time)

---

### **Wiring**:

```
Potensiometer:
  VCC → ESP32 3V3
  SIG → ESP32 GPIO34
  GND → ESP32 GND

LED:
  GPIO15 → Resistor 220Ω → LED → GND
```

---

### **Code**:

```cpp
/*
 * ================================================
 * PROJECT: INTERACTIVE LED DIMMER
 * ================================================
 *
 * Control LED brightness dengan potensiometer:
 * - Pot full left: LED OFF
 * - Pot middle: LED 50% brightness
 * - Pot full right: LED MAX brightness
 */

// Pin definitions
#define POT_PIN 34       // Potensiometer (ADC)
#define LED_PIN 15       // LED output

// PWM settings
#define PWM_CHANNEL 0
#define PWM_FREQ 5000
#define PWM_RESOLUTION 8  // 8-bit = 0-255

void setup() {
  // Setup PWM untuk LED (NEW API)
  ledcAttach(LED_PIN, PWM_FREQ, PWM_RESOLUTION);

  Serial.begin(115200);
  Serial.println("=== INTERACTIVE LED DIMMER ===");
  Serial.println("Turn potentiometer to control LED brightness!");
}

void loop() {
  // Baca potensiometer (0-4095)
  int potValue = analogRead(POT_PIN);

  // Scale ke PWM range (0-255)
  int brightness = map(potValue, 0, 4095, 0, 255);

  // Set LED brightness (write to pin directly)
  ledcWrite(LED_PIN, brightness);

  // Calculate percentage
  int percentage = map(brightness, 0, 255, 0, 100);

  // Print status
  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print(" | Brightness: ");
  Serial.print(brightness);
  Serial.print("/255 (");
  Serial.print(percentage);
  Serial.println("%)");

  delay(50);  // Update 20× per detik (responsive!)
}
```

---

### **Test di Wokwi**:

1. Run simulation
2. **Drag potensiometer knob** (slow atau fast)
3. **Observe**: LED brightness berubah real-time mengikuti pot!
4. Serial monitor: Menampilkan pot value, brightness, percentage

**Expected Behavior**:

- Pot 0% → LED OFF
- Pot 25% → LED redup
- Pot 50% → LED setengah terang
- Pot 75% → LED terang
- Pot 100% → LED maksimal

---

## 📤 Deliverable Pertemuan 3

### **Yang Harus Dikumpulkan**:

#### **1. Screenshot Wokwi LED Dimmer** ✅

Screenshot harus menunjukkan:

- ✓ Wiring: Potensiometer + LED dengan resistor
- ✓ Simulation running (LED menyala dengan brightness tertentu)
- ✓ Potensiometer knob di posisi tertentu (tidak full OFF/ON)
- ✓ Code editor dengan full code
- ✓ Serial Monitor dengan output pot value & brightness

**File naming**: `P03_LEDDimmer_[NIM]_[Nama].png`

---

#### **2. Link Wokwi Project** 🔗

- Save project: `P03_LEDDimmer_[NIM]_[Nama]`
- Share & copy link
- Test link (incognito mode)

---

#### **3. Video Demo** 📹 (Highly Recommended!)

- Screen recording (10-20 detik)
- Tunjukkan: **Putar potensiometer dari 0% → 100%**, LED brightness berubah smooth
- Upload & paste link

---

#### **4. Challenge (Opsional - Bonus!)** 🌟

**Challenge 1: Breathing LED dengan Variable Speed**

- Potensiometer kontrol speed breathing (lambat-cepat)
- Link Wokwi challenge

**Challenge 2: RGB LED Color Mixer** (Advanced!)

- 3× Potensiometer (Red, Green, Blue)
- 1× RGB LED
- Mix warna dengan adjust 3 pot!

**Bonus**: +20% dari nilai deliverable!

---

## 🎓 Rangkuman Pertemuan 3

### **Konsep yang Dipelajari**:

✅ **Analog vs Digital**: Continuous vs discrete signal  
✅ **ADC**: Convert voltage (0-3.3V) → number (0-4095)  
✅ **`analogRead()`**: Baca sensor analog (potensiometer, LDR, dll)  
✅ **PWM**: Duty cycle untuk kontrol smooth (LED brightness, motor speed)  
✅ **LEDC**: ESP32 hardware PWM (16 channel independen!)  
✅ **`ledcWrite()`**: Set PWM duty cycle  
✅ **`map()`**: Scale nilai dari range ke range lain

### **Skills yang Didapat**:

✅ Baca sensor analog (potensiometer)  
✅ Kontrol LED brightness dengan PWM  
✅ Real-time interactive control  
✅ Understand duty cycle & frequency

### **Next Week Preview** (Pertemuan 4):

- Serial Communication & Debugging
- String manipulation
- Parsing input dari serial monitor
- Interactive LED control via keyboard
- Project: LED control command system 💻

---

## 📚 Referensi

### **ESP32 ADC & PWM**:

- [ESP32 ADC Guide](https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/)
- [ESP32 PWM with Arduino IDE](https://randomnerdtutorials.com/esp32-pwm-arduino-ide/)
- [ESP32 LEDC Tutorial](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/ledc.html)

### **PWM Explained**:

- [PWM Tutorial - SparkFun](https://learn.sparkfun.com/tutorials/pulse-width-modulation)
- [Arduino PWM](https://www.arduino.cc/en/Tutorial/Foundations/PWM)

---

<div align="center">

**🎉 Selamat! Anda Sudah Menguasai Analog I/O & PWM!**

**Next**: Pertemuan 4 - Serial Communication & Debugging

---

_"From Digital Clicks to Analog Smoothness!"_ ⚡

**Mata Kuliah Mikrokontroller - Prodi Informatika Unmul**

</div>
