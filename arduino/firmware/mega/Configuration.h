const String SEPARATOR = ".|.";


#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

// If your 32x32 matrix has the SINGLE HEADER input,
// use this pinout:
#define CLK 11  // MUST be on PORTB! (Use pin 11 on Mega)
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

enum CommandType{
    WORD_CLOCK,
    SHOW_TEXT
};

struct Command{
    CommandType commandType;
    uint8_t id;
    String parameters;  
};

