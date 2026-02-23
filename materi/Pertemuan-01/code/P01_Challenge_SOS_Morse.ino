/*
 * ================================================
 * CHALLENGE: SOS MORSE CODE
 * ================================================
 * 
 * Deskripsi:
 * Program untuk menampilkan SOS dalam Morse Code menggunakan LED
 * 
 * SOS Morse Code:
 * S = ··· (3× short blink)
 * O = ─── (3× long blink)
 * S = ··· (3× short blink)
 * 
 * Pattern: ··· ─── ··· (pause) repeat
 * 
 * Author: [Nama Anda]
 * NIM: [NIM Anda]
 */

#define LED_BUILTIN 2

#define SHORT_BLINK 200   // Short blink duration (ms)
#define LONG_BLINK 600    // Long blink duration (ms)
#define PAUSE_SHORT 200   // Pause between blinks (ms)
#define PAUSE_LETTER 500  // Pause between letters (ms)
#define PAUSE_WORD 2000   // Pause before repeat (ms)

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("SOS Morse Code");
}

void loop() {
  // S - 3× short blink (···)
  Serial.println("S: ··· ");
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(SHORT_BLINK);
    digitalWrite(LED_BUILTIN, LOW);
    delay(PAUSE_SHORT);
  }
  
  delay(PAUSE_LETTER);  // Pause antara S dan O
  
  // O - 3× long blink (─── )
  Serial.println("O: ───");
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(LONG_BLINK);
    digitalWrite(LED_BUILTIN, LOW);
    delay(PAUSE_SHORT);
  }
  
  delay(PAUSE_LETTER);  // Pause antara O dan S
  
  // S - 3× short blink (···)
  Serial.println("S: ···");
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(SHORT_BLINK);
    digitalWrite(LED_BUILTIN, LOW);
    delay(PAUSE_SHORT);
  }
  
  Serial.println("--- PAUSE ---\n");
  delay(PAUSE_WORD);  // Pause sebelum repeat
}

/*
 * CHALLENGE TAMBAHAN:
 * 
 * 1. Tambahkan Morse code untuk kata lain:
 *    - A: ·─
 *    - B: ─···
 *    - C: ─·─·
 *    (Cari Morse code table di internet)
 * 
 * 2. Buat fungsi untuk short dan long blink:
 *    void shortBlink() { ... }
 *    void longBlink() { ... }
 * 
 * 3. Buat array untuk pattern:
 *    int sosPattern[] = {1,1,1, 3,3,3, 1,1,1};
 *    (1 = short, 3 = long)
 */
