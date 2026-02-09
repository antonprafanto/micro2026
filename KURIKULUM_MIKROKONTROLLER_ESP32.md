# Kurikulum Mata Kuliah Mikrokontroller ESP32

## Universitas Mulawarman - Prodi Informatika

### 📋 Informasi Mata Kuliah

- **Jumlah Pertemuan**: 16 Pertemuan
- **Platform**: ESP32
- **IDE**: Arduino IDE
- **Target**: Mahasiswa Informatika (tanpa background elektronika)
- **Pendekatan**: Project-based learning dengan teori yang cukup

---

## 🎯 Capaian Pembelajaran

Setelah menyelesaikan mata kuliah ini, mahasiswa diharapkan mampu:

1. Memahami konsep dasar mikrokontroller dan embedded systems
2. Menggunakan ESP32 untuk membangun sistem IoT sederhana
3. Membaca sensor dan mengontrol aktuator
4. Mengimplementasikan komunikasi wireless (WiFi, Bluetooth)
5. Mengintegrasikan ESP32 dengan layanan cloud
6. Merancang dan mengimplementasikan project IoT end-to-end

---

## 📚 Rencana Pertemuan

### **Pertemuan 1: Pengenalan Embedded Systems & ESP32**

**Tujuan**: Memahami konsep dasar embedded systems dan mengenal ESP32

**Materi**:

- Apa itu mikrokontroller dan embedded systems?
- Perbandingan Arduino, ESP8266, ESP32
- Arsitektur ESP32 (CPU, memory, GPIO, peripheral)
- Kelebihan ESP32: WiFi, Bluetooth, dual-core, banyak GPIO
- Pengenalan Arduino IDE untuk ESP32
- Setup environment: Install Arduino IDE, driver, board manager

**Praktikum**:

- Instalasi Arduino IDE dan ESP32 board support
- Upload program "Blink" pertama (LED onboard)
- Modifikasi delay dan observasi hasil

**Deliverable**: Screenshot hasil blink LED

---

### **Pertemuan 2: Dasar Pemrograman Arduino & Digital I/O**

**Tujuan**: Memahami struktur program Arduino dan digital I/O

**Materi**:

- Struktur program Arduino: `setup()`, `loop()`
- Konsep GPIO (General Purpose Input/Output)
- Digital Output: `pinMode()`, `digitalWrite()`
- Digital Input: `pinMode()`, `digitalRead()`
- Pull-up dan pull-down resistor (internal)
- Debouncing untuk button

**Praktikum**:

- LED blink dengan external LED
- Kontrol LED dengan push button
- Multiple LED pattern (traffic light simulation)
- Button counter dengan serial monitor

**Deliverable**: Program traffic light sederhana

---

### **Pertemuan 3: Analog I/O & PWM**

**Tujuan**: Memahami sinyal analog dan PWM

**Materi**:

- Perbedaan sinyal digital vs analog
- ADC (Analog to Digital Converter) pada ESP32
- `analogRead()` dan resolusi ADC (12-bit di ESP32)
- PWM (Pulse Width Modulation) concept
- `analogWrite()` / `ledcWrite()` pada ESP32

**Praktikum**:

- Membaca potensiometer dengan `analogRead()`
- Kontrol brightness LED dengan PWM
- Breathing LED effect
- Kontrol kecepatan motor DC dengan PWM (opsional, jika ada motor)

**Deliverable**: Program LED brightness control dengan potentiometer

---

### **Pertemuan 4: Serial Communication & Debugging**

**Tujuan**: Komunikasi serial untuk debugging dan data monitoring

**Materi**:

- Konsep komunikasi serial (UART)
- Serial Monitor dan Serial Plotter
- `Serial.begin()`, `Serial.print()`, `Serial.println()`
- Input dari serial monitor
- Debugging techniques

**Praktikum**:

- Mengirim data sensor ke serial monitor
- Membuat simple command interface via serial
- Visualisasi data dengan Serial Plotter
- Menu-driven program via serial

**Deliverable**: Program interactive menu via serial

---

### **Pertemuan 5: Sensor Suhu & Kelembaban (DHT22)**

**Tujuan**: Membaca sensor suhu dan kelembaban

**Materi**:

