#include "../include/wifi.h"

Wifi::Wifi(){};

void Wifi::scan() {
    int numberOfNetworks = WiFi.scanNetworks();
    
    for (int i = 0; i < numberOfNetworks; i++) {
        Serial.print("Network name: ");
        Serial.println(WiFi.SSID(i));
        Serial.print("Signal strength: ");
        Serial.println(WiFi.RSSI(i));
        Serial.println("-----------------------");
    }

}

void Wifi::init() {
    const char* ssid = NOME;
    const char* password = SENHA;
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    scan();
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");
    Serial.print("IP Adress: ");
    Serial.println(WiFi.localIP());
}