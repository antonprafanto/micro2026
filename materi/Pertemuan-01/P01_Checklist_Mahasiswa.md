# ✅ Checklist Praktikum - Pertemuan 1

## Pengenalan ESP32 & Blink LED dengan Wokwi

> **Print checklist ini dan centang setiap step yang sudah selesai!** ✓

---

## 👤 Informasi

- **Nama**: **************\_\_\_**************
- **NIM**: **************\_\_\_**************
- **Tanggal**: **************\_\_\_**************

---

## 📚 BAGIAN 1: Persiapan (Sebelum Praktikum)

### **Materi Teori** (Baca di rumah sebelum kelas)

- [ ] Sudah baca materi "Apa itu Embedded Systems"
- [ ] Sudah baca materi "Mengenal Mikrokontroller"
- [ ] Sudah baca materi "Arsitektur ESP32"
- [ ] Sudah baca "Lab Safety Guide" (WAJIB!)
- [ ] Sudah paham pinout ESP32 (GPIO, VCC, GND)

### **Persiapan Tools**

- [ ] Laptop/PC dengan koneksi internet
- [ ] Browser modern (Chrome, Firefox, Edge)
- [ ] Buat akun Wokwi.com (gratis)

**Estimasi waktu**: 30 menit reading

---

## 🖥️ BAGIAN 2: Praktikum Wokwi (Di Lab/Rumah)

### **Step 1: Akses Wokwi**

