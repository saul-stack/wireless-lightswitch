#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>

#include "utils/led_functions.h"
#include "utils/connection_functions.h"
#include "utils/request_handlers.h"

ESP8266WebServer server(80);

void startServer(){

  server.on("/LED", HTTP_POST, handlePostToLed);
  server.on("/LED", HTTP_OPTIONS, handleOptionsRequest);

  server.begin();
  Serial.println("HTTP server started on port 80");
}


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  deactivateLed();

  Serial.begin(9600);

  connectToWiFi();

  startServer();

}

void loop() {
  server.handleClient();
  delay(100);
}
