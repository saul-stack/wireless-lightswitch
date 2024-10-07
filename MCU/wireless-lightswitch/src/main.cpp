#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#include "utils/led_functions.h"
#include "utils/connection_functions.h"
#include "utils/request_handlers.h"

ESP8266WebServer server(PORT);
WiFiManager wifiManager;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  deactivateLed();

  Serial.begin(9600);

  if (!wifiManager.autoConnect(BOARD_HOSTNAME)) {
    Serial.println("Failed to connect and hit timeout");
    ESP.reset();
  }

  Serial.println("Connected to Wi-Fi: " + String(WiFi.SSID()));
  WiFi.hostname(BOARD_HOSTNAME);
  Serial.println("Board Hostname: " + String(BOARD_HOSTNAME));

  startServer();

}

void loop() {
  server.handleClient();
  delay(100);
}
