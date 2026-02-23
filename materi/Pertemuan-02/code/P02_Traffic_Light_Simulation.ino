/*
 * ================================================
 * PROJECT: TRAFFIC LIGHT SIMULATION
 * Pertemuan 2 - Digital I/O & Multiple LED
 * ================================================
 * 
 * Deskripsi:
 * Simulasi lampu lalu lintas dengan 3 LED (Merah, Kuning, Hijau)
 * Pattern: Merah (5s) → Kuning (2s) → Hijau (5s) → Repeat
 * 
 * Hardware Required (Wokwi):
 * - ESP32 DevKit V1
 * - 3× LED (Merah, Kuning/Oranye, Hijau)
 * - 3× Resistor 220Ω
 * 
 * Wiring:
 * GPIO15 → Resistor 220Ω → LED Merah → GND
 * GPIO16 → Resistor 220Ω → LED Kuning → GND
 * GPIO17 → Resistor 220Ω → LED Hijau → GND
 * 
 * Author: [Nama Anda]
 * NIM: [NIM Anda]
 * Tanggal: [Tanggal]
 * ================================================
 */

// ===== KONFIGURASI PIN =====
#define RED_LED    15  // GPIO15 → LED Merah
#define YELLOW_LED 16  // GPIO16 → LED Kuning
#define GREEN_LED  17  // GPIO17 → LED Hijau

// ===== KONFIGURASI TIMING (milliseconds) =====
#define RED_DURATION    5000  // Merah: 5 detik
#define YELLOW_DURATION 2000  // Kuning: 2 detik
#define GREEN_DURATION  5000  // Hijau: 5 detik

// ===== SETUP (Jalan 1x saat boot) =====
void setup() {
  // Set semua LED sebagai OUTPUT
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  
  // Inisialisasi serial communication
  Serial.begin(115200);
  delay(100);
  
  // Print header
  Serial.println("\n=================================");
  Serial.println("  TRAFFIC LIGHT SIMULATION");
  Serial.println("=================================");
  Serial.println("Pattern:");
  Serial.println("  🔴 RED    (5s) - STOP!");
  Serial.println("  🟡 YELLOW (2s) - GET READY!");
  Serial.println("  🟢 GREEN  (5s) - GO!");
  Serial.println("=================================\n");
  
  // Test semua LED (startup test)
  Serial.println("Startup test - All LED ON...");
  digitalWrite(RED_LED, HIGH);
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  delay(1000);
  
  // Matikan semua LED
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  delay(500);
  
  Serial.println("Starting traffic light cycle...\n");
}

// ===== LOOP (Jalan terus-menerus) =====
void loop() {
  // ===== STATE 1: RED LIGHT (Stop!) =====
  Serial.println("🔴 RED LIGHT - STOP!");
  digitalWrite(RED_LED, HIGH);     // Merah ON
  digitalWrite(YELLOW_LED, LOW);   // Kuning OFF
  digitalWrite(GREEN_LED, LOW);    // Hijau OFF
  delay(RED_DURATION);             // Tunggu 5 detik
  
  // ===== STATE 2: YELLOW LIGHT (Get Ready!) =====
  Serial.println("🟡 YELLOW LIGHT - GET READY!");
  digitalWrite(RED_LED, LOW);      // Merah OFF
  digitalWrite(YELLOW_LED, HIGH);  // Kuning ON
  digitalWrite(GREEN_LED, LOW);    // Hijau OFF
  delay(YELLOW_DURATION);          // Tunggu 2 detik
  
  // ===== STATE 3: GREEN LIGHT (Go!) =====
  Serial.println("🟢 GREEN LIGHT - GO!");
  digitalWrite(RED_LED, LOW);      // Merah OFF
  digitalWrite(YELLOW_LED, LOW);   // Kuning OFF
  digitalWrite(GREEN_LED, HIGH);   // Hijau ON
  delay(GREEN_DURATION);           // Tunggu 5 detik
  
  // Separator untuk cycle berikutnya
  Serial.println("--- Cycle Complete! Repeating... ---\n");
  
  // Loop akan otomatis repeat dari awal
}

/*
 * ===== CATATAN PENTING =====
 * 
 * 1. Timing Configuration:
 *    - Ubah RED_DURATION, YELLOW_DURATION, GREEN_DURATION untuk adjust timing
 *    - Satuan: milliseconds (1000ms = 1 detik)
 * 
 * 2. State Machine:
 *    - Setiap state, hanya 1 LED yang ON, 2 lainnya OFF
 *    - Pattern: RED → YELLOW → GREEN → Repeat
 * 
 * 3. Serial Monitor:
 *    - Output menunjukkan state saat ini (untuk debugging)
 *    - Baud rate: 115200
 * 
 * 4. Startup Test:
 *    - Saat boot, semua LED ON selama 1 detik (test wiring)
 *    - Jika ada LED yang tidak nyala, check wiring!
 * 
 * ===== MODIFIKASI CHALLENGE =====
 * 
 * 1. Ubah Timing:
 *    - Coba Red 3s, Yellow 1s, Green 7s
 *    - Atau sesuaikan dengan timing real traffic light di kotamu!
 * 
 * 2. Tambah Night Mode (Kuning Blink):
 *    - Setelah beberapa cycle normal, masuk night mode
 *    - Night mode: hanya kuning berkedip (ON 500ms, OFF 500ms)
 * 
 * 3. Pedestrian Button:
 *    - Tambah button (GPIO4)
 *    - Saat button ditekan, paksa ke RED untuk kasih jalan pejalan kaki
 * 
 * 4. Counter:
 *    - Tambah counter, tampilkan cycle ke berapa di serial monitor
 *    - "Cycle #1", "Cycle #2", dst.
 * 
 * ===== COMMON ERRORS & SOLUTIONS =====
 * 
 * Error: "LED tidak menyala"
 * - Check wiring: GPIO → Resistor → LED anode → LED cathode → GND
 * - Polaritas LED: kaki panjang (anode) ke resistor, kaki pendek (cathode) ke GND
 * - Code: pinMode(LED_PIN, OUTPUT) sudah ada di setup()?
 * 
 * Error: "Semua LED nyala bersamaan"
 * - Check logic di each state: pastikan hanya 1 HIGH, 2 LOW
 * - Mungkin lupa digitalWrite(LED, LOW) untuk LED yang lain
 * 
 * Error: "Timing tidak sesuai"
 * - Check delay() duration
 * - Pastikan tidak ada delay() tambahan yang tidak disengaja
 * 
 * ===== NEXT STEPS =====
 * 
 * Setelah berhasil:
 * - Screenshot & share link Wokwi untuk submission
 * - Coba modifikasi timing atau pattern
 * - Challenge: Tambah button atau night mode!
 */
