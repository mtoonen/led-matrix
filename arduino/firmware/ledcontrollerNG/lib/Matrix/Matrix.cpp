#include <Matrix.h>


RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

void initMatrix(){
  matrix.begin();

}
void drawShape(){
  
}

void drawText(String text){
  matrix.fillScreen(0);
  matrix.setTextColor(matrix.ColorHSV(100, 255, 255, true));
  matrix.setCursor(0, 0);
  matrix.print(text);
}
