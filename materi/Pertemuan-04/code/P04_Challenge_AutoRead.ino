/*
 * ═══════════════════════════════════════════════════════
 *  CHALLENGE P04: Auto-Read Sensor + Serial Menu Extended
 * ═══════════════════════════════════════════════════════
 *
 *  Pertemuan 4 Challenge: Serial Communication & Debugging
 *  Mata Kuliah Mikrokontroller - Prodi Informatika Unmul
 *
 *  Extends P04_SerialMenu dengan:
 *   → Pilihan 7: Auto-Read Sensor (update tiap 2 detik)
 *                Ketik 's' + Enter untuk stop
 *
 *  Wiring:
 *   - LED    : GPIO15 → 220Ω → LED Anode → Cathode → GND
 *   - Pot    : VCC→3V3, SIG→GPIO34, GND→GND
 *
 *  Serial Monitor: 115200 baud, Line Ending = NL & CR
 */

// ── Pin Definitions ──────────────────────────────────────────────────────────
#define LED_PIN 15
#define POT_PIN 34

// ── PWM Configuration
// ──────────────────────────────────────────────────────────
#define PWM_FREQ 5000
#define PWM_RES 8

// ── Global Variables
// ──────────────────────────────────────────────────────────
bool ledState = false;
int ledBrightness = 0;

// ─────────────────────────────────────────────────────────────────────────────
void printMenu() {
  Serial.println();
  Serial.println("╔══════════════════════════════╗");
  Serial.println("║     ESP32 Control Menu       ║");
  Serial.println("╠══════════════════════════════╣");
  Serial.println("║  1. LED ON                   ║");
  Serial.println("║  2. LED OFF                  ║");
  Serial.println("║  3. Blink 5x                 ║");
  Serial.println("║  4. Read Sensor (ADC)        ║");
  Serial.println("║  5. Set Brightness (0-255)   ║");
  Serial.println("║  6. System Info              ║");
  Serial.println("║  7. Auto Read Sensor 🔴       ║"); // <-- NEW CHALLENGE!
  Serial.println("║  0. Tampilkan Menu lagi      ║");
  Serial.println("╚══════════════════════════════╝");
  Serial.print("Pilihan (0-7): ");
}

// ─────────────────────────────────────────────────────────────────────────────
void blinkLED(int times) {
  Serial.printf("\nBlinking LED %d kali...\n", times);
  for (int i = 0; i < times; i++) {
    ledcWrite(LED_PIN, 255);
    delay(200);
    ledcWrite(LED_PIN, 0);
    delay(200);
    Serial.printf("  Blink %d/%d ✓\n", i + 1, times);
  }
  ledcWrite(LED_PIN, ledBrightness);
  Serial.println("✅ Blink selesai!");
}

// ─────────────────────────────────────────────────────────────────────────────
void readSensor() {
  int adcRaw = analogRead(POT_PIN);
  float voltage = (adcRaw / 4095.0) * 3.3;
  int percent = map(adcRaw, 0, 4095, 0, 100);

  Serial.println("\n┌─── Sensor Reading ───┐");
  Serial.printf("│ ADC Value  : %4d      │\n", adcRaw);
  Serial.printf("│ Voltage    : %.2fV     │\n", voltage);
  Serial.printf("│ Percentage : %3d%%     │\n", percent);
  Serial.println("└──────────────────────┘");
}

// ─────────────────────────────────────────────────────────────────────────────
void systemInfo() {
  Serial.println("\n┌─── System Info ────────────────┐");
  Serial.printf("│ Uptime       : %.1f s          \n", millis() / 1000.0);
  Serial.printf("│ LED State    : %s              \n", ledState ? "ON" : "OFF");
  Serial.printf("│ Brightness   : %d/255 (%.1f%%) \n", ledBrightness,
                ledBrightness / 255.0 * 100);
  Serial.printf("│ Free Heap    : %d bytes        \n", ESP.getFreeHeap());
  Serial.printf("│ CPU Freq     : %d MHz          \n", ESP.getCpuFreqMHz());
  Serial.println("└────────────────────────────────┘");
}

// ─────────────────────────────────────────────────────────────────────────────
// CHALLENGE: Auto-Read Sensor
// Update sensor tiap 2 detik. Ketik 's' + Enter untuk stop.
// ─────────────────────────────────────────────────────────────────────────────
void autoReadSensor() {
  Serial.println("\n🔴 AUTO READ MODE ON");
  Serial.println("   Sensor update tiap 2 detik.");
  Serial.println("   Ketik 's' + Enter untuk stop.\n");

  int readCount = 0;

  while (true) {
    // Cek apakah ada input stop ('s')
    if (Serial.available() > 0) {
      String input = Serial.readStringUntil('\n');
      input.trim();
      input.toLowerCase();
      if (input == "s" || input == "stop") {
        Serial.println("\n⏹️  AUTO READ STOPPED.");
        break;
      }
    }

    // Baca sensor
    readCount++;
    int adcRaw = analogRead(POT_PIN);
    float voltage = (adcRaw / 4095.0) * 3.3;
    int percent = map(adcRaw, 0, 4095, 0, 100);

    Serial.printf("[%3d] ADC: %4d | %.2fV | %3d%% | t=%.1fs\n", readCount,
                  adcRaw, voltage, percent, millis() / 1000.0);

    // Tunggu 2 detik sambil tetap cek input setiap 100ms
    for (int i = 0; i < 20; i++) {
      delay(100);
      if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        input.trim();
        input.toLowerCase();
        if (input == "s" || input == "stop") {
          Serial.println("\n⏹️  AUTO READ STOPPED.");
          return;
        }
      }
    }
  }
}

// ─────────────────────────────────────────────────────────────────────────────
void handleMenu(int choice) {
  switch (choice) {
  case 1:
    ledcWrite(LED_PIN, 255);
    ledState = true;
    ledBrightness = 255;
    Serial.println("\n✅ LED ON (255/255)");
    break;

  case 2:
    ledcWrite(LED_PIN, 0);
    ledState = false;
    ledBrightness = 0;
    Serial.println("\n✅ LED OFF");
    break;

  case 3:
    blinkLED(5);
    break;

  case 4:
    readSensor();
    break;

  case 5:
    Serial.print("\nMasukkan brightness (0-255): ");
    while (Serial.available() == 0) {
      delay(10);
    }
    {
      String br = Serial.readStringUntil('\n');
      br.trim();
      int brightness = constrain(br.toInt(), 0, 255);
      ledcWrite(LED_PIN, brightness);
      ledState = (brightness > 0);
      ledBrightness = brightness;
      Serial.printf("✅ Brightness → %d/255 (%.1f%%)\n", brightness,
                    brightness / 255.0 * 100);
    }
    break;

  case 6:
    systemInfo();
    break;

  case 7: // ← CHALLENGE: Auto-Read!
    autoReadSensor();
    break;

  case 0:
    break;

  default:
    Serial.println("\n❌ Pilihan tidak valid! Pilih 0-7.");
    break;
  }
  printMenu();
}

// ─────────────────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  ledcAttach(LED_PIN, PWM_FREQ, PWM_RES);
  ledcWrite(LED_PIN, 0);

  delay(200);
  Serial.println("\n🚀 ESP32 Serial Menu (Challenge: Auto-Read)");
  Serial.println("Mikrokontroller - Prodi Informatika Unmul\n");
  printMenu();
}

// ─────────────────────────────────────────────────────────────────────────────
void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    if (input.length() == 0)
      return;
    Serial.println(input);
    handleMenu(input.toInt());
  }
}
