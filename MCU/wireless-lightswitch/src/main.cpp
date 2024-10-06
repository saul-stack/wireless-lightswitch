#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>

#include "utils/led_functions.h"
#include "utils/connection_functions.h"

ESP8266WebServer server(80);

void handleOptionsRequest() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
  server.send(204);
}

void handlePostToLed() {  

  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
  
  if (server.hasArg("plain")) {
    String requestBody = server.arg("plain");

    JsonDocument parsedJson;

    DeserializationError error = deserializeJson(parsedJson, requestBody);

    if (error) {
      Serial.println("deserializeJson() failed: " + String(error.f_str()));
      server.send(400, "text/plain", "Invalid JSON");
      return;
    }

    const char* action = parsedJson["action"];
    Serial.println("LED action: " + String(action));

    if (String(action) == "activate") {
      toggleLedOn();
    } else if (String(action) == "deactivate") {
      toggleLedOff();
    } else if (String(action) == "toggle") {
      toggleLed();
    } else if (String(action) == "blink") {
      blinkLed();
    } else {
      server.send(400, "text/plain", "Invalid 'action' key.");
      Serial.println("Invalid LED action: " + String(action) + "\n");
    }
  } else {
    server.send(400, "text/plain", "Invalid request.");
    Serial.println("Received invalid /LED request");
  }
}


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
