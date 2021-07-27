#ifndef LEDMESSAGE_H
#define LEDMESSAGE_H

#include <Arduino.h>
enum MessageType{
    TEXT,
    SHAPE,
    UNDEFINED

};

struct LedMessage{
    int id;
    String message;
    MessageType type;
    bool processed;
};
#endif