int lastupdate = 0;
int updateThreshold = 1000 * 5;
void setupOta(){
    

  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);

  // Hostname defaults to esp3232-[MAC]
  // ArduinoOTA.setHostname("myesp32");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");
  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
        blinkLed(ledPinGreen,2);
        blinkLed(ledPinRed,2);
    })
    .onEnd([]() {
        blinkLed(ledPinGreen,3);
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
       // blinkLed(ledPinGreen,1);
     //    blinkLed(ledPinRed,1);
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
        blinkLed(ledPinRed,3);
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();
}

void update(){
    int currentTime = millis();
    if( (currentTime - lastupdate ) > updateThreshold){
        lastupdate = currentTime;
        ArduinoOTA.handle();
    }
}


void blinkLed(int led,int num){
    for(int i = 0 ;i < num ;i++){
        digitalWrite(led,HIGH);
        delay(100);
        digitalWrite(led,LOW);
        delay(100);
    }
}

