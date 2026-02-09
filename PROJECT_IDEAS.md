# 💡 Project Ideas - Mata Kuliah Mikrokontroller ESP32

## Inspirasi Project Akhir untuk Mahasiswa

---

## 📌 Panduan Memilih Project

### **Kriteria Project yang Baik**:

✅ **Solvable**: Bisa diselesaikan dalam 4-5 minggu  
✅ **Measurable**: Ada output yang bisa diukur/didemo  
✅ **Realistic**: Komponen tersedia dan affordable  
✅ **Interesting**: Topik yang Anda minati (lebih enjoy!)  
✅ **Valuable**: Punya nilai guna untuk real-world

### **Minimum Requirements** (checklist):

- [ ] Min 3 sensor/input device
- [ ] Min 2 aktuator/output device
- [ ] Display (OLED/Web dashboard)
- [ ] Komunikasi wireless (WiFi/Bluetooth/MQTT)
- [ ] Data logging atau cloud integration
- [ ] Security consideration

---

## 🏡 Kategori 1: Smart Home & Automation

### **1.1 Smart Room Monitoring & Control**

**Deskripsi**: Sistem monitoring dan kontrol kamar/ruangan otomatis

**Fitur**:

- Monitor suhu & kelembaban (DHT22)
- Deteksi gerakan dengan PIR
- Kontrol lampu (relay/LED) otomatis
- Web dashboard untuk remote control
- Alarm jika suhu/kelembaban abnormal
- Data logging ke ThingSpeak

**Komponen**:

- ESP32, DHT22, PIR sensor, Relay module, LED indicator, Buzzer

**Level**: ⭐⭐ (Beginner-Intermediate)

**Extension Ideas**:

- Tambah LDR untuk kontrol lampu berdasarkan cahaya
- Mobile app (Blynk/Flutter)
- Voice control via Google Assistant (IFTTT)

---

### **1.2 Smart Door Lock System**

**Deskripsi**: Sistem kunci pintu dengan multiple authentication

**Fitur**:

- Unlock via RFID card
- Unlock via Bluetooth (smartphone)
- Unlock via web (password)
- Log semua akses (timestamp, metode)
- Alert jika ada unauthorized access
- Display status di OLED

**Komponen**:

- ESP32, RFID RC522, Servo motor (untuk lock), Buzzer, OLED, LED

**Level**: ⭐⭐⭐ (Intermediate)

**Extension Ideas**:

- Face recognition dengan ESP32-CAM
- OTP (One-Time Password) via SMS/email
- Battery backup untuk power outage

---

### **1.3 Energy Monitoring System**

**Deskripsi**: Monitor konsumsi listrik peralatan rumah

**Fitur**:

- Ukur voltage & current (sensor ACS712 atau PZEM-004T)
- Hitung daya (Watt) dan energi (kWh)
- Web dashboard dengan grafik real-time
- Prediksi biaya listrik bulanan
- Alert jika konsumsi melebihi threshold
- Data export ke CSV

**Komponen**:

- ESP32, ACS712 (current sensor) atau PZEM-004T, OLED, Relay (optional ON/OFF control)

**Level**: ⭐⭐⭐⭐ (Advanced)

**Extension Ideas**:

- Machine learning untuk prediksi pola konsumsi
- Integrasi dengan tarif PLN real-time
- Multi-channel monitoring (beberapa device)

---

## 🌱 Kategori 2: Smart Agriculture

### **2.1 Smart Plant Watering System**

**Deskripsi**: Sistem penyiraman tanaman otomatis berdasarkan kelembaban tanah

**Fitur**:

- Soil moisture sensor untuk deteksi kekeringan
- Pompa air otomatis (relay + water pump)
- Mode manual & otomatis (via web)
- Monitoring suhu & kelembaban udara (DHT22)
- Jadwal penyiraman (RTC)
- Notifikasi via Telegram jika tanah kering

**Komponen**:

