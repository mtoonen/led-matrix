#include <WifiMeine.h>

// WIFI
#define SPIWIFI SPI     // The SPI port
#define SPIWIFI_SS 13   // Chip select pin
#define ESP32_RESETN 12 // Reset pin
#define SPIWIFI_ACK 11  // a.k.a BUSY or READY pin
#define ESP32_GPIO0 -1

//#define SERVER "led.meinetoonen.nl"
#define SERVER "192.168.68.113"
#define PATH "/led/messages/unprocessed"
#define PATHCHECK "/led/messages/checkunprocessed"
#define PATHPROCESSED "/led/messages/processed/"
// your network key Index number (needed only for WEP)
WiFiClient client;
ReadBufferingClient bufferedClient{client, 64};

WifiMeine::WifiMeine()
{
}

void WifiMeine::initWifi()
{
  // Set up the pins!
  WiFi.setPins(SPIWIFI_SS, SPIWIFI_ACK, ESP32_RESETN, ESP32_GPIO0, &SPIWIFI);

  // check for the WiFi module:
  while (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    delay(1000);
  }
  String fv = WiFi.firmwareVersion();
  Serial.println(fv);
  if (fv < "1.0.0")
  {
    Serial.println("Please upgrade the firmware");
    while (1)
      delay(10);
  }
  Serial.println("Firmware OK");

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  do
  {
    status = WiFi.begin(ssid, pass);
    delay(100); // wait until connected
  } while (status != WL_CONNECTED);
  Serial.println("Connected to wifi");

  printWifiStatus();
}

boolean WifiMeine::checkServer()
{
  //  Serial.println("checkserver");
  doRequest(PATHCHECK);
  String s = bufferedClient.readString();
  if (s.equals("1"))
  {
    return true;
  }
  else
  {
    return false;
  }
}

LedMessage *WifiMeine::readServer()
{
  mmatrix->setLoading(15);
  doRequest(PATH);
  mmatrix->setLoading(35);
  // matrixThread.check();
  //matrixThread.check();
  // Allocate the JSON document
  // Use arduinojson.org/v6/assistant to compute the capacity.
  Serial.println("parsing json");

  const size_t capacity = 192; // JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 160;
  DynamicJsonDocument doc(capacity);

  //matrixThread.check();
  Serial.println("json parsed");
  // Parse JSON object
  DeserializationError error = deserializeJson(doc, bufferedClient);

  if (error)
  {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    client.stop();
    Serial.println("stopped");
    return NULL;
  }
  Serial.println("deserialized");
  mmatrix->setLoading(55);

  LedMessage *m = parseInput(doc);
  Serial.println("iput parsed");

  // Disconnect
  client.stop();
  Serial.println("stopped");
  mmatrix->setLoading(75);
  return m;
}

void WifiMeine::writeMessageProcessed(int id)
{
  Serial.print("Setting to processed:");
  Serial.println(id);
  String path = PATHPROCESSED + id;
  Serial.println("Padje:" + path);
  doRequest(PATHPROCESSED + String(id));
  matrixThread->check();
  // Disconnect
  client.stop();
  matrixThread->check();
}

LedMessage *WifiMeine::parseInput(DynamicJsonDocument doc)
{
  LedMessage *m = new LedMessage();

  m->id = doc["id"].as<long>();
  m->payload = doc["payload"].as<String>();
  m->processed = doc["processed"].as<bool>();
  m->r = doc["r"].as<int>();
  m->g = doc["g"].as<int>();
  m->b = doc["b"].as<int>();
  String type = doc["type"].as<String>();
  MessageType mt = UNDEFINED;

  Serial.print("Type=");
  Serial.println(type);
  if (type.equals("text"))
  {
    mt = TEXT;
  }
  else if (type.equals("shape"))
  {
    mt = SHAPE;
  }
  else if (type.equals("text_scrolling"))
  {
    mt = TEXT_SCROLLING;
  }
  else
  {
    mt = TEXT;
  }
  m->type = mt;
  printLedMessage(m);
  return m;
}

void WifiMeine::printLedMessage(LedMessage *lm)
{
  Serial.println("*****");
  Serial.print("id: ");
  Serial.println(lm->id);
  Serial.print("payload: ");
  Serial.println(lm->payload);
  Serial.print("type: ");
  Serial.println(lm->type);
  Serial.print("processed: ");
  Serial.println(lm->processed);
}

int WifiMeine::doRequest(String requestPath)
{

  // Serial.println("\nStarting connection to server...");
  // Serial.print("Request ");
  // Serial.println(requestPath);

  // Connect to HTTP server

  client.setTimeout(2000);
  if (!client.connect(SERVER, 8080))
  {
    Serial.println(F("Connection failed"));
    return -1;
  }
  // Serial.println("connected");
  // Send HTTP request
  client.println("GET " + requestPath + " HTTP/1.0");
  client.println(F("Host: " SERVER));
  client.println(F("Connection: close"));
  if (client.println() == 0)
  {
    Serial.println(F("Failed to send request"));
    client.stop();
    return -1;
  }
  // Serial.println("request done");

  // Check HTTP status
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  if (strcmp(status, "HTTP/1.1 200 ") != 0)
  {
    Serial.print(F("Unexpected response: "));
    Serial.println(status);
    client.stop();
    return -1;
  }
  // Serial.println("bytes read");

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders))
  {
    Serial.println(F("Invalid response"));
    client.stop();
    return -1;
  }
  return 1;
}

void WifiMeine::setMatrix(TimedAction &mT, MatrixMeine &mm)
{
  matrixThread = &mT;
  mmatrix = &mm;
}

void WifiMeine::printWifiStatus()
{
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
