# ✅ Checklist Praktikum - Pertemuan 5

## Sensor Suhu & Kelembaban (DHT22) + LED Indikator

> **Print checklist ini dan centang setiap step yang sudah selesai!** ✓

---

## 👤 Informasi

- **Nama**: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_
- **NIM**: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_
- **Tanggal**: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

---

## 📚 BAGIAN 1: Persiapan (Sebelum Praktikum)

### **Materi Teori** (Baca di rumah sebelum kelas)

- [ ] Sudah baca materi "Sensor Analog vs Digital"
- [ ] Sudah baca materi "DHT22 vs DHT11"
- [ ] Sudah baca materi "Protokol 1-Wire"
- [ ] Sudah baca materi "Error Handling (`isnan()`)"
- [ ] Paham kenapa butuh pull-up resistor 10kΩ
- [ ] Paham minimum sampling period DHT22 = 2 detik

### **Review Pertemuan 1-4**

- [ ] Paham GPIO, `pinMode()`, `digitalWrite()`
- [ ] Paham Serial Communication (`Serial.begin()`, `Serial.printf()`)
- [ ] Familiar dengan Arduino IDE 2.x
- [ ] Paham wiring LED + resistor

### **Persiapan Tools & Hardware**

- [ ] Arduino IDE 2.x terinstall
- [ ] ESP32 Board Support terinstall
- [ ] Library **DHT sensor library** (Adafruit) terinstall
- [ ] Library **Adafruit Unified Sensor** terinstall
- [ ] ESP32 DevKit V1 siap
- [ ] Sensor DHT22 siap
- [ ] Breadboard + jumper wires siap
- [ ] LED 3 warna (biru, hijau, merah) siap
- [ ] Resistor 220Ω × 3 (untuk LED) siap
- [ ] Resistor 10kΩ × 1 (pull-up DHT22) siap

**Estimasi waktu persiapan**: 30-40 menit (termasuk install library)

---

## 🔌 BAGIAN 2: Persiapan Wiring

### **Step 1: Rangkai DHT22**

> ⚠️ **CABUT USB dari ESP32 sebelum memasang wiring!**

- [ ] Pasang DHT22 di breadboard
- [ ] DHT22 Pin 1 (VCC) → ESP32 3V3
- [ ] DHT22 Pin 2 (DATA) → ESP32 GPIO4
- [ ] DHT22 Pin 4 (GND) → ESP32 GND
- [ ] Pasang resistor 10kΩ antara DATA dan 3V3 (pull-up)
  - Atau: jika pakai **modul 3-pin**, resistor sudah built-in → skip ini

---

### **Step 2: Rangkai 3 LED**

- [ ] LED Biru:
  - [ ] GPIO15 → Resistor 220Ω → LED Anode (kaki panjang)
  - [ ] LED Cathode (kaki pendek) → GND
- [ ] LED Hijau:
  - [ ] GPIO16 → Resistor 220Ω → LED Anode
  - [ ] LED Cathode → GND
- [ ] LED Merah:
  - [ ] GPIO17 → Resistor 220Ω → LED Anode
  - [ ] LED Cathode → GND

---

### **Step 3: Safety Check**

- [ ] Polaritas LED benar? (panjang = anode ke resistor)
- [ ] Tidak ada short circuit (VCC ke GND langsung)?
- [ ] Pull-up resistor terpasang untuk DHT22?
- [ ] Semua koneksi kencang (tidak ada kabel lepas)?
- [ ] Foto/cek wiring persis seperti diagram di materi

---

## 📟 BAGIAN 3: Praktikum 1 — Baca Suhu & Kelembaban Dasar

### **Step 1: Upload Code Praktikum 1**

- [ ] Buka Arduino IDE
- [ ] Copy code **Praktikum 5.1** dari materi
- [ ] Paste ke Arduino IDE
- [ ] Pilih Board: **ESP32 Dev Module**
- [ ] Pilih Port: COM yang benar
- [ ] Klik **Upload** ▶️

---

### **Step 2: Verify Output**

- [ ] Buka **Serial Monitor** (115200 baud)
- [ ] Splash screen tampil: "Praktikum 5.1: Baca DHT22"
- [ ] Data suhu tampil (contoh: `Suhu: 28.5 °C`)
- [ ] Data kelembaban tampil (contoh: `Kelembaban: 65.2 %`)
- [ ] Data update setiap 2 detik
- [ ] Nilai **masuk akal** (suhu ruangan biasanya 24-32°C)

---

### **Pertanyaan Pemahaman**

