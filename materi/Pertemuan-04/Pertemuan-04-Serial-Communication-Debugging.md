# Pertemuan 4: Serial Communication & Debugging

## Mata Kuliah Mikrokontroller - Prodi Informatika Unmul

> **"Talk to Your ESP32 - The Power of Serial Communication!"** 📡

---

## 📋 Informasi Pertemuan

- **Durasi**: 3 × 50 menit (150 menit)
- **Tipe**: Teori + Praktikum Wokwi
- **Prerequisites**: Pertemuan 1-3 (GPIO, Digital I/O, PWM)
- **Deliverable**: Serial Menu Interaktif (screenshot + link Wokwi)
- **Batas Waktu**: 1 minggu setelah pertemuan

---

## 🎯 Tujuan Pembelajaran

Setelah pertemuan ini, mahasiswa mampu:

1. **Memahami** konsep UART dan komunikasi serial
2. **Menggunakan** `Serial.print()` dan `Serial.println()` untuk output
3. **Menerima input** dari Serial Monitor menggunakan `Serial.read()` dan `Serial.parseInt()`
4. **Membuat** program interaktif berbasis serial menu
5. **Menggunakan** Serial Plotter untuk visualisasi data real-time
6. **Menerapkan** debugging strategies dengan serial prints

---

## 📖 Outline Materi

### **Bagian 1: Teori Serial Communication (50 menit)**

1. Apa itu UART & Komunikasi Serial?
2. Baud Rate
3. Fungsi-fungsi `Serial` di ESP32
4. Serial Monitor di Arduino IDE
5. Debugging dengan Serial

### **Bagian 2: Serial Input & Parsing (30 menit)**

6. Menerima Input dari Serial Monitor
7. Parsing String & Integer
8. Pola pembuatan Menu Interaktif
9. **HardwareSerial** — UART1/UART2 dengan Custom Pin

### **Bagian 3: Praktikum Wokwi (70 menit)**

9. Hello World & Sensor Output
10. Serial Plotter: Visualisasi Sinyal
11. LED Control via Serial Command
12. **Project**: Interactive Serial Menu

---

# BAGIAN 1: TEORI SERIAL COMMUNICATION (50 menit)

## 1️⃣ Apa itu UART & Komunikasi Serial?

### **Review: Cara Komputer Berkomunikasi**

Ada 2 cara utama mengirim data:

| Metode       | Cara Kerja                                        | Contoh                   |
| ------------ | ------------------------------------------------- | ------------------------ |
| **Parallel** | Banyak bit sekaligus lewat banyak kabel           | Printer jadul (LPT port) |
| **Serial**   | Satu bit per satu, secara berurutan lewat 1 kabel | USB, UART, SPI, I2C      |

---

### **UART (Universal Asynchronous Receiver-Transmitter)**

> **UART** = Protokol serial yang sangat sederhana – dua perangkat berkomunikasi hanya dengan **2 kabel**: TX dan RX.

**Cara kerja**:

```
Device A                    Device B
  TX  ─────────────────►  RX     (A kirim → B terima)
  RX  ◄─────────────────  TX     (B kirim → A terima)
  GND ─────────────────── GND    (Ground bersama)
```

**UART Properties**:

- **Asynchronous**: Tidak ada clock signal terpisah
- **Full-duplex**: Bisa kirim dan terima secara bersamaan
- **Point-to-point**: Komunikasi 2 perangkat saja

---

### **ESP32 ↔ PC via USB**

Saat kamu hubungkan ESP32 ke PC via USB, sebetulnya terjadi konversi:

```
ESP32 (UART0)
  TX (GPIO1) ──► CH340G/CP2102 ──► USB ──► PC
  RX (GPIO3) ◄── CH340G/CP2102 ◄── USB ◄── PC
```

**CH340G / CP2102** = IC converter UART-to-USB (ada di board ESP32)

Di sisi PC, muncul sebagai **COM port** (Windows) atau **/dev/ttyUSB** (Linux/Mac).

---

### **Serial Ports di ESP32**

ESP32 punya **3 hardware UART**:

| Port      | TX Default | RX Default | Kegunaan                                   |
| --------- | ---------- | ---------- | ------------------------------------------ |
| **UART0** | GPIO1      | GPIO3      | Default `Serial` – debugging ke PC via USB |
| **UART1** | GPIO10     | GPIO9      | ⚠️ Terhubung ke SPI Flash — harus remap!   |
| **UART2** | GPIO17     | GPIO16     | Free to use (GPS, GSM, sensor eksternal)   |

> ⚠️ **PERHATIAN — UART1 (GPIO9/GPIO10)**: Pin default UART1 terhubung ke **SPI Flash internal** ESP32. Jika kamu langsung pakai GPIO9/GPIO10 untuk UART1, program bisa **crash atau tidak stabil**! Gunakan `HardwareSerial` dengan custom pin (lihat Seksi 9).

> 📌 **Catatan Board Khusus**: Pin UART di atas berlaku untuk **ESP32 standar** (DevKit). Jika kamu pakai **ESP32-S3**, layoutnya **berbeda sama sekali** — selalu cek pinout board spesifik kamu sebelum wiring!

**Best Practice**: Gunakan **UART0** (`Serial`) untuk debugging ke PC. Gunakan **UART2** atau UART1 dengan custom pin untuk komunikasi ke perangkat eksternal.

---

## 2️⃣ Baud Rate

### **Apa itu Baud Rate?**

> **Baud Rate** = Kecepatan transmisi data dalam **bits per second (bps)**.

**Analogi**: Bayangkan baud rate seperti **kecepatan bicara**:

