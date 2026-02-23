# 📝 Template Submission - Pertemuan 3

## Interactive LED Dimmer (Analog I/O & PWM)

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

## 🎯 Deliverable Pertemuan 3

### **1. Screenshot Wokwi Simulator** ✅

**Petunjuk**:

- Ambil screenshot dari Wokwi simulator yang menunjukkan:
  - **Wiring circuit**: Potensiometer + LED dengan resistor (circuit jelas)
  - **Simulation running**: LED menyala dengan brightness tertentu (tidak OFF, tidak MAX)
  - **Potensiometer knob**: Di posisi antara 25%-75% (untuk tunjukkan variasi)
  - **Code editor**: Full code visible
  - **Serial monitor**: Output pot value & brightness percentage
- Pastikan **seluruh window Wokwi visible**

**Paste screenshot di sini** atau upload sebagai file terpisah dengan nama:
`P03_LEDDimmer_[NIM]_[Nama].png`

**Contoh**:

```
P03_LEDDimmer_2111001_AntonPrafanto.png
```

---

### **2. Link Wokwi Project (Public)** 🔗

**Petunjuk**:

- Save project Wokwi Anda dengan nama: `P03_LEDDimmer_[NIM]_[Nama]`
- Klik tombol "Share" di Wokwi
- Copy link public project
- **Test link** di browser incognito (pastikan bisa dibuka orang lain!)

**Link Wokwi Project**:

```
[Paste link Wokwi Anda di sini]
Contoh: https://wokwi.com/projects/123456789
```

---

### **3. Code Program** 💻

**Petunjuk**:

- Copy seluruh code dari Wokwi editor
- Paste di bawah dengan format code block

**Code**:

```cpp
// Paste code Interactive LED Dimmer Anda di sini




```

---

### **4. Verifikasi Wiring** 🔌

**Checklist Wiring** (centang ✓):

**Potensiometer:**

- [ ] VCC/Pin 1 terhubung ke ESP32 3V3
- [ ] SIG/Pin 2 (wiper) terhubung ke ESP32 GPIO34 (ADC pin)
- [ ] GND/Pin 3 terhubung ke ESP32 GND

**LED:**

- [ ] ESP32 GPIO15 → Resistor 220Ω
- [ ] Resistor → LED Anode (kaki panjang/+)
- [ ] LED Cathode (kaki pendek/-) → GND
- [ ] Polaritas LED benar

---

### **5. Verifikasi Functionality** ✅

**Test Checklist** (centang ✓ jika berfungsi):

| Test                   | Expected Behavior                            | ✓   |
| ---------------------- | -------------------------------------------- | --- |
| Pot 0% (full left)     | LED OFF atau sangat redup                    | [ ] |
| Pot 25%                | LED redup (25% brightness)                   | [ ] |
| Pot 50% (middle)       | LED setengah terang                          | [ ] |
| Pot 75%                | LED terang (75% brightness)                  | [ ] |
| Pot 100% (full right)  | LED maksimal brightness                      | [ ] |
| **Real-time response** | LED brightness berubah smooth saat putar pot | [ ] |
| **Serial Monitor**     | Menampilkan pot value & brightness           | [ ] |

---

### **6. Penjelasan Singkat** 📝

**Pertanyaan 1**: Apa perbedaan antara `analogRead()` dan `digitalRead()`?

**Jawaban**:

```
[Tulis jawaban Anda di sini]
(Hint: range nilai, resolusi, use case)



```

---

**Pertanyaan 2**: Apa fungsi PWM dalam project ini? Mengapa tidak bisa pakai `digitalWrite()` saja?

**Jawaban**:

```
[Tulis jawaban Anda di sini]
(Hint: duty cycle, brightness control)



```

---

**Pertanyaan 3**: Jelaskan apa yang dilakukan oleh fungsi `map()` dalam code!

**Jawaban**:

```
[Tulis jawaban Anda di sini]
(Hint: scaling dari range ke range, contoh: ADC 0-4095 ke PWM 0-255)



```

---

**Pertanyaan 4**: Apa perbedaan antara duty cycle 25% vs 75%?

**Jawaban**:

```
[Tulis jawaban Anda di sini]
(Hint: waktu ON vs OFF, brightness LED)



```

---

### **7. Video Demo** 📹 (Highly Recommended!)

**Petunjuk**:

- Screen recording Wokwi simulation (15-30 detik)
- Tunjukkan: **Putar potensiometer dari 0% → 100% (smooth)**
- LED brightness harus berubah secara real-time mengikuti pot
- Upload ke Google Drive / YouTube (unlisted)
- Paste link di bawah

**Link Video Demo**:

```
[Paste link video Anda di sini]
```

**Note**: Video **SANGAT DIREKOMENDASIKAN** untuk P03 karena menunjukkan real-time interaction!

---

### **8. Challenge (Opsional - Bonus Poin!)** 🌟

Jika Anda sudah mengerjakan challenge:

**Challenge yang dikerjakan**:

- [ ] Breathing LED dengan Variable Speed (pot kontrol speed fade)
- [ ] Dual LED Inverse Control (2 LED, saat 1 terang, 1 redup)
- [ ] RGB LED Color Mixer (3 pot untuk R, G, B)
- [ ] LED dengan Threshold (ON hanya jika pot > 50%)
- [ ] Lainnya (jelaskan): **\*\*\*\***\_**\*\*\*\***

**Link Wokwi Challenge** (jika ada):

```
[Paste link Wokwi challenge Anda]
```

**Screenshot Challenge**:
Paste screenshot atau upload sebagai file terpisah.

**Penjelasan Modifikasi**:

```
[Jelaskan apa yang Anda modifikasi/tambahkan]
(Contoh: Tambah pot untuk kontrol speed breathing, range 100ms-1000ms per step)




```

