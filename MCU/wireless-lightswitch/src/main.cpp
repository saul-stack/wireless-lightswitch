#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
const char* ssid = WIFI_SSID;
const char* password = PASSWORD;
void activateLED() {
  digitalWrite(LED_BUILTIN, LOW);
}
void deactivateLED() {
  digitalWrite(LED_BUILTIN, HIGH);
}
void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  deactivateLED();
}
