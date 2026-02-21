#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Explicitly define I2C pins for ESP32
  Wire.begin(21, 22);  // SDA = GPIO21, SCL = GPIO22

  Serial.println("Starting BME280 test...");

  // Try address 0x76 first
  if (!bme.begin(0x76)) {
    Serial.println("Could not find BME280 at 0x76, trying 0x77...");

    // Then try 0x77
    if (!bme.begin(0x77)) {
      Serial.println("BME280 not found. Check wiring!");
      while (1);
    }
  }

  Serial.println("BME280 found!");
}

void loop() {

  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.println("----------------------");

  delay(2000);
}