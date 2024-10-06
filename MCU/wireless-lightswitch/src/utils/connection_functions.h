#pragma once

#include <ESP8266WebServer.h>

extern ESP8266WebServer server;
extern const int PORT;

void connectToWiFi();
void startServer();