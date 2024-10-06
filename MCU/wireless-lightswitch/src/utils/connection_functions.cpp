#include <ESP8266WiFi.h>
#include <Arduino.h>

#include "connection_functions.h"
#include "request_handlers.h"

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

void startServer(){

  server.on("/LED", HTTP_POST, handlePostToLed);
  server.on("/LED", HTTP_OPTIONS, handleOptionsRequest);

  server.begin();
  Serial.println("HTTP server started on port `" + String(PORT));
}