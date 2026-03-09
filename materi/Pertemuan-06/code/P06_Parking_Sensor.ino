/*
 * =============================================
 *  PROJECT: ESP32 PARKING SENSOR
 *           HC-SR04 + BUZZER + LED INDICATOR
 * =============================================
 *
 *  Pertemuan 6: Sensor Jarak & Interrupt Basics
 *  Mata Kuliah Mikrokontroller - Prodi Informatika Unmul
 *
 *  Features:
 *   - HC-SR04 mengukur jarak secara real-time
 *   - Buzzer beep rate berubah sesuai jarak:
 *     • > 50cm  = OFF (aman)
 *     • 20-50cm = Beep lambat (waspada)
 *     • 10-20cm = Beep sedang (dekat)
 *     • < 10cm  = Beep cepat (bahaya!)
 *   - LED indikator 3 warna:
 *     • Hijau  = Aman (> 50cm)
 *     • Kuning = Waspada (20-50cm)
 *     • Merah  = Bahaya (< 20cm)
 *   - Error handling (out of range / timeout)
 *   - Serial output terformat
 *
 *  Wiring:
 *   - HC-SR04 VCC  → ESP32 VIN (5V!)
 *   - HC-SR04 Trig → ESP32 GPIO5
 *   - HC-SR04 Echo → Voltage Divider (1kΩ+2kΩ) → ESP32 GPIO18
 *   - HC-SR04 GND  → ESP32 GND
 *   - Buzzer (+)   → ESP32 GPIO19
 *   - Buzzer (-)   → ESP32 GND
 *   - LED Hijau    → GPIO15 → 220Ω → GND
 *   - LED Kuning   → GPIO16 → 220Ω → GND
 *   - LED Merah    → GPIO17 → 220Ω → GND
 *
 *  PENTING:
 *   ⚠️ HC-SR04 Echo pin output 5V!
 *      WAJIB pasang voltage divider (1kΩ + 2kΩ) sebelum GPIO18.
 *      Tanpa voltage divider, GPIO ESP32 bisa RUSAK!
 *
 *  Serial Monitor Settings:
 *   - Baud Rate: 115200
 */

// ── Pin Definitions ──────────────────────────────────────────────────────────
#define TRIG_PIN    5       // HC-SR04 Trigger → GPIO5
#define ECHO_PIN    18      // HC-SR04 Echo → GPIO18 (via voltage divider!)
#define BUZZER_PIN  19      // Active buzzer → GPIO19

#define LED_GREEN   15      // LED Hijau  (Aman)    > 50cm → GPIO15
#define LED_YELLOW  16      // LED Kuning (Waspada) 20-50cm → GPIO16
#define LED_RED     17      // LED Merah  (Bahaya)  < 20cm → GPIO17

// ── Distance Thresholds (cm) ─────────────────────────────────────────────────
#define DIST_SAFE     50    // > 50cm = aman
#define DIST_WARNING  20    // 20-50cm = waspada
#define DIST_CLOSE    10    // 10-20cm = dekat, < 10cm = bahaya

// ── Buzzer Intervals (ms) ────────────────────────────────────────────────────
#define BEEP_SLOW     500   // Waspada: beep per 500ms
#define BEEP_MEDIUM   200   // Dekat: beep per 200ms
#define BEEP_FAST     80    // Bahaya: beep per 80ms
#define BEEP_DURATION 50    // Durasi beep ON (ms)

