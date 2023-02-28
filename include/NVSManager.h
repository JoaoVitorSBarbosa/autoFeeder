#ifndef NVS_H
#define NVS_H

#include <Arduino.h>
#include <EEPROM.h>
#include "defines.h"

class NVS {

private:
    
public:
    NVS();
    bool insertString(String string);
    String readString();
};

#endif