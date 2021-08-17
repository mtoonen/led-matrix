#ifndef WIFIMEINE_h
#define WIFIMEINE_h
#include <WiFiNINA.h>
#include <Wire.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include <LedMessage.h>
#include "arduino_secrets.h" 
#include <StreamUtils.h>
#include <TimedAction.h>


class WifiMeine{
    public:
        WifiMeine();
        void initWifi();
        LedMessage* readServer();
        boolean checkServer();
        void writeMessageProcessed(int id);
        void setMatrix(TimedAction& matrixThread);
    private:
        int doRequest(String requestPath);
        void printLedMessage(LedMessage* lm);
        LedMessage* parseInput(DynamicJsonDocument doc);
        void printWifiStatus();

        TimedAction* matrixThread;
        const char* ssid = SECRET_SSID;
        const char* pass = SECRET_PASS;
        int status = WL_IDLE_STATUS;
        int keyIndex = 0;
};
#endif