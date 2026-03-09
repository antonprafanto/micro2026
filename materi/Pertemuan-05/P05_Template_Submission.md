# 📝 Template Submission - Pertemuan 5

## Sensor Suhu & Kelembaban DHT22 + LED Indikator

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

## 🎯 Deliverable Pertemuan 5

### **1. Foto Hardware** 📷

**Petunjuk**:

- Ambil foto hardware setup di breadboard yang menunjukkan:
  - **ESP32** terhubung ke breadboard
  - **DHT22 sensor** terpasang dengan benar
  - **3 LED** (biru, hijau, merah) + resistor 220Ω
  - **Pull-up resistor** 10kΩ (jika bukan modul 3-pin)
  - **Wiring** terlihat jelas
- Foto dari sudut yang jelas menunjukkan semua koneksi

**Paste foto di sini** atau upload sebagai file terpisah dengan nama:
`P05_Hardware_[NIM]_[Nama].jpg`

**Contoh**:

```
P05_Hardware_2111001_AntonPrafanto.jpg
```

---

### **2. Screenshot Serial Monitor** 🖥️

**Petunjuk**:

- Buka Serial Monitor (115200 baud)
- Tunggu minimal 3 pembacaan berhasil
- Screenshot yang menunjukkan:
  - **Splash screen** di startup
  - **Data suhu & kelembaban** (min 3 pembacaan)
  - **Status label** (DINGIN/NORMAL/PANAS)
  - **LED test** output

**Paste screenshot di sini** atau upload sebagai file terpisah:
`P05_SerialMonitor_[NIM]_[Nama].png`

---

### **3. Video Demo** 📹 (WAJIB!)

**Petunjuk**:

- Rekam video (20-60 detik) yang menunjukkan:
  - ESP32 boot → LED test berurutan (biru → hijau → merah)
  - Serial Monitor menampilkan suhu & kelembaban real-time
  - LED hijau menyala saat suhu normal
  - Genggam sensor → LED berubah ke merah (panas)
  - (Opsional) Dekatkan es → LED berubah ke biru (dingin)
- Upload ke Google Drive / YouTube (unlisted)

**Link Video Demo**:

```
[Paste link video Anda di sini]
```

**Note**: Video **WAJIB** karena sensor hardware real-time lebih jelas di video!

---

### **4. Code Program** 💻

**Petunjuk**:

- Copy seluruh code dari Arduino IDE
- Paste di bawah dengan format code block

**Code**:

```cpp
// Paste code P05_DHT22_LED_Indicator Anda di sini




```

---

### **5. Verifikasi Wiring** 🔌

**Checklist Wiring** (centang ✓):

**DHT22:**

- [ ] VCC/Pin 1 terhubung ke ESP32 3V3
- [ ] DATA/Pin 2 terhubung ke ESP32 GPIO4
- [ ] GND/Pin 4 terhubung ke ESP32 GND
- [ ] Pull-up 10kΩ terpasang antara DATA dan 3V3 (atau modul built-in)

**LED Biru:**

- [ ] ESP32 GPIO15 → Resistor 220Ω → LED Anode (kaki panjang)
- [ ] LED Cathode (kaki pendek) → GND

**LED Hijau:**

- [ ] ESP32 GPIO16 → Resistor 220Ω → LED Anode
- [ ] LED Cathode → GND

**LED Merah:**

- [ ] ESP32 GPIO17 → Resistor 220Ω → LED Anode
- [ ] LED Cathode → GND

---

### **6. Verifikasi Functionality** ✅

**Test Checklist** (centang ✓ jika berfungsi):

