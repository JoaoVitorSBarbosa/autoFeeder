#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h> 
#include <ArduinoJson.h>

class TelegramBot {
   private:
    void handleNewMessages(int numNewMessages);

   public:
    TelegramBot();
    void respVerify(unsigned long* lastTimeBotRan);
};
