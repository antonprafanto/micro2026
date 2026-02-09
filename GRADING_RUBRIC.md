# 📊 Grading Rubric - Mata Kuliah Mikrokontroller ESP32

## Panduan Penilaian Detail untuk Dosen & Mahasiswa

---

## 📋 Ringkasan Komponen Penilaian

| Komponen                     | Bobot    | Keterangan                             |
| ---------------------------- | -------- | -------------------------------------- |
| **Praktikum (Deliverable)**  | 25%      | Pertemuan 1-7, 9-15                    |
| **UTS**                      | 20%      | Teori (40%) + Praktikum (60%)          |
| **Project Akhir**            | 40%      | Presentasi + Demo + Kode + Dokumentasi |
| **UAS Teori**                | 10%      | Essay questions                        |
| **Attitude & Participation** | 5%       | Kehadiran, diskusi, peer helping       |
| **TOTAL**                    | **100%** |                                        |

---

## 1️⃣ Praktikum / Lab Deliverable (25%)

### **Overview**:

- Total pertemuan dengan deliverable: **13 kali** (pertemuan 1-7, 9-15, skip UTS dan UAS)
- Bobot per deliverable: **25% / 13 = ~1.92% per praktikum**
- Deadline: **1 minggu setelah praktikum** (submit via e-learning/GitHub)

### **Rubrik Penilaian per Praktikum** (100 poin):

| Kriteria           | Excellent (90-100)                              | Good (75-89)                       | Fair (60-74)                     | Poor (<60)            | Bobot |
| ------------------ | ----------------------------------------------- | ---------------------------------- | -------------------------------- | --------------------- | ----- |
| **Functionality**  | Sistem bekerja sempurna sesuai requirement      | Sistem bekerja dengan minor bugs   | Sistem sebagian bekerja          | Sistem tidak bekerja  | 40%   |
| **Code Quality**   | Code clean, well-structured, fully commented    | Code readable, basic comments      | Code messy, minimal comments     | Code unreadable       | 25%   |
| **Wiring/Circuit** | Wiring rapi, sesuai best practice               | Wiring functional tapi kurang rapi | Wiring berantakan tapi bekerja   | Wiring salah          | 15%   |
| **Documentation**  | Video demo clear + screenshot + comment lengkap | Video/screenshot + comment basic   | Hanya video atau screenshot      | Tidak ada dokumentasi | 10%   |
| **Timeliness**     | Submit tepat waktu                              | Submit 1-3 hari terlambat (-10%)   | Submit 4-7 hari terlambat (-20%) | Submit >7 hari (-50%) | 10%   |

### **Submission Requirements**:

Setiap praktikum harus submit:

1. **Source Code** (.ino file)
   - Fully commented (Bahasa Indonesia OK)
   - Include wiring pinout di comments

   ```cpp
   /*
    * Praktikum 5: Monitoring Suhu DHT22
    *
    * Wiring:
    * - DHT22 VCC  -> 3.3V
    * - DHT22 Data -> GPIO 15
    * - DHT22 GND  -> GND
    * - LED Merah  -> GPIO 2 (via resistor 220Ω)
    */
   ```

2. **Video Demo** (format MP4, max 2 menit, max 50MB)
   - Tunjukkan sistem berfungsi
   - Narasi singkat (opsional)
   - Upload ke Google Drive/YouTube (unlisted)

3. **Circuit Diagram** (foto atau Fritzing)
   - Jelas dan readable
   - Label komponen

4. **Serial Monitor Screenshot** (jika applicable)
   - Tunjukkan output program

### **Late Submission Policy**:

- **1-3 hari terlambat**: -10%
- **4-7 hari terlambat**: -20%
- **>7 hari terlambat**: -50%
- **Tidak submit**: 0

### **Contoh Penilaian**:

**Mahasiswa A - Praktikum 5 (DHT22)**:

- Functionality: 95 (sistem perfect) × 40% = 38
- Code Quality: 85 (comments OK, bisa lebih clean) × 25% = 21.25
- Wiring: 90 (rapi dan benar) × 15% = 13.5
- Documentation: 80 (video OK, tapi screenshot kurang) × 10% = 8
- Timeliness: 100 (tepat waktu) × 10% = 10
- **Total**: 90.75 → **A**

