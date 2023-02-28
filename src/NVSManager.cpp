#include "../include/NVSManager.h"

NVS::NVS() {
    EEPROM.begin(80);
}

String NVS::readString() {
    String string;
    char readChar = ' ';
    int i = 0;

    while (readChar != '\0') {
        readChar = char(EEPROM.read(i));
        delay(10);
        i++;

        if (readChar != '\0') {
            string += readChar;
        }
    }

    return string;
}

bool NVS::insertString(String string) {
    delay(10);

    for (unsigned int i = 0; i < string.length(); ++i) {
        EEPROM.write(i, string[i]);
    }

    EEPROM.write(string.length(), '\0');
    EEPROM.commit();
    if(string != readString()) return false;
    return true;
}

