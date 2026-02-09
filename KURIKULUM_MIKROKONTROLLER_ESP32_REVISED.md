# Kurikulum Mata Kuliah Mikrokontroller ESP32 (REVISED)

## Universitas Mulawarman - Prodi Informatika

### 📋 Informasi Mata Kuliah

- **Kode MK**: (sesuaikan dengan kode MK di kampus)
- **SKS**: 3 SKS (2 SKS Teori + 1 SKS Praktikum)
- **Semester**: (Genap/Ganjil, sesuaikan)
- **Jumlah Pertemuan**: 16 Pertemuan (14 Materi + 1 UTS + 1 UAS)
- **Platform**: ESP32 Development Board
- **IDE**: Arduino IDE 2.x
- **Target**: Mahasiswa Informatika (tanpa background elektronika)
- **Pendekatan**: Project-based learning, hands-on, beginner-friendly

---

## 🎯 Capaian Pembelajaran Mata Kuliah (CPMK)

Setelah menyelesaikan mata kuliah ini, mahasiswa diharapkan mampu:

### Aspek Kognitif:

1. **Memahami** konsep dasar embedded systems, mikrokontroller, dan arsitektur ESP32
2. **Menganalisis** kebutuhan hardware dan software untuk aplikasi IoT
3. **Mengevaluasi** solusi teknis berdasarkan requirement dan constraint

### Aspek Psikomotor:

4. **Menggunakan** ESP32 untuk membaca sensor dan mengontrol aktuator
5. **Mengimplementasikan** komunikasi wireless (WiFi, Bluetooth, MQTT)
6. **Merancang** dan membangun sistem IoT end-to-end
7. **Mengintegrasikan** ESP32 dengan cloud platform dan database

### Aspek Afektif:

8. **Berkolaborasi** dalam tim untuk menyelesaikan project
9. **Mendokumentasikan** code, circuit, dan project dengan baik
10. **Troubleshoot** masalah hardware dan software secara mandiri

---

## 📅 Kalender Perkuliahan (16 Pertemuan)

| Minggu | Topik                                            | Jenis        | Deliverable             |
| ------ | ------------------------------------------------ | ------------ | ----------------------- |
| 1      | Pengenalan Embedded Systems & ESP32 + Lab Safety | Materi + Lab | Blink LED + Safety Quiz |
| 2      | Digital I/O & Breadboard Basics                  | Materi + Lab | Traffic Light           |
| 3      | Analog I/O & PWM                                 | Materi + Lab | LED Dimmer              |
| 4      | Serial Communication & Debugging                 | Materi + Lab | Serial Menu             |
| 5      | Sensor Suhu/Kelembaban (DHT22)                   | Materi + Lab | Temp Monitor            |
| 6      | Sensor Jarak & Interrupt Basics                  | Materi + Lab | Parking Sensor          |
| 7      | Display LCD/OLED & Review                        | Materi + Lab | Sensor Dashboard        |
| **8**  | **UJIAN TENGAH SEMESTER (UTS)**                  | **Ujian**    | **Teori + Praktik**     |
| 9      | WiFi & Web Server                                | Materi + Lab | Web Dashboard           |
| 10     | REST API, JSON & Cloud (ThingSpeak)              | Materi + Lab | Cloud Logging           |
| 11     | Bluetooth & Mobile App Integration               | Materi + Lab | BT Control              |
| 12     | MQTT Protocol & Security Basics                  | Materi + Lab | MQTT Chat               |
| 13     | Data Logging, RTC & OTA Update                   | Materi + Lab | Smart Logger            |
| 14     | Power Management & Advanced Topics               | Materi + Lab | Low Power Demo          |
| 15     | Project Integration & Presentation Prep          | Workshop     | Project Progress        |
| **16** | **PRESENTASI PROJECT AKHIR & UAS**               | **Ujian**    | **Project + Demo**      |

---

## 📚 Rencana Pertemuan Detail

### **Pertemuan 1: Pengenalan Embedded Systems & ESP32 + Lab Safety**

**Durasi**: 3 x 50 menit  
**Tujuan**: Memahami embedded systems, mengenal ESP32, dan lab safety basics

**Materi Teori (60 menit)**:

- Apa itu embedded systems? (contoh: smartphone, IoT, automotive)
- Perbandingan mikrokontroller: Arduino Uno, ESP8266, ESP32
- Arsitektur ESP32: dual-core CPU, WiFi/BT, GPIO, ADC, DAC, PWM
- Kenapa ESP32? (powerful, affordable, versatile)
- Arduino IDE vs ESP-IDF vs MicroPython
- Komponen dasar: resistor (color code), LED (polarity), breadboard

**Lab Safety untuk Non-Elektronika (30 menit)**:

