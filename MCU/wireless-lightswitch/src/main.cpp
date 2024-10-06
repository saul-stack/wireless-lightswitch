#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* device_name = "esp8266-lightswitch";

ESP8266WebServer server(80);


void activateLED() {
  digitalWrite(LED_BUILTIN, LOW);
}

void deactivateLED() {
  digitalWrite(LED_BUILTIN, HIGH);
}


void blinkLED() {
  deactivateLED();  
  delay(50);
  activateLED();
  delay(100);
  deactivateLED();  
  server.send(200, "text/plain", "LED was turned on briefly");
}

void turnOnLED() {
  activateLED();
  server.send(200, "text/plain", "LED was turned on");
}

void turnOffLED() {
  deactivateLED();
  server.send(200, "text/plain", "LED was turned off");
}

void toggleLED() {
  if (digitalRead(LED_BUILTIN) == HIGH) {
    activateLED();
    server.send(200, "text/plain", "LED was turned on");
  } else {
    deactivateLED();
    server.send(200, "text/plain", "LED was turned off");
  }
}


void handleOptionsRequest() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
  server.send(204);
}

void handlePostToLED() {  

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
      turnOnLED();
    } else if (String(action) == "deactivate") {
      turnOffLED();
    } else if (String(action) == "toggle") {
      toggleLED();
    } else if (String(action) == "blink") {
      blinkLED();
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

  server.on("/LED", HTTP_POST, handlePostToLED);
  server.on("/LED", HTTP_OPTIONS, handleOptionsRequest);

  server.begin();
  Serial.println("HTTP server started on port 80");
}

void connectToWiFi(){
   WiFi.hostname(device_name);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to " + String(ssid));  

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected.\nIP address: " + WiFi.localIP().toString());
  Serial.println("Device name: " + String(device_name));

}


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  deactivateLED();

  Serial.begin(9600);

  connectToWiFi();

  startServer();

}

void loop() {
  server.handleClient();
  delay(100);
}
