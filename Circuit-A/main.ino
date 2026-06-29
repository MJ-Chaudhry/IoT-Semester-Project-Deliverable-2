#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#include "DHTesp.h"

constexpr int DHT_PIN = 15;
constexpr int MQ5_PIN = 36;
constexpr int GAS_THRESHOLD = 3000;

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
  int mq5_value = analogRead(MQ5_PIN);

  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  Serial.println(data.temperature);

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("T: " + String(data.temperature, 2) + " C");
  display.println("H: " + String(data.humidity, 1) + "%");
  if (mq5_value > GAS_THRESHOLD) {
    display.println("Leaking!");
  } else {
    display.println("No Leak");
  }
  display.display();

  delay(200);
}