- [ ] **Q**: Apa perbedaan sensor analog (LM35) dan sensor digital (DHT22)?  
       Jawab: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

- [ ] **Q**: Mengapa perlu `delay(2000)` dan bukan `delay(500)` untuk DHT22?  
       Jawab: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

---

## 📟 BAGIAN 4: Praktikum 2 — Error Handling + Output Terformat

### **Step 1: Upload Code Praktikum 2**

- [ ] Copy code **Praktikum 5.2** dari materi
- [ ] Upload ke ESP32

---

### **Step 2: Test Normal Operation**

- [ ] Buka Serial Monitor (115200)
- [ ] Verify splash screen dengan box border (╔══╗)
- [ ] Data tampil terformat dalam box (┌───┐)
- [ ] Heat Index tampil
- [ ] Counter "#1", "#2", "#3" bertambah tiap pembacaan

---

### **Step 3: Test Error Handling**

- [ ] **Cabut** kabel DATA (GPIO4) dari DHT22
- [ ] Verify: pesan error "❌ Pembacaan GAGAL!" muncul
- [ ] Verify: counter fail bertambah
- [ ] Verify: pesan suggestion "Cek wiring..." muncul
- [ ] **Pasang kembali** kabel DATA
- [ ] Verify: pembacaan kembali normal (counter fail reset)

---

### **Pertanyaan Pemahaman**

- [ ] **Q**: Apa fungsi `isnan()` dan mengapa penting?  
       Jawab: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

- [ ] **Q**: Apa itu Heat Index dan bagaimana cara menghitungnya?  
       Jawab: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

---

## 🔆 BAGIAN 5: Praktikum 3 — LED Indikator Suhu

### **Step 1: Upload Code Praktikum 3**

- [ ] Copy code **Praktikum 5.3** dari materi
- [ ] Upload ke ESP32

---

### **Step 2: Verify LED Test di Startup**

- [ ] Saat ESP32 boot, LED biru menyala sebentar → mati
- [ ] Lalu LED hijau menyala sebentar → mati
- [ ] Lalu LED merah menyala sebentar → mati
- [ ] Pesan "✅ LED test selesai!" muncul di Serial Monitor

---

### **Step 3: Verify LED Indikator**

| Kondisi | Cara Test | LED yang Menyala | ✓ |
|---------|-----------|------------------|---|
| Normal (25-30°C) | Suhu ruangan biasa | 🟢 Hijau | [ ] |
| Panas (>30°C) | Genggam sensor dengan tangan | 🔴 Merah | [ ] |
| Dingin (<25°C) | Dekatkan es batu ke sensor | 🔵 Biru | [ ] |
| Error | Cabut kabel DATA | Semua blink | [ ] |

---

### **Step 4: Troubleshooting (jika ada masalah)**

**Problem: Suhu selalu NaN**

- [ ] Cek kabel DATA terhubung ke GPIO4
- [ ] Cek pull-up 10kΩ terpasang (DATA ke 3V3)
- [ ] Cek DHT22 VCC → 3V3 dan GND → GND
- [ ] Coba cabut-pasang USB ESP32

**Problem: LED tidak menyala**

- [ ] Cek polaritas LED (panjang + ke resistor)
- [ ] Cek resistor terpasang (220Ω)
- [ ] Test manual: upload kode `digitalWrite(LED_BLUE, HIGH)` di `setup()`

**Problem: Suhu tidak berubah saat dipegang**

- [ ] Pegang lebih lama (10-15 detik) — sensor perlu waktu response
- [ ] Pastikan pegang bagian sensor (kisi-kisi), bukan casing
- [ ] Cek apakah sensor terhalang casing modul

---

## 🏆 BAGIAN 6: Project Akhir — P05_DHT22_LED_Indicator

### **Step 1: Upload Code Final**

- [ ] Copy code dari `code/P05_DHT22_LED_Indicator.ino`
- [ ] Upload ke ESP32

---

### **Step 2: Verify Semua Fitur**

- [ ] Splash screen dengan info pin dan threshold
- [ ] LED test saat startup (3 LED berurutan)
- [ ] Pembacaan suhu & kelembaban terformat
- [ ] Heat Index ditampilkan
- [ ] Status label (DINGIN/NORMAL/PANAS) sesuai suhu
- [ ] LED yang menyala sesuai status
- [ ] Error handling saat kabel DATA dicabut
- [ ] LED blink error saat sensor disconnected
- [ ] Recovery saat kabel DATA dipasang kembali

---

## 📸 BAGIAN 7: Dokumentasi