---

## 2️⃣ UTS - Ujian Tengah Semester (20%)

### **Format**:

- **Durasi**: 100 menit
- **Materi**: Pertemuan 1-7

### **A. Teori (40% dari UTS = 8% dari total)**

#### **Tipe Soal**:

1. **Multiple Choice** (20 soal × 1.5 poin = 30 poin)
   - Konsep embedded systems
   - ESP32 architecture
   - GPIO, PWM, ADC
   - I2C protocol
   - Sensor basics

2. **Essay** (2 soal × 20 poin = 40 poin)
   - Analisis circuit
   - Debugging scenario
   - Design challenge

3. **Short Answer** (10 soal × 3 poin = 30 poin)
   - Code snippets
   - Calculation (resistor, voltage divider)

**Total Teori**: 100 poin

#### **Rubrik Essay** (per soal 20 poin):

| Kriteria                         | Poin |
| -------------------------------- | ---- |
| Pemahaman konsep benar & lengkap | 8    |
| Analisis mendalam & reasoning    | 6    |
| Solusi praktis & implementable   | 4    |
| Penulisan jelas & terstruktur    | 2    |

**Contoh Soal Essay**:

> "Anda ingin membuat sistem parking sensor dengan HC-SR04. Namun, LED indikator tidak menyala meskipun serial monitor menunjukkan jarak dengan benar. Analisis kemungkinan penyebab dan solusinya!" (20 poin)

**Jawaban Ideal**:

- Kemungkinan 1: LED polaritas terbalik (analisis + solusi = 5 poin)
- Kemungkinan 2: Resistor tidak terpasang/nilai terlalu besar (5 poin)
- Kemungkinan 3: GPIO pin tidak di-set sebagai OUTPUT (5 poin)
- Kemungkinan 4: GPIO pin bentrok dengan fungsi lain (3 poin)
- Cara debug: multimeter, swap LED, check code (2 poin)

---

### **B. Praktikum UTS (60% dari UTS = 12% dari total)**

#### **Format**:

- **Durasi**: 60 menit
- **Open Documentation**: Boleh akses Arduino reference, library docs
- **No Internet** kecuali docs.arduino.cc
- **Individual Work**

#### **Contoh Task**:

> "Buat sistem monitoring ruangan dengan requirement:
>
> 1. DHT22 untuk suhu & kelembaban
> 2. LED indikator: Hijau (suhu normal <28°C), Merah (suhu tinggi ≥28°C)
> 3. OLED menampilkan suhu, kelembaban, dan status
> 4. Data dikirim ke serial monitor setiap 3 detik
> 5. Button untuk toggle display ON/OFF (power saving)"

#### **Rubrik Praktikum UTS** (100 poin):

| Kriteria                | Detail                                      | Poin |
| ----------------------- | ------------------------------------------- | ---- |
| **Sensor Reading**      | DHT22 dibaca dengan benar                   | 15   |
| **LED Indicator Logic** | LED berubah sesuai threshold                | 15   |
| **OLED Display**        | Menampilkan semua data dengan benar         | 20   |
| **Serial Output**       | Data terkirim setiap 3s dengan format benar | 10   |
| **Button Toggle**       | Display ON/OFF berfungsi                    | 15   |
| **Wiring**              | Circuit benar dan rapi                      | 10   |
| **Code Quality**        | Well-structured, no redundancy              | 10   |
| **Error Handling**      | Handle sensor error (isnan check)           | 5    |

**Grading**:

- **90-100**: A (sistem sempurna, semua fitur jalan, code clean)
- **75-89**: B (sistem jalan, ada minor bugs atau 1 fitur tidak jalan)
- **60-74**: C (sistem sebagian jalan, 2+ fitur tidak jalan)
- **<60**: D/E (sistem tidak bekerja atau requirement tidak terpenuhi)

---

## 3️⃣ Project Akhir (40%)

### **Overview**:

