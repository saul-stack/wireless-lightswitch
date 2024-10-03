#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
ESP8266WebServer server(80);

void activateLED() {
  digitalWrite(LED_BUILTIN, LOW);
}
void deactivateLED() {
  digitalWrite(LED_BUILTIN, HIGH);
}

void blinkLED() {
  deactivateLED();  
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

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  deactivateLED();
  Serial.println("Connecting to " + String(ssid));  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected.\nIP address: " + WiFi.localIP().toString());

  server.on("/blink", blinkLED);
  server.on("/on", turnOnLED);
  server.on("/off", turnOffLED);
  server.on("/toggle", toggleLED);

  server.begin();
  Serial.println("HTTP server started on port 80");
}

void loop() {
  server.handleClient();
  delay(100);
}
