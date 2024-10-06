#include <Arduino.h>
#include "led_functions.h"

void activateLed() {
  digitalWrite(LED_BUILTIN, LOW);
}

void deactivateLed() {
  digitalWrite(LED_BUILTIN, HIGH);
}


void blinkLed() {
  deactivateLed();  
  delay(50);
  activateLed();
  delay(100);
  deactivateLed();  
  server.send(200, "text/plain", "LED was turned on briefly");
}

void toggleLedOn() {
  activateLed();
  server.send(200, "text/plain", "LED was turned on");
}

void toggleLedOff() {
  deactivateLed();
  server.send(200, "text/plain", "LED was turned off");
}

void toggleLed() {
  if (digitalRead(LED_BUILTIN) == HIGH) {
    activateLed();
    server.send(200, "text/plain", "LED was turned on");
  } else {
    deactivateLed();
    server.send(200, "text/plain", "LED was turned off");
  }
}
