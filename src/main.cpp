#include <ESP8266WiFi.h>
#include <Arduino.h>
#include "../include/defines.h"
#include "../include/wifi.h"
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h> 
#include <ArduinoJson.h>

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

unsigned long lastTimeBotRan;

Wifi wifi = Wifi();
void setup () {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    delay(3000);
    configTime(0, 0, "pool.ntp.org");
    client.setTrustAnchors(&cert);
    wifi.init();
}

void loop () {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}