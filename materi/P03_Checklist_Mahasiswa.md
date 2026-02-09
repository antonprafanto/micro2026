# ✅ Checklist Praktikum - Pertemuan 3

## Analog I/O & Interactive LED Dimmer

> **Print checklist ini dan centang setiap step yang sudah selesai!** ✓

---

## 👤 Informasi

- **Nama**: **************\_\_\_**************
- **NIM**: **************\_\_\_**************
- **Tanggal**: **************\_\_\_**************

---

## 📚 BAGIAN 1: Persiapan (Sebelum Praktikum)

### **Materi Teori** (Baca di rumah sebelum kelas)

- [ ] Sudah baca materi "Analog vs Digital Signal"
- [ ] Sudah baca materi "ADC (Analog-to-Digital Converter)"
- [ ] Sudah baca materi "PWM (Pulse Width Modulation)"
- [ ] Sudah baca materi "LEDC di ESP32"
- [ ] Sudah baca materi "Potensiometer Basics"
- [ ] Paham duty cycle & frequency

### **Review Pertemuan 1-2**

- [ ] Paham GPIO (INPUT/OUTPUT)
- [ ] Paham `digitalWrite()` untuk kontrol LED
- [ ] Familiar dengan Wokwi interface
- [ ] Paham wiring LED dengan resistor

### **Persiapan Tools**

- [ ] Laptop/PC dengan koneksi internet
- [ ] Browser modern (Chrome recommended)
- [ ] Login ke akun Wokwi

**Estimasi waktu**: 45 menit reading

---

## 🖥️ BAGIAN 2: Praktikum 1 - Baca Potensiometer (ADC)

### **Step 1: Buat Project Baru**

- [ ] Login ke Wokwi
- [ ] Klik "New Project" → "ESP32"
- [ ] Rename: `P03_Read_Potentiometer_[NIM]_[Nama]`

---

### **Step 2: Add Potensiometer**

- [ ] Klik tombol "+"
- [ ] Add component: **"Potentiometer"**
- [ ] Pot muncul di simulation area
- [ ] (Optional) Drag pot untuk reposition

---

### **Step 3: Wiring Potensiometer**

- [ ] Click **Pot VCC** (pin atas)
- [ ] Drag ke **ESP32 3V3**
- [ ] Click **Pot SIG** (pin tengah / wiper)
- [ ] Drag ke **ESP32 GPIO34** (ADC pin!)
- [ ] Click **Pot GND** (pin bawah)
- [ ] Drag ke **ESP32 GND**

**Visual Check**:

- ✓ Pot VCC → ESP32 3V3 (power)
- ✓ Pot SIG → ESP32 GPIO34 (ADC signal)
- ✓ Pot GND → ESP32 GND (ground)

---

### **Step 4: Upload Code**

- [ ] Copy code praktikum 1 dari materi (read potensiometer)
- [ ] Paste ke Wokwi editor
- [ ] Code key check:
  ```cpp
  #define POT_PIN 34
  int potValue = analogRead(POT_PIN);
  ```

---

### **Step 5: Test ADC Reading**

- [ ] Run simulation (Play ▶️)
- [ ] Buka Serial Monitor
- [ ] **Drag knob pot** ke kiri penuh
- [ ] **Verify**: ADC value ~0, Voltage ~0V, Percentage ~0%
- [ ] **Drag knob pot** ke tengah
- [ ] **Verify**: ADC value ~2048, Voltage ~1.65V, Percentage ~50%
- [ ] **Drag knob pot** ke kanan penuh
- [ ] **Verify**: ADC value ~4095, Voltage ~3.3V, Percentage ~100%

**Pelajaran**: ADC mengubah voltage analog (0-3.3V) → angka digital (0-4095)!

---

### **Step 6: Understand `map()` Function**

- [ ] Lihat di code: `int percentage = map(potValue, 0, 4095, 0, 100);`
- [ ] **Pertanyaan**: Apa fungsi `map()`?  
       Jawab: **************\_\_\_**************
- [ ] **Pertanyaan**: Kenapa range 0-4095 (bukan 0-255)?  
       Jawab: **************\_\_\_**************

---

## 💡 BAGIAN 3: Praktikum 2 - LED Dimmer dengan PWM

