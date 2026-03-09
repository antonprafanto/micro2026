# ✅ Checklist Praktikum - Pertemuan 6

## Sensor Jarak (HC-SR04) & Interrupt Basics

> **Print checklist ini dan centang setiap step yang sudah selesai!** ✓

---

## 👤 Informasi

- **Nama**: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_
- **NIM**: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_
- **Tanggal**: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

---

## 📚 BAGIAN 1: Persiapan (Sebelum Praktikum)

### **Materi Teori**

- [ ] Sudah baca materi "Prinsip Sonar & Ultrasonik"
- [ ] Sudah baca materi "HC-SR04: Cara Kerja"
- [ ] Paham rumus: `jarak = (durasi × 0.034) / 2`
- [ ] Sudah baca materi "Polling vs Interrupt"
- [ ] Paham `attachInterrupt()`, ISR, `volatile`, `IRAM_ATTR`
- [ ] Sudah baca materi "Voltage Divider" (PENTING untuk keamanan!)

### **Persiapan Hardware**

- [ ] Arduino IDE 2.x terinstall
- [ ] ESP32 Board Support terinstall
- [ ] **Tidak perlu library tambahan** (HC-SR04 pakai `pulseIn()` built-in)
- [ ] ESP32 DevKit V1 siap
- [ ] HC-SR04 Ultrasonic Sensor siap
- [ ] Buzzer aktif siap
- [ ] LED 3 warna (hijau, kuning, merah) siap
- [ ] Resistor 220Ω × 3 (untuk LED) siap
- [ ] Resistor 1kΩ × 1 (voltage divider R1) siap
- [ ] Resistor 2kΩ × 1 atau 1kΩ × 2 seri (voltage divider R2) siap
- [ ] Breadboard + jumper wires siap

---

## 🔌 BAGIAN 2: Wiring

### **Step 1: Voltage Divider DULU!** ⚠️

> 🚨 **PENTING**: HC-SR04 Echo pin output **5V** — ESP32 max **3.6V**! Tanpa voltage divider, GPIO ESP32 bisa **RUSAK**!

- [ ] Pasang resistor 1kΩ (R1): satu ujung di jalur Echo, ujung lain ke titik junction
- [ ] Pasang resistor 2kΩ (R2): satu ujung di titik junction, ujung lain ke GND
- [ ] Titik junction → GPIO18 ESP32

```
Echo ──[1kΩ]──┬──► GPIO18 (3.33V ✅)
              [2kΩ]
              │
             GND
```

### **Step 2: Rangkai HC-SR04**

> ⚠️ **CABUT USB dari ESP32 sebelum wiring!**

- [ ] HC-SR04 VCC → ESP32 **VIN** (5V) — ⚠️ BUKAN 3V3!
- [ ] HC-SR04 Trig → ESP32 **GPIO5**
- [ ] HC-SR04 Echo → melalui **voltage divider** → **GPIO18**
- [ ] HC-SR04 GND → ESP32 **GND**

### **Step 3: Rangkai Buzzer**

- [ ] Buzzer (+) → ESP32 **GPIO19**
- [ ] Buzzer (-) → ESP32 **GND**

### **Step 4: Rangkai 3 LED**

- [ ] LED Hijau: GPIO15 → Resistor 220Ω → LED Anode → Cathode → GND
- [ ] LED Kuning: GPIO16 → Resistor 220Ω → LED Anode → Cathode → GND
- [ ] LED Merah: GPIO17 → Resistor 220Ω → LED Anode → Cathode → GND

### **Step 5: Safety Check** ⚠️

- [ ] HC-SR04 VCC ke **VIN (5V)**, bukan 3V3?
- [ ] Voltage divider terpasang di Echo?
- [ ] Tidak ada short circuit?
- [ ] Polaritas LED benar?
- [ ] Polaritas buzzer benar?
- [ ] Semua koneksi kencang?

---

## 📟 BAGIAN 3: Praktikum 1 — Baca Jarak Dasar

### **Step 1: Upload Code**

- [ ] Copy code **Praktikum 6.1** dari materi
- [ ] Pilih Board: **ESP32 Dev Module**
- [ ] Pilih Port: COM yang benar
- [ ] Upload ▶️

### **Step 2: Verify Output**

- [ ] Buka Serial Monitor (115200)
- [ ] Jarak tampil (contoh: `📏 Jarak: 45.2 cm`)
- [ ] Dekatkan tangan → jarak berkurang
- [ ] Jauhkan tangan → jarak bertambah
- [ ] Test batas dekat (<5cm)
- [ ] Test batas jauh (>3m) → error muncul

### **Pertanyaan**