- **Kelompok**: 2-3 mahasiswa
- **Timeline**:
  - Minggu 10: Proposal submit
  - Minggu 15: Progress check (workshop)
  - Minggu 16: Final presentation & demo
- **Tema**: Bebas (Smart Home, Agriculture, Health, Automation, dll)

### **Minimum Requirements**:

1. Min **3 sensor/input** (DHT22, HC-SR04, button, PIR, dll)
2. Min **2 aktuator/output** (LED, buzzer, relay, motor, display)
3. **Komunikasi wireless**: WiFi, Bluetooth, atau MQTT
4. **Data logging/cloud**: ThingSpeak, Firebase, atau SPIFFS
5. **User interface**: Web dashboard, mobile app, atau OLED
6. **Security consideration**: Password, API key management, HTTPS

### **Rubrik Penilaian Project Akhir** (100 poin):

#### **A. Functionality (35 poin)**

| Kriteria             | Excellent (30-35)                      | Good (24-29)                          | Fair (18-23)                  | Poor (<18)            |
| -------------------- | -------------------------------------- | ------------------------------------- | ----------------------------- | --------------------- |
| Sistem bekerja       | 100% fitur berfungsi perfect           | 80-99% fitur bekerja                  | 60-79% fitur bekerja          | <60% fitur bekerja    |
| Reliability          | Stabil, no crash, error handling bagus | Occasional bugs, basic error handling | Sering error tapi recoverable | Frequent crashes      |
| Real-world usability | Siap pakai untuk real use case         | Butuh minor improvement               | Prototype level               | Proof-of-concept saja |

**Penilaian**:

- Semua requirement terpenuhi + stable = 35
- Semua requirement terpenuhi + minor bugs = 30-34
- 1-2 requirement tidak terpenuhi = 24-29
- 3+ requirement tidak terpenuhi = <24

---

#### **B. Complexity & Integration (25 poin)**

| Kriteria                                                                                   | Poin     |
| ------------------------------------------------------------------------------------------ | -------- |
| **Jumlah Komponen**: 3-4 komponen (15 poin), 5-6 komponen (20 poin), 7+ komponen (25 poin) | 0-25     |
| **Integration Quality**: Komponen saling terintegrasi dengan baik (bukan berdiri sendiri)  | Bonus +5 |
| **Advanced Features**: OTA update, multi-threading, BLE, encryption, dll                   | Bonus +5 |

**Contoh**:

- Project dengan 5 sensor + 3 aktuator + integrasi cloud + mobile app = **25 poin**
- Project dengan 3 sensor + 1 LED + serial monitor only = **15 poin**

---

#### **C. Code Quality (15 poin)**

| Kriteria                                                           | Poin |
| ------------------------------------------------------------------ | ---- |
| **Structure**: Modular (functions, tidak semua di loop), organized | 5    |
| **Comments**: Fully commented, explain logic, wiring               | 4    |
| **Naming**: Variable & function names descriptive                  | 2    |
| **No Hardcode**: Credentials di config file terpisah               | 2    |
| **Efficiency**: No unnecessary delay, optimized logic              | 2    |

**Deducted if**:

- Semua code di `loop()` tanpa fungsi: -3
- Tidak ada comment: -4
- Hardcode WiFi password di main code: -2

---

#### **D. Presentation & Demo (10 poin)**

| Kriteria                                                             | Poin |
| -------------------------------------------------------------------- | ---- |
| **Slide Quality**: Jelas, visual menarik, tidak terlalu banyak teks  | 2    |
| **Communication**: Jelas, percaya diri, semua anggota berpartisipasi | 3    |
| **Live Demo**: Smooth, no technical issue, explain while demo        | 4    |
| **Q&A**: Bisa jawab pertanyaan dengan baik                           | 1    |

**Tips**:

- Latihan demo sebelum presentasi!
- Siapkan video backup jika live demo gagal
- Explain "why" bukan hanya "what"

---

#### **E. Documentation (10 poin)**

