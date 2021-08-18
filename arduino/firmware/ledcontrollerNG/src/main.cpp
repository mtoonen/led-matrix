#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "MatrixMeine.h"
#include <LedMessage.h>
#include <WifiMeine.h>
#include <TimedAction.h>
#include <main.h>

MatrixMeine mmatrix;
WifiMeine mwifi;

TimedAction wifiThread = TimedAction(5000, checkWifi);
TimedAction matrixThread = TimedAction(20, checkMatrix);
bool wifiOn = true;

void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing matrix");
  mmatrix.initMatrix();
  LedMessage *msg = new LedMessage();
  msg->type = TEXT;
  msg->payload = "Initializing WiFi...";
  mmatrix.drawText(msg);
  mwifi.setMatrix(matrixThread, mmatrix);

  if (wifiOn)
  {
    mwifi.initWifi();
  }
  msg->shown = false;
  msg->g = 255;
  msg->payload = "Connected";
  mmatrix.drawText(msg);
  //  mmatrix.setLoading(10);

  LedMessage *msg2 = new LedMessage();
  msg2->type = TEXT_SCROLLING;
  msg2->b = 255;
  msg2->payload = "Waiting to receive";
  mmatrix.setMessage(msg2);
  // mmatrix.setLoading(10);
}

void checkWifi()
{
  if (wifiOn && mwifi.checkServer())
  {
    mmatrix.setLoading(10);
    LedMessage *m = mwifi.readServer();
    mmatrix.setLoading(95);
    if (m != NULL && m->payload != NULL && m->payload != "")
    {
      Serial.println(m->type);
      mmatrix.setMessage(m);
      mmatrix.setLoading(100);
      matrixThread.check();
      mwifi.writeMessageProcessed(m->id);
      matrixThread.check();
    }
  }
  else
  {
    matrixThread.check();
  }
}

void checkMatrix()
{
  //  Serial.println("checkmatrix");
  mmatrix.process();
}

void loop()
{

  if (!mmatrix.isBusy)
  {
    wifiThread.check();
  }
  else
  {
    //  Serial.println("chyeck matrix");
    matrixThread.check();
  }
}
