/*
 * =============================================
 *  PROJECT: ESP32 INTERACTIVE SERIAL MENU
 * =============================================
 *
 *  Pertemuan 4: Serial Communication & Debugging
 *  Mata Kuliah Mikrokontroller - Prodi Informatika Unmul
 *
 *  Features:
 *   - Menu interaktif via Serial Monitor (pilihan 0-6)
 *   - LED ON/OFF/Blink control
 *   - LED Brightness control (0-255)
 *   - ADC Sensor reading (Potensiometer)
 *   - System Info (uptime, free heap, CPU freq)
 *
 *  Wiring:
 *   - LED    : GPIO15 → Resistor 220Ω → LED Anode → LED Cathode → GND
 *   - Pot    : VCC→3V3, SIG→GPIO34, GND→GND
 *
 *  Serial Monitor Settings:
 *   - Baud Rate : 115200
 *   - Line Ending: NL & CR (Both NL & CR)
 */

// ── Pin Definitions ──────────────────────────────────────────────────────────
#define LED_PIN 15
#define POT_PIN 34

// ── PWM Configuration
// ──────────────────────────────────────────────────────────
#define PWM_FREQ 5000 // 5 kHz (smooth untuk LED)
#define PWM_RES 8     // 8-bit resolution (0-255)

// ── Global Variables
// ──────────────────────────────────────────────────────────
bool ledState = false;
int ledBrightness = 0;

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: printMenu
// Tampilkan menu interaktif ke Serial Monitor
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
  Serial.println("║  0. Tampilkan Menu lagi      ║");
  Serial.println("╚══════════════════════════════╝");
  Serial.print("Pilihan (0-6): ");
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: blinkLED
// Blink LED sebanyak n kali, lalu restore ke brightness semula
// ─────────────────────────────────────────────────────────────────────────────
void blinkLED(int times) {
  Serial.printf("\nBlinking LED %d kali...\n", times);
  for (int i = 0; i < times; i++) {
    ledcWrite(LED_PIN, 255); // LED ON
    delay(200);
    ledcWrite(LED_PIN, 0); // LED OFF
    delay(200);
    Serial.printf("  Blink %d/%d ✓\n", i + 1, times);
  }
  // Restore ke brightness sebelumnya
  ledcWrite(LED_PIN, ledBrightness);
  Serial.println("✅ Blink selesai!");
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: readSensor
// Baca nilai ADC dari potensiometer dan tampilkan di serial
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
// FUNCTION: systemInfo
// Tampilkan informasi sistem ESP32
// ─────────────────────────────────────────────────────────────────────────────
void systemInfo() {
  unsigned long uptimeMs = millis();
  float uptimeSec = uptimeMs / 1000.0;

  Serial.println("\n┌─── System Info ────────────────┐");
  Serial.printf("│ Uptime       : %lu ms (%.1fs)  \n", uptimeMs, uptimeSec);
  Serial.printf("│ LED State    : %s              \n", ledState ? "ON" : "OFF");
  Serial.printf("│ Brightness   : %d/255 (%.1f%%) \n", ledBrightness,
                ledBrightness / 255.0 * 100);
  Serial.printf("│ Free Heap    : %d bytes        \n", ESP.getFreeHeap());
  Serial.printf("│ CPU Freq     : %d MHz          \n", ESP.getCpuFreqMHz());
  Serial.printf("│ Flash Size   : %d KB           \n",
                ESP.getFlashChipSize() / 1024);
  Serial.println("└────────────────────────────────┘");
}

// ─────────────────────────────────────────────────────────────────────────────
// FUNCTION: handleMenu
// Proses pilihan menu dari user
// ─────────────────────────────────────────────────────────────────────────────
void handleMenu(int choice) {
  switch (choice) {

  case 1: // LED ON ──────────────────────────────────────────────────────
    ledcWrite(LED_PIN, 255);
    ledState = true;
    ledBrightness = 255;
    Serial.println("\n✅ LED ON (brightness: 255/255 = 100%)");
    break;

  case 2: // LED OFF ─────────────────────────────────────────────────────
    ledcWrite(LED_PIN, 0);
    ledState = false;
    ledBrightness = 0;
    Serial.println("\n✅ LED OFF");
    break;

  case 3: // BLINK 5x ────────────────────────────────────────────────────
    blinkLED(5);
    break;

  case 4: // READ SENSOR ──────────────────────────────────────────────────
    readSensor();
    break;

  case 5: // SET BRIGHTNESS ───────────────────────────────────────────────
    Serial.print("\nMasukkan brightness (0-255): ");
    // Tunggu user input
    while (Serial.available() == 0) {
      delay(10); // Non-blocking wait
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

  case 6: // SYSTEM INFO ──────────────────────────────────────────────────
    systemInfo();
    break;

  case 0: // TAMPILKAN MENU ───────────────────────────────────────────────
    // Menu ditampilkan di printMenu() di bawah
    break;

  default: // PILIHAN TIDAK VALID ─────────────────────────────────────────
    Serial.println("\n❌ Pilihan tidak valid! Pilih 0-6.");
    break;
  }

  // Selalu tampilkan menu lagi setelah handle
  printMenu();
}

// ─────────────────────────────────────────────────────────────────────────────
// SETUP
// ─────────────────────────────────────────────────────────────────────────────
void setup() {
  // Inisialisasi Serial
  Serial.begin(115200);

  // Inisialisasi LED dengan LEDC (PWM)
  ledcAttach(LED_PIN, PWM_FREQ, PWM_RES);
  ledcWrite(LED_PIN, 0); // Pastikan LED mati saat start

  // Splash screen
  delay(200);
  Serial.println("\n");
  Serial.println("╔═══════════════════════════════════════╗");
  Serial.println("║    ESP32 Interactive Serial Menu      ║");
  Serial.println("║    Pertemuan 4: Serial Communication  ║");
  Serial.println("║    Mikrokontroller - Prodi Informatika ║");
  Serial.println("╚═══════════════════════════════════════╝");
  Serial.println();
  Serial.printf("Baud Rate  : 115200\n");
  Serial.printf("LED Pin    : GPIO%d\n", LED_PIN);
  Serial.printf("Sensor Pin : GPIO%d (ADC)\n", POT_PIN);
  Serial.println();
  Serial.println("⚙️  Setup selesai! Menampilkan menu...");
  delay(500);

  // Tampilkan menu pertama kali
  printMenu();
}

// ─────────────────────────────────────────────────────────────────────────────
// LOOP
// ─────────────────────────────────────────────────────────────────────────────
void loop() {
  // Cek apakah ada input dari Serial Monitor
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim(); // Hapus whitespace/newline

    // Abaikan input kosong
    if (input.length() == 0)
      return;

    // Echo input
    Serial.println(input);

    // Parse pilihan (integer)
    int choice = input.toInt();

    // Handle menu
    handleMenu(choice);
  }
}