- Jenis sensor suhu: DHT11, DHT22, DS18B20
- Protokol komunikasi 1-Wire (DHT)
- Library DHT sensor
- Cara membaca datasheet sensor
- Error handling saat pembacaan sensor

**Praktikum**:

- Instalasi library DHT
- Membaca data DHT22
- Menampilkan data ke serial monitor
- Indikator LED berdasarkan suhu (threshold)

**Deliverable**: Sistem monitoring suhu dengan indikator LED

---

### **Pertemuan 6: Sensor Jarak & Motion (Ultrasonic, PIR)**

**Tujuan**: Deteksi jarak dan gerakan

**Materi**:

- Sensor ultrasonic HC-SR04 (prinsip kerja)
- Trigger dan Echo pulse
- Menghitung jarak dari waktu tempuh
- Sensor PIR (Passive Infrared) untuk deteksi gerakan
- Aplikasi: automatic door, alarm system

**Praktikum**:

- Mengukur jarak dengan HC-SR04
- Display jarak di serial monitor
- Deteksi gerakan dengan PIR
- Membuat alarm sederhana (buzzer + PIR)

**Deliverable**: Sistem deteksi parkir dengan buzzer warning

---

### **Pertemuan 7: Display LCD/OLED**

**Tujuan**: Menampilkan data ke LCD atau OLED

**Materi**:

- LCD 16x2 dengan I2C
- OLED display (SSD1306) dengan I2C
- Protokol I2C (konsep dasar)
- Library untuk LCD/OLED
- Menggambar text, shape di OLED

**Praktikum**:

- Setup komunikasi I2C
- Menampilkan text di LCD/OLED
- Display data sensor (suhu/jarak) di OLED
- Membuat UI sederhana dengan menu

**Deliverable**: Dashboard sensor di OLED (suhu + jarak)

---

### **Pertemuan 8: Web Server Dasar di ESP32**

**Tujuan**: Membuat web server sederhana untuk monitoring

**Materi**:

- Konsep WiFi AP dan STA mode
- Koneksi ESP32 ke WiFi
- Library ESP32 WebServer
- HTTP request & response basics
- HTML sederhana untuk interface

**Praktikum**:

- Koneksi ESP32 ke WiFi router
- Membuat web server sederhana
- Menampilkan "Hello World" di browser
- Menampilkan data sensor di web page
- Control LED via web button

**Deliverable**: Web dashboard untuk monitoring 1 sensor

---

### **Pertemuan 9: REST API & JSON**

**Tujuan**: Komunikasi dengan format JSON dan REST API

**Materi**:

- Konsep REST API
- Format data JSON
- Library ArduinoJson
- Parsing dan creating JSON
- GET dan POST request

**Praktikum**:

- Membuat REST API endpoint di ESP32
- Return sensor data dalam format JSON
- Parsing JSON dari API eksternal
- Kontrol aktuator via API POST request

**Deliverable**: REST API untuk kontrol LED dan baca sensor

---

### **Pertemuan 10: WiFi & Cloud Integration (ThingSpeak/Blynk)**

**Tujuan**: Mengirim data sensor ke cloud platform

**Materi**:

- IoT cloud platforms overview
- ThingSpeak untuk data logging
- API key dan channel setup
- HTTP POST untuk upload data
- Visualisasi data di dashboard cloud

**Praktikum**:

- Setup ThingSpeak account dan channel
- Upload data sensor ke ThingSpeak
- Membuat grafik real-time di ThingSpeak
- Setup alert/notification (opsional)

**Deliverable**: Sistem monitoring suhu cloud-based

---

### **Pertemuan 11: Bluetooth & BLE Communication**

**Tujuan**: Komunikasi dengan smartphone via Bluetooth

**Materi**:

- Bluetooth Classic vs BLE (Bluetooth Low Energy)
- Serial Bluetooth pada ESP32
- Library BluetoothSerial
- Pairing dengan smartphone
- App mobile untuk testing (Serial Bluetooth Terminal)

**Praktikum**:

- Setup Bluetooth Serial
- Komunikasi dua arah ESP32 - smartphone
- Kontrol LED dari smartphone
- Kirim data sensor ke smartphone

**Deliverable**: Aplikasi kontrol LED via Bluetooth dengan smartphone

---