### **Step 1: Add LED ke Project**

- [ ] Keep pot dari praktikum 1
- [ ] Klik "+" → Add **LED**
- [ ] Add **Resistor 220Ω**

---

### **Step 2: Wiring LED**

- [ ] Click **ESP32 GPIO15**
- [ ] Drag ke **Resistor pin 1**
- [ ] Click **Resistor pin 2**
- [ ] Drag ke **LED anode** (kaki panjang / +)
- [ ] Click **LED cathode** (kaki pendek / -)
- [ ] Drag ke **ESP32 GND**

**Visual Check**:

- ✓ GPIO15 → Resistor → LED anode → LED cathode → GND
- ✓ Polaritas LED benar (panjang=anode, pendek=cathode)

---

### **Step 3: Understand PWM Concept**

- [ ] Baca materi PWM di pertemuan 3
- [ ] **Pertanyaan**: Apa itu Duty Cycle?  
       Jawab: **************\_\_\_**************
- [ ] **Pertanyaan**: Kenapa LED bisa redup dengan PWM (padahal digital cuma HIGH/LOW)?  
       Jawab: **************\_\_\_**************

**Key Concept**:

- Duty Cycle 0% = LED OFF (always LOW)
- Duty Cycle 50% = LED setengah terang (50% ON, 50% OFF sangat cepat)
- Duty Cycle 100% = LED MAX (always HIGH)

---

### **Step 4: Upload Code PWM Breathing**

- [ ] Copy code praktikum 2 (LED breathing effect)
- [ ] Paste ke Wokwi editor
- [ ] Code key check:
  ```cpp
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(LED_PIN, PWM_CHANNEL);
  ledcWrite(PWM_CHANNEL, brightness);
  ```

---

### **Step 5: Test PWM Breathing**

- [ ] Run simulation
- [ ] **Observe**: LED **fade in** (redup → terang) smooth
- [ ] **Observe**: LED **fade out** (terang → redup) smooth
- [ ] **Observe**: Pattern repeat (breathing effect)
- [ ] Serial Monitor: brightness value 0-255

**Pelajaran**: PWM memungkinkan kontrol brightness smooth (bukan hanya ON/OFF)!

---

### **Step 6: Understand LEDC Functions**

- [ ] **`ledcSetup(channel, freq, resolution)`**:  
       Fungsi: **************\_\_\_**************
- [ ] **`ledcAttachPin(pin, channel)`**:  
       Fungsi: **************\_\_\_**************
- [ ] **`ledcWrite(channel, value)`**:  
       Fungsi: **************\_\_\_**************

---

## 🎚️ BAGIAN 4: Praktikum 3 - Interactive LED Dimmer (PROJECT!)

### **Step 1: Buat Project Final**

- [ ] **Option A**: Gunakan project dari praktikum 1-2 (sudah ada pot + LED)
- [ ] **Option B**: Buat project baru
- [ ] Rename: `P03_LEDDimmer_[NIM]_[Nama]`

---

### **Step 2: Verify Wiring Complete**

**Checklist Wiring**:

- [ ] Potensiometer: VCC → 3V3, SIG → GPIO34, GND → GND
- [ ] LED: GPIO15 → Resistor → Anode → Cathode → GND
- [ ] Total 2 komponen + 1 resistor
- [ ] Semua wire terhubung (tidak ada yang lepas)

**Foto wiring** untuk dokumentasi!

---

### **Step 3: Upload Code Interactive Dimmer**

- [ ] Copy code `P03_Interactive_LED_Dimmer.ino`
- [ ] Paste ke Wokwi editor
- [ ] Code structure check:
  - [ ] `#define POT_PIN 34` ← pot input
  - [ ] `#define LED_PIN 15` ← LED output
  - [ ] `ledcSetup()` di setup()
  - [ ] `analogRead(POT_PIN)` di loop()
  - [ ] `map()` untuk scaling ADC → PWM
  - [ ] `ledcWrite()` untuk set brightness

---

### **Step 4: Understand Code Logic**

**Flow**:

```
1. Baca pot (ADC 0-4095)
   ↓
2. Scale ke PWM range (map 0-4095 → 0-255)
   ↓
3. Set LED brightness (ledcWrite)
   ↓
4. Print status di serial
   ↓
5. Loop (repeat 20× per detik)
```

