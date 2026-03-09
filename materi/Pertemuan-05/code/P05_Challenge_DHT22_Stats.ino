/*
 * =============================================
 *  CHALLENGE: DHT22 STATISTICS MONITOR
 *  WITH INTERACTIVE SERIAL MENU
 * =============================================
 *
 *  Pertemuan 5: Sensor Suhu & Kelembaban (DHT22)
 *  Mata Kuliah Mikrokontroller - Prodi Informatika Unmul
 *
 *  Features:
 *   - Semua fitur dari P05_DHT22_LED_Indicator.ino
 *   - Rolling window statistik (10 pembacaan terakhir)
 *   - Hitung MIN, MAX, AVERAGE suhu & kelembaban
 *   - Serial Menu interaktif:
 *     1. Baca sensor sekarang
 *     2. Tampilkan statistik (min/max/avg)
 *     3. Reset statistik
 *     4. Set alarm threshold suhu
 *     5. System info
 *     0. Tampilkan menu
 *   - Alarm: warning di serial jika suhu melewati threshold
 *
 *  Wiring: (sama dengan P05_DHT22_LED_Indicator.ino)
 *   - DHT22 VCC  → ESP32 3V3
 *   - DHT22 DATA → ESP32 GPIO4 (+ pull-up 10kΩ ke 3V3)
 *   - DHT22 GND  → ESP32 GND
 *   - LED Biru   → GPIO15 → Resistor 220Ω → GND
 *   - LED Hijau  → GPIO16 → Resistor 220Ω → GND
 *   - LED Merah  → GPIO17 → Resistor 220Ω → GND
 *
 *  Serial Monitor Settings:
 *   - Baud Rate  : 115200
 *   - Line Ending: NL & CR (Both NL & CR)
 */

#include <DHT.h>

// ── Pin Definitions ──────────────────────────────────────────────────────────
#define DHT_PIN     4
#define DHT_TYPE    DHT22

#define LED_BLUE    15
#define LED_GREEN   16
#define LED_RED     17

// ── Temperature Thresholds ───────────────────────────────────────────────────
#define TEMP_COLD   25.0
#define TEMP_HOT    30.0

// ── Statistics Configuration ─────────────────────────────────────────────────
#define WINDOW_SIZE 10      // Rolling window: simpan 10 pembacaan terakhir

// ── Global Variables ─────────────────────────────────────────────────────────
DHT dht(DHT_PIN, DHT_TYPE);

// Statistics arrays
float tempHistory[WINDOW_SIZE];
float humHistory[WINDOW_SIZE];
int historyIndex = 0;       // Index saat ini di array
int historyCount = 0;       // Jumlah data yang sudah tersimpan (max WINDOW_SIZE)

// Counters
int readCount = 0;
int failCount = 0;

// Alarm threshold (bisa diubah via serial)
float alarmTempHigh = 35.0;   // Default alarm suhu tinggi
float alarmTempLow  = 20.0;   // Default alarm suhu rendah

