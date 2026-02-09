# Materi Mikrokontroller ESP32

## Prodi Informatika - Universitas Mulawarman

> Repository materi pembelajaran praktikum mikrokontroller menggunakan ESP32 dan Arduino IDE

---

## 📚 Daftar Pertemuan

### ✅ Pertemuan 1: Pengenalan ESP32 & Lab Safety

**Topik**: Embedded systems basics, ESP32 architecture, Wokwi simulator, Blink LED onboard

**Materi**:

- 📖 [Pertemuan-01-Pengenalan-ESP32.md](materi/Pertemuan-01-Pengenalan-ESP32.md) - Materi lengkap teori & praktikum

**Code**:

- 💻 [P01_Blink_LED_Dasar.ino](materi/code/P01_Blink_LED_Dasar.ino) - Template blink LED onboard
- 🌟 [P01_Challenge_SOS_Morse.ino](materi/code/P01_Challenge_SOS_Morse.ino) - Challenge: SOS Morse code

**Dokumen Pendukung**:

- ✅ [P01_Checklist_Mahasiswa.md](materi/P01_Checklist_Mahasiswa.md) - Step-by-step checklist praktikum
- 📝 [P01_Template_Submission.md](materi/P01_Template_Submission.md) - Template submission deliverable

**Deliverable**: Screenshot Wokwi + Link project Blink LED

---

### ✅ Pertemuan 2: Digital I/O & Breadboard Basics

**Topik**: GPIO, pinMode(), digitalWrite(), digitalRead(), Pull-up resistor, Multiple LED control

**Materi**:

- 📖 [Pertemuan-02-Digital-IO-Breadboard.md](materi/Pertemuan-02-Digital-IO-Breadboard.md) - Materi lengkap teori & praktikum

**Code**:

- 💻 [P02_Traffic_Light_Simulation.ino](materi/code/P02_Traffic_Light_Simulation.ino) - Project: Traffic light simulator
- 🌟 [P02_Challenge_Pedestrian_Button.ino](materi/code/P02_Challenge_Pedestrian_Button.ino) - Challenge: Pedestrian crossing button

**Dokumen Pendukung**:

- ✅ [P02_Checklist_Mahasiswa.md](materi/P02_Checklist_Mahasiswa.md) - Step-by-step checklist praktikum
- 📝 [P02_Template_Submission.md](materi/P02_Template_Submission.md) - Template submission deliverable

**Deliverable**: Screenshot Wokwi + Link project Traffic Light

---

### ✅ Pertemuan 3: Analog I/O & PWM

**Topik**: ADC, analogRead(), PWM, LEDC, Duty cycle, Potensiometer, LED brightness control

**Materi**:

- 📖 [Pertemuan-03-Analog-IO-PWM.md](materi/Pertemuan-03-Analog-IO-PWM.md) - Materi lengkap teori & praktikum

**Code**:

- 💻 [P03_Interactive_LED_Dimmer.ino](materi/code/P03_Interactive_LED_Dimmer.ino) - Project: Interactive LED dimmer dengan potensiometer

**Dokumen Pendukung**:

- ✅ [P03_Checklist_Mahasiswa.md](materi/P03_Checklist_Mahasiswa.md) - Step-by-step checklist praktikum
- 📝 [P03_Template_Submission.md](materi/P03_Template_Submission.md) - Template submission deliverable

**Deliverable**: Screenshot Wokwi + Link project LED Dimmer + Video demo

---

### 🔜 Pertemuan 4-16: Coming Soon...

---

## 📂 Struktur Repository

```
micro2026/
├── README.md                          # File ini - Overview materi
├── KURIKULUM_MIKROKONTROLLER_ESP32_REVISED.md  # Kurikulum lengkap 16 pertemuan
├── LAB_SAFETY_GUIDE.md                # Panduan keselamatan lab elektronika
├── GRADING_RUBRIC.md                  # Rubrik penilaian
├── PROJECT_IDEAS.md                   # 20+ ide project final
├── BUDGET_AND_KIT_GUIDE.md            # Panduan budget & komponen
└── materi/
    ├── ESP32_Pinout_Reference.md      # Referensi pinout ESP32
    │
    ├── Pertemuan-01-Pengenalan-ESP32.md
    ├── Pertemuan-02-Digital-IO-Breadboard.md
    ├── Pertemuan-03-Analog-IO-PWM.md
    │
    ├── P01_Checklist_Mahasiswa.md
    ├── P01_Template_Submission.md
    ├── P02_Checklist_Mahasiswa.md
    ├── P02_Template_Submission.md
    ├── P03_Checklist_Mahasiswa.md
    ├── P03_Template_Submission.md
    │
    └── code/
        ├── P01_Blink_LED_Dasar.ino
        ├── P01_Challenge_SOS_Morse.ino
        ├── P02_Traffic_Light_Simulation.ino
        ├── P02_Challenge_Pedestrian_Button.ino
        └── P03_Interactive_LED_Dimmer.ino
```

