/*
 * =============================================
 *  PROJECT: ESP32 DHT22 TEMPERATURE MONITOR
 *           WITH LED INDICATOR
 * =============================================
 *
 *  Pertemuan 5: Sensor Suhu & Kelembaban (DHT22)
 *  Mata Kuliah Mikrokontroller - Prodi Informatika Unmul
 *
 *  Features:
 *   - Membaca suhu dan kelembaban dari DHT22
 *   - Error handling dengan isnan() dan retry counter
 *   - LED indikator 3 warna berdasarkan suhu:
 *     • Biru  (< 25°C)  = Dingin
 *     • Hijau (25-30°C) = Normal
 *     • Merah (> 30°C)  = Panas
 *   - Heat Index calculation
 *   - Serial output terformat
 *   - LED test saat startup
 *
 *  Wiring:
 *   - DHT22 VCC  → ESP32 3V3
 *   - DHT22 DATA → ESP32 GPIO4 (+ pull-up 10kΩ ke 3V3)
 *   - DHT22 GND  → ESP32 GND
 *   - LED Biru   → GPIO15 → Resistor 220Ω → GND
 *   - LED Hijau  → GPIO16 → Resistor 220Ω → GND
 *   - LED Merah  → GPIO17 → Resistor 220Ω → GND
 *
 *  Library:
 *   - DHT sensor library by Adafruit
 *   - Adafruit Unified Sensor
 *
 *  Serial Monitor Settings:
 *   - Baud Rate: 115200
 */

#include <DHT.h>

// ── Pin Definitions ──────────────────────────────────────────────────────────
#define DHT_PIN     4       // DHT22 DATA pin → GPIO4
#define DHT_TYPE    DHT22   // Sensor type: DHT22 (AM2302)

#define LED_BLUE    15      // LED Biru  (Dingin)  → GPIO15
#define LED_GREEN   16      // LED Hijau (Normal)  → GPIO16
#define LED_RED     17      // LED Merah (Panas)   → GPIO17

// ── Temperature Thresholds ───────────────────────────────────────────────────
#define TEMP_COLD   25.0    // Di bawah ini → Dingin (LED Biru)
#define TEMP_HOT    30.0    // Di atas ini  → Panas  (LED Merah)
                            // Di antara    → Normal (LED Hijau)

// ── Global Variables ─────────────────────────────────────────────────────────
DHT dht(DHT_PIN, DHT_TYPE);

int readCount = 0;          // Counter pembacaan berhasil
int failCount = 0;          // Counter pembacaan gagal berturut-turut
const int MAX_FAIL = 5;     // Batas warning error berturut-turut

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: testAllLEDs
// Nyalakan semua LED satu per satu saat startup (visual test)
// ─────────────────────────────────────────────────────────────────────────────
void testAllLEDs() {
  Serial.println("🔵 Testing LED Biru...");
  digitalWrite(LED_BLUE, HIGH);
  delay(400);
  digitalWrite(LED_BLUE, LOW);

  Serial.println("🟢 Testing LED Hijau...");
  digitalWrite(LED_GREEN, HIGH);
  delay(400);
  digitalWrite(LED_GREEN, LOW);

  Serial.println("🔴 Testing LED Merah...");
  digitalWrite(LED_RED, HIGH);
  delay(400);
  digitalWrite(LED_RED, LOW);

  Serial.println("✅ Semua LED OK!\n");
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: updateLEDs
// Nyalakan LED yang sesuai dengan range suhu, matikan sisanya
// ─────────────────────────────────────────────────────────────────────────────
void updateLEDs(float suhu) {
  // Matikan semua LED dulu
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);

  // Nyalakan LED berdasarkan suhu
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
// Return string status berdasarkan suhu
// ─────────────────────────────────────────────────────────────────────────────
String getStatusLabel(float suhu) {
  if (suhu < TEMP_COLD) {
    return "🔵 DINGIN";
  } else if (suhu > TEMP_HOT) {
    return "🔴 PANAS";
  } else {
    return "🟢 NORMAL";
  }
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: blinkErrorLEDs
// Blink semua LED sebagai indikator error
// ─────────────────────────────────────────────────────────────────────────────
void blinkErrorLEDs() {
  // Nyalakan semua
  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, HIGH);
  delay(150);
  // Matikan semua
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);
  delay(150);
  // Nyalakan lagi (blink 2x)
  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, HIGH);
  delay(150);
  // Matikan semua
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);
}

