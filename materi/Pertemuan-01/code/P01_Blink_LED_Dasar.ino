/*
 * ================================================
 * PERTEMUAN 1: BLINK LED ONBOARD ESP32
 * ================================================
 * 
 * Deskripsi:
 * Program sederhana untuk membuat LED onboard ESP32 berkedip
 * ON-OFF setiap 1 detik. Ini adalah program "Hello World" untuk
 * embedded systems!
 * 
 * Hardware Required:
 * - ESP32 DevKit V1 (NodeMCU-32S atau sejenisnya)
 * - Kabel USB untuk koneksi ke laptop
 * 
 * Wiring:
 * Tidak perlu wiring! LED onboard sudah built-in di GPIO 2
 * 
 * Library Required:
 * Tidak ada (menggunakan fungsi Arduino core)
 * 
 * Cara Upload:
 * 1. Hubungkan ESP32 ke laptop via USB
 * 2. Pilih board: Tools → Board → ESP32 Dev Module
 * 3. Pilih port: Tools → Port → COM# (sesuai yang terdeteksi)
 * 4. Klik Upload (atau Ctrl+U)
 * 5. Jika stuck "Connecting...", tekan tombol BOOT di ESP32
 * 
 * Expected Result:
 * - LED onboard (biru kecil di board) akan berkedip setiap 1 detik
 * - Serial monitor akan menampilkan "LED ON" dan "LED OFF"
 * 
 * Author: [Nama Anda]
 * NIM: [NIM Anda]
 * Tanggal: [Tanggal]
 * ================================================
 */

// ===== KONFIGURASI PIN =====
#define LED_BUILTIN 2  // GPIO 2 adalah LED onboard di ESP32
                       // (beberapa board bisa GPIO 25, cek board Anda)

// ===== KONFIGURASI TIMING =====
#define BLINK_DELAY 1000  // Delay dalam milliseconds (1000ms = 1 detik)

// ===== SETUP (Jalan 1x saat boot) =====
void setup() {
  // Inisialisasi serial communication (untuk debugging)
  Serial.begin(115200);  // Baud rate 115200 (standar untuk ESP32)
  
  // Tunggu serial connection ready (untuk beberapa board)
  delay(100);
  
  // Set GPIO 2 sebagai OUTPUT
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Print pesan startup
  Serial.println("\n=================================");
  Serial.println("ESP32 Blink Program");
  Serial.println("Pertemuan 1 - Mikrokontroller");
  Serial.println("=================================");
  Serial.println("LED akan berkedip setiap 1 detik");
  Serial.println();
}

// ===== LOOP (Jalan terus-menerus) =====
void loop() {
  // Nyalakan LED (set GPIO ke HIGH = 3.3V)
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("💡 LED ON");
  
  // Tunggu sesuai BLINK_DELAY
  delay(BLINK_DELAY);
  
  // Matikan LED (set GPIO ke LOW = 0V)
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("⚫ LED OFF");
  
  // Tunggu sesuai BLINK_DELAY
  delay(BLINK_DELAY);
  
  // Loop akan repeat otomatis dari awal
}

/*
 * ===== CATATAN PENTING =====
 * 
 * 1. pinMode():
 *    - Mengatur mode GPIO (INPUT atau OUTPUT)
 *    - Harus dipanggil di setup() sebelum digunakan
 * 
 * 2. digitalWrite():
 *    - HIGH = nyalakan LED (3.3V di ESP32)
 *    - LOW = matikan LED (0V/GND)
 * 
 * 3. delay():
 *    - Mengehentikan program selama waktu tertentu
 *    - Satuan: milliseconds (1000ms = 1 detik)
 *    - Blocking function (program berhenti total)
 * 
 * 4. Serial.begin():
 *    - Inisialisasi komunikasi serial untuk debugging
 *    - Baud rate harus sama dengan Serial Monitor (115200)
 * 
 * ===== MODIFIKASI CHALLENGE =====
 * 
 * 1. Ubah kecepatan blink:
 *    - Coba ubah BLINK_DELAY menjadi 500, 2000, 100
 *    - Lihat perbedaannya!
 * 
 * 2. Buat pattern berbeda:
 *    - ON 2 detik, OFF 0.5 detik
 *    - ON 0.2 detik, OFF 0.2 detik (3×), pause 1 detik, repeat
 * 
 * 3. Blink dengan hitungan:
 *    - Tambahkan counter, print "Blink count: X"
 * 
 * ===== TROUBLESHOOTING =====
 * 
 * Jika LED tidak berkedip:
 * - Cek apakah upload sukses (lihat pesan di Arduino IDE)
 * - Cek Serial Monitor apakah ada output
 * - Tekan tombol RST di ESP32 untuk restart
 * - Coba upload ulang dengan tekan BOOT
 * 
 * Jika error "Board not found":
 * - Install driver CH340 atau CP2102
 * - Coba USB port lain
 * - Restart Arduino IDE
 * 
 * ===== NEXT STEPS =====
 * 
 * Setelah berhasil, coba:
 * - Pertemuan 2: External LED dengan breadboard
 * - Tambahkan button untuk kontrol
 * - Multiple LED pattern (traffic light)
 */
