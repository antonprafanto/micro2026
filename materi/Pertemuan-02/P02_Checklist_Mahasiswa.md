# ✅ Checklist Praktikum - Pertemuan 2

## Digital I/O & Traffic Light Simulation

> **Print checklist ini dan centang setiap step yang sudah selesai!** ✓

---

## 👤 Informasi

- **Nama**: **************\_\_\_**************
- **NIM**: **************\_\_\_**************
- **Tanggal**: **************\_\_\_**************

---

## 📚 BAGIAN 1: Persiapan (Sebelum Praktikum)

### **Materi Teori** (Baca di rumah sebelum kelas)

- [ ] Sudah baca materi "Konsep GPIO"
- [ ] Sudah baca materi "Digital Signal: HIGH vs LOW"
- [ ] Sudah baca materi "pinMode(), digitalWrite(), digitalRead()"
- [ ] Sudah baca materi "Pull-up dan Pull-down Resistor"
- [ ] Sudah baca materi "Breadboard & Wiring"

### **Review Pertemuan 1**

- [ ] Sudah menyelesaikan Pertemuan 1 (Blink LED onboard)
- [ ] Familiar dengan Wokwi interface
- [ ] Paham cara save & share project Wokwi

### **Persiapan Tools**

- [ ] Laptop/PC dengan koneksi internet
- [ ] Browser modern (Chrome, Firefox, Edge)
- [ ] Login ke akun Wokwi

**Estimasi waktu**: 40 menit reading

---

## 🖥️ BAGIAN 2: Praktikum 1 - External LED Blink

### **Step 1: Buat Project Baru**

- [ ] Login ke Wokwi
- [ ] Klik "New Project" → Pilih "ESP32"
- [ ] Rename project: `P02_External_LED_[NIM]_[Nama]`

---

### **Step 2: Add Components**

- [ ] Klik tombol "+" di simulation area
- [ ] Add **LED** (Red LED)
- [ ] Add **Resistor** (220 ohm)
- [ ] Kedua komponen muncul di simulation area

**Note**: Komponen bisa di-drag untuk reposition.

---

### **Step 3: Wiring**

- [ ] Click **GPIO15** di ESP32 board
- [ ] Drag ke **resistor pin 1** (salah satu ujung)
- [ ] Click **resistor pin 2** (ujung satunya)
- [ ] Drag ke **LED anode** (kaki panjang, biasanya ada tanda +)
- [ ] Click **LED cathode** (kaki pendek, tanda -)
- [ ] Drag ke **GND** di ESP32

**Visual Check**:

- ✓ Wire terbentuk dari GPIO15 → Resistor → LED → GND
- ✓ Tidak ada wire yang putus/lepas

---

### **Step 4: Upload Code**

- [ ] Copy code external LED blink dari materi
- [ ] Paste ke Wokwi code editor (replace semua code)
- [ ] Code snippet key:
  ```cpp
  #define LED_PIN 15
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH/LOW);
  ```

---

### **Step 5: Run & Verify**

- [ ] Klik **Play** ▶️
- [ ] **Verify**: LED merah di breadboard berkedip ON-OFF
- [ ] **Verify**: Serial Monitor menampilkan "LED ON" / "LED OFF"
- [ ] Jika tidak berkedip, check wiring!

**Troubleshoot** (jika LED tidak nyala):

- [ ] Check GPIO number di code (harus 15)
- [ ] Check polaritas LED (panjang=anode, pendek=cathode)
- [ ] Reset simulation (tombol Reset 🔄)

---

### **Step 6: Eksperimen Timing**

- [ ] Ubah `delay(1000)` menjadi `delay(500)`
- [ ] Run lagi → LED berkedip lebih cepat!
- [ ] Kembalikan ke `delay(1000)`

**Pelajaran**: Delay mengontrol kecepatan blink.

---

## 🔘 BAGIAN 3: Praktikum 2 - Button Control LED

### **Step 1: Add Button Component**

- [ ] Keep LED dari praktikum 1 (jangan dihapus!)
- [ ] Klik "+" → Add **Push Button**
- [ ] Button muncul di simulation area

---

### **Step 2: Wiring Button**

- [ ] Click **Button pin 1**
- [ ] Drag ke **GPIO4** di ESP32
- [ ] Click **Button pin 2**
- [ ] Drag ke **GND** di ESP32

**Visual Check**:

- ✓ Button pin 1 → GPIO4
- ✓ Button pin 2 → GND
- ✓ LED tetap terhubung (dari praktikum 1)

---

### **Step 3: Upload Code Button Control**

