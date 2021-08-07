#include <Arduino.h>
#include "MatrixMeine.h"
#include <WifiMeine.h>
#include <LedMessage.h>

MatrixMeine mmatrix;
void setup()
{
  
  Serial.begin(9600);
  // put your setup code here, to run once:
  Serial.println("Initializing matrix");
  mmatrix.initMatrix();
  LedMessage* msg = new LedMessage();
  msg->type = TEXT;
  msg->payload = "Initializing WiFi...";
  mmatrix.drawText(msg);
 // initWifi();
  msg->payload = "Connected";
  mmatrix.drawText(msg);

  LedMessage* msg2 = new LedMessage();
  msg2->type = TEXT_SCROLLING;
  msg2->payload = "meine is cool";
  mmatrix.drawMessage(msg2);
}

void loop()
{
  mmatrix.process();
  delay(20);
  // put your main code here, to run repeatedly:

 /* LedMessage *m = readServer();
  if (m != NULL && m->payload != NULL && m->payload != "")
  {
    Serial.println(m->type);
    mmatrix.drawMessage(m);
    writeMessageProcessed(m->id);
  }
  if(mmatrix.process()){

  }
  delay(5000);*/
}