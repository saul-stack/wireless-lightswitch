#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <wifiManager.h>
#include <DNSServer.h>

#include "connection_functions.h"
#include "request_handlers.h"

WiFiManager wifiManager;

void startServer(){

  server.on("/LED", HTTP_POST, handlePostToLed);
  server.on("/LED", HTTP_OPTIONS, handleOptionsRequest);

  server.begin();
  Serial.println("HTTP server started on port " + String(PORT));
}

void initialiseWifi(){

  if (!wifiManager.autoConnect(BOARD_HOSTNAME)) {
    Serial.println("Failed to connect to Wifi");
    ESP.reset();
  }

  Serial.println("\n Connected to Wi-Fi: " + String(WiFi.SSID()));
  WiFi.hostname(BOARD_HOSTNAME);
  Serial.println("Board Hostname: " + String(BOARD_HOSTNAME));
}