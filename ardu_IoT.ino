#include "pHmeter.h"

int SensorPin = A0;

void setup() {
  Serial.begin(9600);

}

void loop() {
  float pHValue pH.measure();
  int humidity = analogRead(SensorPin);
  Serial.println(pHValue);
  Serial.println(humidity);
  delay(1000);

}
