#include <ESP8266WiFi.h>
#include <Arduino.h>

#include "connection_functions.h"
#include "request_handlers.h"

void startServer(){

  server.on("/LED", HTTP_POST, handlePostToLed);
  server.on("/LED", HTTP_OPTIONS, handleOptionsRequest);

  server.begin();
  Serial.println("HTTP server started on port " + String(PORT));
}