#include <WiFiClientSecure.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "Configuration.h"

const int buttonPin = 2;
const int ledPinRed = 14;
const int ledPinGreen = 19;

unsigned long lastConnectionTime = 0;            // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 2L * 1000L; // delay between updates, in milliseconds

WiFiClientSecure client;
//WiFiClient client;
HardwareSerial Serial1(2);  // UART1/Serial1 pins 16,17

void setup() {
    pinMode(ledPinRed, OUTPUT);
    pinMode(ledPinGreen, OUTPUT);
    pinMode(buttonPin, INPUT);
    
    Serial1.begin(115200);
    Serial.begin(115200);
    
    Serial.println("Booting");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }
    Serial.println("verbonden");
    Serial1.println("verbonden");
    //setupOta();
    
    client.setCACert(test_root_ca);
}

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void loop() {
    /*int reading = digitalRead(buttonPin);
    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }
    
    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != buttonState) {
            buttonState = reading;
            
            if (buttonState == HIGH) {
                pollServer();
            }
        }
    }
    lastButtonState = reading;*/

    unsigned long current = millis();
    if( (current - lastConnectionTime) > postingInterval){
        pollServer();        
    }

    readReponse();
}

void readReponse(){
    while (client.available() > 0) {
        String s = client.readStringUntil('\r');
        Serial1.println(s);
    }
}


void pollServer() {
    Serial1.println("Polling...");
    Serial.println("Polling...");
    // close any connection before send a new request.
    // This will free the socket on the WiFi shield
    client.stop();
    Serial1.println("After stop");
    
    // if there's a successful connection:
    if (client.connect(server, 443)) {
        String url = "/led-server/action/matrix/poll";
        Serial1.println("connecting...");
        // send the HTTP PUT request:
        client.println("GET " + url + " HTTP/1.1");
        client.println("Host: " + (String) server);
        client.println("User-Agent: ArduinoWiFi/1.1");
        client.println("Connection: close");
        client.println();
        
        // note the time that the connection was made:
        lastConnectionTime = millis();
    } else {
    // if you couldn't make a connection:
        Serial1.println("connection failed");
    }
}
