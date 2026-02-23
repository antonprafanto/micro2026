# 📝 Template Submission - Pertemuan 2

## Traffic Light Simulation

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

## 🎯 Deliverable Pertemuan 2

### **1. Screenshot Wokwi Simulator** ✅

**Petunjuk**:

- Ambil screenshot dari Wokwi simulator yang menunjukkan:
  - **Wiring circuit**: 3 LED (merah, kuning, hijau) dengan resistor
  - **Simulation running**: Salah satu LED menyala
  - **Code editor**: Full code visible
  - **Serial monitor**: Output state traffic light
- Pastikan **seluruh window Wokwi visible**

**Paste screenshot di sini** atau upload sebagai file terpisah dengan nama:
`P02_TrafficLight_[NIM]_[Nama].png`

**Contoh**:

```
P02_TrafficLight_2111001_AntonPrafanto.png
```

---

### **2. Link Wokwi Project (Public)** 🔗

**Petunjuk**:

- Save project Wokwi Anda dengan nama: `P02_TrafficLight_[NIM]_[Nama]`
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
// Paste code Traffic Light Simulation Anda di sini




```

---

### **4. Verifikasi Wiring** 🔌

**Checklist Wiring** (centang ✓):

- [ ] 3× LED terpasang (Merah, Kuning, Hijau)
- [ ] 3× Resistor 220Ω terpasang di setiap LED
- [ ] Wiring: ESP32 GPIO → Resistor → LED Anode → LED Cathode → GND
- [ ] Polaritas LED benar (panjang=anode, pendek=cathode)
- [ ] Semua ground terhubung ke ESP32 GND

---

### **5. Verifikasi Pattern** ✅

**Traffic Light Pattern** (sesuai requirement):
| State | LED ON | Durasi | ✓ |
|-------|--------|--------|---|
| RED | Merah | 5 detik | [ ] |
| YELLOW | Kuning | 2 detik | [ ] |
| GREEN | Hijau | 5 detik | [ ] |
| **Loop** | Repeat | Terus menerus | [ ] |

Centang ✓ jika pattern Anda sudah sesuai!

---

### **6. Penjelasan Singkat** 📝

**Pertanyaan 1**: Apa fungsi `pinMode()` untuk LED di program?

**Jawaban**:

```
[Tulis jawaban Anda di sini]


```

---

**Pertanyaan 2**: Mengapa setiap LED perlu resistor?

**Jawaban**:

```
[Tulis jawaban Anda di sini]


```

---

**Pertanyaan 3**: Bagaimana cara mengontrol multiple LED agar hanya 1 yang menyala di satu waktu?

**Jawaban**:

```
[Tulis jawaban Anda di sini]


```

---

### **7. Video Demo** 📹 (Opsional - Recommended!)

**Petunjuk**:

- Screen recording Wokwi simulation (10-30 detik)
- Tunjukkan **minimal 1 cycle lengkap**: Merah → Kuning → Hijau → Repeat
- Upload ke Google Drive / YouTube (unlisted)
- Paste link di bawah

**Link Video Demo**:

```
[Paste link video Anda di sini]
```

**Note**: Video sangat membantu dosen verifikasi submission Anda! Highly recommended!

---

### **8. Challenge (Opsional - Bonus Poin!)** 🌟

Jika Anda sudah mengerjakan challenge:

**Challenge yang dikerjakan**:

- [ ] Pedestrian Button (paksa RED saat button ditekan)
- [ ] Night Mode (kuning blink)
- [ ] Timing custom (jelaskan): ********\_********
- [ ] Lainnya (jelaskan): ********\_********

**Link Wokwi Challenge** (jika ada):

```
[Paste link Wokwi challenge Anda]
```

**Screenshot Challenge**:
Paste screenshot atau upload sebagai file terpisah.

**Penjelasan Modifikasi**:

```
[Jelaskan apa yang Anda modifikasi/tambahkan]




```

---

## ✅ Checklist Sebelum Submit

Pastikan semua item di bawah sudah ✅:

- [ ] Nama, NIM, Kelas sudah diisi
- [ ] Screenshot Wokwi disertakan (jelas, tidak blur)
- [ ] Link Wokwi project sudah di-test (bisa dibuka)
- [ ] Code sudah di-paste dengan lengkap
- [ ] Wiring checklist sudah diverifikasi
- [ ] Pattern checklist sudah diverifikasi
- [ ] 3 pertanyaan sudah dijawab
- [ ] (Opsional) Video demo disertakan
- [ ] (Opsional) Challenge sudah dikerjakan
- [ ] File submission sudah di-rename sesuai format

---

## 📤 Format Nama File Submission

Jika submit sebagai **file terpisah** (bukan via form online):

**Format**: `P02_[NIM]_[NamaLengkap].pdf` atau `.md`

**Contoh**:

```
P02_2111001_AntonPrafanto.pdf
P02_2111001_AntonPrafanto.md
```

**Jika ada file terpisah**:

```
P02_TrafficLight_2111001_AntonPrafanto.png (screenshot)
P02_Challenge_2111001_AntonPrafanto.png (challenge screenshot)
```

---

## 📅 Deadline

**Batas Waktu Submit**: [Diisi dosen - biasanya 1 minggu setelah pertemuan]

**Platform Submission**:

- [ ] E-learning (LMS)
- [ ] Google Classroom
- [ ] Email ke: [email dosen]
- [ ] Lainnya: ********\_********

---

## 🎓 Penilaian

Deliverable ini akan dinilai berdasarkan:

| Kriteria                                    | Bobot |
| ------------------------------------------- | ----- |
| Wiring benar (3 LED + resistor + ESP32)     | 30%   |
| Code lengkap dan simulation jalan           | 30%   |
| Traffic light pattern sesuai (timing benar) | 25%   |
| Screenshot & link Wokwi valid               | 10%   |
| Ketepatan waktu submit                      | 5%    |
| **Bonus**: Challenge                        | +15%  |
| **Bonus**: Video demo                       | +5%   |

**Total maksimal**: 120% (jika mengerjakan semua bonus!)

---

## ❓ FAQ

**Q: Boleh tidak pakai warna LED yang exact (misal kuning tidak ada, pakai oranye)?**  
A: Boleh! Yang penting pattern-nya benar (3 LED berbeda). Di Wokwi ada pilihan warna, tapi jika pakai hardware, warna apa saja OK.

**Q: Timing saya sedikit berbeda (misal Red 4.5s bukan 5s). Apakah masalah?**  
A: Tidak apa-apa selama mendekati (±1 detik OK). Yang penting pattern-nya benar. Tapi jika bisa exact, lebih bagus!

**Q: LED saya tidak menyala di Wokwi, tapi code sudah benar. Kenapa?**  
A: Check wiring:

1. GPIO → Resistor → LED anode (panjang)
2. LED cathode (pendek) → GND
3. Polaritas LED harus benar!
4. Coba reset simulation.

**Q: Boleh submit video saja tanpa screenshot?**  
A: Tidak, screenshot (**WAJIB**. Video bonus (opsional tapi recommended).

**Q: Saya pakai GPIO lain (bukan 15, 16, 17). Boleh?**  
A: Boleh! Tapi jelaskan di code comment GPIO mana yang Anda pakai. Hindari GPIO6-11 (flash)!

**Q: Challenge wajib dikerjakan?**  
A: Tidak wajib, tapi dapat **bonus +15%**! Jika ingin nilai maksimal, kerjakan challenge.

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
