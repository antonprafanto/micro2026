# ✅ Checklist Praktikum - Pertemuan 4

## Serial Communication & Interactive Menu

> **Print checklist ini dan centang setiap step yang sudah selesai!** ✓

---

## 👤 Informasi

- **Nama**: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_
- **NIM**: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_
- **Tanggal**: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

---

## 📚 BAGIAN 1: Persiapan (Sebelum Praktikum)

### **Materi Teori** (Baca di rumah sebelum kelas)

- [ ] Sudah baca materi "UART & Komunikasi Serial"
- [ ] Sudah baca materi "Baud Rate"
- [ ] Sudah baca materi "Serial.print() & Serial.println()"
- [ ] Sudah baca materi "Serial.available() & Serial.read()"
- [ ] Sudah baca materi "Debugging dengan Serial"
- [ ] Paham cara kerja `Serial.readStringUntil('\n')`

### **Review Pertemuan 1-3**

- [ ] Paham GPIO, `digitalWrite()`, `analogRead()`
- [ ] Paham PWM & `ledcAttach()` / `ledcWrite()`
- [ ] Familiar dengan Wokwi interface
- [ ] Paham wiring LED + Potensiometer

### **Persiapan Tools**

- [ ] Laptop/PC dengan koneksi internet
- [ ] Browser modern (Chrome recommended)
- [ ] Login ke akun Wokwi
- [ ] (Opsional) Arduino IDE untuk compile real hardware

**Estimasi waktu**: 40 menit reading

---

## 🖥️ BAGIAN 2: Praktikum 1 - Hello World & Sensor Output

### **Step 1: Buat Project Baru**

- [ ] Login ke Wokwi
- [ ] Klik "New Project" → "ESP32"
- [ ] Rename: `P04_Hello_Serial_[NIM]_[Nama]`

---

### **Step 2: Add Potensiometer**

- [ ] Klik "+" → Add **Potentiometer**
- [ ] Wiring:
  - [ ] Pot VCC → ESP32 3V3
  - [ ] Pot SIG → ESP32 GPIO34
  - [ ] Pot GND → ESP32 GND

---

### **Step 3: Upload & Run Code**

- [ ] Copy code Praktikum 1 dari materi
- [ ] Paste ke Wokwi editor
- [ ] Verify baris kunci:
  ```cpp
  Serial.begin(115200);
  Serial.printf("Voltage    : %.2fV\n", voltage);
  ```
- [ ] Run simulation ▶️

---

### **Step 4: Test Serial Monitor**

- [ ] Buka Serial Monitor (ikon terminal)
- [ ] **Pilih baud rate 115200**
- [ ] Verify output tampil: ADC Raw, Voltage, Percentage, Uptime
- [ ] **Drag knob** potensiometer → nilai berubah
- [ ] **Test baud rate salah** (ganti ke 9600) – lihat garbage characters
- [ ] **Kembali ke 115200** → output normal

**Pelajaran**: Baud rate harus match antara ESP32 dan Serial Monitor!

---

### **Pertanyaan Pemahaman**

- [ ] **Q**: Kenapa output menjadi rusak (garbage) saat baud rate berbeda?  
       Jawab: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

- [ ] **Q**: Apa perbedaan `Serial.print()` vs `Serial.println()`?  
       Jawab: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

---

## 📈 BAGIAN 3: Praktikum 2 - Serial Plotter

### **Step 1: Tambah LED ke Project**

- [ ] Keep potensiometer dari Praktikum 1
- [ ] Klik "+" → Add **LED**
- [ ] Klik "+" → Add **Resistor** (220Ω)
- [ ] Wiring LED:
  - [ ] GPIO15 → Resistor → LED Anode → LED Cathode → GND

---

### **Step 2: Upload Code Serial Plotter**

- [ ] Copy code Praktikum 2 dari materi
- [ ] Paste ke Wokwi editor
- [ ] Verify kunci:
  ```cpp
  Serial.print(potValue);
  Serial.print("\t");
  Serial.println(brightness);
  ```

---

### **Step 3: Buka & Amati Serial Plotter**

- [ ] Run simulation ▶️
- [ ] Klik **ikon grafik 📊** (Serial Plotter) di Wokwi
- [ ] **Drag pot pelan-pelan** dari kiri ke kanan
- [ ] Observe: **2 garis** berbeda naik turun
- [ ] Garis 1 (Pot_ADC): range 0-4095
- [ ] Garis 2 (LED_Brightness): range 0-255

---

### **Pertanyaan Pemahaman**

- [ ] **Q**: Mengapa ada 2 garis di Serial Plotter (bukan 1)?  
       Jawab: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

- [ ] **Q**: Apa fungsi karakter `\t` di antara dua nilai yang dikirim?  
       Jawab: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

---

## 🔆 BAGIAN 4: Praktikum 3 - LED Control via Serial

### **Step 1: Upload Code LED Control**

- [ ] Copy code Praktikum 3 dari materi
- [ ] Paste ke Wokwi editor
- [ ] Struktur code check:
  - [ ] `cmd.toLowerCase()` → case-insensitive
  - [ ] `cmd == "on"` → LED ON
  - [ ] `cmd.startsWith("dim:")` → set brightness
  - [ ] `cmd.substring(4).toInt()` → parse nilai