- ESP32, Soil moisture sensor, DHT22, Relay module, Water pump (DC 5V), RTC DS3231

**Level**: ⭐⭐⭐ (Intermediate)

**Extension Ideas**:

- Tambah light sensor untuk monitor cahaya
- Multi-plant monitoring (beberapa pot)
- AI prediction kapan perlu siram berdasarkan history

---

### **2.2 Greenhouse Monitoring & Control**

**Deskripsi**: Sistem monitoring greenhouse dengan automatic ventilation

**Fitur**:

- Monitor suhu, kelembaban, cahaya (LDR)
- Automatic fan control jika suhu tinggi
- Automatic light jika cahaya kurang (relay + growlight)
- Water misting jika kelembaban rendah
- Web dashboard dengan grafik
- Cloud logging (ThingSpeak)

**Komponen**:

- ESP32, DHT22, LDR, Relay (3-channel), Fan, LED growlight, Soil moisture

**Level**: ⭐⭐⭐⭐ (Advanced)

**Extension Ideas**:

- Camera untuk monitoring visual (ESP32-CAM)
- CO2 sensor (MQ-135)
- Nutrient monitoring (TDS sensor)

---

### **2.3 Chicken Coop Automation**

**Deskripsi**: Sistem otomasi kandang ayam (cocok untuk Unmul - tema peternakan!)

**Fitur**:

- Automatic feeder (schedule-based, servo motor)
- Temperature & humidity monitoring
- Automatic light (relay, timer-based)
- Egg counter (IR sensor atau load cell)
- Alert jika suhu ekstrem (heat stress)
- Data logging untuk analisis produktivitas

**Komponen**:

- ESP32, DHT22, Servo, Relay, IR sensor/load cell, RTC, Buzzer

**Level**: ⭐⭐⭐ (Intermediate)

**Extension Ideas**:

- Weight monitoring (load cell untuk berat ayam)
- Ammonia detection (MQ-137)
- IoT dashboard untuk farm management

---

## 🏥 Kategori 3: Health & Safety

### **3.1 Personal Health Monitor (Wearable-like)**

**Deskripsi**: Sistem monitoring kesehatan portabel

**Fitur**:

- Heart rate monitoring (pulse sensor/MAX30102)
- Body temperature (MLX90614 non-contact atau DS18B20)
- SpO2 monitoring (MAX30102)
- OLED display real-time data
- Bluetooth ke smartphone
- Alert jika vital sign abnormal

**Komponen**:

- ESP32, MAX30102 (heart rate + SpO2), MLX90614 (temperature), OLED, Buzzer, Battery

**Level**: ⭐⭐⭐⭐ (Advanced)

**Extension Ideas**:

- GPS tracker (for elderly/patient tracking)
- Fall detection (MPU6050 accelerometer)
- Cloud sync untuk medical record

---

### **3.2 Medicine Reminder & Pill Dispenser**

**Deskripsi**: Pengingat minum obat dengan dispenser otomatis

**Fitur**:

- Reminder berdasarkan jadwal (RTC)
- Alarm (buzzer + LED) saat waktu minum obat
- Servo motor untuk dispense pill
- Confirmation button (pasien confirm sudah minum)
- Log compliance (% ketaatan minum obat)
- Notifikasi ke caregiver via Telegram jika lupa

**Komponen**:

- ESP32, RTC DS3231, Servo motor, Buzzer, Button, LED, OLED

**Level**: ⭐⭐⭐ (Intermediate)

**Extension Ideas**:

- RFID untuk multi-patient (rumah sakit)
- Pill counting sensor
- Mobile app untuk caregiver monitoring

---

### **3.3 Air Quality Monitor**

**Deskripsi**: Monitoring kualitas udara dalam ruangan

**Fitur**:

- PM2.5 & PM10 (sensor PMS5003/PMS7003)
- CO2 level (MQ-135 atau MH-Z19)
- Temperature & humidity (DHT22)
- Air Quality Index (AQI) calculation
- LED indikator (hijau/kuning/merah)
- Web dashboard dengan tren 24 jam
- Alert jika kualitas buruk