### **Pertemuan 12: MQTT Protocol untuk IoT**

**Tujuan**: Implementasi protokol MQTT untuk IoT messaging

**Materi**:

- Konsep MQTT: publisher, subscriber, broker
- Topic dan QoS (Quality of Service)
- Public MQTT broker (HiveMQ, Mosquitto)
- Library PubSubClient
- Use case: smart home, sensor network

**Praktikum**:

- Setup koneksi ke MQTT broker
- Publish data sensor ke topic
- Subscribe ke topic untuk kontrol
- Membuat sistem multi-device communication

**Deliverable**: 2 ESP32 berkomunikasi via MQTT

---

### **Pertemuan 13: Data Logging & SPIFFS/SD Card**

**Tujuan**: Menyimpan data lokal di ESP32

**Materi**:

- File system pada ESP32 (SPIFFS)
- SD Card module dengan SPI
- Membaca dan menulis file
- CSV format untuk sensor data
- Log rotation dan management

**Praktikum**:

- Setup SPIFFS filesystem
- Logging data sensor ke file
- Membaca historical data
- Export data via web server
- (Opsional) SD Card logging untuk data besar

**Deliverable**: Data logger dengan web interface untuk download

---

### **Pertemuan 14: Real-Time Clock & Timer**

**Tujuan**: Manajemen waktu dan scheduling task

**Materi**:

- RTC (Real-Time Clock) module: DS3231
- NTP (Network Time Protocol) untuk sync waktu via WiFi
- Hardware timer pada ESP32
- Software timer dan scheduling
- Time-based automation

**Praktikum**:

- Sync waktu dengan NTP server
- Display real-time clock di OLED
- Scheduling task (e.g., baca sensor setiap 10 menit)
- Time-stamped data logging

**Deliverable**: Scheduled sensor reading dengan timestamp

---

### **Pertemuan 15: Project Integration - Smart Home Prototype**

**Tujuan**: Integrasi semua komponen dalam satu project

**Materi**:

- System design untuk IoT project
- Best practices: modular code, error handling
- Power management
- Security basics (password, HTTPS)

**Praktikum**:

- Merancang sistem smart home sederhana
- Integrasi: sensor (DHT22, PIR), display (OLED), connectivity (WiFi)
- Web dashboard untuk monitoring dan kontrol
- Cloud data logging (ThingSpeak)
- Alert system via email/notification (opsional)

**Deliverable**: Working prototype smart home system

---

### **Pertemuan 16: Presentasi Project & Evaluasi**

**Tujuan**: Presentasi project akhir dan peer review

**Agenda**:

- Presentasi project kelompok (10-15 menit/kelompok)
- Demo sistem
- Q&A dan feedback
- Peer review
- Evaluasi pembelajaran
- Future learning path (ESP-IDF, FreeRTOS, dll)

**Deliverable**:

- Project documentation
- Source code (GitHub)
- Video demo
- Laporan project

---

## 🛠️ Perangkat yang Dibutuhkan

### Hardware Essentials (per mahasiswa/kelompok):

1. **ESP32 Development Board** (NodeMCU-32S atau sejenisnya)
2. **Kabel USB Micro/Type-C** (untuk programming)
3. **Breadboard** (400 atau 800 point)
4. **Jumper wires** (male-male, male-female)
5. **LED** (berbagai warna, 5-10 pcs)
6. **Resistor** (220Ω - 10kΩ, assorted)
7. **Push button** (2-4 pcs)
8. **Sensor DHT22** (suhu & kelembaban)
9. **Sensor HC-SR04** (ultrasonic)
10. **Sensor PIR** (motion detector)
11. **OLED Display 0.96" I2C** (SSD1306)
12. **Buzzer**
13. **Potensiometer 10kΩ**

### Hardware Opsional:

- **RTC Module DS3231**
- **SD Card Module**
- **Relay Module** (untuk kontrol AC appliances)
- **Motor DC + L298N Driver** (opsional)

### Software:

1. **Arduino IDE** (versi terbaru)
2. **Driver ESP32** (CH340 atau CP2102, sesuai board)
3. **Library Arduino**: DHT, Adafruit SSD1306, WiFi, WebServer, ArduinoJson, PubSubClient
4. **Serial Terminal** app di smartphone (opsional)

---

