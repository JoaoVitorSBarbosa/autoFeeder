#include <ArduinoJson.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>
#include "NVSManager.h"


class TelegramBot {
   private:

    String newResp();
    String meiaConverter(String meiasHoras);
    void handleNewMessages(int numNewMessages);
    void startMessage(String from_name, String chat_id);
    void initMessage(String chat_id);
    void intervalMessage(String chat_id);
    void qtdyMessage(String chat_id);
    void viewMessage(String chat_id);
    void cancelMessage(String chat_id);
    void saveMessage(String chat_id);

   public:
    bool cancelNext = false;
    TelegramBot();
    void respVerify();
    void sendMessage(String message);
};
