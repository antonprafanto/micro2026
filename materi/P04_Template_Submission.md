# 📝 Template Submission - Pertemuan 4

## Interactive Serial Menu (Serial Communication & Debugging)

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

## 🎯 Deliverable Pertemuan 4

### **1. Screenshot Wokwi Simulator** ✅

**Petunjuk**:

- Ambil screenshot dari Wokwi simulator yang menunjukkan:
  - **Wiring circuit**: Potensiometer + LED + Resistor terhubung dengan benar
  - **Simulation running**: LED dalam kondisi aktif
  - **Serial Monitor**: Tampilkan menu + minimal 3 interaksi perintah
  - **Code editor**: Bagian penting code visible
- Pastikan **seluruh window Wokwi visible**

**Paste screenshot di sini** atau upload sebagai file terpisah dengan nama:
`P04_SerialMenu_[NIM]_[Nama].png`

**Contoh**:

```
P04_SerialMenu_2111001_AntonPrafanto.png
```

---

### **2. Link Wokwi Project (Public)** 🔗

**Petunjuk**:

- Save project Wokwi Anda dengan nama: `P04_SerialMenu_[NIM]_[Nama]`
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
// Paste code Interactive Serial Menu Anda di sini




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

| Pilihan | Perintah  | Expected Behavior                          | ✓   |
| ------- | --------- | ------------------------------------------ | --- |
| 1       | Ketik `1` | LED ON penuh (255/255)                     | [ ] |
| 2       | Ketik `2` | LED OFF                                    | [ ] |
| 3       | Ketik `3` | LED blink 5x, setiap blink ada log serial  | [ ] |
| 4       | Ketik `4` | ADC value, voltage, dan persentase tampil  | [ ] |
| 5       | Ketik `5` | Prompt minta input brightness → LED update | [ ] |
| 6       | Ketik `6` | Uptime, LED state, free heap tampil        | [ ] |
| 0       | Ketik `0` | Menu ditampilkan ulang                     | [ ] |
| Error   | Ketik `9` | Pesan "pilihan tidak valid"                | [ ] |

---

### **6. Penjelasan Singkat** 📝

**Pertanyaan 1**: Apa itu Baud Rate, dan apa yang terjadi jika Baud Rate di ESP32 dan Serial Monitor berbeda?

**Jawaban**:

```
[Tulis jawaban Anda di sini]
(Hint: kecepatan transmisi, garbage characters)




```

---

**Pertanyaan 2**: Jelaskan perbedaan antara `Serial.print()` dan `Serial.println()`. Kapan menggunakan masing-masing?

**Jawaban**:

```
[Tulis jawaban Anda di sini]
(Hint: newline, formatting output, kegunaan)




```

---

**Pertanyaan 3**: Apa fungsi `Serial.available()` sebelum memanggil `Serial.readStringUntil()`? Kenapa penting?

**Jawaban**:

```
[Tulis jawaban Anda di sini]
(Hint: buffer, non-blocking, mengapa perlu cek dulu)




```

---

**Pertanyaan 4**: Jelaskan strategi debugging yang paling berguna dari pertemuan ini. Berikan contoh penggunaannya!

**Jawaban**:

```
[Tulis jawaban Anda di sini]
(Hint: print variable, checkpoint, timestamp)




```

---

### **7. Video Demo** 📹 (Highly Recommended!)

**Petunjuk**:

- Screen recording Wokwi simulation (20-45 detik)
- Tunjukkan: Ketik minimal 4 pilihan menu yang berbeda + LED bereaksi
- Upload ke Google Drive / YouTube (unlisted)
- Paste link di bawah

**Link Video Demo**:

```
[Paste link video Anda di sini]
```

**Note**: Video **SANGAT DIREKOMENDASIKAN** karena interaksi serial menu lebih jelas terlihat di video!

---

### **8. Challenge (Opsional - Bonus Poin!)** 🌟

Jika Anda sudah mengerjakan challenge:

**Challenge yang dikerjakan**:

- [ ] Auto-Read Sensor (pilihan 7, auto update tiap 2 detik dengan stop command)
- [ ] Password Protection (password sebelum masuk menu)
- [ ] Brightness Level Display (ASCII bar visualizer)
- [ ] Lainnya (jelaskan): \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

**Link Wokwi Challenge** (jika ada):

```
[Paste link Wokwi challenge Anda]
```

**Screenshot Challenge**:
Paste screenshot atau upload sebagai file terpisah.

**Penjelasan Modifikasi**:

```
[Jelaskan apa yang Anda modifikasi/tambahkan]
(Contoh: Menambahkan opsi 7 untuk auto-read sensor setiap 2 detik.
Ketik 's' + Enter untuk stop. Flow: cek Serial.available() dalam
loop auto-read untuk deteksi perintah stop.)




```