// ─────────────────────────────────────────────────────────────────────────────
// SETUP
// ─────────────────────────────────────────────────────────────────────────────
void setup() {
  // Inisialisasi Serial
  Serial.begin(115200);

  // Inisialisasi sensor DHT22
  dht.begin();

  // Inisialisasi LED pins
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  // Matikan semua LED
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);

  // Splash screen
  delay(200);
  Serial.println("\n");
  Serial.println("╔════════════════════════════════════════╗");
  Serial.println("║   ESP32 DHT22 Temperature Monitor      ║");
  Serial.println("║   Pertemuan 5: Sensor Suhu & Kelembaban ║");
  Serial.println("║   Mikrokontroller - Prodi Informatika   ║");
  Serial.println("╚════════════════════════════════════════╝");
  Serial.println();
  Serial.printf("DHT22 Pin     : GPIO%d\n", DHT_PIN);
  Serial.printf("LED Biru      : GPIO%d (< %.0f°C)\n", LED_BLUE, TEMP_COLD);
  Serial.printf("LED Hijau     : GPIO%d (%.0f-%.0f°C)\n", LED_GREEN, TEMP_COLD, TEMP_HOT);
  Serial.printf("LED Merah     : GPIO%d (> %.0f°C)\n", LED_RED, TEMP_HOT);
  Serial.printf("Baud Rate     : 115200\n");
  Serial.printf("Read Interval : 2 detik\n");
  Serial.println();

  // Test semua LED
  testAllLEDs();

  // Tunggu sensor siap
  Serial.println("Menunggu sensor DHT22 siap (2 detik)...");
  delay(2000);
  Serial.println("✅ Sistem siap! Monitoring suhu dimulai...\n");
}

// ─────────────────────────────────────────────────────────────────────────────
// LOOP
// ─────────────────────────────────────────────────────────────────────────────
void loop() {
  // Baca data dari sensor DHT22
  float t = dht.readTemperature();    // Suhu dalam Celsius
  float h = dht.readHumidity();       // Kelembaban dalam persen

  // ──── ERROR HANDLING ────────────────────────────────────────────────────
  if (isnan(t) || isnan(h)) {
    failCount++;
    Serial.printf("❌ Pembacaan GAGAL! (gagal berturut-turut: %d/%d)\n",
                  failCount, MAX_FAIL);
    Serial.println("   → Cek: VCC→3V3, DATA→GPIO4+pullup 10kΩ, GND→GND");

    if (failCount >= MAX_FAIL) {
      Serial.println("⚠️  WARNING: Sensor error berkepanjangan!");
      Serial.println("   → Pastikan DHT22 terhubung dengan benar");
      Serial.println("   → Cek pull-up resistor 10kΩ antara DATA dan 3V3");
      Serial.println("   → Coba cabut USB, cek wiring, lalu pasang kembali");
    }

    // Blink LED sebagai indikator error visual
    blinkErrorLEDs();

    delay(2000);
    return;  // Skip, coba lagi di iterasi berikutnya
  }

  // ──── DATA VALID ────────────────────────────────────────────────────────
  failCount = 0;   // Reset fail counter
  readCount++;

  // Hitung Heat Index
  float heatIndex = dht.computeHeatIndex(t, h, false);  // false = Celsius

  // Update LED berdasarkan suhu
  updateLEDs(t);
  String status = getStatusLabel(t);

  // Tampilkan data di Serial Monitor
  Serial.println("┌─── Sensor Reading ─────────────────────┐");
  Serial.printf("│ Reading #%-4d                           \n", readCount);
  Serial.printf("│ Suhu         : %6.1f °C                \n", t);
  Serial.printf("│ Kelembaban   : %6.1f %%                \n", h);
  Serial.printf("│ Heat Index   : %6.1f °C                \n", heatIndex);
  Serial.printf("│ Status       : %s                      \n", status.c_str());
  Serial.printf("│ Uptime       : %lu detik               \n", millis() / 1000);
  Serial.println("└─────────────────────────────────────────┘");
  Serial.println();

  // Tunggu 2 detik (minimum sampling period DHT22)
  delay(2000);
}
