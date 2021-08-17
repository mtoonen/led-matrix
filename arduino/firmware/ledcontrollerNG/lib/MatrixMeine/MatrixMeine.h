#ifndef MATRIXMEINE_h
#define MATRIXMEINE_h
#include <RGBmatrixPanel.h>
#include <LedMessage.h>
// LED defines

class MatrixMeine{
    public:

        MatrixMeine();
        void initMatrix();
        bool process();
        void drawMessage(LedMessage *msg);
        void drawText(LedMessage* msg);
        void scrollText(LedMessage* msg);
        void drawShape(LedMessage* msg);
        bool isBusy = false;
    private:
        LedMessage* current;
        int16_t    textX, textMin;
        
};
#endif