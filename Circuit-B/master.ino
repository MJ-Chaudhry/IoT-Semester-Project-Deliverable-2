// MASTER ESP Code
// This ESP measures the MQ-5 reading,
// If it crosses the threshold, it sends a signal to the slave.

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

constexpr int MQ5_PIN = 36;

constexpr int GAS_THRESHOLD = 3000;

void setup() {
  Serial.begin(115200);
}

void loop() {
  int mq5_value = analogRead(MQ5_PIN);

  if (mq5_value > GAS_THRESHOLD) {
    Serial.write(1);
  } else {
    Serial.write(0);
  }

  delay(200);
}