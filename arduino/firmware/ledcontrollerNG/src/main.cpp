#include <Arduino.h>
#include <Matrix.h>
#include <WifiMeine.h>
#include <LedMessage.h>

void setup()
{
  Serial.begin(9600);
  // put your setup code here, to run once:
  Serial.println("Initializing matrix");
  initMatrix();
  drawText("Initializing WiFi...");
  initWifi();
  drawText("Connected");
}

void loop()
{
  // put your main code here, to run repeatedly:

  LedMessage *m = readServer();
  if (m != NULL && m->message != NULL && m->message != "")
  {
    Serial.println(m->type);
    drawText(m->message);
    writeMessageProcessed(m->id);
  }
  delay(5000);
  // drawText("meine is echt cool");
}