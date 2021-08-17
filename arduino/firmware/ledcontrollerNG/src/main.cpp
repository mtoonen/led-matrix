#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "MatrixMeine.h"
#include <LedMessage.h>
#include <WifiMeine.h>
#include <TimedAction.h>


MatrixMeine mmatrix;
WifiMeine mwifi;


void checkWifi(){
  if(mwifi.checkServer()){
    LedMessage *m = mwifi.readServer();
    if (m != NULL && m->payload != NULL && m->payload != "")
    {
      Serial.println(m->type);
      mmatrix.drawMessage(m);
      mwifi.writeMessageProcessed(m->id);
    }
  }
}

void checkMatrix(){
  mmatrix.process();
}
int matrixDelay = 20;



TimedAction wifiThread = TimedAction(5000,checkWifi);
TimedAction matrixThread = TimedAction(20,checkMatrix);
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
  mwifi.setMatrix(matrixThread);
  mwifi.initWifi();
  msg->payload = "Connected";
  mmatrix.drawText(msg);

  LedMessage* msg2 = new LedMessage();
  msg2->type = TEXT_SCROLLING;
  msg2->payload = "meine is cool";
  mmatrix.drawMessage(msg2);
}

void loop()
{
  
  // wifiThread.check();
  if(!mmatrix.isBusy){
    wifiThread.check();
    matrixThread.check();
  }else{
    matrixThread.check();
  }
}