- [ ] **Q**: Mengapa rumus jarak dibagi 2?
       Jawab: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

---

## 📟 BAGIAN 4: Praktikum 2 — Parking Sensor

### **Step 1: Upload Code**

- [ ] Copy code **Praktikum 6.2** dari materi
- [ ] Upload ke ESP32

### **Step 2: Test Semua Zone**

| Zone | Jarak | LED | Buzzer | ✓ |
|------|-------|-----|--------|---|
| AMAN | >50cm | 🟢 Hijau | OFF | [ ] |
| WASPADA | 20-50cm | 🟡 Kuning | Beep lambat | [ ] |
| DEKAT | 10-20cm | 🔴 Merah | Beep sedang | [ ] |
| BAHAYA | <10cm | 🔴 Blink | Beep cepat | [ ] |
| Error | >4m | — | — | [ ] |

### **Pertanyaan**

- [ ] **Q**: Apa fungsi `pulseIn()` dan apa yang di-return?
       Jawab: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

---

## 📟 BAGIAN 5: Praktikum 3 — Interrupt Demo

### **Step 1: Tambah Push Button**

- [ ] Push button: satu ujung ke **GPIO4**, ujung lain ke **GND**
- [ ] (Kita pakai INPUT_PULLUP, jadi tidak perlu resistor tambahan)

### **Step 2: Upload & Test**

- [ ] Copy code **Praktikum 6.3** dari materi
- [ ] Upload ke ESP32
- [ ] Monitoring jarak berjalan (ON)
- [ ] **Tekan button** → monitoring OFF
- [ ] **Tekan lagi** → monitoring ON
- [ ] Verify: button press **TIDAK PERNAH TERLEWAT** meskipun ada delay

### **Pertanyaan**

- [ ] **Q**: Apa perbedaan polling dan interrupt? Kapan pakai masing-masing?
       Jawab: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

- [ ] **Q**: Mengapa variable yang diubah di ISR harus `volatile`?
       Jawab: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

---

## 🏆 BAGIAN 6: Project Akhir — P06_Parking_Sensor

- [ ] Upload `code/P06_Parking_Sensor.ino`
- [ ] Splash screen tampil dengan pin info
- [ ] Komponen test (LED + buzzer berurutan)
- [ ] Semua zone berfungsi (aman/waspada/dekat/bahaya)
- [ ] Status bar visual (`█████░░░░░`) tampil
- [ ] Error handling saat out of range

---

## 📸 BAGIAN 7: Dokumentasi

### **Foto/Screenshot**

- [ ] Foto hardware: breadboard, HC-SR04, LED, buzzer, **voltage divider terlihat**
- [ ] Screenshot Serial Monitor: min 3 pembacaan + berbagai zone
- [ ] Save: `P06_Parking_[NIM]_[Nama].png`

### **Video Demo (WAJIB!)**

- [ ] Rekam 20-60 detik
- [ ] Tunjukkan:
  - [ ] Boot → komponen test
  - [ ] Dekatkan tangan bertahap: aman → waspada → dekat → bahaya
  - [ ] LED berubah warna sesuai jarak
  - [ ] Buzzer beep rate berubah
  - [ ] Jauhkan tangan → kembali aman
- [ ] Upload ke Google Drive / YouTube
- [ ] Copy link

---

## 🌟 BAGIAN 8: Challenge (Opsional — Bonus!)

- [ ] Tambah PIR sensor (VCC→VIN, OUT→GPIO4, GND→GND)
- [ ] Upload `P06_Challenge_PIR_Interrupt.ino`
- [ ] Test menu interaktif
- [ ] Gerakan terdeteksi → counter naik (interrupt)
- [ ] Test alarm: gerakan + jarak dekat → buzzer alarm
- [ ] Screenshot statistik

---

## 📤 BAGIAN 9: Submission

- [ ] Buka `P06_Template_Submission.md`
- [ ] Isi semua section
- [ ] Quality check: foto jelas, video valid, code lengkap
- [ ] Submit sebelum deadline!

---

## ✅ Final Check

- [ ] Semua checklist ✓
- [ ] Hardware berfungsi — **voltage divider terpasang**
- [ ] Foto & video ready
- [ ] Submission ready
- [ ] (Optional) Challenge completed

**Paraf**: \_\_\_\_\_\_\_\_\_ **Tanggal**: \_\_\_\_\_\_\_\_\_

---

**🎉 Selamat! Anda sudah menguasai Sensor Jarak & Interrupt Basics!**

**Next**: Pertemuan 7 — Display LCD/OLED & Review 📺

---

**Checklist ini dibuat untuk**: Mata Kuliah Mikrokontroller — Prodi Informatika Unmul
