#include "InternetButton.h"
#include "math.h"

/**
 * Sensor calibration data:
 * Wet = 1520
 * Dry = 3120
 * (Calibrate this for yourself!)
 */

InternetButton b = InternetButton();

// Pin definitions
int moistureRead = A0;
int moisturePower = D2;
int pumpPower = D1;

void setup() {
  b.begin();

  pinMode(moisturePower, OUTPUT);
  pinMode(pumpPower, OUTPUT);

  Particle.function("moisture", measureMoisture);
  Particle.function("waterPlant", waterPlant);
  Particle.function("delayWithProgress", delayWithProgress);
}

void loop() {
  return;
}

int measureMoisture(String unused) {
  digitalWrite(moisturePower, HIGH);
  delay(250);
  int moistureLevel = analogRead(moistureRead);
  digitalWrite(moisturePower, LOW);
  return moistureLevel;
}

// TODO: let this take an amount of time in sec
int waterPlant(String unused) {
  digitalWrite(pumpPower, HIGH);
  delayWithProgress("15000");
  digitalWrite(pumpPower, LOW);
  return 0;
}

/**
 * Shows an LED count up while delaying for a total of totalLength ms.
 * Needs to take a string so we can expose it as a Particle function.
 */
int delayWithProgress(String totalLength) {
  int totalLengthInt = totalLength.toInt();
  int delayPerLED = totalLengthInt / 11;
  b.allLedsOff();
  for (int i = 1; i <= 11; i++) {
    b.ledOn(i, 0, 190, 227);
    delay(delayPerLED);
  }
  b.allLedsOff();
  return delayPerLED;
}
