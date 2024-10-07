#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>

#include "utils/led_functions.h"
#include "utils/connection_functions.h"
#include "utils/request_handlers.h"

ESP8266WebServer server(PORT);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  deactivateLed();

  Serial.begin(9600);

  initialiseWifi();

  startServer();

}

void loop() {
  server.handleClient();
  delay(100);
}
