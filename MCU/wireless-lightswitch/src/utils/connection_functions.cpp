#include <ESP8266WiFi.h>
#include <Arduino.h>
#include "connection_functions.h"


void connectToWiFi(){
  WiFi.hostname(BOARD_HOSTNAME);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting to " + String(WIFI_SSID));  

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected.\nIP address: " + WiFi.localIP().toString());
  Serial.println("Device name: " + String(BOARD_HOSTNAME));

}