---

## 🎯 Cara Menggunakan Repository Ini

### **Untuk Mahasiswa**:

1. **Baca Materi Pertemuan** (`Pertemuan-XX-....md`)
   - Pelajari teori sebelum praktikum
   - Pahami konsep sebelum coding

2. **Gunakan Checklist** (`PXX_Checklist_Mahasiswa.md`)
   - Print checklist dan centang setiap step
   - Follow step-by-step saat praktikum
   - Troubleshooting guide tersedia

3. **Copy Code Template** (`code/PXX_....ino`)
   - Buka file `.ino` di Arduino IDE atau Wokwi
   - Pelajari comment di code
   - Modifikasi sesuai kebutuhan

4. **Submit dengan Template** (`PXX_Template_Submission.md`)
   - Isi template submission
   - Screenshot Wokwi + Link project
   - Jawab pertanyaan pemahaman

### **Untuk Dosen/Asisten**:

1. Gunakan materi pertemuan sebagai slide guide
2. Checklist mahasiswa bisa dicetak untuk guided lab
3. Template submission untuk standardisasi penilaian
4. Grading rubric ada di `GRADING_RUBRIC.md`

---

## 🛠️ Tools & Platform

- **Simulator**: [Wokwi](https://wokwi.com) - ESP32 online simulator (FREE!)
- **IDE**: Arduino IDE 2.x atau Wokwi web editor
- **Hardware**: ESP32 DevKit V1 (untuk praktikum fisik - opsional)

---

## 📊 Progress Materi

| Pertemuan             | Status         | Materi | Code | Checklist | Template |
| --------------------- | -------------- | ------ | ---- | --------- | -------- |
| P01: ESP32 Basics     | ✅ Complete    | ✅     | ✅   | ✅        | ✅       |
| P02: Digital I/O      | ✅ Complete    | ✅     | ✅   | ✅        | ✅       |
| P03: Analog I/O & PWM | ✅ Complete    | ✅     | ✅   | ✅        | ✅       |
| P04-P16               | 🔜 Coming Soon | ⏳     | ⏳   | ⏳        | ⏳       |

**Progress**: 3/16 pertemuan (18.75%)

---

## 🎓 Topik yang Sudah Dicakup

✅ Embedded systems & ESP32 architecture  
✅ Wokwi simulator basics  
✅ Digital I/O (GPIO, pinMode, digitalWrite, digitalRead)  
✅ Pull-up resistor & debouncing  
✅ Multiple LED control (traffic light)  
✅ Analog I/O (ADC 12-bit)  
✅ PWM/LEDC (LED brightness control)  
✅ Potensiometer sensor reading

---

## 🔜 Topik Mendatang (Planned)

⏳ Serial Communication & Debugging  
⏳ WiFi Basics (AP Mode, STA Mode)  
⏳ Web Server & REST API  
⏳ Sensor Integration (DHT22, HC-SR04, PIR)  
⏳ OLED Display  
⏳ Bluetooth & BLE  
⏳ MQTT Protocol  
⏳ Cloud Integration (ThingSpeak)  
⏳ Final Project

---

## 📞 Kontak & Support

- **Repository**: [github.com/antonprafanto/micro2026](https://github.com/antonprafanto/micro2026)
- **Issues**: Gunakan GitHub Issues untuk bug report atau request materi
- **Dosen**: [Sesuaikan dengan info dosen]

---

## 📜 License

Materi ini dibuat untuk keperluan pendidikan di Prodi Informatika, Universitas Mulawarman.

---

## 🙏 Acknowledgments

- **Espressif Systems** - ESP32 documentation
- **Wokwi** - Amazing online simulator
- **Random Nerd Tutorials** - ESP32 reference
- **Arduino Community** - Code examples & libraries

---

<div align="center">

**Selamat Belajar!** 🚀

_"From Blink to IoT, One Step at a Time"_

</div>
