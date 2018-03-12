#include "Configuration.h"
String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete
Command* c;
uint8_t currentId;
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, true);

void setup() {
    c = new Command();
    Serial.begin(115200);
    Serial1.begin(115200); // RX:19, TX:18
    inputString.reserve(200);
    Serial.println("Beginning1...");
    
    matrix.begin();
    
    matrix.setCursor(1, 0);    // start at top left, with one pixel of spacing
    matrix.setTextSize(1);     // size 1 == 8 pixels high
    matrix.setTextWrap(true); // Don't wrap at end of line - will do ourselves
    
    matrix.setTextColor(matrix.Color333(0,7,7),matrix.Color333(0,0,0));
    matrix.println("Initialising...");
    matrix.swapBuffers(false);
}

void loop() {
   while (Serial1.available()) {
        char inChar = (char)Serial1.read();
        inputString += inChar;
        if (inChar == '\n') {
            stringComplete = true;
        }
    }
    if (stringComplete) {
        parseResponse(inputString);
        inputString = "";
        stringComplete = false;
    }
}

void processCommand(){
    matrix.fillScreen(0);
    matrix.setCursor(1, 0);

    String params = c->parameters;
    Serial.println( "Setting leds to:" + params);
         
    matrix.println(params);
    matrix.swapBuffers(false);
}

void parseResponse(String s){
    int sepLength = SEPARATOR.length(); 
    Serial.println(s);
    if(inputString.startsWith(SEPARATOR) &&  (inputString.length() > 3*sepLength)){
       
        Serial.print("Command found:>");
        Serial.println(inputString + "<");
        // .|.0.|.pietpuk.|.12.|.
        // .|.<int>CommandType.|.<String>CommandParaters.|.<int>id.|.
        int firstIndex = sepLength;
        int secondIndex =  s.indexOf(SEPARATOR, firstIndex + 1);
        int thirdIndex = s.indexOf(SEPARATOR, secondIndex + 1);
        int fourthIndex = s.indexOf(SEPARATOR, thirdIndex + 1);
        
        String commandType = s.substring(firstIndex, secondIndex);
        String params = s.substring(secondIndex+ sepLength, thirdIndex);
        String idString = s.substring(thirdIndex+ sepLength, fourthIndex);
        uint8_t id =   idString.toInt();
        Serial.println("CommandType: >" + commandType + "<");
        Serial.println("Params: >"+ params + "<");
        Serial.println("id: >"+ idString + "<");
        if(currentId != id){
            currentId = id;
            //c->commandType = commandType;
            c->parameters = params;
            c->id = id;
            processCommand();
        }
    }
}