**Komponen**:

- ESP32, PMS5003, MQ-135, DHT22, RGB LED, OLED, Buzzer

**Level**: ⭐⭐⭐⭐ (Advanced)

**Extension Ideas**:

- Machine learning untuk prediksi AQI
- Integrasi dengan smart fan/air purifier
- Multi-room monitoring

---

## 🏫 Kategori 4: Education & Labs

### **4.1 Smart Attendance System**

**Deskripsi**: Sistem absensi dengan multiple method

**Fitur**:

- RFID card scanning
- Face recognition (ESP32-CAM) - opsional
- QR code scanning
- Auto-send data ke Google Sheets/database
- OLED display nama + status
- Late detection (based on class schedule)
- Export report (CSV)

**Komponen**:

- ESP32, RFID RC522, ESP32-CAM (opsional), OLED

**Level**: ⭐⭐⭐ (Intermediate)

**Extension Ideas**:

- Temperature screening (untuk protokol kesehatan)
- Geofencing (hanya bisa absen di area tertentu)
- Mobile app untuk dosen review attendance

---

### **4.2 Lab Equipment Monitoring & Booking**

**Deskripsi**: Sistem monitoring dan booking peralatan lab

**Fitur**:

- RFID untuk borrow/return equipment
- Real-time availability status (web dashboard)
- Usage time tracking
- Automatic reminder jika overdue
- Equipment location tracking (which room)
- Maintenance schedule tracker

**Komponen**:

- ESP32, RFID reader, OLED, Buzzer, Real-time database (Firebase)

**Level**: ⭐⭐⭐ (Intermediate)

**Extension Ideas**:

- Multiple ESP32 nodes (distributed system)
- Mobile app untuk booking
- Equipment condition reporting

---

## 🚗 Kategori 5: Transportation & Security

### **5.1 Smart Parking System**

**Deskripsi**: Sistem parkir dengan deteksi slot kosong

**Fitur**:

- Ultrasonic sensors untuk deteksi mobil (per slot)
- LED indikator merah/hijau per slot
- Display jumlah slot kosong di OLED
- Web dashboard peta parking
- Entry/exit barrier control (servo motor)
- Parking duration & fee calculation

**Komponen**:

- ESP32, HC-SR04 (multiple), Servo, LED, OLED

**Level**: ⭐⭐⭐ (Intermediate)

**Extension Ideas**:

- License plate recognition (ESP32-CAM)
- Payment integration (RFID e-money)
- Reservation system

---

### **5.2 Vehicle Tracking & Security**

**Deskripsi**: GPS tracker dengan alarm & geofencing

**Fitur**:

- GPS tracking (NEO-6M module)
- Real-time location di Google Maps (web)
- Geofencing alert (jika keluar area tertentu)
- Motion detection (MPU6050)
- Starter disable (relay untuk immobilizer)
- Panic button (kirim alert + koordinat)

**Komponen**:

- ESP32, NEO-6M GPS, MPU6050, Relay, Button, Buzzer

**Level**: ⭐⭐⭐⭐ (Advanced)

**Extension Ideas**:

- Fuel level monitoring
- Engine diagnostic (OBD-II reader)
- Driver behavior scoring (acceleration, braking)

---

### **5.3 Bike/Motorcycle Smart Lock**

**Deskripsi**: Kunci motor pintar dengan multiple unlock method

**Fitur**:

- Unlock via Bluetooth (smartphone proximity)
- Unlock via keypad (password)
- Alarm jika ada gerakan saat terkunci (MPU6050)
- GPS tracking jika dicuri
- Auto-lock setelah smartphone menjauh
- Low battery warning

**Komponen**:

- ESP32, Servo/solenoid lock, MPU6050, Keypad, Buzzer, GPS (opsional), Battery

**Level**: ⭐⭐⭐⭐ (Advanced)

**Extension Ideas**:

- Fingerprint sensor
- Remote engine start
- Sharing access (multiple users)

---

## 🎮 Kategori 6: Entertainment & Hobbies

### **6.1 Smart Aquarium Controller**

**Deskripsi**: Otomasi dan monitoring akuarium

**Fitur**:

- Temperature monitoring (DS18B20 waterproof)
- pH monitoring (pH sensor)
- Automatic light schedule (relay + LED strip)
- Automatic feeder (servo motor)
- Water level detection (ultrasonic)
- Alert jika parameter abnormal
- Web dashboard

**Komponen**:

- ESP32, DS18B20, pH sensor, Relay, Servo, HC-SR04, LED strip, RTC

**Level**: ⭐⭐⭐⭐ (Advanced)

**Extension Ideas**:

- Camera untuk live view (ESP32-CAM)
- TDS sensor untuk water quality
- Automatic water changer (pump + relay)

---

### **6.2 Weather Station**

**Deskripsi**: Stasiun cuaca personal dengan cloud logging

**Fitur**:

- Temperature & humidity (DHT22)
- Barometric pressure (BMP180/BMP280)
- Rain detection (rain sensor)
- Wind speed (anemometer DIY dengan Hall sensor)
- UV index (GUVA-S12SD)
- OLED display local data
- Upload to Weather Underground API
- Forecast prediction based on pressure trend

**Komponen**:

- ESP32, DHT22, BMP280, Rain sensor, Hall sensor (anemometer), UV sensor, OLED

**Level**: ⭐⭐⭐⭐ (Advanced)

**Extension Ideas**:

- Solar powered
- LoRa untuk remote sending
- Lightning detector (AS3935)

---

### **6.3 Smart Pet Feeder**

**Deskripsi**: Pemberi makan hewan peliharaan otomatis

**Fitur**:

- Scheduled feeding (RTC)
- Portion control (servo untuk dispense)
- Manual feeding via web/app
- Food level monitoring (ultrasonic di container)
- Feeding log & analytics
- Camera untuk lihat pet (ESP32-CAM)
- Voice recording play saat feeding

**Komponen**:

- ESP32, Servo, RTC, HC-SR04, ESP32-CAM (opsional), Speaker (opsional)

**Level**: ⭐⭐⭐ (Intermediate)

**Extension Ideas**:

- Weight monitoring (load cell)
- Pet recognition (RFID collar untuk multi-pet)
- Activity tracking

---

## 🏭 Kategori 7: Industrial & Monitoring

### **7.1 Vibration & Predictive Maintenance**

**Deskripsi**: Monitor getaran mesin untuk predictive maintenance

**Fitur**:

- Vibration detection (MPU6050/ADXL345)
- Temperature monitoring (thermocouple)
- Pattern analysis (FFT untuk anomaly detection)
- Alert jika getaran abnormal
- Maintenance schedule tracker
- Data logging untuk ML training

**Komponen**:

- ESP32, MPU6050, Thermocouple + MAX6675, Buzzer, OLED

**Level**: ⭐⭐⭐⭐⭐ (Very Advanced)

**Extension Ideas**:

- Machine learning model untuk failure prediction
- Multiple sensor nodes (MQTT network)
- Integration dengan SCADA

---

### **7.2 Inventory Management System**

**Deskripasi**: Sistem tracking inventory dengan barcode/RFID

**Fitur**:

- Barcode scanning (camera module)
- RFID tagging untuk expensive items
- Real-time stock database (Firebase)
- Low stock alert
- Web dashboard untuk stock monitoring
- Check-in/check-out logging

**Komponen**:

- ESP32, ESP32-CAM atau Barcode scanner module, RFID, OLED

**Level**: ⭐⭐⭐⭐ (Advanced)

**Extension Ideas**:

- Mobile app untuk warehouse staff
- Automatic reorder (integration dengan supplier API)
- Expiry date tracking

---

## 🎓 Tips Sukses Project Akhir

