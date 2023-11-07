#include "pHmeter.h"

void setup() {
  Serial.begin(9600);

}

void loop() {
  float pHValue pH.measure();
  Serial.println(pHValue);
  delay(1000);

}
