#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "utils/led_functions.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* BOARD_HOSTNAME = "esp8266-lightswitch";

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

void connectToWiFi(){
  WiFi.hostname(BOARD_HOSTNAME);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to " + String(ssid));  

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected.\nIP address: " + WiFi.localIP().toString());
  Serial.println("Device name: " + String(BOARD_HOSTNAME));

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