### **1. Planning Phase (Minggu 10-11)**:

- [ ] Pilih topik yang Anda **passionate** about
- [ ] Research feasibility (komponen tersedia? budget cukup?)
- [ ] Buat **proposal** dengan: problem statement, solution, komponen list, timeline
- [ ] Diskusikan dengan dosen

### **2. Prototyping Phase (Minggu 12-13)**:

- [ ] Beli komponen
- [ ] Test tiap sensor/aktuator **one by one** (jangan langsung integrasi!)
- [ ] Buat breadboard prototype

### **3. Integration Phase (Minggu 14)**:

- [ ] Integrasi semua komponen
- [ ] Implement feature 1 by 1, test incrementally
- [ ] Handle edge cases & error

### **4. Polish Phase (Minggu 15)**:

- [ ] UI/UX improvement
- [ ] Code cleanup & commenting
- [ ] Documentation (README, circuit diagram)
- [ ] Video demo recording
- [ ] Presentation slides

### **5. Presentation (Minggu 16)**:

- [ ] Latihan demo 3-5x sebelum presentasi
- [ ] Siapkan video backup jika live demo gagal
- [ ] Q&A preparation: pikirkan pertanyaan yang mungkin ditanya

---

## 🚫 Kesalahan yang Sering Terjadi (AVOID!)

❌ **Scope terlalu besar**: "Saya mau buat smart city!" → Impossible dalam 5 minggu!  
❌ **Komponen langka**: Gunakan komponen yang mudah didapat di Indonesia  
❌ **Tidak test dulu**: Langsung beli semua komponen tanpa test → ada yang tidak kompatibel  
❌ **Menunda**: Mulai minggu 15 → KIAMAT!  
❌ **Solo hero**: Tidak kolaborasi dengan partner  
❌ **Hardcode everything**: WiFi password di code, push ke GitHub public → HACKED!  
❌ **No documentation**: Code tanpa comment, circuit tidak didokumentasi

---

## 💰 Budget Estimation per Kategori

| Kategori          | Est. Budget    | Difficulty | Wow Factor |
| ----------------- | -------------- | ---------- | ---------- |
| Smart Home        | Rp 250k - 400k | ⭐⭐       | ⭐⭐⭐     |
| Smart Agriculture | Rp 300k - 500k | ⭐⭐⭐     | ⭐⭐⭐⭐   |
| Health & Safety   | Rp 350k - 600k | ⭐⭐⭐⭐   | ⭐⭐⭐⭐⭐ |
| Transportation    | Rp 400k - 700k | ⭐⭐⭐⭐   | ⭐⭐⭐⭐   |
| Industrial        | Rp 350k - 550k | ⭐⭐⭐⭐⭐ | ⭐⭐⭐⭐   |

**Note**: Harga sudah termasuk ESP32 + starter kit basic (Rp 215k)

---

## 📚 Resources untuk Inspirasi Lebih

1. **Hackster.io** - ESP32 project database
2. **Instructables** - DIY electronics projects
3. **YouTube**: randomnerdtutorials, GreatScott!, Andreas Spiess
4. **GitHub**: Search "ESP32 + [topik Anda]"
5. **Reddit**: r/esp32, r/arduino

---

## ✅ Final Checklist Sebelum Submit Proposal

- [ ] Project description jelas (1-2 paragraf)
- [ ] Problem statement & solution
- [ ] Feature list (min 5 fitur)
- [ ] Komponen list lengkap dengan harga estimasi
- [ ] Block diagram sistem
- [ ] Timeline realistic (per minggu breakdown)
- [ ] Risk assessment (apa yang mungkin fail? backup plan?)
- [ ] Diskusi dengan partner tentang pembagian tugas

---

**Good luck dengan project Anda!** 🚀  
**Ingat**: _"The best project is the one you actually finish!"_

---

**Terakhir diupdate**: Februari 2026  
**Untuk**: Mata Kuliah Mikrokontroller - Prodi Informatika Unmul