// Auto-read mode
bool autoReadMode = true;     // Mulai dengan auto-read aktif
unsigned long lastReadTime = 0;
const unsigned long READ_INTERVAL = 2000;  // 2 detik

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: testAllLEDs
// ─────────────────────────────────────────────────────────────────────────────
void testAllLEDs() {
  Serial.println("  🔵 LED Biru...");
  digitalWrite(LED_BLUE, HIGH);
  delay(300);
  digitalWrite(LED_BLUE, LOW);

  Serial.println("  🟢 LED Hijau...");
  digitalWrite(LED_GREEN, HIGH);
  delay(300);
  digitalWrite(LED_GREEN, LOW);

  Serial.println("  🔴 LED Merah...");
  digitalWrite(LED_RED, HIGH);
  delay(300);
  digitalWrite(LED_RED, LOW);

  Serial.println("  ✅ LED test OK!\n");
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: updateLEDs
// ─────────────────────────────────────────────────────────────────────────────
void updateLEDs(float suhu) {
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);

  if (suhu < TEMP_COLD) {
    digitalWrite(LED_BLUE, HIGH);
  } else if (suhu > TEMP_HOT) {
    digitalWrite(LED_RED, HIGH);
  } else {
    digitalWrite(LED_GREEN, HIGH);
  }
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: getStatusLabel
// ─────────────────────────────────────────────────────────────────────────────
String getStatusLabel(float suhu) {
  if (suhu < TEMP_COLD) return "🔵 DINGIN";
  else if (suhu > TEMP_HOT) return "🔴 PANAS";
  else return "🟢 NORMAL";
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: addToHistory
// Tambahkan pembacaan ke rolling window
// ─────────────────────────────────────────────────────────────────────────────
void addToHistory(float temp, float hum) {
  tempHistory[historyIndex] = temp;
  humHistory[historyIndex] = hum;
  historyIndex = (historyIndex + 1) % WINDOW_SIZE;  // Circular buffer
  if (historyCount < WINDOW_SIZE) {
    historyCount++;
  }
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: resetHistory
// Reset semua statistik
// ─────────────────────────────────────────────────────────────────────────────
void resetHistory() {
  historyIndex = 0;
  historyCount = 0;
  readCount = 0;
  failCount = 0;
  for (int i = 0; i < WINDOW_SIZE; i++) {
    tempHistory[i] = 0;
    humHistory[i] = 0;
  }
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: checkAlarm
// Cek apakah suhu melewati alarm threshold
// ─────────────────────────────────────────────────────────────────────────────
void checkAlarm(float temp) {
  if (temp >= alarmTempHigh) {
    Serial.println("🚨 ══════════════════════════════════════ 🚨");
    Serial.printf("🚨 ALARM! Suhu TINGGI: %.1f°C (threshold: %.1f°C)\n",
                  temp, alarmTempHigh);
    Serial.println("🚨 ══════════════════════════════════════ 🚨");
  } else if (temp <= alarmTempLow) {
    Serial.println("🚨 ══════════════════════════════════════ 🚨");
    Serial.printf("🚨 ALARM! Suhu RENDAH: %.1f°C (threshold: %.1f°C)\n",
                  temp, alarmTempLow);
    Serial.println("🚨 ══════════════════════════════════════ 🚨");
  }
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: readAndDisplay
// Baca sensor dan tampilkan data + simpan ke history
// ─────────────────────────────────────────────────────────────────────────────
void readAndDisplay() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    failCount++;
    Serial.printf("❌ Pembacaan GAGAL! (gagal: %d)\n", failCount);
    return;
  }

  failCount = 0;
  readCount++;

  // Simpan ke history
  addToHistory(t, h);

  // Hitung heat index
  float hi = dht.computeHeatIndex(t, h, false);

  // Update LED
  updateLEDs(t);

  // Tampilkan
  Serial.println("┌─── Sensor Reading ─────────────────────┐");
  Serial.printf("│ #%-4d            %s\n", readCount, getStatusLabel(t).c_str());
  Serial.printf("│ Suhu         : %6.1f °C               \n", t);
  Serial.printf("│ Kelembaban   : %6.1f %%               \n", h);
  Serial.printf("│ Heat Index   : %6.1f °C               \n", hi);
  Serial.printf("│ Data Points  : %d/%d                   \n", historyCount, WINDOW_SIZE);
  Serial.println("└─────────────────────────────────────────┘");

  // Cek alarm
  checkAlarm(t);
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: showStatistics
// Hitung dan tampilkan MIN, MAX, AVERAGE dari history
// ─────────────────────────────────────────────────────────────────────────────
void showStatistics() {
  if (historyCount == 0) {
    Serial.println("\n⚠️ Belum ada data! Baca sensor dulu (pilih 1).\n");
    return;
  }

  // Hitung statistik suhu
  float tempMin = tempHistory[0], tempMax = tempHistory[0], tempSum = 0;
  float humMin = humHistory[0], humMax = humHistory[0], humSum = 0;

  for (int i = 0; i < historyCount; i++) {
    // Suhu
    if (tempHistory[i] < tempMin) tempMin = tempHistory[i];
    if (tempHistory[i] > tempMax) tempMax = tempHistory[i];
    tempSum += tempHistory[i];

    // Kelembaban
    if (humHistory[i] < humMin) humMin = humHistory[i];
    if (humHistory[i] > humMax) humMax = humHistory[i];
    humSum += humHistory[i];
  }

  float tempAvg = tempSum / historyCount;
  float humAvg = humSum / historyCount;

  Serial.println();
  Serial.println("╔═══════════════════════════════════════════╗");
  Serial.println("║        📊 STATISTIK SENSOR               ║");
  Serial.println("╠═══════════════════════════════════════════╣");
  Serial.printf("║  Data Points   : %d / %d (window)        \n", historyCount, WINDOW_SIZE);
  Serial.printf("║  Total Reading : %d                      \n", readCount);
  Serial.printf("║  Total Fail    : %d                      \n", failCount);
  Serial.println("╠═══════════════════════════════════════════╣");
  Serial.println("║ 🌡️  SUHU (°C)                            ║");
  Serial.printf("║  MIN  : %6.1f °C                        \n", tempMin);
  Serial.printf("║  MAX  : %6.1f °C                        \n", tempMax);
  Serial.printf("║  AVG  : %6.1f °C                        \n", tempAvg);
  Serial.printf("║  Range: %6.1f °C                        \n", tempMax - tempMin);
  Serial.println("╠═══════════════════════════════════════════╣");
  Serial.println("║ 💧 KELEMBABAN (%)                        ║");
  Serial.printf("║  MIN  : %6.1f %%                        \n", humMin);
  Serial.printf("║  MAX  : %6.1f %%                        \n", humMax);
  Serial.printf("║  AVG  : %6.1f %%                        \n", humAvg);
  Serial.printf("║  Range: %6.1f %%                        \n", humMax - humMin);
  Serial.println("╠═══════════════════════════════════════════╣");
  Serial.printf("║  Alarm High : %.1f °C                   \n", alarmTempHigh);
  Serial.printf("║  Alarm Low  : %.1f °C                   \n", alarmTempLow);
  Serial.println("╚═══════════════════════════════════════════╝");
  Serial.println();
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: setAlarmThreshold
// Set alarm suhu via Serial input
// ─────────────────────────────────────────────────────────────────────────────
void setAlarmThreshold() {
  Serial.printf("\nAlarm saat ini: LOW=%.1f°C, HIGH=%.1f°C\n",
                alarmTempLow, alarmTempHigh);

  // Set alarm HIGH
  Serial.print("Masukkan alarm suhu TINGGI (°C): ");
  while (Serial.available() == 0) { delay(10); }
  String highStr = Serial.readStringUntil('\n');
  highStr.trim();
  float newHigh = highStr.toFloat();

  if (newHigh > 0 && newHigh <= 80) {
    alarmTempHigh = newHigh;
    Serial.printf("✅ Alarm HIGH → %.1f°C\n", alarmTempHigh);
  } else {
    Serial.println("❌ Nilai tidak valid (harus 1-80)");
  }

  // Set alarm LOW
  Serial.print("Masukkan alarm suhu RENDAH (°C): ");
  while (Serial.available() == 0) { delay(10); }
  String lowStr = Serial.readStringUntil('\n');
  lowStr.trim();
  float newLow = lowStr.toFloat();

  if (newLow >= -40 && newLow < alarmTempHigh) {
    alarmTempLow = newLow;
    Serial.printf("✅ Alarm LOW → %.1f°C\n", alarmTempLow);
  } else {
    Serial.printf("❌ Nilai tidak valid (harus -40 s/d %.1f)\n", alarmTempHigh);
  }

  Serial.printf("\n📢 Alarm aktif: LOW=%.1f°C, HIGH=%.1f°C\n\n",
                alarmTempLow, alarmTempHigh);
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: showSystemInfo
// Tampilkan informasi sistem
// ─────────────────────────────────────────────────────────────────────────────
void showSystemInfo() {
  unsigned long uptimeMs = millis();
  unsigned long uptimeSec = uptimeMs / 1000;
  unsigned long uptimeMin = uptimeSec / 60;

  Serial.println("\n┌─── System Info ────────────────────────┐");
  Serial.printf("│ Uptime     : %lu detik (%lu menit)     \n", uptimeSec, uptimeMin);
  Serial.printf("│ Free Heap  : %d bytes                  \n", ESP.getFreeHeap());
  Serial.printf("│ CPU Freq   : %d MHz                    \n", ESP.getCpuFreqMHz());
  Serial.printf("│ Flash Size : %d KB                     \n", ESP.getFlashChipSize() / 1024);
  Serial.printf("│ Auto-Read  : %s                        \n", autoReadMode ? "ON" : "OFF");
  Serial.printf("│ Alarm High : %.1f °C                   \n", alarmTempHigh);
  Serial.printf("│ Alarm Low  : %.1f °C                   \n", alarmTempLow);
  Serial.println("└────────────────────────────────────────┘\n");
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: printMenu
// Tampilkan menu interaktif
// ─────────────────────────────────────────────────────────────────────────────
void printMenu() {
  Serial.println();
  Serial.println("╔══════════════════════════════════╗");
  Serial.println("║   DHT22 Statistics Monitor       ║");
  Serial.println("╠══════════════════════════════════╣");
  Serial.println("║  1. Baca sensor sekarang         ║");
  Serial.println("║  2. Tampilkan statistik          ║");
  Serial.println("║  3. Reset statistik              ║");
  Serial.println("║  4. Set alarm threshold          ║");
  Serial.println("║  5. System info                  ║");
  Serial.println("║  6. Toggle auto-read ON/OFF      ║");
  Serial.println("║  0. Tampilkan menu               ║");
  Serial.println("╚══════════════════════════════════╝");
  Serial.printf("Auto-Read: %s | Data: %d/%d\n",
                autoReadMode ? "ON (tiap 2 detik)" : "OFF (manual)",
                historyCount, WINDOW_SIZE);
  Serial.print("Pilih (0-6): ");
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: handleMenu
// Proses pilihan menu
// ─────────────────────────────────────────────────────────────────────────────
void handleMenu(int choice) {
  switch (choice) {

    case 1:  // Baca sensor sekarang
      readAndDisplay();
      break;

    case 2:  // Tampilkan statistik
      showStatistics();
      break;

    case 3:  // Reset statistik
      resetHistory();
      Serial.println("\n✅ Statistik di-reset! Semua data dihapus.\n");
      break;

    case 4:  // Set alarm threshold
      setAlarmThreshold();
      break;

    case 5:  // System info
      showSystemInfo();
      break;

    case 6:  // Toggle auto-read
      autoReadMode = !autoReadMode;
      Serial.printf("\n✅ Auto-Read: %s\n\n",
                    autoReadMode ? "ON (sensor dibaca otomatis tiap 2 detik)"
                                 : "OFF (ketik 1 untuk baca manual)");
      break;

    case 0:  // Tampilkan menu
      break;

    default:
      Serial.println("\n❌ Pilihan tidak valid! Pilih 0-6.\n");
      break;
  }

  printMenu();
}

// ─────────────────────────────────────────────────────────────────────────────
// SETUP
// ─────────────────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);

  // Inisialisasi history
  resetHistory();

  delay(200);
  Serial.println("\n");
  Serial.println("╔════════════════════════════════════════════╗");
  Serial.println("║   🏆 DHT22 Statistics Monitor (Challenge) ║");
  Serial.println("║   Pertemuan 5 - Mikrokontroller            ║");
  Serial.println("║   Prodi Informatika Unmul                  ║");
  Serial.println("╚════════════════════════════════════════════╝");
  Serial.println();

  Serial.printf("DHT22      : GPIO%d\n", DHT_PIN);
  Serial.printf("LED Biru   : GPIO%d\n", LED_BLUE);
  Serial.printf("LED Hijau  : GPIO%d\n", LED_GREEN);
  Serial.printf("LED Merah  : GPIO%d\n", LED_RED);
  Serial.printf("Window     : %d pembacaan\n", WINDOW_SIZE);
  Serial.printf("Alarm      : LOW=%.1f°C, HIGH=%.1f°C\n", alarmTempLow, alarmTempHigh);
  Serial.println();

  testAllLEDs();

  Serial.println("Menunggu sensor DHT22 siap...");
  delay(2000);
  Serial.println("✅ Sistem siap!\n");

  printMenu();
}

// ─────────────────────────────────────────────────────────────────────────────
// LOOP
// ─────────────────────────────────────────────────────────────────────────────
void loop() {
  // ── Auto-read mode: baca sensor otomatis tiap 2 detik ────────────────
  if (autoReadMode) {
    unsigned long now = millis();
    if (now - lastReadTime >= READ_INTERVAL) {
      lastReadTime = now;
      readAndDisplay();
      Serial.println();
    }
  }

  // ── Cek input serial (menu) ──────────────────────────────────────────
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.length() == 0) return;

    Serial.println(input);  // Echo input

    int choice = input.toInt();
    handleMenu(choice);
  }
}
