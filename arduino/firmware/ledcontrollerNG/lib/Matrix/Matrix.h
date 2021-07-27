#ifndef MATRIXMEINE_h
#define MATRIXMEINE_h
#include <RGBmatrixPanel.h>
// LED defines
#define CLK A4 
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

void initMatrix();
void drawText(String text);
void drawShape();
#endif