| Item                                                                               | Poin |
| ---------------------------------------------------------------------------------- | ---- |
| **README.md** lengkap: project description, features, setup instruction            | 3    |
| **Circuit Diagram**: Fritzing atau foto wiring yang jelas                          | 2    |
| **Video Demo**: Uploaded di YouTube, 3-5 menit, narasi clear                       | 2    |
| **Code Comments**: In-code documentation                                           | 2    |
| **Project Report** (max 10 halaman): introduction, methodology, result, conclusion | 1    |

**README.md Template**:

```markdown
# Smart Home Monitoring System

## Description

Sistem monitoring dan kontrol smart home dengan ESP32...

## Features

- Real-time temperature & humidity monitoring
- Motion detection with PIR sensor
- LED & buzzer alarm
- Web dashboard for remote control
- Data logging to ThingSpeak

## Hardware Requirements

- ESP32
- DHT22
- PIR sensor
- ...

## Setup Instructions

1. Install Arduino IDE...
2. Install libraries: ...
3. Upload code...
4. Access web dashboard at http://192.168.1.xxx

## Circuit Diagram

![Circuit](circuit_diagram.png)

## Video Demo

[Watch Demo](https://youtube.com/...)

## Team

- Member 1 (NIM)
- Member 2 (NIM)
```

---

#### **F. Innovation & Creativity (5 poin)**

| Kriteria                                                                        | Poin |
| ------------------------------------------------------------------------------- | ---- |
| **Problem Solving**: Menyelesaikan real-world problem dengan kreatif            | 2    |
| **Unique Feature**: Fitur yang tidak diajarkan di kelas tapi dipelajari mandiri | 2    |
| **UI/UX**: Interface (web/mobile) menarik dan user-friendly                     | 1    |

**Bonus Poin**:

- Menggunakan machine learning / AI: +5
- PCB custom design (bukan breadboard): +3
- Mobile app native (Flutter/React Native): +3
- Battery-powered dengan power optimization: +2

---

### **Total Calculation Example**:

**Project: Smart Agriculture Monitoring**

- Functionality: 33 (semua fitur jalan, stabil)
- Complexity: 25 (6 sensor, integrasi cloud, mobile app)
- Code Quality: 13 (terstruktur baik, fully commented, ada hardcode password)
- Presentation: 9 (demo smooth, slide OK, Q&A bagus)
- Documentation: 9 (README lengkap, video OK, circuit kurang detail)
- Innovation: 5 (unique soil moisture prediction feature)
- Bonus: +3 (mobile app Flutter)

**Total: 33 + 25 + 13 + 9 + 9 + 5 + 3 = 97 → A** 🎉

---

## 4️⃣ UAS Teori (10%)

### **Format**:

- **Durasi**: 30 menit (setelah presentasi project)
- **Tipe**: Essay & Analysis
- **Materi**: Keseluruhan (pertemuan 1-15)

### **Contoh Soal**:

**Soal 1 (5 poin)**:

> "Jelaskan perbedaan MQTT dan HTTP untuk IoT, dan kapan sebaiknya menggunakan masing-masing!"

**Rubrik**:

- Penjelasan MQTT (pub-sub, lightweight, persistent connection): 2 poin
- Penjelasan HTTP (request-response, stateless): 1 poin
- Use case yang tepat (MQTT untuk real-time sensor network, HTTP untuk REST API): 2 poin

**Soal 2 (5 poin)**:

> "Sistem IoT Anda di-deploy di lokasi remote dan tidak bisa diakses secara fisik. Sebutkan dan jelaskan 3 strategi untuk maintenance dan troubleshooting!"

**Rubrik**:

- OTA update untuk firmware patch: 2 poin
- Remote monitoring via cloud dashboard: 1.5 poin
- Logging & alert system: 1.5 poin
- Bonus: Watchdog timer, fallback mode, remote reboot: +1

---

## 5️⃣ Attitude & Participation (5%)

### **Kriteria**:

| Aspek                   | Poin | Keterangan                                   |
| ----------------------- | ---- | -------------------------------------------- |
| **Kehadiran**           | 2%   | Min 75% kehadiran untuk dapat nilai          |
| **Partisipasi Diskusi** | 1.5% | Aktif bertanya, menjawab, membantu teman     |
| **Peer Helping**        | 1%   | Membantu teman troubleshoot, share knowledge |
| **Lab Etiquette**       | 0.5% | Workspace bersih, equipment terawat, on-time |