- Baud rate rendah = bicara pelan (lebih mudah diproses)
- Baud rate tinggi = bicara cepat (lebih efisien, butuh hardware handal)

---

### **Common Baud Rates**

| Baud Rate  | Kecepatan         | Keterangan                                   |
| ---------- | ----------------- | -------------------------------------------- |
| 9600       | 9.600 bit/detik   | Legacy, Arduino default (lebih lambat)       |
| 57600      | 57.600 bit/detik  | Medium speed                                 |
| **115200** | 115.200 bit/detik | **ESP32 Recommended** – cukup cepat & stabil |
| 250000     | 250.000 bit/detik | High speed (untuk data besar)                |
| 1000000    | 1 Mbit/detik      | Ultra high (butuh hardware yang bagus)       |

> ⚠️ **PENTING**: Baud rate di **ESP32** dan **Serial Monitor** HARUS sama! Jika berbeda → output menjadi **garbage characters** (karakter acak/rusak).

---

### **Contoh Baud Rate Mismatch**

**ESP32**: `Serial.begin(115200);`  
**Serial Monitor**: dipilih `9600`

**Hasil di Serial Monitor**:

```
ÿþý³ÿ²þ½ÿ²þ½ÿ²þ½ÿ   ← Garbage! (baud rate mismatch)
```

**Fix**: Ganti baud rate di Serial Monitor ke `115200`.

---

## 3️⃣ Fungsi-fungsi `Serial` di ESP32

### **Inisialisasi**

```cpp
void setup() {
  Serial.begin(115200);   // Baud rate 115200
  // ⚠️ Hati-hati: while (!Serial) bisa hang selamanya di ESP32
  // jika Serial Monitor tidak dibuka. Umumnya TIDAK diperlukan di ESP32.
  // while (!Serial);     // Hanya butuh di Arduino Leonardo/Micro
}
```

---

### **Output Functions**

#### **`Serial.print(data)`**

Print data **tanpa** newline di akhir.

```cpp
Serial.print("Suhu: ");
Serial.print(28.5);
// Output: "Suhu: 28.5" (CURSOR TETAP DI SINI)
```

---

#### **`Serial.println(data)`**

Print data **dengan** newline (`\r\n`) di akhir.

```cpp
Serial.println("Hello World!");
// Output: "Hello World!" lalu pindah ke baris baru
```

---

#### **Formatting Numbers**

```cpp
float suhu = 28.567;
Serial.println(suhu);        // Output: 28.57 (default 2 desimal)
Serial.println(suhu, 1);     // Output: 28.6 (1 desimal)
Serial.println(suhu, 4);     // Output: 28.5670 (4 desimal)

int angka = 255;
Serial.println(angka);       // Output: 255 (decimal)
Serial.println(angka, HEX);  // Output: FF (hexadecimal)
Serial.println(angka, BIN);  // Output: 11111111 (binary)
Serial.println(angka, OCT);  // Output: 377 (octal)
```

---

#### **`Serial.printf()` — Format String (Recommended!)**

```cpp
// printf style formatting – lebih ringkas & powerful!
Serial.printf("Suhu: %.2f°C, Kelembaban: %d%%\n", 28.5, 65);
// Output: "Suhu: 28.50°C, Kelembaban: 65%"

int x = 10, y = 20, z = 30;
Serial.printf("X=%d, Y=%d, Z=%d\n", x, y, z);
// Output: "X=10, Y=20, Z=30"
```

**Format specifiers**:

| Specifier | Type    | Contoh                        |
| --------- | ------- | ----------------------------- |
| `%d`      | Integer | `42` → `"42"`                 |
| `%f`      | Float   | `3.14` → `"3.140000"`         |
| `%.2f`    | Float   | `3.14` → `"3.14"` (2 desimal) |
| `%s`      | String  | `"hello"` → `"hello"`         |
| `%c`      | Char    | `'A'` → `"A"`                 |
| `%%`      | Literal | `%` → `"%"`                   |
| `\n`      | Newline | Pindah baris                  |

---

#### **`Serial.write(byte)`**

Kirim raw byte (bukan untuk teks):

```cpp
Serial.write(65);   // Kirim byte 65 = karakter 'A'
Serial.write('A');  // Sama hasilnya
```

---

### **Ringkasan Output Functions**

```cpp
// Output ke Serial Monitor:
Serial.print("text");           // Tanpa newline
Serial.println("text");         // Dengan newline
Serial.printf("format", arg);   // Printf style (ESP32!)

// Value examples:
Serial.println(42);             // Integer: "42"
Serial.println(3.14);           // Float: "3.14"
Serial.println(3.14, 4);        // Float 4 des: "3.1400"
Serial.println(255, HEX);       // Hex: "FF"
Serial.println(255, BIN);       // Binary: "11111111"
```

---

## 4️⃣ Serial Monitor di Arduino IDE

### **Cara Membuka**

1. Upload code ke ESP32
2. Klik **ikon kaca pembesar** (pojok kanan atas) atau `Ctrl+Shift+M`
3. **Pilih baud rate** yang SAMA dengan `Serial.begin()` — biasanya `115200`
4. Lihat output muncul!

---

### **Tampilan Serial Monitor**

```
┌─────────────────────────────────────────────────────┐
│  📨 Serial Monitor                              ×   │
├─────────────────────────────────────────────────────┤
│  Output dari ESP32:                                  │
│  > Hello World!                                      │
│  > ADC Value: 2048                                   │
│  > Suhu: 28.5°C                                      │
│                                                      │
├─────────────────┬───────────────────────────────────┤
│  [Input field]  │ [Send]  │ Baud: [115200 ▼]         │
└─────────────────────────────────────────────────────┘
```