### **Foto/Screenshot Requirements**

- [ ] **Foto hardware**: Breadboard dengan DHT22 + 3 LED + ESP32 terhubung
- [ ] **Screenshot Serial Monitor**: Menampilkan min 3 pembacaan berhasil
- [ ] **Screenshot error**: Pesan error saat kabel DATA dicabut
- [ ] Semua foto/screenshot jelas, tidak blur
- [ ] Save: `P05_DHT22_[NIM]_[Nama].png`

---

### **Video Demo (WAJIB!)**

- [ ] Screen recording + kamera hardware (20-60 detik)
- [ ] Tunjukkan:
  - [ ] ESP32 boot → LED test berurutan
  - [ ] Serial Monitor menampilkan suhu & kelembaban
  - [ ] LED hijau menyala (suhu normal)
  - [ ] Genggam sensor → LED berubah ke merah (panas)
  - [ ] (Opsional) Dekatkan es → LED berubah ke biru (dingin)
- [ ] Upload ke Google Drive / YouTube (unlisted)
- [ ] Copy link

---

## 🌟 BAGIAN 8: Challenge (Opsional — Bonus!)

### **Challenge: DHT22 Statistics Monitor**

- [ ] Upload code `P05_Challenge_DHT22_Stats.ino`
- [ ] Test menu interaktif (pilihan 1-6)
- [ ] Baca sensor (pilihan 1) → data tersimpan di statistik
- [ ] Tampilkan statistik (pilihan 2) → min/max/avg tampil
- [ ] Reset statistik (pilihan 3) → data terhapus
- [ ] Set alarm (pilihan 4) → masukkan threshold baru
- [ ] Test alarm: atur alarm HIGH=28°C → genggam sensor → alarm muncul
- [ ] Screenshot statistik output

---

## 📤 BAGIAN 9: Submission

### **Persiapan Submission**

- [ ] Buka `P05_Template_Submission.md`
- [ ] Isi informasi mahasiswa
- [ ] Paste foto hardware
- [ ] Paste screenshot Serial Monitor
- [ ] Paste link video demo
- [ ] Paste code lengkap
- [ ] Checklist wiring completed
- [ ] Checklist functionality completed
- [ ] Jawab 4 pertanyaan
- [ ] (Opsional) Include challenge

### **Quality Check**

- [ ] Foto hardware jelas (DHT22, LED, wiring visible)
- [ ] Screenshot Serial Monitor jelas (suhu, kelembaban, status)
- [ ] Link video valid (test di incognito!)
- [ ] Code lengkap (tidak terpotong)
- [ ] Wiring checklist semua ✓
- [ ] Semua pertanyaan dijawab
- [ ] File name: `P05_[NIM]_[Nama].pdf/md`

### **Submit!**

- [ ] Upload ke platform (e-learning/GClassroom)
- [ ] Verify file ter-upload
- [ ] Submit **BEFORE DEADLINE**!

**DEADLINE**: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

---

## 📊 Self-Assessment

| Kriteria | Score (1-10) | Notes |
|---|---|---|
| Pemahaman sensor digital (DHT22) | \_\_\_\_ / 10 | Paham cara kerja? |
| Wiring hardware | \_\_\_\_ / 10 | Wiring benar pertama kali? |
| Error handling (isnan) | \_\_\_\_ / 10 | Paham NaN handling? |
| LED indikator | \_\_\_\_ / 10 | Semua LED berfungsi? |
| Ketepatan waktu | \_\_\_\_ / 10 | Submit on-time? |

**Total**: \_\_\_\_ / 50

**Reflection**: Apa yang paling menantang dari materi ini?

```
_________________________________________________________________
_________________________________________________________________
```

**Most Useful Skill**: Apa yang paling berguna untuk project ke depan?

```
_________________________________________________________________
_________________________________________________________________
```

---

## ✅ Final Check

- [ ] Semua checklist di atas ✓
- [ ] Hardware berfungsi baik
- [ ] Foto & video ready
- [ ] Submission file ready
- [ ] Deadline noted
- [ ] (Optional) Challenge completed

**Paraf**: \_\_\_\_\_\_\_\_\_ **Tanggal**: \_\_\_\_\_\_\_\_\_

---

**🎉 Selamat! Anda sudah menguasai Sensor Suhu & Kelembaban DHT22!**

**Next**: Pertemuan 6 — Sensor Jarak & Interrupt Basics 📏

---

**Checklist ini dibuat untuk**: Mata Kuliah Mikrokontroller — Prodi Informatika Unmul
