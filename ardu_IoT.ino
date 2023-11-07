#include <DFRobot_PH.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <Ethernet.h>
#include <RestClient.h>
#include <ArduinoJson.h>


RestClient client = RestClient("http://192.168.0.127:8080");

String response;
String status;

int SensorPin = A0;
const int TEMP_SENSOR_PIN = 13;

OneWire oneWire(TEMP_SENSOR_PIN);
DallasTemperature tempSensor(&oneWire);

float tempCelsius;
float tempFahrenheit;

void setup() {
  Serial.begin(9600);

  StaticJsonDocument<200> doc;
  DynamicJsonDocument  StaticJsonDocument(1024);
  JsonObject root = StaticJsonDocument.createObject();

  tempSensor.begin();

  Serial.println("connecting to network");
  client.dhcp();
  
}

void report () {
  response = "";
  
  int statusCode = client.post(serverURI + "/api/weather",root, &response);
  Serial.print("Status code from server: ");
  Serial.println(statusCode);
  Serial.print("Response body from server: ");
  Serial.println(response);
  return;

}

void sensors() { 
  tempSensor.requestTemperatures();
  tempCelsius = tempSensor.getTempCByIndex(0);
  float pHValue = pH.measure();
  int humidity = analogRead(SensorPin);

  root["temp"] = tempCelsius;
  root["hum"] = humidity;
  root["pres"] = pHValue; // The server should receive pH but instead we need to set pHValue to "pres" field
  
  root.prettyPrintTo(Serial);

  return;
}

void loop() {
  while (true) {
    delay(5000);
    sensors();
    report();
  }
}
