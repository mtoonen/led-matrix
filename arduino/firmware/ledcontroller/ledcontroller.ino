
#include <RGBmatrixPanel.h>

#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoJson.h>
#include "arduino_secrets.h" 

// LED defines
#define CLK A4 
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

// WIFI
  #define SPIWIFI       SPI  // The SPI port
  #define SPIWIFI_SS    13   // Chip select pin
  #define ESP32_RESETN  12   // Reset pin
  #define SPIWIFI_ACK   11   // a.k.a BUSY or READY pin
  #define ESP32_GPIO0   -1

  
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)


#define SERVER "meinetoonen.nl"
#define PATH   "/led/messages/unprocessed"
WiFiClient client;

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

int cur = 0;
const int sizeArray = 3;
String results[sizeArray] = { "Hou", "van", "jou!" };

void setup() {
  int      x, y, hue;
  float    dx, dy, d;
  uint8_t  sat, val;
  uint16_t c;

  Serial.begin(9600);
  
  matrix.begin();
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("WiFi Scanning test");

  // Set up the pins!
  WiFi.setPins(SPIWIFI_SS, SPIWIFI_ACK, ESP32_RESETN, ESP32_GPIO0, &SPIWIFI);

  // check for the WiFi module:
  while (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    delay(1000);
  }
  String fv = WiFi.firmwareVersion();
  Serial.println(fv);
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
    while (1) delay(10);
  }
  Serial.println("Firmware OK");

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
   // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  do {
    status = WiFi.begin(ssid, pass);
    delay(100); // wait until connected
  } while (status != WL_CONNECTED);
  Serial.println("Connected to wifi");
#if defined(USE_OLED)
  display.print("...OK!");
  display.display();
#endif

  printWifiStatus();

}
void loop() {
  matrix.fillScreen(0);
 /* drawText(results[cur]);
  matrix.swapBuffers(false);
  if(cur == sizeArray){
    cur = 0;
  }else{
    cur ++;
  }
  delay(1000);

  */
  readServer();
  
  delay(10000);
}

void readServer(){
  
  Serial.println("\nStarting connection to server...");

// Connect to HTTP server
  
  client.setTimeout(10000);
  if (!client.connect(SERVER, 8080)) {
    Serial.println(F("Connection failed"));
    return;
  }
// Send HTTP request
  client.println("GET "  PATH  " HTTP/1.0");
  client.println(F("Host: " SERVER));
  client.println(F("Connection: close"));
  if (client.println() == 0) {
    Serial.println(F("Failed to send request"));
    client.stop();
    return;
  }

  // Check HTTP status
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  if (strcmp(status, "HTTP/1.1 200 ") != 0) {
    Serial.print(F("Unexpected response: "));
    Serial.println(status);
    client.stop();
    return;
  }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)) {
    Serial.println(F("Invalid response"));
    client.stop();
    return;
  }

  // Allocate the JSON document
  // Use arduinojson.org/v6/assistant to compute the capacity.
  const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 160;
  DynamicJsonDocument doc(capacity);

  // Parse JSON object
  DeserializationError error = deserializeJson(doc, client);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    client.stop();
    return;
  }

  // Extract values
  Serial.println(F("Response:"));
  
  const char* message = doc["message"];
  Serial.println(message);
  drawText(message);

  // Disconnect
  client.stop();
}

void drawShape(){
  
}

void drawText(String text){
  matrix.setTextColor(matrix.ColorHSV(100, 255, 255, true));
  matrix.setCursor(0, 0);
  matrix.print(text);
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