---

### **Features Serial Monitor**

| Feature          | Cara Pakai                                          |
| ---------------- | --------------------------------------------------- |
| **Baud Rate**    | Dropdown kanan bawah – harus match `Serial.begin()` |
| **Autoscroll**   | Checkbox – aktifkan agar output selalu terlihat     |
| **Timestamp**    | Checkbox – tambahkan timestamp tiap baris           |
| **Line Ending**  | Pilih "Both NL & CR" untuk input terbaik            |
| **Clear Output** | Klik icon trash 🗑️                                  |
| **Input**        | Ketik di input field → tekan Enter atau [Send]      |

---

### **Serial Plotter**

> **Serial Plotter** = Real-time graph dari data serial. Sangat berguna untuk visualisasi sensor!

**Cara membuka**: `Tools` → `Serial Plotter` (atau `Ctrl+Shift+L`)

**Format output untuk Serial Plotter**:

```cpp
// Cara 1: Single value
Serial.println(analogValue);        // 1 garis

// Cara 2: Multiple values (dipisah spasi atau tab)
Serial.print(suhu);
Serial.print(" ");
Serial.println(kelembaban);          // 2 garis

// Cara 3: Labeled values (Arduino IDE 2.x)
Serial.printf("Suhu:%f Kelembaban:%f\n", suhu, kelembaban);
```

> 💡 **Tip**: Buka Serial Plotter saat praktikum untuk lihat sinyal PWM naik-turun secara visual!

---

## 5️⃣ Debugging dengan Serial

### **Filosofi Debugging**

> **Debugging** = Proses menemukan dan memperbaiki bug dalam program.

**Golden Rule**: "Jika kamu tidak tahu apa yang terjadi di dalam program, **print saja semuanya!**"

---

### **Strategi Debugging dengan Serial**

#### **1. Print variable values**

```cpp
void loop() {
  int sensor = analogRead(34);
  Serial.printf("DEBUG: sensor=%d\n", sensor);  // Debug print!

  int mapped = map(sensor, 0, 4095, 0, 255);
  Serial.printf("DEBUG: mapped=%d\n", mapped);  // Debug print!

  ledcWrite(LED_PIN, mapped);
}
```

**Cara membaca**: Lihat apakah nilai masuk akal. Kalau `sensor` selalu 0 → masalah di wiring!

---

#### **2. Print di titik penting (Checkpoint)**

```cpp
void setup() {
  Serial.begin(115200);
  Serial.println("🚀 Setup started...");

  if (!ledcAttach(LED_PIN, 5000, 8)) {
    Serial.println("❌ ledcAttach FAILED!");
  } else {
    Serial.println("✅ LEDC OK");
  }

  Serial.println("✅ Setup complete!");
}
```

---

#### **3. Conditional Debug Mode**

```cpp
#define DEBUG true   // Ganti false untuk production

void debugPrint(String msg) {
  if (DEBUG) {
    Serial.println("[DEBUG] " + msg);
  }
}

void loop() {
  int val = analogRead(34);
  debugPrint("Sensor value: " + String(val));   // Hanya print jika DEBUG=true
}
```

---

#### **4. Timestamp untuk Timing Issues**

```cpp
void loop() {
  unsigned long startTime = millis();   // Catat waktu mulai

  // ... beberapa operasi yang mungkin lambat ...
  delay(100);

  unsigned long elapsed = millis() - startTime;
  Serial.printf("Loop took: %lu ms\n", elapsed);  // Berapa lama loop?
}
```

---

### **Common Debugging Issues**

| Problem                     | Kemungkinan Penyebab              | Debug Cara                             |
| --------------------------- | --------------------------------- | -------------------------------------- |
| Serial tidak output apa-apa | Baud rate mismatch                | Cek baud rate di Serial Monitor        |
| Garbage characters          | Baud rate mismatch                | Ganti baud rate Serial Monitor         |
| Value selalu 0              | Wiring salah, pin tidak terhubung | Print pin value, cek diagram           |
| Program freeze/hang         | Infinite loop, blocking code      | Print sebelum dan sesudah tiap section |
| Nilai tidak masuk akal      | Range/scale salah                 | Print nilai setelah setiap konversi    |

---

# BAGIAN 2: SERIAL INPUT & PARSING (30 menit)

## 6️⃣ Menerima Input dari Serial Monitor

### **Input Functions**

#### **`Serial.available()`**

Cek apakah ada data yang bisa dibaca di buffer.

```cpp
int bytesAvailable = Serial.available();  // Return jumlah byte di buffer
// 0 = tidak ada data
// > 0 = ada data masuk
```

---

#### **`Serial.read()`**

Baca 1 byte dari buffer. Return `-1` jika tidak ada data.

```cpp
if (Serial.available() > 0) {
  char c = Serial.read();   // Baca 1 karakter
  Serial.print("Received: ");
  Serial.println(c);
}
```

---

#### **`Serial.readString()`**

Baca seluruh string dari buffer (tunggu timeout 1 detik).

```cpp
if (Serial.available() > 0) {
  String input = Serial.readString();
  input.trim();  // Hapus whitespace/newline di ujung
  Serial.println("Diterima: " + input);
}
```

---

#### **`Serial.parseInt()`**

Parsing integer dari input serial. Skip karakter non-angka, lalu baca digit.

```cpp
if (Serial.available() > 0) {
  int nilai = Serial.parseInt();   // "123abc" → 123
  Serial.printf("Integer: %d\n", nilai);
}
```

