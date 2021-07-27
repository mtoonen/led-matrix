#ifndef WIFIMEINE_h
#define WIFIMEINE_h
#include <WiFiNINA.h>
#include <Wire.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include <LedMessage.h>
#include "arduino_secrets.h" 



// WIFI
#define SPIWIFI       SPI  // The SPI port
#define SPIWIFI_SS    13   // Chip select pin
#define ESP32_RESETN  12   // Reset pin
#define SPIWIFI_ACK   11   // a.k.a BUSY or READY pin
#define ESP32_GPIO0   -1


// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)

#define SERVER "led.meinetoonen.nl"
#define PATH   "/led/messages/unprocessed"
#define PATHPROCESSED   "/led/messages/processed/"


    void initWifi();
    void printWifiStatus();
    LedMessage* readServer();
    int doRequest(String requestPath);
    void writeMessageProcessed(int id);
    void printLedMessage(LedMessage* lm);
    LedMessage* parseInput(DynamicJsonDocument doc);
#endif