## 📊 Metode Evaluasi

### Komponen Penilaian:

1. **Praktikum/Lab Work (30%)**
   - Deliverable tiap pertemuan
   - Code quality & documentation
   - Partisipasi aktif

2. **Quiz/UTS (20%)**
   - Teori embedded systems
   - Pemrograman Arduino
   - Problem solving

3. **Project Akhir (40%)**
   - Kompleksitas sistem
   - Integrasi komponen
   - Presentasi & demo
   - Documentation
   - Kreativitas & inovasi

4. **Attitude & Attendance (10%)**
   - Kehadiran
   - Partisipasi diskusi
   - Kolaborasi tim

---

## 📖 Referensi & Resources

### Buku & Dokumentasi:

1. **ESP32 Official Documentation** - [docs.espressif.com](https://docs.espressif.com)
2. **Arduino Reference** - [arduino.cc/reference](https://www.arduino.cc/reference/en/)
3. **Random Nerd Tutorials** - Excellent ESP32 tutorials
4. **Last Minute Engineers** - Sensor tutorials

### Online Resources:

1. **GitHub Examples**: Search "ESP32 Arduino examples"
2. **YouTube Channels**:
   - DroneBot Workshop
   - Random Nerd Tutorials
   - Great Scott!
3. **Forum**:
   - ESP32.com
   - Arduino Forum
   - Stack Overflow

### Dataset & Tools:

1. **ThingSpeak** - IoT analytics platform
2. **Blynk** - IoT mobile app builder
3. **MQTT Explorer** - MQTT client tool
4. **Fritzing** - Circuit diagram tool

---

## 💡 Tips Mengajar

### Untuk Dosen:

1. **Mulai dari yang Konkret**: Selalu mulai dengan demo hardware yang bisa dilihat/disentuh
2. **Analogi Kehidupan Sehari-hari**: Gunakan analogi (misal: GPIO seperti saklar lampu)
3. **Coding Live**: Live coding di kelas lebih efektif dari slide
4. **Troubleshooting Bersama**: Jadikan error sebagai pembelajaran
5. **Project-based**: Dorong kreativitas dengan project real-world

### Untuk Mahasiswa:

1. **Hands-on Practice**: Tidak bisa belajar embedded tanpa praktek
2. **Google is Your Friend**: Error message = search di Google
3. **Start Simple**: Jangan langsung project kompleks, mulai dari LED blink
4. **Breakout the Problem**: Pecah problem besar jadi komponen kecil
5. **Documentation**: Biasakan dokumentasi code dan circuit

---

## 🎓 Learning Outcomes yang Diharapkan

Setelah 16 pertemuan, mahasiswa mampu:

- ✅ Setup dan programming ESP32 secara mandiri
- ✅ Membaca berbagai jenis sensor
- ✅ Mengontrol aktuator (LED, buzzer, relay, motor)
- ✅ Membuat UI sederhana (LCD/OLED, Web)
- ✅ Implementasi komunikasi wireless (WiFi, Bluetooth, MQTT)
- ✅ Integrasi dengan cloud platform
- ✅ Data logging dan time management
- ✅ Merancang dan implementasi sistem IoT end-to-end
- ✅ Troubleshooting hardware dan software issues
- ✅ Mendokumentasikan project teknis

---

## 🚀 Next Steps (Lanjutan Pembelajaran)

Untuk mahasiswa yang ingin eksplorasi lebih lanjut:

1. **ESP-IDF** (Framework native ESP32, lebih advanced)
2. **FreeRTOS** (Real-time OS untuk ESP32)
3. **MicroPython/CircuitPython** (Python untuk mikrokontroller)
4. **PCB Design** (KiCad, EasyEDA)
5. **Advanced IoT**: LoRaWAN, Zigbee, Thread
6. **Machine Learning on Edge** (TensorFlow Lite)
7. **Low Power Design** (untuk battery-powered devices)

---

**Disusun untuk**: Mata Kuliah Mikrokontroller - Prodi Informatika Universitas Mulawarman  
**Platform**: ESP32 + Arduino IDE  
**Target**: Mahasiswa Informatika tanpa background elektronika  
**Fokus**: Praktis, project-based, easy to understand

_"From Blink to IoT in 16 Weeks!"_ 🚀