---

#### **`Serial.parseFloat()`**

Parsing float dari input serial.

```cpp
if (Serial.available() > 0) {
  float nilai = Serial.parseFloat();  // "3.14xyz" → 3.14
  Serial.printf("Float: %.2f\n", nilai);
}
```

---

### **Input Handling Pattern**

Pola yang paling umum dan reliable:

```cpp
void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');  // Baca sampai Enter
    input.trim();                                  // Bersihkan whitespace

    Serial.print("Input diterima: ");
    Serial.println(input);

    // Process input...
    processInput(input);
  }
}

void processInput(String cmd) {
  if (cmd == "help") {
    Serial.println("Perintah yang tersedia...");
  } else if (cmd == "status") {
    Serial.println("Sistem normal!");
  } else {
    Serial.println("Perintah tidak dikenali: " + cmd);
  }
}
```

---

## 7️⃣ Parsing String & Integer

### **String Methods yang Sering Dipakai**

```cpp
String s = "  Hello World  ";

// ⚠️ Metode IN-PLACE: langsung mengubah isi String s (tidak perlu di-assign ulang)
s.trim();                         // s = "Hello World"
s.toLowerCase();                  // s = "hello world"
s.toUpperCase();                  // s = "HELLO WORLD"
s.replace("World", "ESP32");      // s = "HELLO ESP32"  ← ⚠️ in-place, bukan return!

// Metode READ-ONLY: return nilai, s TIDAK berubah
int    len = s.length();          // 11
int    pos = s.indexOf("World");  // 6
bool   sw  = s.startsWith("H");   // true
bool   ew  = s.endsWith("2");     // true
String sub = s.substring(0, 5);   // "HELLO" (String baru, s tetap)

// Konversi String ↔ angka
int   i  = s.toInt();             // String → int
float f  = s.toFloat();           // String → float
String s2 = String(42);           // int → String: "42"
String s3 = String(3.14, 2);      // float → String: "3.14"
```

---

### **Parsing Command dengan Parameter**

```cpp
// Input: "LED:128"  (format "COMMAND:VALUE")
void processCommand(String cmd) {
  int colonIndex = cmd.indexOf(':');
  if (colonIndex == -1) {
    // Tidak ada ':'
    handleSingleCommand(cmd);
    return;
  }

  String command = cmd.substring(0, colonIndex);   // "LED"
  String valueStr = cmd.substring(colonIndex + 1); // "128"
  int value = valueStr.toInt();                     // 128

  Serial.printf("Command: %s, Value: %d\n", command.c_str(), value);

  if (command == "LED") {
    value = constrain(value, 0, 255);   // Batasi 0-255 agar aman
    ledcWrite(LED_PIN, value);
    Serial.printf("LED brightness set to: %d\n", value);
  } else if (command == "DELAY") {
    value = constrain(value, 0, 5000);  // Max 5 detik – jangan sampai hang!
    delay(value);
    Serial.printf("Delayed %d ms\n", value);
  }
}
```

---

## 8️⃣ Pola Menu Interaktif

### **Konsep Menu-driven Program**

```
User mengetik → ESP32 terima → Parse input → Jalankan aksi → Tampilkan result
```

---

### **Contoh Simple Menu**

```cpp
void printMenu() {
  Serial.println("\n=== ESP32 Control Menu ===");
  Serial.println("1. LED ON");
  Serial.println("2. LED OFF");
  Serial.println("3. Blink 5x");
  Serial.println("4. Read Sensor");
  Serial.println("0. Tampilkan Menu lagi");
  Serial.println("==========================");
  Serial.print("Pilih (0-4): ");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    Serial.println(input);    // Echo input
    int choice = input.toInt();

    switch (choice) {
      case 1:
        // Gunakan ledcWrite() bukan digitalWrite() agar bisa PWM!
        ledcWrite(LED_PIN, 255);   // LED ON (brightness max)
        Serial.println("✅ LED ON");
        break;
      case 2:
        ledcWrite(LED_PIN, 0);     // LED OFF (brightness 0)
        Serial.println("✅ LED OFF");
        break;
      case 3:
        blinkLED(5);
        break;
      case 4:
        readAndPrintSensor();
        break;
      case 0:
        printMenu();
        break;
      default:
        Serial.println("❌ Pilihan tidak valid! Pilih 0-4.");
        break;
    }
    Serial.println();
  }
}
```

---

## 9️⃣ HardwareSerial — Menggunakan UART1 / UART2