- [ ] Pahami flow di atas
- [ ] **Pertanyaan**: Kenapa perlu `map()`? Kenapa tidak langsung `ledcWrite(potValue)`?  
       Jawab: **************\_\_\_**************

**Answer Hint**: ADC = 12-bit (0-4095), PWM 8-bit (0-255). Harus scaling!

---

### **Step 5: Run & Test Interactive Dimmer**

**Test Systematic**:

1. **Test Minimum (0%)**:
   - [ ] Drag pot ke **kiri penuh**
   - [ ] **Verify**: LED **OFF** atau **sangat redup**
   - [ ] Serial: Brightness ~0/255 (~0%)

2. **Test 25%**:
   - [ ] Drag pot ke **~25% dari kiri**
   - [ ] **Verify**: LED **redup** (faint)
   - [ ] Serial: Brightness ~64/255 (~25%)

3. **Test 50%**:
   - [ ] Drag pot ke **tengah**
   - [ ] **Verify**: LED **setengah terang** (medium)
   - [ ] Serial: Brightness ~128/255 (~50%)

4. **Test 75%**:
   - [ ] Drag pot ke **~75% dari kiri**
   - [ ] **Verify**: LED **terang** (bright)
   - [ ] Serial: Brightness ~192/255 (~75%)

5. **Test Maximum (100%)**:
   - [ ] Drag pot ke **kanan penuh**
   - [ ] **Verify**: LED **maksimal brightness**
   - [ ] Serial: Brightness ~255/255 (~100%)

---

### **Step 6: Test Real-Time Response**

- [ ] **Slowly** drag pot dari kiri ke kanan
- [ ] **Observe**: LED brightness berubah **smooth** mengikuti pot
- [ ] **Observe**: Tidak ada lag / delay signifikan
- [ ] **Quickly** drag pot bolak-balik
- [ ] **Verify**: LED tetap responsive (update cepat)

**Expected**: LED brightness EXACTLY follow pot position!

---

### **Step 7: Troubleshooting (Jika Ada Masalah)**

**Problem: Pot tidak berfungsi (LED tetap brightness sama)**

- [ ] Serial Monitor: apakah pot value berubah saat putar?
- [ ] Jika pot value TIDAK berubah → check wiring pot
- [ ] Jika pot value berubah tapi LED tidak → check `map()` & `ledcWrite()`

**Problem: LED tidak menyala sama sekali**

- [ ] Check wiring LED (GPIO → Resistor → Anode → Cathode → GND)
- [ ] Check polaritas (panjang=anode harus ke resistor)
- [ ] Check resistor terpasang (jangan skip!)
- [ ] Manual test: `ledcWrite(PWM_CHANNEL, 255)` di setup()

**Problem: LED brightness tidak smooth (berkedip)**

- [ ] Check PWM_FREQ di code (harus 5000 Hz, bukan 50 Hz!)
- [ ] Check delay() di loop (jangan terlalu besar, max 50ms)

---

### **Step 8: Save & Share Project**

- [ ] Klik **Save** 💾
- [ ] Project name: `P03_LEDDimmer_[NIM]_[Nama]`
- [ ] Klik **Share** 🔗
- [ ] Copy link
- [ ] **Test link** di browser incognito (PENTING!)
- [ ] Link bisa dibuka → ✅ OK untuk submission

---

## 📸 BAGIAN 5: Screenshot & Documentation

### **Screenshot Requirements**

- [ ] Screenshot **seluruh window Wokwi**
- [ ] **Wiring visible**: Pot + LED dengan resistor jelas
- [ ] **Simulation running**: LED menyala (brightness sedang, bukan OFF/MAX)
- [ ] **Pot position**: Di antara 25%-75% (untuk tunjukkan variasi)
- [ ] **Code editor**: Code visible (at least key parts)
- [ ] **Serial Monitor**: Output pot value & brightness visible
- [ ] Screenshot jelas, tidak blur
- [ ] Save: `P03_LEDDimmer_[NIM]_[Nama].png`

---

### **Video Demo (Highly Recommended!)**

