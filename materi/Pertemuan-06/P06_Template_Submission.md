# 📝 Template Submission - Pertemuan 6

## Sensor Jarak (HC-SR04) & Interrupt Basics

---

## 📋 Informasi Mahasiswa

| Field                 | Isi                           |
| --------------------- | ----------------------------- |
| **Nama Lengkap**      | [Tulis nama lengkap Anda]     |
| **NIM**               | [Tulis NIM Anda]              |
| **Kelas**             | [Tulis kelas Anda]            |
| **Tanggal Praktikum** | [Tanggal praktikum dilakukan] |
| **Tanggal Submit**    | [Tanggal submit deliverable]  |

---

## 🎯 Deliverable Pertemuan 6

### **1. Foto Hardware** 📷

**Petunjuk**:

- Foto menunjukkan: ESP32 + HC-SR04 + buzzer + 3 LED + **voltage divider** (resistor 1kΩ+2kΩ)
- **Voltage divider harus TERLIHAT** di foto!

**Paste foto atau upload**: `P06_Hardware_[NIM]_[Nama].jpg`

---

### **2. Screenshot Serial Monitor** 🖥️

**Petunjuk**:

- Serial Monitor (115200 baud)
- Minimal menunjukkan semua 4 zone:
  - 🟢 AMAN (>50cm)
  - 🟡 WASPADA (20-50cm)
  - 🔴 DEKAT (10-20cm)
  - 🔴 BAHAYA (<10cm)

**Paste screenshot atau upload**: `P06_Serial_[NIM]_[Nama].png`

---

### **3. Video Demo** 📹 (WAJIB!)

**Petunjuk** (20-60 detik):

- Boot → komponen test (LED + buzzer)
- Dekatkan tangan secara bertahap ke sensor
- Tunjukkan LED dan buzzer berubah per zone
- Jauhkan tangan → kembali ke aman

**Link Video**: `[Paste link di sini]`

---

### **4. Code Program** 💻

```cpp
// Paste code P06_Parking_Sensor Anda di sini




```

---

### **5. Verifikasi Wiring** 🔌

**HC-SR04:**

- [ ] VCC → ESP32 **VIN (5V)** — bukan 3V3!
- [ ] Trig → ESP32 GPIO5
- [ ] Echo → **Voltage divider (1kΩ+2kΩ)** → GPIO18
- [ ] GND → ESP32 GND

**Voltage Divider:**

- [ ] 1kΩ antara Echo dan titik junction
- [ ] 2kΩ antara titik junction dan GND
- [ ] Junction → GPIO18

**Buzzer:**

- [ ] (+) → GPIO19
- [ ] (-) → GND

**LED:**

- [ ] Hijau: GPIO15 → 220Ω → LED → GND
- [ ] Kuning: GPIO16 → 220Ω → LED → GND
- [ ] Merah: GPIO17 → 220Ω → LED → GND

---

### **6. Verifikasi Functionality** ✅

| Fitur | Expected | ✓ |
|---|---|---|
| Splash screen + info pin | Tampil saat boot | [ ] |
| Komponen test | LED + buzzer berurutan | [ ] |
| Zone AMAN (>50cm) | LED hijau, buzzer OFF | [ ] |
| Zone WASPADA (20-50cm) | LED kuning, beep lambat | [ ] |
| Zone DEKAT (10-20cm) | LED merah, beep sedang | [ ] |
| Zone BAHAYA (<10cm) | LED merah blink, beep cepat | [ ] |
| Out of range | Error message di serial | [ ] |

---

### **7. Penjelasan Singkat** 📝

**Pertanyaan 1**: Jelaskan mengapa HC-SR04 membutuhkan voltage divider pada pin Echo saat digunakan dengan ESP32!

```
[Jawaban Anda]
(Hint: 5V vs 3.6V, keamanan GPIO)



```

**Pertanyaan 2**: Apa fungsi `pulseIn(ECHO_PIN, HIGH)` dan apa yang di-return? Bagaimana nilainya diubah menjadi jarak?

```
[Jawaban Anda]
(Hint: durasi µs, rumus jarak, bagi 2)



```

**Pertanyaan 3**: Jelaskan perbedaan polling dan interrupt. Berikan contoh situasi di mana interrupt lebih baik dari polling!

```
[Jawaban Anda]
(Hint: efisiensi, responsivitas, miss event)



```

**Pertanyaan 4**: Mengapa variable yang diubah di ISR harus dideklarasikan sebagai `volatile`? Apa yang terjadi tanpa `volatile`?

```
[Jawaban Anda]
(Hint: compiler optimization, tidak dibaca ulang)



```

---

### **8. Challenge (Opsional — Bonus!)** 🌟

- [ ] PIR motion detection + interrupt
- [ ] Alarm combo: gerakan + jarak dekat
- [ ] Serial menu interaktif
- [ ] Screenshot output

**Penjelasan**:

```
[Jelaskan modifikasi/tambahan Anda]



```

---

## ✅ Checklist Sebelum Submit

- [ ] Informasi mahasiswa diisi
- [ ] Foto hardware (voltage divider terlihat!)
- [ ] Screenshot Serial Monitor (semua zone)
- [ ] Link video valid
- [ ] Code lengkap
- [ ] Wiring verified
- [ ] Functionality tested
- [ ] 4 pertanyaan dijawab
- [ ] File: `P06_[NIM]_[NamaLengkap].pdf/md`

---

## 📅 Deadline

**Batas Waktu**: [Diisi dosen]

## 🎓 Penilaian

| Kriteria | Bobot |
|---|---|
| Wiring benar (HC-SR04 + voltage divider + LED + buzzer) | 15% |
| Code dan functionality | 30% |
| Semua zone berfungsi (aman/waspada/dekat/bahaya) | 25% |
| Foto hardware + screenshot | 10% |
| Video demo | 10% |
| Penjelasan (4 pertanyaan) | 10% |
| **Bonus**: Challenge PIR + interrupt | +15% |

**Total maksimal**: 115%

---

## ❓ FAQ

**Q: Jarak selalu 0 atau error?**
A: Cek voltage divider — Echo pin HARUS melalui divider. Cek VCC ke VIN (5V), bukan 3V3.

**Q: Buzzer tidak bunyi?**
A: Cek polaritas (+/-). Test manual: `digitalWrite(19, HIGH)` di loop.

**Q: Jarak tidak akurat?**
A: Arahkan sensor ke permukaan datar. Objek kecil/bundar sulit memantulkan gelombang sonar. Hindari permukaan menyerap suara (busa, kain).

**Q: LED kecerahan lemah?**
A: Cek resistor 220Ω — terlalu besar bisa bikin redup. Cek polaritas LED.

---

**Template ini dibuat untuk**: Mata Kuliah Mikrokontroller — Prodi Informatika Unmul