- ⚠️ **Voltage & Current**: USB = 5V (aman), jangan hubungkan langsung ke 220V AC
- ⚠️ **Short Circuit**: Jangan hubungkan VCC ke GND langsung
- ⚠️ **Polarity**: LED, kapasitor electrolytic punya polaritas
- ⚠️ **Resistor**: Selalu gunakan resistor untuk LED (220Ω - 1kΩ)
- ⚠️ **Component Limits**: Cek datasheet untuk max voltage/current
- ⚠️ **What to Do if Smoke/Smell**: Cabut power SEGERA, jangan sentuh komponen panas
- 🔧 **Breadboard 101**: How breadboard works (horizontal/vertical connection)

**Praktikum (60 menit)**:

1. Installation: Arduino IDE, CH340 driver, ESP32 board manager
2. Board selection & port configuration
3. Upload "Blink" program (onboard LED - GPIO 2)
4. Modify blink interval (500ms, 1000ms, 2000ms)
5. Troubleshooting: "Failed to connect" error

**Deliverable**:

- Screenshot program blink running
- Lab safety quiz (10 pertanyaan MCQ di e-learning)

**Referensi**:

- [ESP32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)
- [Arduino IDE Setup](https://randomnerdtutorials.com/installing-esp32-arduino-ide-2-0/)

---

### **Pertemuan 2: Digital I/O & Breadboard Basics**

**Durasi**: 3 x 50 menit  
**Tujuan**: Memahami GPIO, digital I/O, dan penggunaan breadboard

**Materi Teori (50 menit)**:

- GPIO (General Purpose Input/Output) concept
- Digital signal: HIGH (3.3V di ESP32) vs LOW (0V)
- `pinMode()`, `digitalWrite()`, `digitalRead()`
- Pull-up dan pull-down resistor (internal & external)
- Debouncing untuk button (software debounce)
- LED current limiting: Ohm's Law basics (V = IR)

**Breadboard & Wiring (40 menit)**:

- Breadboard anatomy: power rails, terminal strips
- Jumper wire types: M-M, M-F, F-F
- Wiring best practices: color coding (red=VCC, black=GND)
- Component placement on breadboard
- Reading circuit diagrams (Fritzing basics)

**Praktikum (60 menit)**:

1. External LED blink (dengan resistor)
2. Push button input dengan `digitalRead()`
3. LED ON/OFF dengan button (toggle)
4. Multiple LED pattern: running LED (3 LEDs)
5. **Project**: Traffic light simulation (Red 5s → Yellow 2s → Green 5s)

**Deliverable**:

- Video demo traffic light
- Circuit diagram (Fritzing atau foto breadboard)
- Source code dengan comments

**Komponen yang Dibutuhkan**:

- LED (merah, kuning, hijau)
- Resistor 220Ω (3 pcs)
- Push button (1 pc)
- Jumper wires

---

### **Pertemuan 3: Analog I/O & PWM**

**Durasi**: 3 x 50 menit  
**Tujuan**: Memahami sinyal analog dan PWM untuk kontrol smooth

**Materi Teori (60 menit)**:

- Digital vs Analog signal
- ADC (Analog-to-Digital Converter): 12-bit di ESP32 (0-4095)
- `analogRead()` pada ESP32 (GPIO 32-39 recommended)
- Voltage divider concept untuk sensor analog
- PWM (Pulse Width Modulation): duty cycle, frequency
- LEDC (LED Controller) di ESP32 vs `analogWrite()` Arduino
- `ledcSetup()`, `ledcAttachPin()`, `ledcWrite()`

**Praktikum (90 menit)**:

1. Membaca nilai potensiometer dengan `analogRead()`
2. Map value (0-4095) ke range lain (0-255, 0-100%)
3. Kontrol LED brightness dengan PWM
4. Potensiometer → LED dimmer (real-time control)
5. Breathing LED effect (fade in/out)
6. **Bonus**: RGB LED color mixing dengan 3 PWM channel

**Deliverable**:

- Video: LED dimmer dengan potensiometer
- Serial monitor output menampilkan ADC value
- Source code

**Komponen yang Dibutuhkan**:

- Potensiometer 10kΩ
- LED (atau RGB LED untuk bonus)
- Resistor

---

### **Pertemuan 4: Serial Communication & Debugging**

**Durasi**: 3 x 50 menit  
**Tujuan**: Menggunakan serial untuk debugging dan komunikasi

**Materi Teori (50 menit)**:

- UART (Universal Asynchronous Receiver-Transmitter)
- Baud rate concept (9600, 115200)
- `Serial.begin()`, `Serial.print()`, `Serial.println()`
- `Serial.available()`, `Serial.read()`, `Serial.parseInt()`
- Serial Monitor & Serial Plotter di Arduino IDE
- Debugging strategies: print statements, variable monitoring

**Praktikum (100 menit)**:

1. Print "Hello World" ke serial monitor
2. Print sensor readings (analog value dari potensiometer)
3. Serial Plotter: visualisasi sinyal PWM
4. Input dari serial: LED control via command
5. Interactive menu-driven program:
   ```
   === ESP32 Control Menu ===
   1. LED ON
   2. LED OFF
   3. Blink
   4. Read Sensor
   Pilih (1-4):
   ```

**Deliverable**:

- Screenshot Serial Monitor dengan menu interaction
- Screenshot Serial Plotter dengan sinyal
- Source code program menu

---

### **Pertemuan 5: Sensor Suhu & Kelembaban (DHT22)**

**Durasi**: 3 x 50 menit  
**Tujuan**: Membaca sensor digital (DHT22) dan error handling

**Materi Teori (50 menit)**:

- Jenis sensor suhu: analog (LM35), digital (DHT11/22, DS18B20)
- DHT22 vs DHT11: akurasi, range, response time
- Protokol komunikasi 1-Wire (simplified)
- Library DHT sensor (Adafruit DHT)
- Cara membaca datasheet sensor
- Error handling: sensor disconnected, checksum error

**Praktikum (100 menit)**:

1. Instalasi library: Adafruit DHT Sensor Library
2. Wiring DHT22 (VCC, GND, Data + pull-up resistor 10kΩ)
3. Membaca suhu & kelembaban, tampilkan di serial
4. Handling error: `if (isnan(t) || isnan(h))`
5. LED indikator berdasarkan suhu:
   - < 25°C: LED Biru
   - 25-30°C: LED Hijau
   - \> 30°C: LED Merah

**Deliverable**:

- Video: sistem monitoring suhu dengan LED indikator
- Serial output dengan data suhu/kelembaban
- Source code dengan error handling

**Komponen yang Dibutuhkan**:

- DHT22 sensor
- Resistor 10kΩ (pull-up)
- LED (3 warna)

---

### **Pertemuan 6: Sensor Jarak & Interrupt Basics**

**Durasi**: 3 x 50 menit  
**Tujuan**: Menggunakan sensor ultrasonic dan pengenalan interrupt

**Materi Teori (60 menit)**:

- Sensor ultrasonic HC-SR04: prinsip kerja (sonar)
- Trigger pulse & Echo response
- Menghitung jarak: `distance = (duration * 0.034) / 2` cm
- Sensor PIR (Passive Infrared) untuk deteksi motion
- **Interrupt Basics**: polling vs interrupt
- `attachInterrupt()`, ISR (Interrupt Service Routine)
- Volatile variables dalam ISR

**Praktikum (90 menit)**:

1. Wiring HC-SR04 (VCC, Trig, Echo, GND)
2. Mengukur jarak dan display di serial
3. Parking sensor: buzzer berbunyi saat jarak < 20cm
4. Buzzer frequency berubah sesuai jarak (semakin dekat = semakin cepat)
5. **Bonus**: PIR sensor + interrupt untuk deteksi gerakan

**Deliverable**:

- Video: parking sensor dengan buzzer warning
- Source code

**Komponen yang Dibutuhkan**:

- HC-SR04 ultrasonic sensor
- Buzzer (active atau passive)
- PIR sensor (opsional untuk bonus)

---

### **Pertemuan 7: Display LCD/OLED & Review Materi**

**Durasi**: 3 x 50 menit  
**Tujuan**: Menampilkan data ke display dan review persiapan UTS

**Materi Teori (50 menit)**:

- LCD 16x2 dengan I2C adapter
- OLED display SSD1306 (128x64)
- Protokol I2C: SDA, SCL, address scanning
- Library: Adafruit SSD1306, Adafruit GFX
- Menggambar text, shape, bitmap di OLED

**Praktikum (70 menit)**:

1. I2C address scanning dengan `Wire.h`
2. Setup library OLED
3. Menampilkan "Hello World" di OLED
4. Display data sensor (DHT22 + HC-SR04) di OLED
5. **Mini Project**: Dashboard multi-sensor
   - Line 1: Suhu & Kelembaban
   - Line 2: Jarak dari HC-SR04
   - Update setiap 2 detik

**Review UTS (30 menit)**:

- Q&A materi pertemuan 1-7
- Tips & trik praktikum UTS
- Contoh soal teori

**Deliverable**:

- Video: OLED dashboard dengan 2+ sensor real-time
- Source code

**Komponen yang Dibutuhkan**:

- OLED display SSD1306 (I2C)

---

### **Pertemuan 8: UJIAN TENGAH SEMESTER (UTS)**

**Durasi**: 100 menit (sesuaikan dengan aturan kampus)

**Format Ujian**:

**Bagian 1: Teori (40 menit, 40%)**

- Multiple choice: 20 soal
- Essay: 2 soal
- Materi: Pertemuan 1-7
- Topik: Konsep embedded systems, GPIO, PWM, sensor, I2C, interrupt

**Bagian 2: Praktikum (60 menit, 60%)**

- Implementasi sistem sederhana dengan komponen yang sudah dipelajari
- Contoh soal:
  > "Buat sistem monitoring ruangan dengan:
  >
  > - DHT22 untuk suhu/kelembaban
  > - LED indikator (hijau: normal, merah: suhu > 30°C)
  > - OLED display menampilkan suhu & kelembaban
  > - Data dikirim ke serial monitor setiap 3 detik"

**Rubrik Penilaian Praktikum**:

- Sistem berfungsi penuh: 60%
- Code quality (comments, structure): 20%
- Wiring & circuit: 10%
- Error handling: 10%

**Aturan**:

- Close book untuk teori
- Open documentation (Arduino reference) untuk praktikum
- Tidak boleh akses internet kecuali docs.arduino.cc

---

### **Pertemuan 9: WiFi & Web Server**

**Durasi**: 3 x 50 menit  
**Tujuan**: Koneksi WiFi dan membuat web server di ESP32

**Materi Teori (50 menit)**:

- WiFi mode: Station (STA), Access Point (AP), Hybrid
- Library WiFi.h di ESP32
- `WiFi.begin()`, `WiFi.status()`, `WiFi.localIP()`
- Web Server basics: HTTP request/response
- HTML, CSS basics untuk interface
- Routing: `server.on("/", handleRoot)`

**Praktikum (100 menit)**:

1. Scan WiFi networks available
2. Connect ESP32 ke WiFi router
3. Membuat web server sederhana (Hello World)
4. Menampilkan data sensor (DHT22) di web page (auto-refresh)
5. **Control**: Button di web untuk ON/OFF LED
6. **Styling**: CSS untuk tampilan lebih menarik

**Deliverable**:

- Screenshot web dashboard di browser
- Video: control LED dari web interface
- Source code (HTML inline di code)

**Komponen yang Dibutuhkan**:

- WiFi router/hotspot

---

### **Pertemuan 10: REST API, JSON & Cloud Integration**

**Durasi**: 3 x 50 menit  
**Tujuan**: Komunikasi dengan format JSON dan integrasi cloud

**Materi Teori (60 menit)**:

- REST API concept: GET, POST, PUT, DELETE
- JSON (JavaScript Object Notation) format
- Library ArduinoJson (serialization & deserialization)
- ThingSpeak: IoT platform untuk data logging
- API Key management & security

**Praktikum (90 menit)**:

1. Instalasi ArduinoJson library
2. Membuat JSON response di ESP32 web server
   ```json
   { "temperature": 28.5, "humidity": 65, "distance": 150 }
   ```
3. Parsing JSON (contoh: weather API)
4. Setup ThingSpeak account & channel
5. Upload data sensor ke ThingSpeak via HTTP POST
6. Visualisasi grafik real-time di ThingSpeak

**Deliverable**:

- Screenshot ThingSpeak dashboard dengan grafik
- REST API endpoint yang return JSON
- Source code

**Requirements**:

- ThingSpeak account (gratis)

---

### **Pertemuan 11: Bluetooth & Mobile App Integration**

**Durasi**: 3 x 50 menit  
**Tujuan**: Komunikasi wireless dengan smartphone via Bluetooth

**Materi Teori (50 menit)**:

- Bluetooth Classic vs BLE (Bluetooth Low Energy)
- Use case: BT Classic untuk data transfer, BLE untuk low power
- Library BluetoothSerial untuk ESP32
- Pairing & security
- Mobile app: Serial Bluetooth Terminal (Android)

**Praktikum (100 menit)**:

1. Setup BluetoothSerial.h
2. Membuat ESP32 discoverable dengan nama custom
3. Pairing dengan smartphone
4. Komunikasi dua arah: kirim & terima data
5. **Control**: ON/OFF LED dari smartphone
6. **Monitoring**: Kirim data sensor ke smartphone setiap 2 detik
7. **Bonus**: Buat simple protocol (contoh: "LED:ON", "LED:OFF", "GET:TEMP")

**Deliverable**:

- Screenshot app Serial Bluetooth Terminal
- Video: control LED dari smartphone via BT
- Source code

**Requirements**:

- Smartphone Android dengan Serial Bluetooth Terminal app

---

### **Pertemuan 12: MQTT Protocol & Security Basics**

**Durasi**: 3 x 50 menit  
**Tujuan**: Implementasi MQTT dan pengenalan IoT security

**Materi Teori (60 menit)**:

- **MQTT**: Publisher-Subscriber pattern
- MQTT Broker, Topic, QoS (0, 1, 2)
- Public broker: HiveMQ, Mosquitto
- Library PubSubClient
- **IoT Security Basics**:
  - WiFi security: WPA2, password storage
  - HTTPS vs HTTP
  - MQTT over TLS
  - API key protection (jangan hardcode!)
  - OTA (Over-The-Air) update security

**Praktikum (90 menit)**:

1. Setup PubSubClient library
2. Connect ke public MQTT broker (HiveMQ)
3. Publish data sensor ke topic: `unmul/iot/sensor1/temp`
4. Subscribe ke topic untuk kontrol: `unmul/iot/sensor1/led`
5. **Multi-device**: 2 ESP32 berkomunikasi via MQTT
   - ESP32-A: publish button state
   - ESP32-B: subscribe dan control LED
6. **Security**: Gunakan `config.h` untuk credential (tidak push ke GitHub)

**Deliverable**:

- Video: 2 ESP32 komunikasi via MQTT
- Screenshot MQTT Explorer (client tool)
- Source code dengan credential management

**Requirements**:

- MQTT Explorer app (desktop) untuk monitoring

---

### **Pertemuan 13: Data Logging, RTC & OTA Update**

**Durasi**: 3 x 50 menit  
**Tujuan**: Menyimpan data lokal, real-time clock, dan update firmware wireless

**Materi Teori (60 menit)**:

- **SPIFFS** (SPI Flash File System) di ESP32
- File operations: open, write, read, close
- CSV format untuk sensor data
- **RTC**: DS3231 module vs NTP (Network Time Protocol)
- Time-stamped logging
- **OTA Update**:
  - Update firmware via WiFi (tanpa kabel USB)
  - ArduinoOTA library
  - Use case: device di lokasi remote

**Praktikum (90 menit)**:

1. Setup SPIFFS, upload file system
2. Logging data sensor ke file `/data.csv`
3. Web endpoint untuk download log file
4. NTP sync untuk mendapatkan waktu real-time
5. Time-stamped data logging: `2026-02-09 14:30:00, 28.5, 65`
6. **OTA**: Setup ArduinoOTA, update firmware via WiFi

**Deliverable**:

- File CSV hasil logging (min 100 data point)
- Video: download log via web + OTA update success
- Source code

**Komponen yang Dibutuhkan**:

- (Opsional) RTC DS3231 module jika tidak menggunakan NTP

---

### **Pertemuan 14: Power Management & Advanced Topics**

**Durasi**: 3 x 50 menit  
**Tujuan**: Optimasi power consumption dan topik lanjutan

**Materi Teori (70 menit)**:

- **Power Consumption**: ESP32 active vs sleep mode
- Deep sleep, light sleep, modem sleep
- `esp_sleep_enable_timer_wakeup()`
- Wake-up sources: timer, ext0, ext1, touchpad
- Battery-powered IoT best practices
- **Advanced Topics Overview**:
  - FreeRTOS basics: task, queue, semaphore
  - Dual-core programming di ESP32
  - ESP-IDF (native framework)
  - AsyncWebServer untuk concurrency
  - WebSocket untuk real-time data

**Praktikum (80 menit)**:

1. Current measurement (jika ada multimeter)
2. Deep sleep demo: sleep 10s, wake up, read sensor, sleep again
3. Wake-up dari button press (external interrupt)
4. Calculate battery life:
   - Active: 160mA, Sleep: 10µA
   - Battery: 2000mAh
   - Duty cycle: aktif 10s setiap 5 menit
5. **Bonus**: Multi-core demo (1 core untuk sensor, 1 core untuk WiFi)

**Deliverable**:

- Report perhitungan battery life
- Video: deep sleep + wake up dari button
- Source code

---

### **Pertemuan 15: Project Integration & Presentation Preparation**

**Durasi**: 3 x 50 menit  
**Tujuan**: Workshop integrasi project akhir dan persiapan presentasi

**Format**: Workshop/Konsultasi Project

**Aktivitas**:

1. **Progress Check** (30 menit):
   - Setiap kelompok presentasikan progress project (5 menit/kelompok)
   - Hardware sudah siap?
   - Software sudah jalan?
   - Masalah yang dihadapi?

2. **Troubleshooting Session** (60 menit):
   - Dosen berkeliling membantu debugging
   - Peer helping antar kelompok
   - Tips optimasi dan debugging

3. **Presentation Training** (30 menit):
   - Template presentasi project
   - Cara membuat video demo yang baik
   - Tips presentasi teknis yang efektif

4. **Documentation Review** (30 menit):
   - Review dokumentasi project
   - Code commenting standards
   - README.md untuk GitHub

**Deliverable**:

- Progress report (dokumen)
- Draft presentation slides
- Working prototype (min 70% complete)

**Project Requirements** (Recap):

- Min 3 sensor/input device
- Min 2 actuator/output device
- Display (OLED/Web)
- Komunikasi wireless (WiFi/BT/MQTT)
- Data logging/cloud integration
- Security consideration

---

### **Pertemuan 16: PRESENTASI PROJECT AKHIR & UJIAN AKHIR SEMESTER (UAS)**

**Durasi**: 150 menit (sesuaikan dengan jadwal ujian)

**Format UAS**:

**Bagian 1: Presentasi Project (60%)** - 120 menit

- Alokasi waktu: 10 menit presentasi + 5 menit Q&A per kelompok
- Urutan:
  1. **Introduction** (1 menit): Problem statement, objectives
  2. **System Design** (2 menit): Arsitektur sistem, flowchart
  3. **Live Demo** (4 menit): Demonstrasi sistem berfungsi
  4. **Technical Deep Dive** (2 menit): Highlight kode penting, tantangan
  5. **Conclusion** (1 menit): Result, future improvement
  6. **Q&A** (5 menit): Pertanyaan dari dosen & peer

**Rubrik Penilaian Project**:

- **Functionality** (35%): Sistem bekerja sesuai requirement
- **Complexity & Integration** (25%): Jumlah komponen, integrasi yang baik
- **Code Quality** (15%): Clean code, comments, modularity
- **Presentation** (10%): Komunikasi, slide, demo
- **Documentation** (10%): README, circuit diagram, video
- **Innovation** (5%): Kreativitas, nilai tambah

**Bagian 2: Teori (40%)** - 30 menit

- Essay questions tentang keseluruhan materi
- Analisis kasus IoT
- Design challenge

**Submission Requirements**:

1. **GitHub Repository** dengan:
   - Source code lengkap
   - README.md (description, setup instruction, circuit diagram)
   - Circuit diagram (Fritzing/foto)
   - Video demo (YouTube link, max 5 menit)
2. **Presentation Slides** (PDF)
3. **Project Report** (max 10 halaman, template disediakan)

---

## 🛠️ Perangkat & Komponen yang Dibutuhkan

### **Minimum Starter Kit** (per mahasiswa atau per 2 mahasiswa):

#### Hardware Essentials:

| No        | Komponen                         | Qty | Est. Harga (IDR) | Keterangan             |
| --------- | -------------------------------- | --- | ---------------- | ---------------------- |
| 1         | ESP32 DevKit V1                  | 1   | 60.000           | NodeMCU-32S atau clone |
| 2         | Kabel USB Micro                  | 1   | 10.000           | Untuk programming      |
| 3         | Breadboard 400 point             | 1   | 15.000           | Mini breadboard        |
| 4         | Jumper wires (M-M)               | 20  | 10.000           | Assorted colors        |
| 5         | Jumper wires (M-F)               | 10  | 5.000            | Untuk sensor           |
| 6         | LED (merah, kuning, hijau, biru) | 10  | 5.000            | Assorted               |
| 7         | Resistor (220Ω, 1kΩ, 10kΩ)       | 30  | 5.000            | Assorted pack          |
| 8         | Push button                      | 4   | 4.000            | Tactile switch         |
| 9         | Sensor DHT22                     | 1   | 35.000           | Suhu & kelembaban      |
| 10        | Sensor HC-SR04                   | 1   | 15.000           | Ultrasonic             |
| 11        | Sensor PIR HC-SR501              | 1   | 10.000           | Motion detection       |
| 12        | OLED 0.96" I2C (SSD1306)         | 1   | 35.000           | Display                |
| 13        | Buzzer aktif                     | 1   | 3.000            | 5V active buzzer       |
| 14        | Potensiometer 10kΩ               | 1   | 3.000            | Variable resistor      |
| **TOTAL** |                                  |     | **≈ Rp 215.000** | **Per mahasiswa**      |

#### Hardware Opsional (untuk project akhir):

| No  | Komponen                | Est. Harga (IDR) | Use Case               |
| --- | ----------------------- | ---------------- | ---------------------- |
| 1   | RTC DS3231 Module       | 15.000           | Time-stamped logging   |
| 2   | SD Card Module          | 10.000           | Data logging besar     |
| 3   | Relay Module 1-Channel  | 10.000           | Kontrol AC appliances  |
| 4   | Motor DC + L298N Driver | 25.000           | Robotika/automation    |
| 5   | RGB LED Module          | 5.000            | Indikator warna        |
| 6   | Soil Moisture Sensor    | 10.000           | Smart farming          |
| 7   | MQ-2 Gas Sensor         | 15.000           | Air quality monitoring |
| 8   | Servo Motor SG90        | 15.000           | Actuator               |

### **Software Requirements** (GRATIS):

1. **Arduino IDE 2.x** (Windows/Mac/Linux)
2. **Driver CH340** atau CP2102 (sesuai board ESP32)
3. **Arduino Libraries**:
   - ESP32 Board Support (via Board Manager)
   - DHT sensor library (Adafruit)
   - Adafruit SSD1306
   - Adafruit GFX Library
   - ArduinoJson
   - PubSubClient (MQTT)
   - WiFi.h (built-in ESP32)
4. **Tools**:
   - Fritzing (circuit diagram)
   - MQTT Explorer (MQTT testing)
   - Serial Bluetooth Terminal (Android app)
   - Postman (API testing)

### **Budget Summary**:

- **Minimum per mahasiswa**: Rp 215.000
- **Recommended per mahasiswa** (dengan komponen opsional): Rp 300.000
- **Lab Investment** (untuk 30 mahasiswa):
  - Minimum: Rp 6.450.000
  - Recommended: Rp 9.000.000
  - **Reusable**: Ya, komponen bisa dipakai semester berikutnya (kecuali yang rusak)

### **Procurement Tips**:

1. **Bulk Order**: Harga bisa lebih murah jika beli dalam jumlah banyak
2. **Local vs Online**:
   - Tokopedia, Bukalapak: fast shipping
   - AliExpress, Banggood: lebih murah tapi lama (30-60 hari)
3. **Backup Stock**: Siapkan 10-20% komponen backup (untuk yang rusak)
4. **Quality Check**: Test semua komponen sebelum distribusi ke mahasiswa

---

## 📊 Sistem Evaluasi & Penilaian

### **Komponen Penilaian**:

| Komponen                     | Bobot    | Keterangan                             |
| ---------------------------- | -------- | -------------------------------------- |
| **Praktikum**                | 25%      | Deliverable pertemuan 1-7, 9-15        |
| **UTS**                      | 20%      | Teori (40%) + Praktikum (60%)          |
| **Project Akhir**            | 40%      | Presentasi + Demo + Kode + Dokumentasi |
| **UAS Teori**                | 10%      | Essay questions                        |
| **Attitude & Participation** | 5%       | Kehadiran, diskusi, peer helping       |
| **TOTAL**                    | **100%** |                                        |

### **Grading Scale**:

- **A**: 85-100 (Excellent)
- **AB**: 80-84 (Very Good)
- **B**: 75-79 (Good)
- **BC**: 70-74 (Satisfactory)
- **C**: 65-69 (Fair)
- **D**: 55-64 (Poor)
- **E**: < 55 (Fail)

---

## 📖 Referensi & Resources

### **Official Documentation**:

1. **ESP32 Technical Reference Manual** - [espressif.com](https://www.espressif.com/en/support/documents/technical-documents)
2. **Arduino Language Reference** - [arduino.cc/reference](https://www.arduino.cc/reference/en/)
3. **ESP32 Arduino Core** - [github.com/espressif/arduino-esp32](https://github.com/espressif/arduino-esp32)

### **Recommended Tutorials**:

1. **Random Nerd Tutorials** - Excellent ESP32 tutorials
   - [randomnerdtutorials.com/esp32-tutorials](https://randomnerdtutorials.com/learn-esp32-with-arduino-ide/)
2. **Last Minute Engineers** - Sensor interfacing tutorials
3. **DroneBot Workshop** - YouTube channel

### **Online Platforms**:

1. **Wokwi** - ESP32 online simulator (jika hardware rusak)
2. **ThingSpeak** - IoT data analytics
3. **HiveMQ** - Public MQTT broker

### **Books** (Opsional):

1. "Programming ESP32 with Arduino IDE" - Dr. Ton
2. "IoT Projects with ESP32" - Agus Kurniawan

### **Communities**:

1. **ESP32 Forum** - esp32.com
2. **Arduino Forum** - Indonesia category
3. **Stack Overflow** - Tag: esp32, arduino

---

## 💡 Tips Mengajar untuk Dosen

### **Sebelum Semester Dimulai**:

1. ✅ **Test Semua Kit**: Pastikan semua komponen berfungsi
2. ✅ **Prepare Backup**: Siapkan ESP32 dan komponen cadangan
3. ✅ **Setup E-learning**: Upload materi, video, referensi
4. ✅ **Create Demo Video**: Rekam video demo tiap praktikum
5. ✅ **Prepare Template**: Code template, circuit template

### **Strategi Mengajar**:

1. **Show, Don't Just Tell**: Selalu demo hardware sebelum praktikum
2. **Live Coding**: Coding bersama di kelas lebih efektif dari slide
3. **Error as Learning**: Jangan takut error, jadikan pembelajaran
4. **Peer Learning**: Dorong mahasiswa saling membantu
5. **Real-World Context**: Hubungkan materi dengan aplikasi real (smart home, agriculture, health)

### **Troubleshooting Tips**:

1. **"Failed to connect to ESP32"**:
   - Check driver CH340/CP2102
   - Check port selection
   - Tekan tombol BOOT saat upload
2. **"Brownout detector triggered"**:
   - Power supply tidak cukup
   - Gunakan USB port yang baik atau external power
3. **Sensor tidak terbaca**:
   - Check wiring (VCC, GND, Data pin)
   - Check library sudah terinstall
   - Check GPIO pin compatibility

---

## 🎯 Learning Outcomes yang Diharapkan

Setelah menyelesaikan mata kuliah ini, mahasiswa mampu:

### **Technical Skills**:

- ✅ Setup dan programming ESP32 secara mandiri
- ✅ Membaca datasheet dan menggunakan sensor/aktuator
- ✅ Debugging hardware dan software issues
- ✅ Implement komunikasi wireless (WiFi, Bluetooth, MQTT)
- ✅ Integrasi dengan cloud platform (ThingSpeak, Firebase, dll)
- ✅ Design dan implement sistem IoT end-to-end
- ✅ Optimize power consumption untuk battery-powered device
- ✅ Implement security best practices di IoT

### **Soft Skills**:

- ✅ Problem-solving untuk technical challenges
- ✅ Teamwork dan kolaborasi dalam project
- ✅ Technical documentation (code, diagram, report)
- ✅ Technical presentation dan demo
- ✅ Independent learning (baca dokumentasi, troubleshoot)

### **Mindset**:

- ✅ **Maker Mindset**: Berani mencoba, tidak takut error
- ✅ **Systematic Approach**: Break complex problem into smaller parts
- ✅ **Continuous Learning**: Teknologi IoT terus berkembang

---

## 🚀 Pathway Lanjutan (Post-Course)

### **Level 2 - Intermediate**:

1. **ESP-IDF** (ESP32 native framework, lebih powerful dari Arduino)
2. **FreeRTOS** (Real-time operating system untuk multi-tasking)
3. **AsyncWebServer & WebSocket** (untuk real-time web app)
4. **PCB Design** (KiCad, EasyEDA - dari breadboard ke PCB)

### **Level 3 - Advanced**:

1. **Machine Learning on Edge** (TensorFlow Lite untuk ESP32)
2. **LoRaWAN & NB-IoT** (untuk komunikasi jarak jauh)
3. **Mesh Networking** (ESP-MESH untuk network besar)
4. **Custom Hardware Design** (design board ESP32 sendiri)

### **Spesialisasi**:

1. **Smart Agriculture**: Soil moisture, weather station, automation
2. **Smart Home**: Home automation, security, energy monitoring
3. **Health Tech**: Wearable devices, health monitoring
4. **Industrial IoT**: Predictive maintenance, SCADA integration
5. **Robotics**: Autonomous robot dengan ESP32

### **Career Path**:

- IoT Developer
- Embedded Systems Engineer
- Firmware Engineer
- Hardware Engineer
- IoT Solutions Architect

---

## 📝 Catatan Penting untuk Implementasi

### **Adaptasi Kurikulum**:

- Kurikulum ini **fleksibel** dan bisa disesuaikan dengan:
  - Kalender akademik kampus
  - Budget yang tersedia
  - Jumlah mahasiswa
  - Ketersediaan komponen di pasar lokal

### **Backup Plan**:

- Jika komponen langka/mahal: gunakan **simulator Wokwi**
- Jika WiFi lab tidak stabil: gunakan **hotspot smartphone** atau ESP32 AP mode
- Jika jumlah mahasiswa banyak: **praktikum berpasangan** (2 mahasiswa/kit)

### **Continuous Improvement**:

- Evaluasi tiap semester:
  - Materi mana yang sulit dipahami?
  - Praktikum mana yang paling engage?
  - Komponen mana yang sering rusak?
- Update materi mengikuti perkembangan teknologi

---

**Disusun untuk**: Mata Kuliah Mikrokontroller - Prodi Informatika Universitas Mulawarman  
**Versi**: 2.0 (Revised Edition)  
**Platform**: ESP32 + Arduino IDE  
**Target**: Mahasiswa Informatika tanpa background elektronika  
**Pendekatan**: Project-based, hands-on, beginner-friendly  
**Total Contact Hours**: 48 jam (16 pertemuan × 3 SKS)

---

_"From Zero to IoT Hero in One Semester!"_ 🚀  
_"Building Future-Ready Engineers"_ 💡