---

## ✅ Checklist Sebelum Submit

Pastikan semua item di bawah sudah ✅:

- [ ] Nama, NIM, Kelas sudah diisi
- [ ] Screenshot Wokwi disertakan (jelas, tidak blur)
- [ ] Link Wokwi project sudah di-test (bisa dibuka)
- [ ] Code sudah di-paste dengan lengkap
- [ ] Wiring checklist sudah diverifikasi
- [ ] Functionality test semua pilihan menu (0-6) completed
- [ ] 4 pertanyaan sudah dijawab
- [ ] (Highly Recommended) Video demo disertakan
- [ ] (Opsional) Challenge sudah dikerjakan
- [ ] File submission sudah di-rename sesuai format

---

## 📤 Format Nama File Submission

Jika submit sebagai **file terpisah** (bukan via form online):

**Format**: `P04_[NIM]_[NamaLengkap].pdf` atau `.md`

**Contoh**:

```
P04_2111001_AntonPrafanto.pdf
P04_2111001_AntonPrafanto.md
```

**Jika ada file terpisah**:

```
P04_SerialMenu_2111001_AntonPrafanto.png   (screenshot)
P04_Challenge_2111001_AntonPrafanto.png    (challenge screenshot)
```

---

## 📅 Deadline

**Batas Waktu Submit**: [Diisi dosen - biasanya 1 minggu setelah pertemuan]

**Platform Submission**:

- [ ] E-learning (LMS)
- [ ] Google Classroom
- [ ] Email ke: [email dosen]
- [ ] Lainnya: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

---

## 🎓 Penilaian

Deliverable ini akan dinilai berdasarkan:

| Kriteria                                         | Bobot |
| ------------------------------------------------ | ----- |
| Wiring benar (Pot + LED + Resistor)              | 20%   |
| Code lengkap dan simulation jalan                | 25%   |
| Functionality (semua pilihan menu 0-6 berfungsi) | 30%   |
| Screenshot & link Wokwi valid                    | 10%   |
| Ketepatan waktu submit                           | 5%    |
| Penjelasan (4 pertanyaan)                        | 10%   |
| **Bonus**: Video demo                            | +10%  |
| **Bonus**: Challenge (per challenge)             | +10%  |

**Total maksimal**: 140% (jika mengerjakan semua bonus!)

---

## ❓ FAQ

**Q: Serial Monitor tidak menampilkan output sama sekali. Kenapa?**  
A:

1. Pastikan baud rate di Serial Monitor = 115200 (sama persis dengan `Serial.begin(115200)`)
2. Klik ulang icon Serial Monitor di Wokwi
3. Reset simulation (tekan Stop → lalu Play lagi)

**Q: Saat ketik perintah, menu tidak bereaksi. Kenapa?**  
A:

1. Pastikan Line Ending = **"NL & CR"** di Serial Monitor Wokwi
2. Pastikan **baud rate** 115200
3. Try ketik angka (misalnya `1`) lalu tekan Enter

**Q: Blink function berjalan tapi program macet (tidak mau ketik lagi). Kenapa?**  
A: Ini normal – fungsi `blinkLED()` menggunakan `delay()` yang blocking. Tunggu selesai 5 blink (~2 detik), lalu menu akan muncul kembali.

**Q: Pilihan 5 (Set Brightness) tidak merespons setelah masukkan angka. Kenapa?**  
A:

1. Pastikan Line Ending = "NL & CR"
2. Jangan masukkan karakter selain angka (0-255)
3. Jika tetap bermasalah, reset simulation dan coba lagi

**Q: Serial.printf() tidak dikenali compiler?**  
A: `Serial.printf()` adalah fitur khusus ESP32 (tidak ada di Arduino Uno). Pastikan kamu menggunakan board ESP32 di Arduino IDE / Wokwi, bukan Arduino Uno.

---

## 🆘 Troubleshooting

### **Problem: Output adalah garbage characters**

- [ ] Cek baud rate Serial Monitor – harus 115200
- [ ] Ganti baud rate, lalu reset simulation
- [ ] Pastikan `Serial.begin(115200)` di `setup()`

### **Problem: LED tidak menyala saat pilih menu 1**

- [ ] Check wiring LED: GPIO15 → Resistor → Anode → Cathode → GND
- [ ] Polaritas LED benar? (panjang=anode ke resistor)
- [ ] Resistor terpasang? Jangan skip!
- [ ] Manual test: pindah ke kode simple `ledcWrite(LED_PIN, 255)` di `setup()`

### **Problem: Pilihan 4 (Read Sensor) selalu 0**

- [ ] Check wiring pot: VCC→3V3, SIG→GPIO34, GND→GND
- [ ] Coba drag knob pot – apakah nilai berubah?
- [ ] Jika tidak berubah → wiring pot salah

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