- [ ] Copy code button control LED dari materi
- [ ] Paste ke Wokwi editor
- [ ] Code snippet key:
  ```cpp
  #define BUTTON_PIN 4
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  if (digitalRead(BUTTON_PIN) == LOW) { ... }
  ```

---

### **Step 4: Test Button**

- [ ] Run simulation (Play ▶️)
- [ ] **Click button** di Wokwi simulation (dengan mouse)
- [ ] **Verify**: LED ON saat button ditekan
- [ ] **Verify**: LED OFF saat button dilepas
- [ ] **Verify**: Serial Monitor menampilkan "PRESSED" / "RELEASED"

**Note**: Dengan `INPUT_PULLUP`, button pressed = LOW (bukan HIGH!).

---

### **Step 5: Pahami Pull-up**

- [ ] Baca comment di code tentang pull-up resistor
- [ ] **Pertanyaan**: Kenapa button pressed = LOW (bukan HIGH)?  
       Jawab: **************\_\_\_**************
- [ ] Save pemahaman ini untuk submission

---

## 🚦 BAGIAN 4: Praktikum 3 - Traffic Light (PROJECT UTAMA!)

### **Step 1: Buat Project Baru**

- [ ] Buat project baru: `P02_TrafficLight_[NIM]_[Nama]`
- [ ] Atau gunakan project dari praktikum sebelumnya (hapus button)

---

### **Step 2: Add 3 LED + 3 Resistor**

- [ ] Add **3× LED**:
  - [ ] LED Merah (Red LED)
  - [ ] LED Kuning (Yellow/Orange LED)
  - [ ] LED Hijau (Green LED)
- [ ] Add **3× Resistor** (220Ω each)

**Visual Check**: Total ada 3 LED + 3 resistor di simulation.

---

### **Step 3: Wiring LED 1 (Merah)**

- [ ] GPIO15 → Resistor 1 pin 1
- [ ] Resistor 1 pin 2 → LED Merah anode (+)
- [ ] LED Merah cathode (-) → GND

**Check**: LED merah terhubung lengkap!

---

### **Step 4: Wiring LED 2 (Kuning)**

- [ ] GPIO16 → Resistor 2 pin 1
- [ ] Resistor 2 pin 2 → LED Kuning anode (+)
- [ ] LED Kuning cathode (-) → GND

**Check**: LED kuning terhubung lengkap!

---

### **Step 5: Wiring LED 3 (Hijau)**

- [ ] GPIO17 → Resistor 3 pin 1
- [ ] Resistor 3 pin 2 → LED Hijau anode (+)
- [ ] LED Hijau cathode (-) → GND

**Check**: LED hijau terhubung lengkap!

---

### **Step 6: Final Wiring Check**

**Checklist Visual** (PENTING!):

- [ ] 3 LED terpasang dengan warna berbeda
- [ ] 3 Resistor terpasang (1 per LED)
- [ ] Setiap LED: GPIO → Resistor → Anode → Cathode → GND
- [ ] Polaritas semua LED benar (panjang=anode, pendek=cathode)
- [ ] Tidak ada wire crossing yang membingungkan
- [ ] Semua GND terhubung ke ESP32 GND

**Foto/Screenshot wiring** untuk dokumentasi!

---

### **Step 7: Upload Code Traffic Light**

- [ ] Copy code `P02_Traffic_Light_Simulation.ino` dari materi
- [ ] Paste ke Wokwi editor
- [ ] Code snippet key:
  ```cpp
  #define RED_LED 15
  #define YELLOW_LED 16
  #define GREEN_LED 17
  ```

---

### **Step 8: Understand Code Logic**

- [ ] Baca code, pahami state machine:
  - State 1: RED ON, YELLOW OFF, GREEN OFF (5s)
  - State 2: RED OFF, YELLOW ON, GREEN OFF (2s)
  - State 3: RED OFF, YELLOW OFF, GREEN ON (5s)
  - Loop repeat
- [ ] **Pertanyaan**: Bagaimana cara mengontrol hanya 1 LED ON di 1 waktu?  
       Jawab: **************\_\_\_**************

---

### **Step 9: Run & Verify Traffic Light**

- [ ] Klik **Play** ▶️
- [ ] **Observe** cycle pertama:
  - [ ] Merah ON selama ~5 detik (hitung!)
  - [ ] Kuning ON selama ~2 detik
  - [ ] Hijau ON selama ~5 detik
- [ ] **Verify**: Hanya 1 LED menyala di 1 waktu (tidak ada 2 LED nyala bersamaan)
- [ ] **Verify**: Pattern repeat otomatis (cycle ke-2, ke-3, ...)
- [ ] **Verify**: Serial Monitor menampilkan state (RED, YELLOW, GREEN)

