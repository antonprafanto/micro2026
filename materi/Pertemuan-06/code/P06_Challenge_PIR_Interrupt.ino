/*
 * =============================================
 *  CHALLENGE: PIR MOTION DETECTION
 *  WITH INTERRUPT + HC-SR04 DISTANCE
 * =============================================
 *
 *  Pertemuan 6: Sensor Jarak & Interrupt Basics
 *  Mata Kuliah Mikrokontroller - Prodi Informatika Unmul
 *
 *  Features:
 *   - HC-SR04 mengukur jarak (auto-read)
 *   - PIR HC-SR501 mendeteksi gerakan via INTERRUPT
 *   - Volatile counter untuk gerakan
 *   - Kombinasi alarm: gerakan + jarak dekat
 *   - Serial menu interaktif:
 *     1. Baca jarak sekarang
 *     2. Tampilkan statistik gerakan
 *     3. Reset counter
 *     4. Toggle alarm ON/OFF
 *     5. System info
 *     0. Tampilkan menu
 *
 *  Wiring:
 *   - HC-SR04 VCC  → ESP32 VIN (5V)
 *   - HC-SR04 Trig → ESP32 GPIO5
 *   - HC-SR04 Echo → Voltage Divider (1kΩ+2kΩ) → GPIO18
 *   - HC-SR04 GND  → ESP32 GND
 *   - PIR VCC      → ESP32 VIN (5V)
 *   - PIR OUT      → ESP32 GPIO4 (output 3.3V, langsung tanpa divider)
 *   - PIR GND      → ESP32 GND
 *   - Buzzer (+)   → ESP32 GPIO19
 *   - Buzzer (-)   → ESP32 GND
 *   - LED Hijau    → GPIO15 → 220Ω → GND
 *   - LED Kuning   → GPIO16 → 220Ω → GND
 *   - LED Merah    → GPIO17 → 220Ω → GND
 *
 *  Serial Monitor Settings:
 *   - Baud Rate  : 115200
 *   - Line Ending: NL & CR
 */

// ── Pin Definitions ──────────────────────────────────────────────────────────
#define TRIG_PIN    5
#define ECHO_PIN    18
#define PIR_PIN     4       // PIR output → GPIO4 (interrupt-capable)
#define BUZZER_PIN  19

#define LED_GREEN   15
#define LED_YELLOW  16
#define LED_RED     17

// ── Distance Thresholds ──────────────────────────────────────────────────────
#define DIST_SAFE     50
#define DIST_WARNING  20
#define DIST_CLOSE    10

// ── Volatile Variables (diubah oleh ISR) ─────────────────────────────────────
volatile int motionCount = 0;           // Counter gerakan (dari ISR)
volatile bool motionFlag = false;       // Flag gerakan baru terdeteksi
volatile unsigned long lastMotionTime = 0;  // Waktu gerakan terakhir

// ── Non-volatile Variables ───────────────────────────────────────────────────
bool alarmEnabled = true;
bool autoRead = true;
unsigned long lastReadTime = 0;
const unsigned long READ_INTERVAL = 300;    // Baca jarak tiap 300ms
unsigned long lastDebounceTime = 0;
const unsigned long DEBOUNCE_DELAY = 2000;  // PIR debounce 2s (sensor delay)