| Fitur | Expected Behavior | ✓ |
|---|---|---|
| Splash screen | Info pin, threshold, dan baud rate tampil saat boot | [ ] |
| LED test | 3 LED menyala berurutan (biru → hijau → merah) saat startup | [ ] |
| Baca suhu | Suhu tampil di serial (contoh: 28.5°C) | [ ] |
| Baca kelembaban | Kelembaban tampil di serial (contoh: 65.2%) | [ ] |
| Heat Index | Heat index dihitung dan ditampilkan | [ ] |
| LED Hijau | Menyala saat suhu 25-30°C (normal) | [ ] |
| LED Merah | Menyala saat suhu >30°C (genggam sensor) | [ ] |
| LED Biru | Menyala saat suhu <25°C (dekatkan es) | [ ] |
| Error handling | Pesan error muncul saat kabel DATA dicabut | [ ] |
| LED error | Semua LED blink saat sensor disconnected | [ ] |
| Recovery | Pembacaan normal kembali saat kabel DATA dipasang | [ ] |

---

### **7. Penjelasan Singkat** 📝

**Pertanyaan 1**: Apa perbedaan sensor analog (seperti LM35) dan sensor digital (seperti DHT22)? Sebutkan minimal 3 perbedaan!

**Jawaban**:

```
[Tulis jawaban Anda di sini]
(Hint: output signal, cara membaca, akurasi, noise)




```

---

**Pertanyaan 2**: Mengapa perlu menggunakan `isnan()` sebelum memproses data dari DHT22? Apa yang terjadi jika tidak mengecek?

**Jawaban**:

```
[Tulis jawaban Anda di sini]
(Hint: NaN, sensor gagal, program crash, data salah)




```

---

**Pertanyaan 3**: Jelaskan fungsi pull-up resistor 10kΩ pada pin DATA DHT22. Apa yang terjadi tanpa resistor ini?

**Jawaban**:

```
[Tulis jawaban Anda di sini]
(Hint: open-drain, floating pin, komunikasi gagal)




```

---

**Pertanyaan 4**: DHT22 membutuhkan minimal 2 detik antar pembacaan. Jelaskan mengapa, dan apa yang terjadi jika kita membaca sensor setiap 500ms?

**Jawaban**:

```
[Tulis jawaban Anda di sini]
(Hint: sampling period, data lama, error, sensor response)




```

---

### **8. Challenge (Opsional — Bonus Poin!)** 🌟

Jika Anda sudah mengerjakan challenge:

**Challenge yang dikerjakan**:

- [ ] DHT22 Statistics Monitor (rolling window min/max/avg + serial menu)
- [ ] Custom alarm threshold setting
- [ ] Auto-read toggle ON/OFF
- [ ] Lainnya (jelaskan): \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

**Screenshot Challenge**:
Paste screenshot statistik output atau upload sebagai file terpisah.

**Penjelasan Modifikasi**:

```
[Jelaskan apa yang Anda modifikasi/tambahkan]
(Contoh: Menambahkan fitur statistik min/max/avg dari 10 pembacaan
terakhir. Menu interaktif dengan 6 pilihan. Alarm threshold
bisa diubah via Serial input.)




```

---

## ✅ Checklist Sebelum Submit

Pastikan semua item di bawah sudah ✅:

- [ ] Nama, NIM, Kelas sudah diisi
- [ ] Foto hardware disertakan (DHT22, LED, wiring jelas)
- [ ] Screenshot Serial Monitor disertakan (min 3 pembacaan)
- [ ] Link video demo valid (test di incognito!)
- [ ] Code sudah di-paste dengan lengkap
- [ ] Wiring checklist sudah diverifikasi
- [ ] Functionality test semua fitur completed
- [ ] 4 pertanyaan sudah dijawab
- [ ] (Opsional) Challenge sudah dikerjakan
- [ ] File submission sudah di-rename sesuai format

---

## 📤 Format Nama File Submission

Jika submit sebagai **file terpisah** (bukan via form online):

**Format**: `P05_[NIM]_[NamaLengkap].pdf` atau `.md`

**Contoh**:

```
P05_2111001_AntonPrafanto.pdf
P05_2111001_AntonPrafanto.md
```

**Jika ada file terpisah**:

```
P05_Hardware_2111001_AntonPrafanto.jpg         (foto hardware)
P05_SerialMonitor_2111001_AntonPrafanto.png    (screenshot serial)
P05_Challenge_2111001_AntonPrafanto.png        (challenge screenshot)
```