**Jika tidak sesuai pattern**, check code & wiring!

---

### **Step 10: Troubleshooting (Jika Ada Masalah)**

**Problem: Semua LED tidak menyala**

- [ ] Check wiring: semua LED terhubung ke GND?
- [ ] Check code: semua `pinMode(OUTPUT)` sudah ada?
- [ ] Reset simulation

**Problem: Hanya 1 atau 2 LED yang menyala**

- [ ] Check wiring LED yang tidak menyala
- [ ] Check polaritas (anode vs cathode)
- [ ] Swap wire untuk test

**Problem: Semua LED menyala bersamaan**

- [ ] Check code: pastikan hanya 1 HIGH, 2 LOW di tiap state
- [ ] Example benar:
  ```cpp
  digitalWrite(RED_LED, HIGH);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  ```

**Problem: Timing tidak sesuai**

- [ ] Check `delay()` duration di code
- [ ] Pastikan tidak ada delay tambahan tidak sengaja

---

### **Step 11: Save & Share**

- [ ] Klik **Save** 💾
- [ ] Klik **Share** 🔗
- [ ] Copy link project
- [ ] **Test link** di browser incognito (PENTING!)
- [ ] Simpan link untuk submission

---

## 📸 BAGIAN 5: Screenshot & Documentation

### **Screenshot Requirements**

- [ ] Screenshot **seluruh window Wokwi**
- [ ] **Include**:
  - [ ] Wiring circuit (3 LED visible)
  - [ ] Simulation running (1 LED menyala)
  - [ ] Code editor dengan code visible
  - [ ] Serial Monitor dengan output state
- [ ] Screenshot jelas, tidak blur
- [ ] Save dengan nama: `P02_TrafficLight_[NIM]_[Nama].png`

---

### **Video Demo (Opsional - Recommended!)**

- [ ] Screen recording Wokwi (10-30 detik)
- [ ] Tunjukkan **minimal 1 cycle lengkap**:
  - Merah → Kuning → Hijau → (Repeat mulai)
- [ ] Upload ke Google Drive / YouTube (unlisted)
- [ ] Copy link untuk submission

**Note**: Video sangat membantu dosen verify!

---

## 🌟 BAGIAN 6: Challenge (Opsional - Bonus!)

### **Challenge 1: Custom Timing**

- [ ] Ubah timing: Red 3s, Yellow 1s, Green 7s
- [ ] Test & verify
- [ ] Screenshot hasil

### **Challenge 2: Pedestrian Button**

- [ ] Copy code `P02_Challenge_Pedestrian_Button.ino`
- [ ] Add button component
- [ ] Wire button (GPIO4 → Button → GND)
- [ ] Test: button paksa traffic light ke RED
- [ ] Screenshot & share link

### **Challenge 3: Night Mode**

- [ ] Modifikasi code: setelah 3 cycle normal, masuk night mode
- [ ] Night mode: hanya LED kuning berkedip (ON 500ms, OFF 500ms)
- [ ] Test & dokumentasi

---

## 📤 BAGIAN 7: Submission

### **Persiapan Submission**

- [ ] Buka template `P02_Template_Submission.md`
- [ ] Isi informasi mahasiswa (nama, NIM, kelas)
- [ ] Paste screenshot Wokwi
- [ ] Paste link Wokwi project (verify link valid!)
- [ ] Paste full code
- [ ] Jawab 3 pertanyaan di template
- [ ] (Opsional) Include video demo
- [ ] (Opsional) Include challenge

### **Quality Check**

- [ ] Screenshot jelas (tidak blur, all elements visible)
- [ ] Link Wokwi bisa dibuka (test di browser incognito!)
- [ ] Code lengkap (tidak terpotong)
- [ ] Wiring checklist completed
- [ ] Pattern checklist verified
- [ ] Jawaban 3 pertanyaan masuk akal
- [ ] Nama file sesuai format: `P02_[NIM]_[Nama].pdf` atau `.md`

### **Submit!**

- [ ] Upload ke platform submission (e-learning/Google Classroom)
- [ ] **Double-check** file ter-upload (buka lagi untuk verify)
- [ ] Submit **SEBELUM DEADLINE**!
- [ ] (Opsional) Screenshot bukti submit

**DEADLINE**: **************\_\_\_**************

---

## 📊 Self-Assessment

Nilai diri Anda sendiri (jujur!):