- [ ] Screen recording (15-30 detik)
- [ ] Action: **Drag pot smooth dari 0% → 100%**
- [ ] Show: LED brightness berubah real-time
- [ ] (Optional) Voice narration: "Pot 0%, LED off. Pot 50%, LED medium. Pot 100%, LED max."
- [ ] Upload ke Google Drive / YouTube (unlisted)
- [ ] Copy link

**Why video important?**: Tunjukkan **real-time interaction** yang tidak bisa dari screenshot!

---

## 🌟 BAGIAN 6: Challenge (Opsional - Bonus!)

### **Challenge 1: Breathing LED dengan Variable Speed**

- [ ] Modifikasi code breathing (praktikum 2)
- [ ] **Pot kontrol speed**:
  - Pot 0% = breathing lambat (delay besar)
  - Pot 100% = breathing cepat (delay kecil)
- [ ] Formula: `int delayTime = map(potValue, 0, 4095, 50, 500);`
- [ ] Test & verify
- [ ] Screenshot & link

### **Challenge 2: Dual LED (Inverse Control)**

- [ ] Add LED kedua (GPIO16)
- [ ] Logic: Saat LED1 terang, LED2 redup (inverse)
- [ ] Code:
  ```cpp
  int brightness1 = map(potValue, 0, 4095, 0, 255);
  int brightness2 = 255 - brightness1;  // Inverse!
  ```
- [ ] Test & verify
- [ ] Screenshot & link

### **Challenge 3: LED dengan Threshold**

- [ ] LED hanya ON jika pot > 50%
- [ ] Pot < 50%: LED OFF
- [ ] Pot >= 50%: LED brightness sesuai pot (scaled)
- [ ] Code logic dengan `if-else`
- [ ] Test & verify
- [ ] Screenshot & link

---

## 📤 BAGIAN 7: Submission

### **Persiapan Submission**

- [ ] Buka `P03_Template_Submission.md`
- [ ] Isi informasi mahasiswa
- [ ] Paste screenshot
- [ ] Paste link Wokwi (verify valid!)
- [ ] Paste code lengkap
- [ ] Checklist wiring completed
- [ ] Checklist functionality completed
- [ ] Jawab 4 pertanyaan
- [ ] (Recommended) Include video demo
- [ ] (Optional) Include challenge

### **Quality Check**

- [ ] Screenshot jelas (all elements visible)
- [ ] Link Wokwi valid (test di incognito!)
- [ ] Code lengkap (tidak terpotong)
- [ ] Wiring & functionality checklist semua ✓
- [ ] Jawaban 4 pertanyaan masuk akal
- [ ] Video demo (jika ada) clear & tunjukkan interaction
- [ ] File name correct: `P03_[NIM]_[Nama].pdf/md`

### **Submit!**

- [ ] Upload ke platform (e-learning/GClassroom)
- [ ] Verify file ter-upload
- [ ] Submit **BEFORE DEADLINE**!
- [ ] Screenshot bukti submit (backup)

**DEADLINE**: **************\_\_\_**************

---

## 📊 Self-Assessment

| Kriteria                   | Score (1-10)  | Notes                   |
| -------------------------- | ------------- | ----------------------- |
| Pemahaman ADC & Analog I/O | \_\_\_\_ / 10 | Paham analogRead()?     |
| Pemahaman PWM & Duty Cycle | \_\_\_\_ / 10 | Paham ledcWrite()?      |
| Wiring skill (Pot + LED)   | \_\_\_\_ / 10 | Bisa wire dengan benar? |
| Troubleshooting            | \_\_\_\_ / 10 | Bisa debug error?       |
| Ketepatan waktu            | \_\_\_\_ / 10 | Submit on-time?         |

**Total**: \_\_\_\_ / 50

**Reflection**: Apa yang paling challenging?

```
_________________________________________________________________
_________________________________________________________________
```

**Most Useful Skill**: Apa yang paling berguna?

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

**Paraf**: ****\_\_**** **Tanggal**: ****\_\_****

---

**🎉 Selamat! Anda sudah menguasai Analog I/O & PWM!**

**Next**: Pertemuan 4 - Serial Communication & Debugging

---

**Checklist ini dibuat untuk**: Mata Kuliah Mikrokontroller - Prodi Informatika Unmul
