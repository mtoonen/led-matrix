#include <MatrixMeine.h>

       
#define CLK A4 
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);
MatrixMeine::MatrixMeine(){
  
}

void MatrixMeine::initMatrix(){
  matrix.begin();
  textX = matrix.width();
}

bool MatrixMeine::process(){
  switch(this->current->type){
    case TEXT:
      drawText(this->current);
      break;
    case TEXT_SCROLLING:
      scrollText(this->current);
      break;
    case SHAPE:
      drawShape(this->current);
      break;
    default:
      return false;
  }
  return true;
}

void MatrixMeine::drawShape(LedMessage* msg){
  Serial.println("drawShape" + msg->processed);
  isBusy = false;
  
}

void MatrixMeine::drawText(LedMessage* msg){
  if(!msg->shown){
    matrix.setTextWrap(true); // Allow text to run off right edge
    Serial.println("Drawtext" + msg->processed);
    matrix.fillScreen(0);
    matrix.setTextColor(matrix.ColorHSV(100, 255, 255, true));
    matrix.setCursor(0, 0);
    matrix.print(msg->payload);
    msg->shown = true;
    isBusy = false;
  }
}

void MatrixMeine::scrollText(LedMessage* msg){
  matrix.fillScreen(0);
  if(!msg->shown){
    textMin = (int16_t)sizeof(msg->payload) * -8;
    Serial.print("Textmin:"); Serial.println(textMin);
    msg->shown = true;
    matrix.setTextWrap(false); // Allow text to run off right edge
  }

  matrix.setCursor(textX, 1);
  matrix.print(msg->payload);
  
  if((--textX) < textMin){
    textX = matrix.width();
    isBusy = false;
  }else{
    isBusy = true;
  }

}

void MatrixMeine::drawMessage(LedMessage* msg){
  this->current = msg;
  isBusy = false;
}