| Kriteria                     | Score (1-10)  | Notes                                     |
| ---------------------------- | ------------- | ----------------------------------------- |
| Pemahaman GPIO & Digital I/O | \_\_\_\_ / 10 | Paham pinMode, digitalWrite, digitalRead? |
| Wiring breadboard            | \_\_\_\_ / 10 | Bisa wire 3 LED dengan benar?             |
| Code understanding           | \_\_\_\_ / 10 | Paham state machine traffic light?        |
| Troubleshooting skill        | \_\_\_\_ / 10 | Bisa debug kalau ada error?               |
| Ketepatan waktu              | \_\_\_\_ / 10 | Submit on-time?                           |

**Total**: \_\_\_\_ / 50

**Reflection**: Apa yang paling challenging di pertemuan ini?

```
_________________________________________________________________
_________________________________________________________________
_________________________________________________________________
```

**New Skill Learned**: Apa skill baru yang paling berguna?

```
_________________________________________________________________
_________________________________________________________________
_________________________________________________________________
```

**Next Goal**: Apa yang ingin dipelajari di Pertemuan 3?

```
_________________________________________________________________
_________________________________________________________________
_________________________________________________________________
```

---

## 🆘 Troubleshooting Checklist

### **Wokwi tidak bisa dibuka / lemot**

- [ ] Check koneksi internet
- [ ] Refresh browser (F5)
- [ ] Clear browser cache
- [ ] Coba browser lain (Chrome recommended)
- [ ] Logout & login lagi

### **LED tidak menyala (salah satu atau semua)**

- [ ] Check wiring: GPIO → Resistor → LED anode → LED cathode → GND
- [ ] Polaritas LED: kaki panjang (anode) ke resistor, pendek (cathode) ke GND
- [ ] Resistor terpasang? (jangan skip!)
- [ ] Code: `pinMode(LED_PIN, OUTPUT)` ada?
- [ ] Code: `digitalWrite(LED_PIN, HIGH)` dipanggil?
- [ ] Reset simulation (🔄 button)

### **Traffic light pattern salah**

- [ ] Check timing: RED 5s, YELLOW 2s, GREEN 5s
- [ ] Check logic: hanya 1 LED HIGH di tiap state
- [ ] Serial Monitor: verify output state benar
- [ ] Code: tidak ada typo di GPIO pin number?

### **Link Wokwi tidak bisa dibuka**

- [ ] Project sudah di-**SAVE** (💾)?
- [ ] Sudah klik **SHARE** (🔗)?
- [ ] Copy link yang benar (format: `https://wokwi.com/projects/xxxxx`)
- [ ] Test link di browser incognito
- [ ] Visibility project: Public (bukan Private)

### **Screenshot blur / tidak jelas**

- [ ] Zoom window Wokwi hingga pas (jangan terlalu kecil)
- [ ] Screenshot dengan resolusi penuh
- [ ] Save sebagai PNG (bukan JPG compressed)
- [ ] Pastikan semua elements visible (code, circuit, serial monitor)

---

## 📚 Learning Resources

### **Jika masih bingung, baca lagi**:

- [ ] Materi Pertemuan 2: Section "GPIO & Digital I/O"
- [ ] Materi Pertemuan 2: Section "Breadboard & Wiring"
- [ ] ESP32 Pinout Reference (file terpisah)
- [ ] Wokwi Docs: [https://docs.wokwi.com](https://docs.wokwi.com)

### **Video Tutorial** (cari di YouTube):

- "ESP32 LED Wokwi tutorial"
- "Traffic light simulation Arduino"
- "ESP32 multiple LED control"

---

## 💬 Butuh Bantuan?

Jika sudah coba troubleshooting tapi masih stuck:

1. **Tanya teman** (peer learning!)
2. **Grup WA kelas** (share screenshot, teman bisa bantu)
3. **Asisten lab** (via email/WA/office hours)
4. **Dosen** (jika masalah konsep)

**Jangan malu bertanya!** Everyone starts somewhere. 😊

---

## ✅ Final Check

Sebelum tutup praktikum:

- [ ] Semua checklist di atas sudah ✓
- [ ] Project Wokwi sudah di-save (verify di dashboard Wokwi)
- [ ] Link Wokwi sudah di-test (bisa dibuka)
- [ ] Screenshot sudah diambil & disimpan
- [ ] File submission sudah siap
- [ ] Deadline noted di kalender
- [ ] (Opsional) Challenge sudah dikerjakan

**Paraf**: ****\_\_**** **Tanggal**: ****\_\_****

---

**🎉 Selamat! Anda sudah menguasai Digital I/O & Traffic Light!**

**Next**: Pertemuan 3 - Analog I/O & PWM (LED Dimmer!) 🌟

---

**Checklist ini dibuat untuk**: Mata Kuliah Mikrokontroller - Prodi Informatika Unmul