// ── Global Variables ─────────────────────────────────────────────────────────
int readCount = 0;
int errorCount = 0;

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: readDistance
// Kirim trigger pulse, baca echo, hitung jarak (cm)
// Return: jarak dalam cm, atau -1 jika error/timeout
// ─────────────────────────────────────────────────────────────────────────────
float readDistance() {
  // Kirim trigger pulse 10µs
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Baca durasi echo (timeout 30ms ≈ ~5 meter max)
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  // Timeout check — tidak ada pantulan
  if (duration == 0) {
    return -1;
  }

  // Hitung jarak
  float distance = (duration * 0.034) / 2.0;

  // Validasi range (HC-SR04: 2-400cm)
  if (distance < 2 || distance > 400) {
    return -1;
  }

  return distance;
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: allLEDsOff
// Matikan semua LED
// ─────────────────────────────────────────────────────────────────────────────
void allLEDsOff() {
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: testAllComponents
// Test semua LED dan buzzer saat startup
// ─────────────────────────────────────────────────────────────────────────────
void testAllComponents() {
  Serial.println("Testing komponen...");

  Serial.println("  🟢 LED Hijau...");
  digitalWrite(LED_GREEN, HIGH);
  delay(300);
  digitalWrite(LED_GREEN, LOW);

  Serial.println("  🟡 LED Kuning...");
  digitalWrite(LED_YELLOW, HIGH);
  delay(300);
  digitalWrite(LED_YELLOW, LOW);

  Serial.println("  🔴 LED Merah...");
  digitalWrite(LED_RED, HIGH);
  delay(300);
  digitalWrite(LED_RED, LOW);

  Serial.println("  🔊 Buzzer...");
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("  ✅ Semua komponen OK!\n");
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: beepBuzzer
// Beep buzzer dengan interval tertentu (non-blocking style)
// ─────────────────────────────────────────────────────────────────────────────
void beepBuzzer(int interval) {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(BEEP_DURATION);
  digitalWrite(BUZZER_PIN, LOW);
  delay(interval - BEEP_DURATION);
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: getStatusBar
// Buat visual bar berdasarkan jarak
// ─────────────────────────────────────────────────────────────────────────────
String getStatusBar(float jarak) {
  int bars = map(constrain((int)jarak, 0, 100), 0, 100, 10, 0);
  String bar = "";
  for (int i = 0; i < 10; i++) {
    if (i < bars) bar += "█";
    else bar += "░";
  }
  return bar;
}

// ─────────────────────────────────────────────────────────────────────────────
// SETUP
// ─────────────────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);

  // Pin setup
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  // Matikan semua output
  digitalWrite(BUZZER_PIN, LOW);
  allLEDsOff();

  // Splash screen
  delay(200);
  Serial.println("\n");
  Serial.println("╔════════════════════════════════════════╗");
  Serial.println("║   🅿️ ESP32 Parking Sensor              ║");
  Serial.println("║   Pertemuan 6: Sensor Jarak & Interrupt ║");
  Serial.println("║   Mikrokontroller - Prodi Informatika   ║");
  Serial.println("╚════════════════════════════════════════╝");
  Serial.println();
  Serial.printf("Trig Pin    : GPIO%d\n", TRIG_PIN);
  Serial.printf("Echo Pin    : GPIO%d (via voltage divider)\n", ECHO_PIN);
  Serial.printf("Buzzer Pin  : GPIO%d\n", BUZZER_PIN);
  Serial.printf("LED Hijau   : GPIO%d (> %dcm)\n", LED_GREEN, DIST_SAFE);
  Serial.printf("LED Kuning  : GPIO%d (%d-%dcm)\n", LED_YELLOW, DIST_WARNING, DIST_SAFE);
  Serial.printf("LED Merah   : GPIO%d (< %dcm)\n", LED_RED, DIST_WARNING);
  Serial.println();

  // Test komponen
  testAllComponents();

  Serial.println("Monitoring jarak dimulai...\n");
}

// ─────────────────────────────────────────────────────────────────────────────
// LOOP
// ─────────────────────────────────────────────────────────────────────────────
void loop() {
  float jarak = readDistance();

  // Reset output
  allLEDsOff();
  digitalWrite(BUZZER_PIN, LOW);

  // ── Error Handling ──────────────────────────────────────────────────────
  if (jarak < 0) {
    errorCount++;
    Serial.printf("⚠️ [%d] Out of range / timeout\n", errorCount);
    delay(500);
    return;
  }

  readCount++;
  String bar = getStatusBar(jarak);

  // ── Zone Handling ───────────────────────────────────────────────────────

  if (jarak > DIST_SAFE) {
    // ── ZONE: AMAN ────────────────────────────────────────────────────
    digitalWrite(LED_GREEN, HIGH);
    Serial.printf("#%-4d │ %5.1f cm │ %s │ 🟢 AMAN\n",
                  readCount, jarak, bar.c_str());
    delay(200);

  } else if (jarak > DIST_WARNING) {
    // ── ZONE: WASPADA ─────────────────────────────────────────────────
    digitalWrite(LED_YELLOW, HIGH);
    Serial.printf("#%-4d │ %5.1f cm │ %s │ 🟡 WASPADA\n",
                  readCount, jarak, bar.c_str());
    beepBuzzer(BEEP_SLOW);

  } else if (jarak > DIST_CLOSE) {
    // ── ZONE: DEKAT ───────────────────────────────────────────────────
    digitalWrite(LED_RED, HIGH);
    Serial.printf("#%-4d │ %5.1f cm │ %s │ 🔴 DEKAT!\n",
                  readCount, jarak, bar.c_str());
    beepBuzzer(BEEP_MEDIUM);

  } else {
    // ── ZONE: BAHAYA ──────────────────────────────────────────────────
    Serial.printf("#%-4d │ %5.1f cm │ %s │ 🔴 BAHAYA!!!\n",
                  readCount, jarak, bar.c_str());
    // Rapid blink + beep
    for (int i = 0; i < 3; i++) {
      digitalWrite(LED_RED, HIGH);
      digitalWrite(BUZZER_PIN, HIGH);
      delay(BEEP_FAST / 2);
      digitalWrite(LED_RED, LOW);
      digitalWrite(BUZZER_PIN, LOW);
      delay(BEEP_FAST / 2);
    }
  }
}
