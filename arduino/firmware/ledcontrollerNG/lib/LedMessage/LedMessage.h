#ifndef LEDMESSAGE_H
#define LEDMESSAGE_H

#include <Arduino.h>
enum MessageType{
    TEXT,
    TEXT_SCROLLING,
    SHAPE,
    UNDEFINED

};

struct LedMessage{
    int id;
    String payload;
    int r;
    int g;
    int b;
    MessageType type;
    bool processed;
    bool shown;
};
#endif