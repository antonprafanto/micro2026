/*
 * ================================================
 * PROJECT: INTERACTIVE LED DIMMER
 * Pertemuan 3 - Analog I/O & PWM
 * ================================================
 * 
 * Deskripsi:
 * Control LED brightness dengan potensiometer secara real-time
 * - Pot 0%: LED OFF
 * - Pot 50%: LED setengah terang
 * - Pot 100%: LED maksimal
 * 
 * Hardware Required (Wokwi):
 * - ESP32 DevKit V1
 * - 1× Potensiometer (10kΩ recommended)
 * - 1× LED (any color)
 * - 1× Resistor 220Ω
 * 
 * Wiring:
 * Potensiometer:
 *   VCC → ESP32 3.3V
 *   SIG (wiper) → ESP32 GPIO34 (ADC pin)
 *   GND → ESP32 GND
 * 
 * LED:
 *   GPIO15 → Resistor 220Ω → LED Anode (+) → LED Cathode (-) → GND
 * 
 * Author: [Nama Anda]
 * NIM: [NIM Anda]
 * Tanggal: [Tanggal]
 * ================================================
 */

// ===== PIN CONFIGURATION =====
#define POT_PIN 34       // Potensiometer di GPIO34 (ADC1_6 - recommended!)
#define LED_PIN 15       // LED output di GPIO15

// ===== PWM CONFIGURATION =====
#define PWM_CHANNEL 0    // PWM channel (ESP32 punya 0-15)
#define PWM_FREQ 5000    // Frequency 5 kHz (smooth untuk mata manusia)
#define PWM_RESOLUTION 8 // 8-bit resolution (0-255, sama seperti Arduino)

// ===== SETUP (Jalan 1x saat boot) =====
void setup() {
  // Setup PWM untuk LED
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(LED_PIN, PWM_CHANNEL);
  
  // Inisialisasi serial communication
  Serial.begin(115200);
  delay(100);
  
  // Print header
  Serial.println("\n======================================");
  Serial.println("     INTERACTIVE LED DIMMER");
  Serial.println("======================================");
  Serial.println("Controls:");
  Serial.println("  - Turn POT left: LED dimmer");
  Serial.println("  - Turn POT right: LED brighter");
  Serial.println("======================================\n");
  
  // Test LED (startup test)
  Serial.println("Startup test - LED fading...");
  for (int i = 0; i <= 255; i += 5) {
    ledcWrite(PWM_CHANNEL, i);
    delay(10);
  }
  for (int i = 255; i >= 0; i -= 5) {
    ledcWrite(PWM_CHANNEL, i);
    delay(10);
  }
  
  Serial.println("Ready! Turn the potentiometer.\n");
}

// ===== LOOP (Jalan terus-menerus) =====
void loop() {
  // Baca nilai ADC dari potensiometer (0-4095)
  int potValue = analogRead(POT_PIN);
  
  // Scale ADC value (0-4095) ke PWM range (0-255)
  int brightness = map(potValue, 0, 4095, 0, 255);
  
  // Set LED brightness via PWM
  ledcWrite(PWM_CHANNEL, brightness);
  
  // Calculate percentage untuk display
  int percentage = map(brightness, 0, 255, 0, 100);
  
  // Print status ke serial monitor
  Serial.print("POT: ");
  Serial.print(potValue);
  Serial.print(" (");
  printProgressBar(percentage);
  Serial.print(") | Brightness: ");
  Serial.print(brightness);
  Serial.print("/255");
  Serial.print(" (");
  Serial.print(percentage);
  Serial.println("%)");
  
  delay(50);  // Update rate: 20× per detik (responsive!)
}

// ===== HELPER FUNCTION: Progress Bar =====
void printProgressBar(int percentage) {
  // Visual progress bar untuk serial monitor
  int bars = percentage / 5;  // 20 bars max (100% / 5)
  
  for (int i = 0; i < 20; i++) {
    if (i < bars) {
      Serial.print("█");  // Filled bar
    } else {
      Serial.print("░");  // Empty bar
    }
  }
}

/*
 * ===== CATATAN PENTING =====
 * 
 * 1. ADC (Analog-to-Digital Converter):
 *    - ESP32 ADC: 12-bit resolution (0-4095)
 *    - Voltage range: 0V - 3.3V
 *    - GPIO34-39: ADC1 pins (recommended, tidak conflict dengan WiFi)
 * 
 * 2. PWM (Pulse Width Modulation):
 *    - Technique untuk control analog output dengan digital signal
 *    - Duty cycle: percentage waktu signal ON (0-100%)
 *    - Frequency: berapa kali ON-OFF per detik (Hz)
 * 
 * 3. LEDC (LED Controller):
 *    - ESP32 hardware PWM peripheral
 *    - 16 channel independen (0-15)
 *    - Configurable frequency & resolution
 *    - Setup: ledcSetup() → ledcAttachPin() → ledcWrite()
 * 
 * 4. map() Function:
 *    - Linear scaling dari range ke range lain
 *    - Syntax: map(value, fromLow, fromHigh, toLow, toHigh)
 *    - Example: map(2048, 0, 4095, 0, 255) = 128
 * 
 * ===== TROUBLESHOOTING =====
 * 
 * Problem: "LED tidak berubah brightness saat putar pot"
 * - Check wiring potensiometer (VCC, SIG, GND correct?)
 * - Check GPIO number di code (34 untuk pot, 15 untuk LED)
 * - Serial monitor: apakah pot value berubah saat putar?
 * - Jika pot value tidak berubah → wiring pot salah
 * - Jika pot value berubah tapi LED tidak → check ledcWrite()
 * 
 * Problem: "LED sangat redup, tidak bisa terang penuh"
 * - Check resistor value (jangan terlalu besar, pakai 220Ω-330Ω)
 * - Check PWM brightness reach 255 (print di serial monitor)
 * - Check polaritas LED (anode ke resistor, cathode ke GND)
 * 
 * Problem: "LED berkedip-kedip saat adjust pot"
 * - PWM frequency terlalu rendah (pastikan 5000 Hz)
 * - delay() terlalu besar (kurangi jadi 50ms atau 20ms)
 * 
 * Problem: "Serial monitor output terlalu cepat, tidak bisa baca"
 * - Increase delay() di loop (coba 100ms atau 200ms)
 * - Atau kurangi Serial.print() calls (comment yang tidak perlu)
 * 
 * ===== MODIFIKASI CHALLENGE =====
 * 
 * 1. Breathing LED dengan Variable Speed:
 *    - Potensiometer kontrol speed fade in/out
 *    - Speed lambat (delay besar) vs cepat (delay kecil)
 * 
 * 2. Dual LED (Inverse Control):
 *    - 2 LED: saat LED1 terang, LED2 redup (inverse)
 *    - brightness1 = 255, brightness2 = 255 - brightness1
 * 
 * 3. LED dengan Threshold:
 *    - Pot < 50%: LED OFF
 *    - Pot >= 50%: LED ON dengan brightness sesuai pot
 *    - Simulasi "push to start" mechanism
 * 
 * 4. Multiple Brightness Levels (Discrete):
 *    - Bukan smooth, tapi step-step: 0%, 25%, 50%, 75%, 100%
 *    - Map pot value ke 5 discrete levels
 * 
 * ===== NEXT STEPS =====
 * 
 * Setelah berhasil:
 * - Screenshot & share link Wokwi untuk submission
 * - Coba putar pot dari 0% → 100% smooth
 * - Challenge: Tambah LED kedua atau RGB LED!
 */