---

## 📅 Deadline

**Batas Waktu Submit**: [Diisi dosen — biasanya 1 minggu setelah pertemuan]

**Platform Submission**:

- [ ] E-learning (LMS)
- [ ] Google Classroom
- [ ] Email ke: [email dosen]
- [ ] Lainnya: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

---

## 🎓 Penilaian

Deliverable ini akan dinilai berdasarkan:

| Kriteria | Bobot |
|---|---|
| Wiring benar (DHT22 + 3 LED + resistor) | 15% |
| Code lengkap dan berfungsi | 25% |
| Functionality (semua fitur: suhu, LED, error handling) | 30% |
| Foto hardware + screenshot Serial Monitor | 10% |
| Video demo | 10% |
| Penjelasan (4 pertanyaan) | 10% |
| **Bonus**: Challenge (statistics monitor) | +15% |

**Total maksimal**: 115% (jika mengerjakan bonus!)

---

## ❓ FAQ

**Q: Serial Monitor tidak menampilkan data suhu — output selalu `nan`?**  
A:

1. Pastikan DHT22 VCC terhubung ke **3V3** (bukan 5V)
2. Pastikan pull-up resistor 10kΩ terpasang antara DATA dan 3V3
3. Pastikan DATA terhubung ke **GPIO4** (sesuai `#define DHT_PIN 4`)
4. Cabut USB → cek wiring → pasang kembali

**Q: LED tidak menyala sama sekali?**  
A:

1. Cek polaritas LED — kaki panjang (anode) harus ke resistor
2. Cek resistor terpasang (220Ω)
3. Test manual: upload code `digitalWrite(15, HIGH)` di `setup()` → LED nyala?
4. Cek pin: LED Biru=GPIO15, Hijau=GPIO16, Merah=GPIO17

**Q: Suhu terbaca tapi tidak berubah saat tangan memegang sensor?**  
A:

1. Pegang **bagian kisi-kisi sensor** (bukan casing plastik/modul PCB)
2. Tunggu 10-15 detik — DHT22 perlu waktu response
3. Tangan manusia ≈ 35-37°C → seharusnya cukup untuk trigger LED merah (>30°C)

**Q: Error "DHT.h: No such file or directory"?**  
A: Library belum terinstall! Instal via Library Manager:
Sketch → Include Library → Manage Libraries → cari "DHT sensor library" by Adafruit → Install All

**Q: Upload gagal — "Failed to connect to ESP32"?**  
A:

1. Pastikan port COM benar (Tools → Port)
2. Tekan tombol **BOOT** di ESP32 saat upload
3. Coba kabel USB lain (beberapa kabel hanya charge, tidak data)
4. Install driver CH340 jika belum

---

## 🆘 Troubleshooting

### **Problem: Suhu tidak stabil (loncat-loncat)**

- [ ] Pastikan kabel DATA tidak terlalu panjang (max 10 meter)
- [ ] Pastikan pull-up resistor terpasang
- [ ] Cek apakah ada sumber noise di dekat sensor

### **Problem: DHT22 panas saat disentuh**

- [ ] Cek apakah VCC dan GND tidak tertukar!
- [ ] Cek apakah ada short circuit
- [ ] **CABUT USB SEGERA** jika sensor panas!

### **Problem: Kelembaban selalu 99.9%**

- [ ] Sensor mungkin terlalu dekat dengan sumber uap air
- [ ] Cek apakah sensor basah/lembab → keringkan
- [ ] Cek wiring — kemungkinan data terganggu

---

## 📞 Kontak

Jika ada pertanyaan atau kendala teknis:

- **Dosen**: [Nama & email]
- **Asisten Lab**: [Nama & email]
- **Grup WA Kelas**: [Link]

---

**Good luck!** 🚀

---

**Template ini dibuat untuk**: Mata Kuliah Mikrokontroller — Prodi Informatika Unmul