### **Attendance Points**:

- 100% hadir: 2%
- 90-99% hadir: 1.8%
- 75-89% hadir: 1.5%
- <75% hadir: 0% (dan bisa tidak berhak ikut UAS sesuai aturan kampus)

### **Participation**:

Dosen observe selama semester:

- Sering bertanya konseptual (bukan hanya "kok error?"): +0.5
- Membantu teman tanpa diminta: +0.5
- Share resources/tutorial di grup kelas: +0.3
- Active dalam diskusi online (forum/Discord): +0.2

---

## 📊 Final Grade Calculation

### **Example - Mahasiswa X**:

| Komponen      | Skor | Bobot    | Kontribusi     |
| ------------- | ---- | -------- | -------------- |
| Praktikum     | 85   | 25%      | 21.25          |
| UTS Teori     | 78   | 8%       | 6.24           |
| UTS Praktikum | 92   | 12%      | 11.04          |
| Project Akhir | 88   | 40%      | 35.2           |
| UAS Teori     | 82   | 10%      | 8.2            |
| Attitude      | 95   | 5%       | 4.75           |
| **TOTAL**     |      | **100%** | **86.68 → AB** |

### **Grading Scale**:

- **A**: 85-100
- **AB**: 80-84
- **B**: 75-79
- **BC**: 70-74
- **C**: 65-69
- **D**: 55-64
- **E**: <55

---

## 🎯 Tips Mendapat Nilai Terbaik

### **Untuk Mahasiswa**:

1. **Jangan Skip Praktikum**: 25% dari nilai total, tiap pertemuan penting!
2. **Document Everything**: Foto wiring, video demo, buat sejak awal
3. **Start Project Early**: Jangan tunggu minggu 15!
4. **Ask Questions**: Dosen menilai partisipasi, jangan malu bertanya
5. **Code Clean**: Bukan hanya jalan, tapi juga readable dan maintainable
6. **Test Incrementally**: Jangan langsung buat sistem kompleks, step by step
7. **Collaborate**: Peer helping dikasih poin bonus!

### **Untuk Dosen**:

1. **Transparency**: Share rubrik ini di awal semester
2. **Consistent**: Gunakan rubrik yang sama untuk semua mahasiswa
3. **Feedback**: Berikan feedback untuk deliverable (tidak hanya angka)
4. **Flexibility**: Beri kesempatan resubmit untuk deliverable dengan nilai <60
5. **Encourage**: Appreciate effort, bukan hanya result

---

## 📝 Resubmission Policy

### **Praktikum Deliverable**:

- Nilai <60: boleh **resubmit 1x** (max nilai 75)
- Deadline resubmit: Sebelum UAS
- Harus show improvement yang signifikan

### **Project Akhir**:

- Tidak ada resubmit (final presentation adalah final)
- Tapi ada **progress check** minggu 15 untuk feedback

---

## ❓ FAQ

**Q: Jika sakit dan tidak bisa hadir praktikum, bagaimana?**  
A: Submit surat sakit/izin, deadline deliverable tetap 1 minggu. Jika ada alasan valid, extension bisa diberikan.

**Q: Boleh kerjasama untuk praktikum deliverable?**  
A: Boleh diskusi konsep, tapi code dan wiring harus individual. Copy-paste code = plagiarism.

**Q: Project akhir boleh topik sama dengan kelompok lain?**  
A: Boleh, tapi implementation harus berbeda. Akan dinilai dari kreativitas dan fitur unik.

**Q: Jika komponen rusak saat praktikum, nilai saya bagaimana?**  
A: Lapor ke dosen segera. Jika bukan kesalahan Anda, akan diberi komponen baru dan extension.

**Q: Nilai praktikum bagus tapi UTS jelek, bisa lulus?**  
A: Bisa, selama total akhir ≥65 (grade C). Tapi usahakan balance.

---

**Terakhir diupdate**: Februari 2026  
**Untuk**: Mata Kuliah Mikrokontroller - Prodi Informatika Unmul  
**Dosen Pengampu**: [Nama Dosen]
