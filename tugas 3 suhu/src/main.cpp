#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// --- Konfigurasi pin ---
#define DHTPIN 14        // Pin data DHT22
#define DHTTYPE DHT22
#define LDR_PIN 34       // Pin analog LDR (AO)

// --- Inisialisasi sensor ---
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4); // Alamat I2C LCD: 0x27 umum di Wokwi

void setup() {
  Serial.begin(115200);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("   Sistem Monitoring");
  delay(2000);
  lcd.clear();
}

void loop() {
  float suhu = dht.readTemperature();     // Celsius
  float kelembapan = dht.readHumidity();
  int cahaya = analogRead(LDR_PIN);       // Nilai 0 - 4095 (ESP32 ADC)

  // Tampilkan di Serial Monitor
  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.print(" C | Kelembapan: ");
  Serial.print(kelembapan);
  Serial.print(" % | Cahaya: ");
  Serial.println(cahaya);

  // Tampilkan di LCD
  lcd.setCursor(0, 0);
  lcd.print("Suhu     : ");
  lcd.print(suhu, 1);
  lcd.print((char)223); // simbol derajat
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Kelembapan: ");
  lcd.print(kelembapan, 1);
  lcd.print(" %");

  lcd.setCursor(0, 2);
  lcd.print("Cahaya   : ");
  lcd.print(cahaya);

  lcd.setCursor(0, 3);
  lcd.print("Monitoring Aktif...");

  delay(2000); // update setiap 2 detik
}
