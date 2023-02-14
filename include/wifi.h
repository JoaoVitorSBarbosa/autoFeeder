#include "defines.h"
#include <ESP8266WiFi.h>

class Wifi {
   private:
    void scan ();
   public:
    Wifi();
    void init();
};