- [ ] Buka browser, kunjungi: [https://wokwi.com](https://wokwi.com)
- [ ] Login dengan akun Wokwi (atau buat akun baru)
- [ ] Klik "New Project" → Pilih "ESP32"
- [ ] Simulator ESP32 muncul di layar

**Troubleshoot**: Jika stuck, refresh browser atau coba browser lain.

---

### **Step 2: Pahami Interface Wokwi**

- [ ] Identify bagian Code Editor (kiri)
- [ ] Identify bagian Simulation (tengah - ESP32 board)
- [ ] Identify bagian Serial Monitor (bawah)
- [ ] Klik tombol "Play" ▶️ untuk test (default code)
- [ ] Klik tombol "Pause" ⏸️ untuk stop
- [ ] Klik tombol "Reset" 🔄 untuk restart

**Catatan**: LED biru kecil di ESP32 simulation = GPIO 2 (LED_BUILTIN)

---

### **Step 3: Upload Code Blink LED**

- [ ] Copy code dari `P01_Blink_LED_Dasar.ino`
- [ ] Paste ke Wokwi code editor (replace all)
- [ ] Klik "Play" ▶️ untuk run simulation
- [ ] **Verifikasi**: LED biru di ESP32 berkedip ON-OFF
- [ ] **Verifikasi**: Serial Monitor menampilkan "LED ON" / "LED OFF"

**Troubleshoot**:

- Jika LED tidak berkedip, check code (pastikan tidak ada typo)
- Jika Serial Monitor kosong, klik icon Serial Monitor di bawah

---

### **Step 4: Eksperimen - Ubah Delay**

- [ ] Ubah `delay(1000)` menjadi `delay(500)`
- [ ] Klik "Play" ▶️ lagi
- [ ] **Observasi**: LED berkedip lebih cepat (2× per detik)
- [ ] Coba ubah menjadi `delay(2000)`
- [ ] **Observasi**: LED berkedip lebih lambat (1× per 2 detik)
- [ ] Kembalikan ke `delay(1000)` (untuk submission)

**Pelajaran**: `delay()` mengontrol kecepatan blink!

---

### **Step 5: Pahami Code**

- [ ] Baca comment di code, pahami maksudnya
- [ ] **Pertanyaan 1**: Apa fungsi `pinMode(LED_BUILTIN, OUTPUT)`?  
       Jawab: **************\_\_\_**************
- [ ] **Pertanyaan 2**: Apa beda `digitalWrite(LED_BUILTIN, HIGH)` vs `LOW`?  
       Jawab: **************\_\_\_**************
- [ ] **Pertanyaan 3**: Kenapa ada 2× `delay()` dalam `loop()`?  
       Jawab: **************\_\_\_**************

**Catatan**: Tulis jawaban di notebook, akan digunakan untuk submission!

---

### **Step 6: Save & Share Project**

- [ ] Klik tombol "Save" di Wokwi (pojok kanan atas)
- [ ] Beri nama project: "P01*Blink_LED*[NIM]\_[Nama]"  
       Contoh: `P01_Blink_LED_2111001_Anton`
- [ ] Klik tombol "Share" 🔗
- [ ] **Copy link** yang muncul (akan digunakan untuk submission)
- [ ] **Test link**: Paste di tab baru, pastikan bisa dibuka

**PENTING**: Jika tidak di-save, project akan hilang!

---

### **Step 7: Ambil Screenshot**

- [ ] Pastikan code + simulation + serial monitor visible
- [ ] Tekan `Windows + Shift + S` (Windows) atau `Cmd + Shift + 4` (Mac)
- [ ] Screenshot **seluruh window Wokwi**
- [ ] Save dengan nama: `P01_Screenshot_[NIM]_[Nama].png`

**Checklist Screenshot Harus Include**:

- ✓ Code editor dengan full code visible
- ✓ ESP32 simulation dengan LED (ON atau OFF)
- ✓ Serial Monitor dengan output "LED ON" / "LED OFF"
- ✓ Tidak blur, jelas terbaca

---

## 🌟 BAGIAN 3: Challenge (Opsional - Bonus!)

### **Challenge 1: SOS Morse Code**

- [ ] Copy code dari `P01_Challenge_SOS_Morse.ino`
- [ ] Paste ke Wokwi (atau buat project baru)
- [ ] Klik "Play" ▶️
- [ ] **Verifikasi**: LED blink pattern `··· ─── ···` (SOS)
- [ ] Save dengan nama: `P01_SOS_[NIM]_[Nama]`
- [ ] Screenshot & Copy link untuk submission

**Pattern SOS**:

- S = 3× short blink (200ms)
- O = 3× long blink (600ms)
- S = 3× short blink (200ms)

---

### **Challenge 2: Custom Pattern** (Advanced)

- [ ] Buat pattern sendiri (misal: ON 2s, OFF 0.5s, ON 0.3s, OFF 1s)
- [ ] Modifikasi code dengan pattern Anda
- [ ] Test di Wokwi
- [ ] **Dokumentasi**: Tulis pattern Anda di submission
- [ ] Screenshot & link

---

## 📤 BAGIAN 4: Submission

### **Persiapan Submission**

- [ ] Buka template submission (`P01_Template_Submission.md`)
- [ ] Isi informasi mahasiswa (nama, NIM, kelas)
- [ ] Paste screenshot Wokwi ke template
- [ ] Paste link Wokwi project (test lagi pastikan valid!)
- [ ] Paste full code ke template
- [ ] Jawab 3 pertanyaan di template
- [ ] (Opsional) Include challenge jika sudah kerjakan

### **Quality Check**

- [ ] Screenshot jelas dan tidak blur
- [ ] Link Wokwi bisa dibuka (test di browser incognito)
- [ ] Code lengkap (tidak terpotong)
- [ ] Jawaban 3 pertanyaan masuk akal
- [ ] Nama file sesuai format: `P01_[NIM]_[Nama].pdf` atau `.md`

### **Submit!**

- [ ] Upload ke platform submission (e-learning/Google Classroom/email)
- [ ] **Double-check** file ter-upload (jangan sampai kosong!)
- [ ] Submit **SEBELUM DEADLINE**!
- [ ] (Opsional) Screenshot bukti submit untuk backup

**DEADLINE**: **************\_\_\_**************

---

## 📊 Self-Assessment

Nilai diri Anda sendiri (jujur ya!):

| Kriteria           | Score (1-10)  | Notes                   |
| ------------------ | ------------- | ----------------------- |
| Pemahaman teori    | \_\_\_\_ / 10 | Apakah paham konsep?    |
| Skill Wokwi        | \_\_\_\_ / 10 | Lancar pakai simulator? |
| Code understanding | \_\_\_\_ / 10 | Paham tiap line code?   |
| Ketepatan waktu    | \_\_\_\_ / 10 | Submit on-time?         |

**Total**: \_\_\_\_ / 40

**Reflection**: Apa yang paling challenging di pertemuan ini?

```
_________________________________________________________________
_________________________________________________________________
_________________________________________________________________
```

**Next Goal**: Apa yang ingin dipelajari lebih dalam?

```
_________________________________________________________________
_________________________________________________________________
_________________________________________________________________
```

---

## 🆘 Troubleshooting

Jika ada masalah, cek di sini dulu sebelum tanya dosen/asisten:

### **Wokwi tidak bisa dibuka**

- [ ] Check koneksi internet
- [ ] Coba browser lain (Chrome recommended)
- [ ] Clear browser cache
- [ ] Logout & login lagi

### **LED tidak berkedip di simulation**

- [ ] Check code (ada typo?)
- [ ] Klik "Reset" 🔄 untuk restart simulation
- [ ] Check Serial Monitor (ada error message?)

### **Link Wokwi tidak bisa dibuka orang lain**

- [ ] Pastikan sudah klik "Save" dulu
- [ ] Pastikan sudah klik "Share" (bukan copy URL dari browser)
- [ ] Project visibility harus "Public" (bukan Private)

### **Screenshot blur/tidak jelas**

- [ ] Zoom window Wokwi hingga pas di layar
- [ ] Screenshot dengan resolusi penuh (jangan pakai low quality)
- [ ] Save sebagai PNG (bukan JPG compressed)

---

## 📞 Butuh Bantuan?

Jika sudah coba troubleshooting tapi masih stuck:

1. **Tanya teman** (peer learning!)
2. **Grup WA kelas** (mungkin teman lain punya solusi)
3. **Asisten lab** (via email/WA)
4. **Dosen** (office hours)

**Jangan malu bertanya!** Lebih baik tanya daripada stuck sendirian. 😊

---

## ✅ Final Check

Sebelum tutup praktikum:

- [ ] Semua checklist di atas sudah ✓
- [ ] File submission sudah siap
- [ ] Deadline noted di kalender
- [ ] Wokwi project sudah di-save (jangan sampai hilang!)

**Paraf**: ****\_\_**** **Tanggal**: ****\_\_****

---

**Selamat! Anda sudah menyelesaikan Pertemuan 1!** 🎉

**Next**: Pertemuan 2 - Digital I/O & External LED

---

**Checklist ini dibuat untuk**: Mata Kuliah Mikrokontroller - Prodi Informatika Unmul
