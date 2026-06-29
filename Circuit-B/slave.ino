// SLAVE ESP Code
// Mesures the temperature and humidity.
// If it receives a signal from the master ESP,
// it displays whether a gas leak has been detected.

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#include "DHTesp.h"

constexpr int DHT_PIN = 15;

Adafruit_SH1106G display(128, 64, &Wire, -1);
DHTesp dhtSensor;

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);
  display.begin(0x3C, true);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);

  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
}

void loop() {
  static int mq5_value = 0;

  // Check if data is available in the Serial buffer
  while (Serial.available()) {
    int incomingChar = Serial.read();  // Read each character from the buffer
    
    mq5_value = incomingChar;
  }

  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  Serial.println(data.temperature);

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("T: " + String(data.temperature, 2) + " C");
  display.println("H: " + String(data.humidity, 1) + "%");
  if (mq5_value > 0) {
    display.println("Leaking!");
  } else {
    display.println("No Leak");
  }
  display.display();

  delay(200);
}