> Sumber referensi: [Random Nerd Tutorials — ESP32 UART Communication](https://randomnerdtutorials.com/esp32-uart-communication-serial-arduino/)

### **Kapan Butuh HardwareSerial?**

Kamu butuh `HardwareSerial` saat:

- Menghubungkan modul GPS, GSM, Bluetooth ke ESP32
- Komunikasi **antar dua ESP32 board**
- Pakai lebih dari satu UART secara bersamaan

---

### **Cara Membuat Custom Serial (UART2)**

```cpp
// Buat instance HardwareSerial pada UART2
HardwareSerial mySerial(2);

// GPIO16 = RX default UART2, GPIO17 = TX default UART2
// Kamu bisa juga pakai pin lain, misal: RX_PIN=4, TX_PIN=5
#define RX_PIN 16
#define TX_PIN 17

void setup() {
  Serial.begin(115200);      // UART0 – untuk debug ke PC

  // UART2 – untuk komunikasi ke perangkat lain
  // Format: begin(baudRate, config, RX_pin, TX_pin)
  mySerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

  Serial.println("UART2 siap di GPIO" + String(RX_PIN) + "(RX) dan GPIO" + String(TX_PIN) + "(TX)");
}

void loop() {
  // Kirim data lewat UART2
  mySerial.println("Hello dari ESP32!");

  // Baca data dari UART2 (jika ada perangkat terhubung)
  if (mySerial.available()) {
    String msg = mySerial.readStringUntil('\n');
    Serial.println("UART2 terima: " + msg);
  }

  delay(1000);
}
```

> 💡 **Tips pin aman untuk UART1**: Pakai misalnya GPIO4 (RX) dan GPIO5 (TX) — hindari GPIO9/GPIO10 (SPI Flash) dan GPIO2 (onboard LED/boot mode pada banyak board).

---

### **Memahami Format `SERIAL_8N1`**

Saat memanggil `mySerial.begin()`, ada parameter kedua yaitu **serial frame format**:

```cpp
mySerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
//                    ^^^^^^^^^
//                    Format frame UART
```

`SERIAL_8N1` merupakan format yang paling umum digunakan, artinya:

| Komponen | Nilai       | Arti                               |
| -------- | ----------- | ---------------------------------- |
| `8`      | 8 data bits | Ukuran data per frame              |
| `N`      | No parity   | Tidak ada bit parity (error check) |
| `1`      | 1 stop bit  | Penanda akhir frame                |

Format lain yang tersedia: `SERIAL_7E1`, `SERIAL_8O2`, dll. — tapi **99% kasus pakai `SERIAL_8N1`** sudah cukup.

---

### **Contoh: Komunikasi Antar Dua ESP32**

Skenario ini membutuhkan **2 board ESP32**. Hubungkan:

- TX board A (GPIO19) → RX board B (GPIO21)
- GND board A → GND board B

#### **Code Board Sender (Pengirim)**

```cpp
/*
 * ESP32 UART Sender
 * Mengirim counter ke board lain via UART1
 * Referensi: Random Nerd Tutorials
 */

#define TXD1 19   // TX ke board penerima
#define RXD1 21   // RX dari board penerima

HardwareSerial mySerial(1);  // Pakai UART1 dengan custom pin
int counter = 0;

void setup() {
  Serial.begin(115200);                           // UART0 – debug
  mySerial.begin(9600, SERIAL_8N1, RXD1, TXD1);  // UART1 – ke board lain
  Serial.println("ESP32 UART Transmitter siap!");
}

void loop() {
  mySerial.println(String(counter));              // Kirim via UART1
  Serial.println("Sent: " + String(counter));    // Log ke Serial Monitor
  counter++;
  delay(1000);
}
```

#### **Code Board Receiver (Penerima)**

```cpp
/*
 * ESP32 UART Receiver
 * Menerima data dari board lain via UART1
 * Wiring: GPIO21 (RX board ini) ← GPIO19 (TX board sender)
 * Referensi: Random Nerd Tutorials
 */

// Pin dari perspektif board PENERIMA:
#define MY_RX 21   // terima dari TX sender (GPIO19)
#define MY_TX 19   // kirim balik (opsional, tidak dipakai di contoh ini)

HardwareSerial mySerial(1);  // Pakai UART1 dengan custom pin

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600, SERIAL_8N1, MY_RX, MY_TX);
  Serial.println("ESP32 UART Receiver siap!");
}

void loop() {
  if (mySerial.available()) {
    String message = mySerial.readStringUntil('\n');
    Serial.println("Received: " + message);       // Tampilkan data diterima
  }
}
```

**Expected Output** (Serial Monitor Board Penerima):

```
ESP32 UART Receiver siap!
Received: 0
Received: 1
Received: 2
...
```

---

### **Ringkasan HardwareSerial**

|                | `Serial` (UART0)      | `HardwareSerial mySerial(2)` (UART2) |
| -------------- | --------------------- | ------------------------------------ |
| Pin            | GPIO1(TX) / GPIO3(RX) | Custom — bebas pilih GPIO            |
| Tujuan         | Debug ke PC           | Komunikasi ke modul/board lain       |
| Bisa parallel? | ✅ Ya                 | ✅ Ya                                |
| Konflik flash? | Tidak                 | Tidak (jika bukan GPIO9/10)          |

---

# BAGIAN 3: PRAKTIKUM WOKWI (70 menit)

## 🖥️ Persiapan Wokwi

### **Komponen yang Dibutuhkan (di Wokwi)**

1. **ESP32 DevKit V1** (default)
2. **LED** (1 buah)
3. **Resistor 220Ω** (1 buah)
4. **Potensiometer** (1 buah, untuk praktikum serial plotter)

---

## 📟 Praktikum 1: Hello World & Sensor Output

### **Tujuan**: Memahami Serial.print() & Serial.println()

---

### **Code**:

```cpp
/*
 * Praktikum 4.1: Hello World & Sensor Output
 * Serial Communication Basics
 */

#define POT_PIN 34   // Potensiometer ke GPIO34 (ADC)

void setup() {
  Serial.begin(115200);
  Serial.println("=================================");
  Serial.println("    Mikrokontroller ESP32");
  Serial.println("    Pertemuan 4: Serial Comm");
  Serial.println("=================================");
  Serial.println();
  Serial.println("Baud Rate: 115200");
  Serial.println("Setup selesai! Loop dimulai...");
  Serial.println();
}

void loop() {
  // Baca nilai ADC potensiometer
  int adcValue = analogRead(POT_PIN);
  float voltage = (adcValue / 4095.0) * 3.3;
  int percentage = map(adcValue, 0, 4095, 0, 100);

  // Print dengan berbagai format
  Serial.println("--- Sensor Reading ---");
  Serial.print("ADC Raw    : ");
  Serial.println(adcValue);
  Serial.printf("Voltage    : %.2fV\n", voltage);
  Serial.printf("Percentage : %d%%\n", percentage);

  // Print millis (uptime)
  Serial.printf("Uptime     : %lu ms\n", millis());
  Serial.println();

  delay(1000);  // Update tiap 1 detik
}
```

---

### **Wiring**:

```
Potensiometer:
  VCC → ESP32 3V3
  SIG → ESP32 GPIO34
  GND → ESP32 GND
```

---

### **Expected Output** (Serial Monitor):

```
=================================
    Mikrokontroller ESP32
    Pertemuan 4: Serial Comm
=================================

Baud Rate: 115200
Setup selesai! Loop dimulai...

--- Sensor Reading ---
ADC Raw    : 2048
Voltage    : 1.65V
Percentage : 50%
Uptime     : 1002 ms

--- Sensor Reading ---
ADC Raw    : 3100
Voltage    : 2.50V
Percentage : 76%
Uptime     : 2005 ms
```

---

### **Yang Perlu Dicoba**:

1. Ubah knob potensiometer → lihat nilai berubah
2. Coba baud rate yang salah (9600) → lihat garbage characters
3. Kembali ke 115200 → output normal lagi

---

## 📈 Praktikum 2: Serial Plotter

### **Tujuan**: Visualisasi sinyal secara real-time dengan Serial Plotter

---

### **Code**:

```cpp
/*
 * Praktikum 4.2: Serial Plotter
 * Visualisasi sinyal potensiometer + LED brightness secara real-time
 */

#define POT_PIN 34
#define LED_PIN 15
#define PWM_FREQ 5000
#define PWM_RES  8

void setup() {
  Serial.begin(115200);
  ledcAttach(LED_PIN, PWM_FREQ, PWM_RES);
  // Label untuk Serial Plotter – kirim sekali di setup
  // Format: "Label1:value1 Label2:value2" (Arduino IDE 2.x)
  // Untuk Wokwi, cukup kirim 2 nilai dipisah tab setiap loop
}

void loop() {
  int potValue   = analogRead(POT_PIN);
  int brightness = map(potValue, 0, 4095, 0, 255);

  ledcWrite(LED_PIN, brightness);

  // Format untuk Serial Plotter: 2 nilai dipisah tab
  // Ini akan terbaca sebagai 2 garis berbeda di Plotter!
  Serial.print(potValue);
  Serial.print("\t");          // Tab separator
  Serial.println(brightness);  // Newline di akhir

  delay(50);  // 20 Hz update
}
```

---

### **Wiring**:

```
Potensiometer:
  VCC → ESP32 3V3
  SIG → ESP32 GPIO34
  GND → ESP32 GND

LED:
  GPIO15 → Resistor 220Ω → LED Anode → LED Cathode → GND
```

---

### **Cara Membuka Serial Plotter di Wokwi**:

1. Run simulation
2. Klik ikon **Serial Plotter** (ikon grafik 📊 di bawah)
3. **Drag knob potensiometer** → lihat dua garis bergerak!
4. **Garis 1** (nilai pertama / potValue): rentang 0–4095
5. **Garis 2** (nilai kedua / brightness): rentang 0–255

> 💡 **Catatan**: Di Wokwi, label garis di plotter muncul otomatis sebagai angka index (1, 2). Di Arduino IDE 2.x dengan format `Label:nilai`, nama label akan muncul.

---

## 🔆 Praktikum 3: LED Control via Serial Command

### **Tujuan**: Kontrol LED dari Serial Monitor dengan mengetik perintah

---

### **Code**:

```cpp
/*
 * Praktikum 4.3: LED Control via Serial
 * Kontrol LED dengan perintah teks dari Serial Monitor
 */

#define LED_PIN    15
#define PWM_FREQ   5000
#define PWM_RES    8

bool ledState = false;

void setup() {
  Serial.begin(115200);
  ledcAttach(LED_PIN, PWM_FREQ, PWM_RES);

  Serial.println("=== LED Serial Control ===");
  Serial.println("Perintah:");
  Serial.println("  on       → LED ON (full brightness)");
  Serial.println("  off      → LED OFF");
  Serial.println("  dim:XXX  → Set brightness 0-255");
  Serial.println("             Contoh: dim:128");
  Serial.println("  status   → Lihat status LED");
  Serial.println("==========================");
  Serial.print("Ketik perintah: ");
}

void loop() {
  if (Serial.available() > 0) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    cmd.toLowerCase();

    Serial.println(cmd);  // Echo input

    if (cmd == "on") {
      ledcWrite(LED_PIN, 255);
      ledState = true;
      Serial.println("✅ LED ON (255/255)");

    } else if (cmd == "off") {
      ledcWrite(LED_PIN, 0);
      ledState = false;
      Serial.println("✅ LED OFF (0/255)");

    } else if (cmd.startsWith("dim:")) {
      int value = cmd.substring(4).toInt();
      value = constrain(value, 0, 255);
      ledcWrite(LED_PIN, value);
      ledState = (value > 0);
      Serial.printf("✅ LED brightness → %d/255 (%.1f%%)\n",
                    value, value / 255.0 * 100);

    } else if (cmd == "status") {
      Serial.printf("LED Status: %s\n", ledState ? "ON" : "OFF");

    } else if (cmd.length() > 0) {
      Serial.println("❌ Perintah tidak dikenali: " + cmd);
      Serial.println("   Ketik: on, off, dim:xxx, status");
    }

    Serial.print("\nKetik perintah: ");
  }
}
```

---

### **Test di Serial Monitor**:

1. Ketik `on` → tekan Enter → LED ON
2. Ketik `off` → tekan Enter → LED OFF
3. Ketik `dim:128` → tekan Enter → LED 50%
4. Ketik `dim:64` → tekan Enter → LED 25%
5. Ketik `status` → lihat info LED
6. Ketik `abc` → lihat pesan error

> ⚠️ **Pastikan** di Serial Monitor pilih **"NL & CR"** atau **"Newline"** sebagai line ending!

---

## 🍽️ Praktikum 4: Interactive Serial Menu (PROJECT UTAMA!)

### **Tujuan**: Membuat program menu interaktif lengkap dengan LED + Sensor

---

### **Fitur Program**:

```
╔══════════════════════════════╗
║     ESP32 Control Menu       ║
╠══════════════════════════════╣
║  1. LED ON                   ║
║  2. LED OFF                  ║
║  3. Blink 5x                 ║
║  4. Read Sensor (ADC)        ║
║  5. Set Brightness (0-255)   ║
║  6. System Info              ║
║  0. Tampilkan Menu lagi      ║
╚══════════════════════════════╝
Pilihan (0-6):
```

---

### **Wiring**:

```
Potensiometer:
  VCC → ESP32 3V3
  SIG → ESP32 GPIO34
  GND → ESP32 GND

LED:
  GPIO15 → Resistor 220Ω → LED Anode → LED Cathode → GND
```

---

### **Code Lengkap**:

```cpp
/*
 * =============================================
 *  PROJECT: ESP32 INTERACTIVE SERIAL MENU
 * =============================================
 *
 *  Pertemuan 4: Serial Communication & Debugging
 *  Features:
 *   - Menu interaktif via Serial Monitor
 *   - LED control (ON, OFF, Blink, Brightness)
 *   - Sensor reading (ADC Potensiometer)
 *   - Uptime info
 *
 *  Wiring:
 *   - LED: GPIO15 → 220Ω → LED → GND
 *   - Pot: VCC→3V3, SIG→GPIO34, GND→GND
 */

// ── Pin Definitions ──────────────────────────
#define LED_PIN   15
#define POT_PIN   34

// ── PWM Configuration ─────────────────────────
#define PWM_FREQ  5000  // 5 kHz
#define PWM_RES   8     // 8-bit (0-255)

// ── Global Variables ──────────────────────────
bool   ledState      = false;
int    ledBrightness = 0;

// ────────────────────────────────────────────
void printMenu() {
  Serial.println();
  Serial.println("╔══════════════════════════════╗");
  Serial.println("║     ESP32 Control Menu       ║");
  Serial.println("╠══════════════════════════════╣");
  Serial.println("║  1. LED ON                   ║");
  Serial.println("║  2. LED OFF                  ║");
  Serial.println("║  3. Blink 5x                 ║");
  Serial.println("║  4. Read Sensor (ADC)        ║");
  Serial.println("║  5. Set Brightness (0-255)   ║");
  Serial.println("║  6. System Info              ║");
  Serial.println("║  0. Tampilkan Menu lagi      ║");
  Serial.println("╚══════════════════════════════╝");
  Serial.print("Pilihan (0-6): ");
}

// ────────────────────────────────────────────
void blinkLED(int times) {
  Serial.printf("Blinking LED %d kali...\n", times);
  for (int i = 0; i < times; i++) {
    ledcWrite(LED_PIN, 255);
    delay(200);
    ledcWrite(LED_PIN, 0);
    delay(200);
    Serial.printf("  Blink %d/%d\n", i + 1, times);
  }
  // Restore brightness
  ledcWrite(LED_PIN, ledBrightness);
  Serial.println("✅ Blink selesai!");
}

// ────────────────────────────────────────────
void readSensor() {
  int adcRaw    = analogRead(POT_PIN);
  float voltage = (adcRaw / 4095.0) * 3.3;
  int percent   = map(adcRaw, 0, 4095, 0, 100);

  Serial.println("\n--- Sensor Reading ---");
  Serial.printf("ADC Value  : %d (0-4095)\n", adcRaw);
  Serial.printf("Voltage    : %.2f V\n", voltage);
  Serial.printf("Percentage : %d%%\n", percent);
  Serial.println("---------------------");
}

// ────────────────────────────────────────────
void systemInfo() {
  Serial.println("\n--- System Info ---");
  Serial.printf("Uptime        : %lu ms (%.1f detik)\n",
                millis(), millis() / 1000.0);
  Serial.printf("LED State     : %s\n", ledState ? "ON" : "OFF");
  Serial.printf("LED Brightness: %d/255 (%.1f%%)\n",
                ledBrightness, ledBrightness / 255.0 * 100);
  Serial.printf("Free Heap     : %d bytes\n", ESP.getFreeHeap());
  Serial.printf("CPU Freq      : %d MHz\n", ESP.getCpuFreqMHz());
  Serial.println("-------------------");
}

// ────────────────────────────────────────────
void handleMenu(int choice) {
  switch (choice) {
    case 1:
      ledcWrite(LED_PIN, 255);
      ledState = true;
      ledBrightness = 255;
      Serial.println("\n✅ LED ON (brightness: 255/255)");
      break;

    case 2:
      ledcWrite(LED_PIN, 0);
      ledState = false;
      ledBrightness = 0;
      Serial.println("\n✅ LED OFF");
      break;

    case 3:
      blinkLED(5);
      break;

    case 4:
      readSensor();
      break;

    case 5:
      Serial.print("\nMasukkan brightness (0-255): ");
      while (Serial.available() == 0) { delay(10); }  // Tunggu input
      {
        String br = Serial.readStringUntil('\n');
        br.trim();
        int brightness = constrain(br.toInt(), 0, 255);
        ledcWrite(LED_PIN, brightness);
        ledState = (brightness > 0);
        ledBrightness = brightness;
        Serial.printf("✅ Brightness set: %d/255 (%.1f%%)\n",
                      brightness, brightness / 255.0 * 100);
      }
      break;

    case 6:
      systemInfo();
      break;

    case 0:
      // Fall through to printMenu()
      break;

    default:
      Serial.println("\n❌ Pilihan tidak valid! Pilih 0-6.");
      break;
  }
  printMenu();
}

// ────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  ledcAttach(LED_PIN, PWM_FREQ, PWM_RES);

  Serial.println("\n🚀 ESP32 Serial Menu - Booting...");
  Serial.println("Mikrokontroller ESP32 - Pertemuan 4");
  delay(500);

  printMenu();
}

// ────────────────────────────────────────────
void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.length() == 0) return;

    Serial.println(input);   // Echo input
    int choice = input.toInt();
    handleMenu(choice);
  }
}
```

---

## 🌟 Challenge (Opsional - Bonus!)

### **Challenge 1: Auto-Read Sensor (Pilihan menu 7)**

Tambahkan pilihan menu:

```
7. Auto Read (sensor update tiap 2 detik, tekan 's' untuk stop)
```

**Hint**:

```cpp
case 7:
  Serial.println("Auto mode ON. Ketik 's' lalu Enter untuk stop.");
  while (true) {
    // Cek input stop SEBELUM delay agar responsif
    if (Serial.available()) {
      String input = Serial.readStringUntil('\n');
      input.trim();
      if (input == "s") break;
    }
    readSensor();
    delay(2000);  // ⚠️ Blocking: ketik 's' baru dibaca setelah 2 detik selesai
                  // Versi lebih responsif: ganti delay(2000) dengan loop 20×delay(100)
  }
  Serial.println("Auto mode OFF.");
  break;
```

---

### **Challenge 2: Password Protection**

Tambahkan password sebelum masuk menu:

```cpp
void checkPassword() {
  // Gunakan loop, bukan rekursi (untuk hindari stack overflow!)
  while (true) {
    Serial.print("Masukkan password: ");
    while (Serial.available() == 0) { delay(10); }
    String pass = Serial.readStringUntil('\n');
    pass.trim();

    if (pass == "esp32") {
      Serial.println("\n✅ Password benar! Selamat datang.");
      printMenu();
      return;  // Keluar dari loop
    } else {
      Serial.println("\n❌ Password salah! Coba lagi.");
    }
  }
}
```

---

### **Challenge 3: Command History**

Simpan 5 perintah terakhir dan tampilkan dengan opsi menu `h`:

```cpp
String history[5];
int historyIdx = 0;

void addHistory(String cmd) {
  history[historyIdx % 5] = cmd;
  historyIdx++;
}

void printHistory() {
  Serial.println("--- Command History ---");
  for (int i = 0; i < 5; i++) {
    if (history[i].length() > 0) {
      Serial.printf("  %d. %s\n", i + 1, history[i].c_str());
    }
  }
}
```

---

## 📚 Konsep Penting - Ringkasan

### **Serial Communication**

| Fungsi                         | Kegunaan                             |
| ------------------------------ | ------------------------------------ |
| `Serial.begin(115200)`         | Inisialisasi serial dengan baud rate |
| `Serial.print("text")`         | Print teks tanpa newline             |
| `Serial.println("text")`       | Print teks dengan newline            |
| `Serial.printf("fmt", args)`   | Print dengan format string (ESP32)   |
| `Serial.available()`           | Cek apakah ada data masuk            |
| `Serial.readStringUntil('\n')` | Baca string sampai Enter             |
| `Serial.parseInt()`            | Baca integer dari serial             |

---

### **String Methods**

| Method             | Kegunaan                              |
| ------------------ | ------------------------------------- |
| `s.trim()`         | Hapus whitespace di awal/akhir        |
| `s.toLowerCase()`  | Convert ke lowercase                  |
| `s.toInt()`        | Convert ke integer                    |
| `s.startsWith(x)`  | Cek apakah diawali string x           |
| `s.indexOf(x)`     | Cari posisi substring x               |
| `s.substring(a,b)` | Ambil bagian string dari index a ke b |

---

### **Debugging Tips**

1. ✅ Selalu mulai dengan `Serial.begin(115200)` di `setup()`
2. ✅ Print nilai variable di titik-titik penting
3. ✅ Print "checkpoint" di awal setiap fungsi penting
4. ✅ Gunakan `Serial.printf()` untuk format yang lebih rapi
5. ✅ Gunakan `millis()` untuk debug timing
6. ❌ Jangan lupa cek baud rate jika output tidak terbaca!

---

## 🔗 Referensi

- [Arduino Serial Reference](https://www.arduino.cc/reference/en/language/functions/communication/serial/)
- [ESP32 Arduino Core - Serial](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/serial.html)
- [Wokwi ESP32 Simulator](https://wokwi.com)
- [Serial Communication Basics - SparkFun](https://learn.sparkfun.com/tutorials/serial-communication)

---

**Next**: Pertemuan 5 - Sensor Suhu & Kelembaban (DHT22) 🌡️

---

**Materi ini dibuat untuk**: Mata Kuliah Mikrokontroller - Prodi Informatika Unmul
