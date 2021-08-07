#include <WifiMeine.h>

int status = WL_IDLE_STATUS;

  
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient client;

void initWifi(){

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


LedMessage* readServer(){
  int status = doRequest(PATH);

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
    return NULL;
  }

  LedMessage* m = parseInput(doc);


  // Disconnect
  client.stop();
  return m;
}

void writeMessageProcessed(int id){
  Serial.print("Setting to processed:");Serial.println(id);
  String path = PATHPROCESSED + id;
  Serial.println("Padje:" + path);
  doRequest(PATHPROCESSED + String(id));

  // Disconnect
  client.stop();
}

int doRequest(String requestPath){

  Serial.println("\nStarting connection to server...");
  Serial.print("Request "); Serial.println(requestPath);

// Connect to HTTP server
  
  client.setTimeout(10000);
  if (!client.connect(SERVER, 8080)) {
    Serial.println(F("Connection failed"));
    return -1;
  }
// Send HTTP request
  client.println("GET "  +requestPath+   " HTTP/1.0");
  client.println(F("Host: " SERVER));
  client.println(F("Connection: close"));
  if (client.println() == 0) {
    Serial.println(F("Failed to send request"));
    client.stop();
    return -1;
  }

  // Check HTTP status
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  if (strcmp(status, "HTTP/1.1 200 ") != 0) {
    Serial.print(F("Unexpected response: "));
    Serial.println(status);
    client.stop();
    return -1;
  }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)) {
    Serial.println(F("Invalid response"));
    client.stop();
    return -1;
  }
  return 1;
}

LedMessage* parseInput(DynamicJsonDocument doc){
  LedMessage* m = new LedMessage();
  
  m->id = doc["id"].as<long>();
  m->payload = doc["payload"].as<String>();
  m->processed = doc["processed"].as<bool>();
  m->r = doc["r"].as<int>();
  m->g = doc["g"].as<int>();
  m->b = doc["b"].as<int>();
  String type = doc["type"].as<String>();
  MessageType mt = UNDEFINED;

Serial.print("Type="); Serial.println(type);
  if(type.equals("TEXT")){
      mt = TEXT;
  }else if(type.equals("SHAPE")){
      mt = SHAPE;
  }else if(type.equals("TEXT_SCROLLING")){
    mt = TEXT_SCROLLING;
  }else{
      mt = TEXT;
  }
  m->type = mt;
  printLedMessage(m);
  return m;
}

void printLedMessage(LedMessage* lm){
  Serial.println("*****");
  Serial.print("id: ") + Serial.println(lm->id);
  Serial.print("payload: ") + Serial.println(lm->payload);
  Serial.print("type: ") + Serial.println(lm->type);
  Serial.print("processed: ") + Serial.println(lm->processed);
}