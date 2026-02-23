# 🤖 Mikrokontroller ESP32 — Prodi Informatika Unmul

> Repository materi dan kode praktikum Mata Kuliah Mikrokontroller berbasis ESP32 + Wokwi Simulator.

---

## 📚 Daftar Pertemuan

| #     | Topik                            | Folder                               | Status         |
| ----- | -------------------------------- | ------------------------------------ | -------------- |
| 01    | Pengenalan ESP32 & GPIO          | [Pertemuan-01](materi/Pertemuan-01/) | ✅ Selesai     |
| 02    | Digital I/O & Breadboard         | [Pertemuan-02](materi/Pertemuan-02/) | ✅ Selesai     |
| 03    | Analog I/O & PWM                 | [Pertemuan-03](materi/Pertemuan-03/) | ✅ Selesai     |
| 04    | Serial Communication & Debugging | [Pertemuan-04](materi/Pertemuan-04/) | ✅ Selesai     |
| 05–16 | Sensor, WiFi, MQTT, IoT, dst.    | —                                    | 🔜 Coming Soon |

> 📂 **[Lihat semua materi →](materi/README.md)**

---

## 📁 Struktur Repository

```
micro2026/
├── README.md                           ← File ini
├── KURIKULUM_MIKROKONTROLLER_ESP32_REVISED.md
├── GRADING_RUBRIC.md
├── LAB_SAFETY_GUIDE.md
├── PROJECT_IDEAS.md
├── BUDGET_AND_KIT_GUIDE.md
└── materi/
    ├── README.md                       ← Index navigasi semua pertemuan
    ├── resources/
    │   └── ESP32_Pinout_Reference.md
    ├── Pertemuan-01/
    │   ├── Pertemuan-01-Pengenalan-ESP32.md
    │   ├── P01_Checklist_Mahasiswa.md
    │   ├── P01_Template_Submission.md
    │   └── code/
    │       ├── P01_Blink_LED_Dasar.ino
    │       └── P01_Challenge_SOS_Morse.ino
    ├── Pertemuan-02/
    │   ├── Pertemuan-02-Digital-IO-Breadboard.md
    │   ├── P02_Checklist_Mahasiswa.md
    │   ├── P02_Template_Submission.md
    │   └── code/
    │       ├── P02_Traffic_Light_Simulation.ino
    │       └── P02_Challenge_Pedestrian_Button.ino
    ├── Pertemuan-03/
    │   ├── Pertemuan-03-Analog-IO-PWM.md
    │   ├── P03_Checklist_Mahasiswa.md
    │   ├── P03_Template_Submission.md
    │   └── code/
    │       └── P03_Interactive_LED_Dimmer.ino
    └── Pertemuan-04/
        ├── Pertemuan-04-Serial-Communication-Debugging.md
        ├── P04_Checklist_Mahasiswa.md
        ├── P04_Template_Submission.md
        └── code/
            ├── P04_SerialMenu.ino
            └── P04_Challenge_AutoRead.ino
```

---

## 🎯 Cara Penggunaan

### Untuk Mahasiswa:

1. **Buka folder Pertemuan** sesuai jadwal → klik `Pertemuan-0X/`
2. **Baca materi** `Pertemuan-0X-....md` sebelum kelas
3. **Ikuti checklist** `P0X_Checklist_Mahasiswa.md` saat praktikum
4. **Copy code** dari subfolder `code/` ke Wokwi
5. **Submit** menggunakan `P0X_Template_Submission.md`

### Untuk Dosen / Asisten:

- Gunakan materi sebagai panduan slide/ceramah
- Checklist bisa dicetak untuk guided lab
- Rubik penilaian: [`GRADING_RUBRIC.md`](GRADING_RUBRIC.md)

---

## 🛠️ Tools

| Tool                | Kegunaan                               | Link                                                                    |
| ------------------- | -------------------------------------- | ----------------------------------------------------------------------- |
| **Wokwi**           | ESP32 simulator online (gratis!)       | [wokwi.com](https://wokwi.com)                                          |
| **Arduino IDE 2.x** | IDE untuk compile & upload ke hardware | [arduino.cc](https://www.arduino.cc/en/software)                        |
| **ESP32 Pinout**    | Referensi pin GPIO ESP32               | [ESP32_Pinout_Reference.md](materi/resources/ESP32_Pinout_Reference.md) |

---

## 📊 Progress

| Pertemuan | Topik                | Materi | Code | Docs |
| --------- | -------------------- | ------ | ---- | ---- |
| P01       | ESP32 & GPIO Basics  | ✅     | ✅   | ✅   |
| P02       | Digital I/O          | ✅     | ✅   | ✅   |
| P03       | Analog I/O & PWM     | ✅     | ✅   | ✅   |
| P04       | Serial Communication | ✅     | ✅   | ✅   |
| P05–P16   | —                    | ⏳     | ⏳   | ⏳   |

**4 / 16 pertemuan selesai (25%)**

---

## 📜 Topik yang Sudah Dicakup

✅ ESP32 architecture & Wokwi simulator  
✅ Digital I/O — `pinMode()`, `digitalWrite()`, `digitalRead()`  
✅ Pull-up resistor, debouncing, multiple LED  
✅ Analog I/O — `analogRead()`, ADC 12-bit  
✅ PWM — `ledcAttach()`, `ledcWrite()`, duty cycle  
✅ Serial communication — `Serial.print()`, `Serial.printf()`  
✅ Serial input parsing — `readStringUntil()`, `parseInt()`  
✅ Debugging dengan Serial print  
✅ Interactive serial menu

## 🔜 Topik Mendatang

⏳ Sensor DHT22 (suhu & kelembaban)  
⏳ Sensor jarak HC-SR04  
⏳ OLED Display (I2C)  
⏳ WiFi — AP Mode & STA Mode  
⏳ Web Server & REST API  
⏳ Bluetooth & BLE  
⏳ MQTT & Cloud IoT  
⏳ Final Project

---

## 📞 Kontak

- **Repository**: [github.com/antonprafanto/micro2026](https://github.com/antonprafanto/micro2026)
- **Issues**: Gunakan GitHub Issues untuk pertanyaan atau laporan bug

---

<div align="center">

**Selamat Belajar!** 🚀

_"From Blink to IoT — One Step at a Time"_

**Mata Kuliah Mikrokontroller | Prodi Informatika | Universitas Mulawarman**

</div>
