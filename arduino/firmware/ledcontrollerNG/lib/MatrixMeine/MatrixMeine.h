#ifndef MATRIXMEINE_h
#define MATRIXMEINE_h
#include <RGBmatrixPanel.h>
#include <LedMessage.h>
// LED defines

class MatrixMeine
{
public:
    MatrixMeine();
    void initMatrix();
    bool process();
    void setLoading(double percentage);
    void setLoading(double percentage, String text);
    void setMessage(LedMessage *msg);
    void drawText(LedMessage *msg);
    void scrollText(LedMessage *msg);
    void drawShape(LedMessage *msg);
    bool isBusy = false;

private:
    LedMessage *current;
    int16_t textX, textMin;
    int heightBox = 6;
    int widthBox = 24;
    int xBox = 4;
    int yBox = 10;
    int heightFill = heightBox - 2;
    double widthFill = widthBox - 2;

    double ratio = 100.0 / widthFill;
};
#endif