---

### **Step 2: Test Semua Perintah**

> ⚠️ **Pastikan** pilih **"NL & CR"** sebagai Line Ending di Serial Monitor!

| Perintah  | Expected Result                | ✓   |
| --------- | ------------------------------ | --- |
| `on`      | LED ON penuh (255/255)         | [ ] |
| `off`     | LED OFF                        | [ ] |
| `dim:128` | LED ~50% brightness            | [ ] |
| `dim:64`  | LED ~25% brightness            | [ ] |
| `dim:255` | LED 100% brightness            | [ ] |
| `dim:0`   | LED OFF                        | [ ] |
| `status`  | Tampil info status LED         | [ ] |
| `abc`     | Pesan error "tidak dikenali"   | [ ] |
| `ON`      | LED ON (test case-insensitive) | [ ] |

---

### **Pertanyaan Pemahaman**

- [ ] **Q**: Apa fungsi `cmd.toLowerCase()` sebelum compare string?  
       Jawab: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

- [ ] **Q**: Apa fungsi `constrain(value, 0, 255)`?  
       Jawab: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

---

## 🍽️ BAGIAN 5: Praktikum 4 - Interactive Serial Menu (PROJECT!)

### **Step 1: Buat Project Final**

- [ ] **Option A**: Gunakan project dari Praktikum 1-3 (sudah ada Pot + LED)
- [ ] **Option B**: Buat project baru
- [ ] Rename: `P04_SerialMenu_[NIM]_[Nama]`

---

### **Step 2: Verify Wiring Complete**

**Checklist Wiring**:

- [ ] Potensiometer: VCC→3V3, SIG→GPIO34, GND→GND
- [ ] LED: GPIO15 → 220Ω → Anode → Cathode → GND
- [ ] Semua wire terhubung dengan benar

---

### **Step 3: Upload Code Menu**

- [ ] Copy code `P04_SerialMenu.ino` dari materi
- [ ] Paste ke Wokwi editor
- [ ] Struktur code check:
  - [ ] `printMenu()` – fungsi tampilkan menu
  - [ ] `blinkLED(5)` – blink LED 5x
  - [ ] `readSensor()` – baca potensiometer
  - [ ] `systemInfo()` – tampilkan info sistem
  - [ ] `handleMenu(int choice)` – handle pilihan menu
  - [ ] `Serial.readStringUntil('\n')` di `loop()`

---

### **Step 4: Test Semua Menu**

- [ ] Run simulation ▶️
- [ ] Menu tampil di Serial Monitor
- [ ] **Test pilihan 1** (LED ON):
  - [ ] Ketik `1` → Enter
  - [ ] Verify: LED nyala penuh + pesan "✅ LED ON"
- [ ] **Test pilihan 2** (LED OFF):
  - [ ] Ketik `2` → Enter
  - [ ] Verify: LED mati + pesan "✅ LED OFF"
- [ ] **Test pilihan 3** (Blink):
  - [ ] Ketik `3` → Enter
  - [ ] Verify: LED blink 5x + pesan setiap blink
- [ ] **Test pilihan 4** (Read Sensor):
  - [ ] Ketik `4` → Enter
  - [ ] Verify: ADC Value, Voltage, Percentage tampil
  - [ ] Drag pot → ketik 4 lagi → nilai berbeda
- [ ] **Test pilihan 5** (Set Brightness):
  - [ ] Ketik `5` → Enter
  - [ ] Verify: Prompt muncul "Masukkan brightness:"
  - [ ] Ketik `128` → Enter
  - [ ] Verify: LED ~50% brightness
- [ ] **Test pilihan 6** (System Info):
  - [ ] Ketik `6` → Enter
  - [ ] Verify: Uptime, LED state, free heap tampil
- [ ] **Test pilihan 0** (Tampilkan menu):
  - [ ] Ketik `0` → Enter
  - [ ] Verify: Menu tampil ulang
- [ ] **Test pilihan invalid**:
  - [ ] Ketik `9` → Enter
  - [ ] Verify: Pesan error "tidak valid"

---

### **Step 5: Test Flow Sequence**

- [ ] Test sequence: `1` → `4` → `5:64` → `3` → `2` → `6`
- [ ] Semua transisi berjalan smooth
- [ ] Menu selalu muncul kembali setelah tiap aksi
- [ ] Tidak ada program crash / freeze

---

### **Step 6: Troubleshooting (jika ada masalah)**

**Problem: Menu tidak tampil saat startup**

- [ ] Check `printMenu()` dipanggil di `setup()`
- [ ] Check `Serial.begin(115200)` ada di paling atas `setup()`
- [ ] Reset simulation Wokwi

**Problem: Input tidak dibaca / menu tidak bereaksi**

- [ ] Check Line Ending = "NL & CR"
- [ ] Check baud rate = 115200
- [ ] Print `Serial.available()` untuk debug

**Problem: LED tidak blink**

