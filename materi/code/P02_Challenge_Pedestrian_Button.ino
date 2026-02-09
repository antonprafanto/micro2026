/*
 * ================================================
 * CHALLENGE: PEDESTRIAN CROSSING BUTTON
 * ================================================
 * 
 * Deskripsi:
 * Traffic light dengan pedestrian button:
 * - Normal: RED → YELLOW → GREEN (loop)
 * - Saat button ditekan: Paksa ke RED untuk kasih jalan pejalan kaki
 * - Setelah 10 detik, lanjut cycle normal
 * 
 * Wiring:
 * GPIO15 → Resistor → LED Merah → GND
 * GPIO16 → Resistor → LED Kuning → GND
 * GPIO17 → Resistor → LED Hijau → GND
 * GPIO4  → Button pin 1, Button pin 2 → GND
 * 
 * Author: [Nama Anda]
 * NIM: [NIM Anda]
 */

// Pin definitions
#define RED_LED    15
#define YELLOW_LED 16
#define GREEN_LED  17
#define PED_BUTTON 4  // Pedestrian button

// Timing
#define RED_DURATION    5000
#define YELLOW_DURATION 2000
#define GREEN_DURATION  5000
#define PED_RED_DURATION 10000  // Pedestrian crossing: 10 detik merah

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(PED_BUTTON, INPUT_PULLUP);
  
  Serial.begin(115200);
  Serial.println("Traffic Light with Pedestrian Button");
  Serial.println("Press button to activate pedestrian crossing!");
}

void loop() {
  // Check pedestrian button sebelum tiap state
  if (digitalRead(PED_BUTTON) == LOW) {
    pedestrianCrossing();
  }
  
  // Normal traffic light cycle
  // RED
  Serial.println("🔴 RED");
  setTrafficLight(HIGH, LOW, LOW);
  delayWithButtonCheck(RED_DURATION);
  
  // YELLOW
  Serial.println("🟡 YELLOW");
  setTrafficLight(LOW, HIGH, LOW);
  delayWithButtonCheck(YELLOW_DURATION);
  
  // GREEN
  Serial.println("🟢 GREEN");
  setTrafficLight(LOW, LOW, HIGH);
  delayWithButtonCheck(GREEN_DURATION);
}

// Function: Set traffic light state
void setTrafficLight(int red, int yellow, int green) {
  digitalWrite(RED_LED, red);
  digitalWrite(YELLOW_LED, yellow);
  digitalWrite(GREEN_LED, green);
}

// Function: Delay dengan button check
void delayWithButtonCheck(unsigned long duration) {
  unsigned long start = millis();
  while (millis() - start < duration) {
    if (digitalRead(PED_BUTTON) == LOW) {
      pedestrianCrossing();
      return;  // Exit delay, sudah handle pedestrian
    }
    delay(10);  // Small delay
  }
}

// Function: Pedestrian crossing mode
void pedestrianCrossing() {
  Serial.println("\n🚶 PEDESTRIAN BUTTON PRESSED!");
  Serial.println("⚠️ Forcing RED light for pedestrian crossing...");
  
  // Paksa ke RED
  setTrafficLight(HIGH, LOW, LOW);
  
  // Countdown untuk pedestrian
  for (int i = 10; i > 0; i--) {
    Serial.print("  Pedestrian crossing time: ");
    Serial.print(i);
    Serial.println(" seconds");
    delay(1000);
  }
  
  Serial.println("✅ Pedestrian crossing complete!");
  Serial.println("Resuming normal traffic light...\n");
  
  // Debounce: tunggu button dilepas
  while (digitalRead(PED_BUTTON) == LOW) {
    delay(10);
  }
  delay(100);  // Extra debounce
}

/*
 * CHALLENGE TAMBAHAN:
 * 
 * 1. Pedestrian LED:
 *    - Tambah LED hijau untuk pedestrian (GPIO18)
 *    - ON saat pedestrian crossing, OFF saat tidak
 * 
 * 2. Buzzer:
 *    - Tambah buzzer (GPIO19)
 *    - Beep saat countdown pedestrian crossing
 * 
 * 3. Multiple Button Press Prevention:
 *    - Jika button ditekan saat sudah pedestrian mode, ignore
 *    - Atau: queue request, proses setelah cycle selesai
 */
