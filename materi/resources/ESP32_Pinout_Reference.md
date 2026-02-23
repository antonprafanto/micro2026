# 📍 ESP32 Pinout Reference & Diagram

## Quick Reference untuk Mahasiswa

---

## 🔗 Pinout Diagram Visual

Untuk pinout diagram visual lengkap dengan gambar, lihat referensi berikut:

### **1. Random Nerd Tutorials - ESP32 Pinout Reference** (RECOMMENDED)

**Link**: [https://randomnerdtutorials.com/esp32-pinout-reference-gpios/](https://randomnerdtutorials.com/esp32-pinout-reference-gpios/)

**Isi**:

- ✅ Pinout diagram lengkap ESP32 DevKit V1
- ✅ Penjelasan setiap pin (ADC, Touch, PWM, dll)
- ✅ Pin yang aman vs pin yang harus dihindari
- ✅ Contoh wiring untuk sensor

**Action**: **PRINT** dan tempelkan di meja belajar Anda!

---

### **2. Wokwi Docs - ESP32 DevKit V1**

**Link**: [https://docs.wokwi.com/parts/wokwi-esp32-devkit-v1](https://docs.wokwi.com/parts/wokwi-esp32-devkit-v1)

**Isi**:

- ✅ Interactive pinout di Wokwi simulator
- ✅ Hover mouse untuk lihat pin labels
- ✅ Contoh wiring di simulator

---

### **3. ESP32 Official Datasheet**

**Link**: [https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)

**Isi**:

- ✅ Spesifikasi teknis lengkap
- ✅ Electrical characteristics
- ✅ Untuk yang ingin deep dive

---

## 📋 Pin Summary Table

### **Power Pins**

| Pin     | Voltage | Fungsi       | Catatan                                   |
| ------- | ------- | ------------ | ----------------------------------------- |
| **3V3** | 3.3V    | Output power | Max 600mA (untuk sensor)                  |
| **VIN** | 5V      | Input/Output | Input dari USB atau output 5V             |
| **GND** | 0V      | Ground       | Common ground untuk semua komponen        |
| **EN**  | 3.3V    | Enable/Reset | Pull HIGH untuk enable, LOW untuk disable |

---

### **GPIO yang Aman Dipakai** (Recommended)

| Pin        | Fungsi Alternatif           | Use Case                       |
| ---------- | --------------------------- | ------------------------------ |
| **GPIO2**  | LED_BUILTIN, ADC2_2, TOUCH2 | LED, Touch sensor              |
| **GPIO4**  | ADC2_0, TOUCH0              | General GPIO, sensor digital   |
| **GPIO5**  | VSPI_SS                     | General GPIO, SPI              |
| **GPIO12** | ADC2_5, TOUCH5, HSPI_MISO   | Input (hati-hati saat boot!)   |
| **GPIO13** | ADC2_4, TOUCH4, HSPI_MOSI   | General GPIO                   |
| **GPIO14** | ADC2_6, TOUCH6, HSPI_SCK    | General GPIO                   |
| **GPIO15** | ADC2_3, TOUCH3, HSPI_SS     | General GPIO (recommended)     |
| **GPIO16** | UART2_RX                    | General GPIO, UART             |
| **GPIO17** | UART2_TX                    | General GPIO, UART             |
| **GPIO18** | VSPI_SCK                    | General GPIO, SPI clock        |
| **GPIO19** | VSPI_MISO                   | General GPIO, SPI              |
| **GPIO21** | **I2C_SDA**                 | OLED, sensor I2C (default SDA) |
| **GPIO22** | **I2C_SCL**                 | OLED, sensor I2C (default SCL) |
| **GPIO23** | VSPI_MOSI                   | General GPIO, SPI              |
| **GPIO25** | ADC2_8, DAC1                | Analog output (DAC)            |
| **GPIO26** | ADC2_9, DAC2                | Analog output (DAC)            |
| **GPIO27** | ADC2_7, TOUCH7              | General GPIO                   |
| **GPIO32** | ADC1_4, TOUCH9              | Analog input (ADC)             |
| **GPIO33** | ADC1_5, TOUCH8              | Analog input (ADC)             |

---

### **GPIO Input-Only** (ADC1)

| Pin             | Fungsi | Catatan                     |
| --------------- | ------ | --------------------------- |
| **GPIO34**      | ADC1_6 | Input only, no pull-up/down |
| **GPIO35**      | ADC1_7 | Input only, no pull-up/down |
| **GPIO36 (VP)** | ADC1_0 | Input only, no pull-up/down |
| **GPIO39 (VN)** | ADC1_3 | Input only, no pull-up/down |

**Use case**: Sensor analog (potensiometer, LDR, soil moisture)

---

### **GPIO yang HARUS DIHINDARI** ⚠️

| Pin          | Alasan             | Konsekuensi                                                |
| ------------ | ------------------ | ---------------------------------------------------------- |
| **GPIO0**    | BOOT button        | Harus HIGH saat boot, LOW = programming mode               |
| **GPIO1**    | TX0 (Serial debug) | Digunakan untuk USB serial                                 |
| **GPIO3**    | RX0 (Serial debug) | Digunakan untuk USB serial                                 |
| **GPIO6-11** | **Flash memory**   | Terhubung ke internal Flash, **JANGAN PAKAI SAMA SEKALI!** |
| **GPIO12**   | Boot config        | Harus LOW saat boot (jika HIGH = boot fail)                |

**⚠️ CRITICAL**: GPIO6-11 bisa **brick ESP32** jika digunakan!

---

## 🔌 Default Peripheral Pins

### **I2C** (untuk OLED, sensor I2C)

- **SDA**: GPIO21
- **SCL**: GPIO22

**Contoh wiring**:

```
OLED VCC --- 3.3V
OLED GND --- GND
OLED SDA --- GPIO21
OLED SCL --- GPIO22
```

---

### **SPI** (untuk SD card, display TFT)

- **MOSI**: GPIO23
- **MISO**: GPIO19
- **SCK**: GPIO18
- **SS**: GPIO5

---

### **UART** (Serial communication)

- **UART0** (USB debug):
  - TX: GPIO1
  - RX: GPIO3
- **UART2** (General use):
  - TX: GPIO17
  - RX: GPIO16

---

## 🎯 Quick Decision Guide

### **"Pin mana yang harus saya pakai?"**

#### **Untuk LED** 🔴:

- GPIO2, GPIO15, GPIO16, GPIO17 (aman & recommended)

#### **Untuk Button** 🔘:

- GPIO4, GPIO15, GPIO16, GPIO17 (dengan internal pull-up)

#### **Untuk Sensor Analog** 📊 (potensiometer, LDR):

- GPIO32, GPIO33, GPIO34, GPIO35, GPIO36, GPIO39 (ADC pins)

#### **Untuk Sensor I2C** 📡 (OLED, RTC, MPU6050):

- SDA: GPIO21
- SCL: GPIO22

#### **Untuk PWM** 🌀 (servo, motor, LED dimmer):

- Hampir semua GPIO (kecuali GPIO6-11)
- Recommended: GPIO2, GPIO15-17, GPIO25-27

---

## 💡 Tips Pinout

### **1. Color Coding Wiring**

Gunakan warna jumper wire yang konsisten:

- **Merah**: VCC / 3.3V / 5V
- **Hitam/Coklat**: GND
- **Kuning**: Signal/Data
- **Hijau/Biru**: I2C (SDA/SCL)

### **2. Breadboard Power Rails**

Selalu hubungkan:

```
ESP32 3V3 → Breadboard (+) rail
ESP32 GND → Breadboard (-) rail
```

Sehingga semua sensor bisa ambil power dari breadboard rail.

### **3. Check Voltage Level**

- ESP32 logic: **3.3V**
- Beberapa sensor: 5V tolerant
- **Jangan** hubungkan 5V ke GPIO (max 3.6V!)

### **4. Multimeter untuk Verify**

Jika ragu:

- Test voltage di pin dengan multimeter
- GND harus 0V
- VCC harus 3.3V atau 5V

---

## 📸 Praktik Terbaik

### **Before Wiring Checklist**:

- [ ] ESP32 **TIDAK TERHUBUNG** ke USB (power OFF)
- [ ] Cek polaritas komponen (LED, sensor)
- [ ] Cek tidak ada VCC↔GND short circuit
- [ ] Resistor terpasang untuk LED

### **After Wiring Checklist**:

- [ ] Visual inspection (semua wire terhubung benar)
- [ ] Foto circuit untuk dokumentasi
- [ ] Power ON → test

---

## 🆘 Troubleshooting Pinout

### **Sensor tidak terbaca**:

- [ ] Check wiring (VCC, GND, Data pin)
- [ ] Verifikasi GPIO pin di code sesuai wiring
- [ ] Test GPIO dengan LED (untuk verify pin bekerja)

### **ESP32 tidak boot**:

- [ ] Check GPIO0, GPIO12 (harus kondisi benar saat boot)
- [ ] Cabut semua wire, coba boot
- [ ] Jika boot sukses, masalah di wiring salah satu komponen

### **Brownout detector triggered**:

- [ ] Terlalu banyak komponen tarik power dari 3V3
- [ ] Gunakan external power supply
- [ ] Kurangi jumlah LED menyala bersamaan

---

## 📚 Referensi Tambahan

### **Interactive Tools**:

- [Wokwi Simulator](https://wokwi.com) - Hover mouse di pin untuk lihat label
- [ESP32 Pinout Calculator](https://www.espboards.dev/blog/esp32-pinout/) - Pin recommendation tool

### **Cheat Sheets untuk Print**:

- [ESP32 Pinout Poster](https://randomnerdtutorials.com/esp32-pinout-reference-gpios/) - Print A4, warna
- [ESP32 Quick Reference](https:// docs.micropython.org/en/latest/esp32/quickref.html) - MicroPython, tapi pinout sama

---

<div align="center">

**📌 BOOKMARK HALAMAN INI!**

Anda akan sering buka referensi ini selama semester.

**Print & tempel di meja belajar** untuk akses cepat!

</div>

---

**Terakhir diupdate**: Februari 2026  
**Untuk**: Mata Kuliah Mikrokontroller - Prodi Informatika Unmul