// ─────────────────────────────────────────────────────────────────────────────
// ISR: Dipanggil otomatis saat PIR mendeteksi gerakan
// ─────────────────────────────────────────────────────────────────────────────
void IRAM_ATTR onMotionDetected() {
  unsigned long now = millis();
  // Simple debounce (PIR punya delay sendiri, tapi tambahan safety)
  if (now - lastMotionTime > DEBOUNCE_DELAY) {
    motionCount++;
    motionFlag = true;
    lastMotionTime = now;
  }
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: readDistance
// ─────────────────────────────────────────────────────────────────────────────
float readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return -1;

  float distance = (duration * 0.034) / 2.0;
  if (distance < 2 || distance > 400) return -1;
  return distance;
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: allLEDsOff
// ─────────────────────────────────────────────────────────────────────────────
void allLEDsOff() {
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: triggerAlarm
// Buzzer alarm saat gerakan + jarak dekat
// ─────────────────────────────────────────────────────────────────────────────
void triggerAlarm(float jarak) {
  Serial.println("🚨 ══════════════════════════════════════ 🚨");
  Serial.printf("🚨 ALARM! Gerakan terdeteksi! (jarak: %.1fcm)\n", jarak);
  Serial.printf("🚨 Total gerakan: %d\n", motionCount);
  Serial.println("🚨 ══════════════════════════════════════ 🚨");

  // Alarm pattern: 5 beep cepat
  for (int i = 0; i < 5; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_RED, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_RED, LOW);
    delay(100);
  }
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: readAndDisplay
// Baca jarak dan tampilkan + handle motion flag
// ─────────────────────────────────────────────────────────────────────────────
void readAndDisplay() {
  float jarak = readDistance();

  allLEDsOff();
  digitalWrite(BUZZER_PIN, LOW);

  if (jarak < 0) {
    Serial.println("  ⚠️ Out of range");
    return;
  }

  // Update LED
  if (jarak > DIST_SAFE) {
    digitalWrite(LED_GREEN, HIGH);
    Serial.printf("  📏 Jarak: %5.1f cm  │ 🟢 AMAN\n", jarak);
  } else if (jarak > DIST_WARNING) {
    digitalWrite(LED_YELLOW, HIGH);
    Serial.printf("  📏 Jarak: %5.1f cm  │ 🟡 WASPADA\n", jarak);
  } else {
    digitalWrite(LED_RED, HIGH);
    Serial.printf("  📏 Jarak: %5.1f cm  │ 🔴 DEKAT!\n", jarak);
  }

  // Handle motion flag (set by ISR)
  if (motionFlag) {
    motionFlag = false;
    Serial.printf("  🏃 GERAKAN TERDETEKSI! (total: %d)\n", motionCount);

    // Alarm: gerakan + jarak dekat
    if (alarmEnabled && jarak < DIST_SAFE) {
      triggerAlarm(jarak);
    }
  }
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: showStats
// ─────────────────────────────────────────────────────────────────────────────
void showStats() {
  unsigned long uptimeSec = millis() / 1000;
  unsigned long timeSinceMotion = (lastMotionTime > 0)
    ? (millis() - lastMotionTime) / 1000 : 0;

  Serial.println();
  Serial.println("╔══════════════════════════════════════╗");
  Serial.println("║      📊 STATISTIK GERAKAN            ║");
  Serial.println("╠══════════════════════════════════════╣");
  Serial.printf("║  Total Gerakan    : %d               \n", motionCount);
  Serial.printf("║  Alarm            : %s               \n",
                alarmEnabled ? "ON 🔔" : "OFF 🔕");
  Serial.printf("║  Sejak Gerakan    : %lu detik lalu   \n", timeSinceMotion);
  Serial.printf("║  Uptime           : %lu detik        \n", uptimeSec);
  Serial.println("╚══════════════════════════════════════╝");
  Serial.println();
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: showSystemInfo
// ─────────────────────────────────────────────────────────────────────────────
void showSystemInfo() {
  Serial.println("\n┌─── System Info ────────────────────────┐");
  Serial.printf("│ Free Heap   : %d bytes                 \n", ESP.getFreeHeap());
  Serial.printf("│ CPU Freq    : %d MHz                   \n", ESP.getCpuFreqMHz());
  Serial.printf("│ Uptime      : %lu detik                \n", millis() / 1000);
  Serial.printf("│ PIR Pin     : GPIO%d (interrupt)       \n", PIR_PIN);
  Serial.printf("│ Auto-Read   : %s                       \n", autoRead ? "ON" : "OFF");
  Serial.printf("│ Alarm       : %s                       \n",
                alarmEnabled ? "ON" : "OFF");
  Serial.println("└────────────────────────────────────────┘\n");
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: printMenu
// ─────────────────────────────────────────────────────────────────────────────
void printMenu() {
  Serial.println();
  Serial.println("╔══════════════════════════════════╗");
  Serial.println("║   PIR + HC-SR04 Challenge        ║");
  Serial.println("╠══════════════════════════════════╣");
  Serial.println("║  1. Baca jarak sekarang          ║");
  Serial.println("║  2. Statistik gerakan            ║");
  Serial.println("║  3. Reset counter gerakan        ║");
  Serial.println("║  4. Toggle alarm ON/OFF          ║");
  Serial.println("║  5. System info                  ║");
  Serial.println("║  6. Toggle auto-read ON/OFF      ║");
  Serial.println("║  0. Tampilkan menu               ║");
  Serial.println("╚══════════════════════════════════╝");
  Serial.printf("Auto-Read: %s | Motion: %d | Alarm: %s\n",
                autoRead ? "ON" : "OFF", motionCount,
                alarmEnabled ? "ON" : "OFF");
  Serial.print("Pilih (0-6): ");
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: handleMenu
// ─────────────────────────────────────────────────────────────────────────────
void handleMenu(int choice) {
  switch (choice) {
    case 1:
      readAndDisplay();
      break;

    case 2:
      showStats();
      break;

    case 3:
      motionCount = 0;
      motionFlag = false;
      Serial.println("\n✅ Counter gerakan di-reset!\n");
      break;

    case 4:
      alarmEnabled = !alarmEnabled;
      Serial.printf("\n✅ Alarm: %s\n\n",
                    alarmEnabled ? "ON 🔔 (bunyi saat gerakan + jarak dekat)"
                                 : "OFF 🔕");
      break;

    case 5:
      showSystemInfo();
      break;

    case 6:
      autoRead = !autoRead;
      Serial.printf("\n✅ Auto-Read: %s\n\n",
                    autoRead ? "ON (jarak dibaca otomatis)" : "OFF (manual)");
      break;

    case 0:
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

  // Pin setup
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  // Reset outputs
  digitalWrite(BUZZER_PIN, LOW);
  allLEDsOff();

  // Attach PIR interrupt
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), onMotionDetected, RISING);

  delay(200);
  Serial.println("\n");
  Serial.println("╔════════════════════════════════════════════╗");
  Serial.println("║   🏆 PIR + HC-SR04 Challenge (Interrupt)  ║");
  Serial.println("║   Pertemuan 6 - Mikrokontroller            ║");
  Serial.println("║   Prodi Informatika Unmul                  ║");
  Serial.println("╚════════════════════════════════════════════╝");
  Serial.println();
  Serial.printf("HC-SR04 Trig : GPIO%d\n", TRIG_PIN);
  Serial.printf("HC-SR04 Echo : GPIO%d (voltage divider!)\n", ECHO_PIN);
  Serial.printf("PIR Sensor   : GPIO%d (interrupt RISING)\n", PIR_PIN);
  Serial.printf("Buzzer       : GPIO%d\n", BUZZER_PIN);
  Serial.println();

  Serial.println("⏳ Menunggu PIR sensor stabilize (5 detik)...");
  Serial.println("   (PIR butuh waktu 'pemanasan' saat pertama dinyalakan)");
  delay(5000);
  Serial.println("✅ Sistem siap!\n");

  printMenu();
}

// ─────────────────────────────────────────────────────────────────────────────
// LOOP
// ─────────────────────────────────────────────────────────────────────────────
void loop() {
  // Auto-read mode
  if (autoRead) {
    unsigned long now = millis();
    if (now - lastReadTime >= READ_INTERVAL) {
      lastReadTime = now;
      readAndDisplay();
    }
  } else {
    // Cek motion flag bahkan saat auto-read OFF
    if (motionFlag) {
      motionFlag = false;
      Serial.printf("\n🏃 GERAKAN! (total: %d)\n", motionCount);
      if (alarmEnabled) {
        float j = readDistance();
        if (j > 0 && j < DIST_SAFE) {
          triggerAlarm(j);
        }
      }
    }
  }

  // Cek input serial (menu)
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    if (input.length() == 0) return;
    Serial.println(input);
    int choice = input.toInt();
    handleMenu(choice);
  }
}