---

## ✅ Checklist Sebelum Submit

Pastikan semua item di bawah sudah ✅:

- [ ] Nama, NIM, Kelas sudah diisi
- [ ] Screenshot Wokwi disertakan (jelas, tidak blur)
- [ ] Link Wokwi project sudah di-test (bisa dibuka)
- [ ] Code sudah di-paste dengan lengkap
- [ ] Wiring checklist sudah diverifikasi
- [ ] Functionality test checklist completed
- [ ] 4 pertanyaan sudah dijawab
- [ ] (Highly Recommended) Video demo disertakan
- [ ] (Opsional) Challenge sudah dikerjakan
- [ ] File submission sudah di-rename sesuai format

---

## 📤 Format Nama File Submission

Jika submit sebagai **file terpisah** (bukan via form online):

**Format**: `P03_[NIM]_[NamaLengkap].pdf` atau `.md`

**Contoh**:

```
P03_2111001_AntonPrafanto.pdf
P03_2111001_AntonPrafanto.md
```

**Jika ada file terpisah**:

```
P03_LEDDimmer_2111001_AntonPrafanto.png (screenshot)
P03_Challenge_2111001_AntonPrafanto.png (challenge screenshot)
```

---

## 📅 Deadline

**Batas Waktu Submit**: [Diisi dosen - biasanya 1 minggu setelah pertemuan]

**Platform Submission**:

- [ ] E-learning (LMS)
- [ ] Google Classroom
- [ ] Email ke: [email dosen]
- [ ] Lainnya: **\*\*\*\***\_**\*\*\*\***

---

## 🎓 Penilaian

Deliverable ini akan dinilai berdasarkan:

| Kriteria                                            | Bobot |
| --------------------------------------------------- | ----- |
| Wiring benar (Pot + LED + Resistor)                 | 25%   |
| Code lengkap dan simulation jalan                   | 25%   |
| Functionality (LED brightness mengikuti pot smooth) | 30%   |
| Screenshot & link Wokwi valid                       | 10%   |
| Ketepatan waktu submit                              | 5%    |
| Penjelasan (4 pertanyaan)                           | 5%    |
| **Bonus**: Video demo                               | +10%  |
| **Bonus**: Challenge                                | +20%  |

**Total maksimal**: 130% (jika mengerjakan semua bonus!)

---

## ❓ FAQ

**Q: ADC saya baca nilai random/tidak stabil. Kenapa?**  
A:

1. Check wiring pot: VCC ke 3V3, SIG ke GPIO34, GND ke GND
2. Jangan pakai GPIO yang conflict dengan WiFi (hindari ADC2)
3. Tambah small delay (10-50ms) sebelum `analogRead()`
4. Jika di Wokwi, reset simulation

**Q: LED brightness tidak smooth, berkedip-kedip. Kenapa?**  
A:

1. PWM frequency terlalu rendah → pastikan 5000 Hz
2. `delay()` terlalu besar → kurangi jadi 50ms atau less
3. Check `ledcAttach()` sudah dipanggil di `setup()`

**Q: Pot sudah full right, tapi LED tidak maksimal terang. Kenapa?**  
A:

1. Check `map()` scaling: pastikan max value 255 (untuk 8-bit PWM)
2. Check resistor LED tidak terlalu besar (pakai 220Ω, bukan 10kΩ!)
3. Print brightness value di serial monitor untuk debug

**Q: Serial Monitor tidak menampilkan output. Kenapa?**  
A:

1. Baud rate di Serial Monitor harus 115200 (sesuai `Serial.begin(115200)`)
2. Click icon Serial Monitor di Wokwi (bawah simulation)
3. Check `Serial.println()` ada di code

**Q: Boleh pakai GPIO lain untuk pot atau LED?**  
A:

- **Pot**: Boleh, tapi HARUS ADC pin (GPIO32-39 recommended, ADC1!)
- **LED**: Boleh GPIO mana saja (kecuali GPIO6-11)
- Jika ganti, update di code!

**Q: Video demo wajib?**  
A: Tidak wajib, tapi **HIGHLY RECOMMENDED** (+10% bonus!). Video tunjukkan real-time interaction yang susah diverify dari screenshot saja.

---

## 🆘 Troubleshooting

### **Problem: Pot tidak berfungsi (value tetap 0 atau 4095)**

- [ ] Check wiring: VCC, SIG, GND correct?
- [ ] Coba GPIO lain (32, 33, 35)
- [ ] Reset simulation Wokwi
- [ ] Print pot value di serial monitor untuk debug

### **Problem: LED tidak menyala sama sekali**

- [ ] Check wiring LED: GPIO → Resistor → Anode → Cathode → GND
- [ ] Polaritas LED benar? (panjang=anode, pendek=cathode)
- [ ] Resistor terpasang? (jangan skip!)
- [ ] `ledcAttach()` sudah dipanggil?
- [ ] Try manual test: `ledcWrite(LED_PIN, 255)` di `setup()`

### **Problem: LED nyala tapi brightness tidak berubah**

- [ ] Check pot value di serial monitor (berubah saat putar?)
- [ ] Jika pot value tidak berubah → wiring pot salah
- [ ] Jika pot value berubah → check `map()` dan `ledcWrite()`
- [ ] Print brightness value sebelum `ledcWrite()` untuk debug

---

## 📞 Kontak

Jika ada pertanyaan atau kendala teknis:

- **Dosen**: [Nama & email]
- **Asisten Lab**: [Nama & email]
- **Grup WA Kelas**: [Link]

---

**Good luck!** 🚀

---

**Template ini dibuat untuk**: Mata Kuliah Mikrokontroller - Prodi Informatika Unmul