- [ ] Check wiring LED (GPIO15 → Resistor → Anode → Cathode → GND)
- [ ] Manual test: ketik `1` dulu (LED ON), lalu `3` (blink)

**Problem: Serial.parseInt() baca 0 terus**

- [ ] Pastikan Line Ending "NL & CR" dipilih
- [ ] Check tidak ada whitespace di awal input

---

### **Step 7: Save & Share Project**

- [ ] Klik **Save** 💾
- [ ] Nama project: `P04_SerialMenu_[NIM]_[Nama]`
- [ ] Klik **Share** 🔗
- [ ] Copy link
- [ ] **Test link** di browser incognito – bisa dibuka?

---

## 📸 BAGIAN 6: Screenshot & Documentation

### **Screenshot Requirements**

- [ ] Screenshot **seluruh window Wokwi**
- [ ] **Wiring visible**: Pot + LED + Resistor terhubung
- [ ] **Simulation running**: LED dalam kondisi tertentu (ON atau sedang blink)
- [ ] **Serial Monitor**: Menu tampil dengan beberapa interaksi (minimal 3 command)
- [ ] Screenshot jelas, tidak blur
- [ ] Save: `P04_SerialMenu_[NIM]_[Nama].png`

---

### **Video Demo (Highly Recommended!)**

- [ ] Screen recording (20-45 detik)
- [ ] Demonstrate: Ketik setidaknya 4 pilihan berbeda dari menu
- [ ] Show: LED bereaksi sesuai perintah
- [ ] Show: Serial Monitor output untuk setiap pilihan
- [ ] Upload ke Google Drive / YouTube (unlisted)
- [ ] Copy link

**Why video important?**: Interaksi real-time menu jauh lebih jelas di video!

---

## 🌟 BAGIAN 7: Challenge (Opsional - Bonus!)

### **Challenge 1: Auto-Read Sensor (pilihan 7)**

- [ ] Tambah opsi menu `7. Auto Read Sensor`
- [ ] Sensor update otomatis tiap 2 detik
- [ ] Ketik `s` lalu Enter untuk stop
- [ ] Test: jalankan auto-read → sensor berubah saat putar pot → stop

### **Challenge 2: Password Protection**

- [ ] Sebelum menu, minta password
- [ ] Password default: `esp32`
- [ ] Salah password → tampil pesan error, minta lagi
- [ ] Benar → lanjut ke menu

### **Challenge 3: Brightness Level Display**

- [ ] Saat LED ON/set brightness, tampilkan ASCII bar:
  ```
  Brightness: [████████░░] 80%
  ```
- [ ] Panjang bar: 10 karakter (`█` untuk ON, `░` untuk OFF)

---

## 📤 BAGIAN 8: Submission

### **Persiapan Submission**

- [ ] Buka `P04_Template_Submission.md`
- [ ] Isi informasi mahasiswa
- [ ] Paste screenshot
- [ ] Paste link Wokwi (verify valid!)
- [ ] Paste code lengkap
- [ ] Checklist wiring completed
- [ ] Checklist functionality completed (semua 7 pilihan menu)
- [ ] Jawab 4 pertanyaan
- [ ] (Recommended) Include video demo
- [ ] (Opsional) Include challenge

### **Quality Check**

- [ ] Screenshot jelas (menu + interaksi + LED visible)
- [ ] Link Wokwi valid (test di incognito!)
- [ ] Code lengkap (tidak terpotong)
- [ ] Wiring checklist semua ✓
- [ ] Functionality checklist: semua menu ter-test
- [ ] Jawaban 4 pertanyaan lengkap
- [ ] File name: `P04_[NIM]_[Nama].pdf/md`

### **Submit!**

- [ ] Upload ke platform (e-learning/GClassroom)
- [ ] Verify file ter-upload
- [ ] Submit **BEFORE DEADLINE**!

**DEADLINE**: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

---

## 📊 Self-Assessment

| Kriteria                        | Score (1-10)  | Notes                    |
| ------------------------------- | ------------- | ------------------------ |
| Pemahaman Serial Communication  | \_\_\_\_ / 10 | Paham print/read serial? |
| Implementasi Serial Menu        | \_\_\_\_ / 10 | Semua menu berfungsi?    |
| Debugging skill                 | \_\_\_\_ / 10 | Bisa pakai serial debug? |
| String parsing & input handling | \_\_\_\_ / 10 | Paham readStringUntil?   |
| Ketepatan waktu                 | \_\_\_\_ / 10 | Submit on-time?          |

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
- [ ] Project Wokwi saved & link valid
- [ ] Screenshot & video ready
- [ ] Submission file ready
- [ ] Deadline noted
- [ ] (Optional) Challenge completed

**Paraf**: \_\_\_\_\_\_\_\_\_ **Tanggal**: \_\_\_\_\_\_\_\_\_

---

**🎉 Selamat! Anda sudah menguasai Serial Communication & Debugging!**

**Next**: Pertemuan 5 - Sensor Suhu & Kelembaban (DHT22) 🌡️

---

**Checklist ini dibuat untuk**: Mata Kuliah Mikrokontroller - Prodi Informatika Unmul
