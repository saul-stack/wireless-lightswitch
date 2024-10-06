#pragma once
#include <ESP8266WebServer.h>

extern ESP8266WebServer server;

void activateLed();
void deactivateLed();
void toggleLed();
void blinkLed();
void toggleLedOn();
void toggleLedOff();