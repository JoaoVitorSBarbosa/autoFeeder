#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#include "../include/NVSManager.h"
#include "../include/defines.h"
#include "../include/funcsAux.h"
#include "../include/telegramBot.h"
#include "../include/wifi.h"

Wifi wifi = Wifi();
NVS nvsMan = NVS();
TelegramBot tbot = TelegramBot();
FuncsAux funcs = FuncsAux();

const long utcOffsetInSeconds = -3 * 3600;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

int getNumHorarios(String horarios) {
    int cont = 1;
    for (unsigned int i = 0; i < horarios.length(); i++) {
        if (horarios[i] == ',') cont++;
    }
    return cont;
}
void getHorarios(String horariosArray[], String horarios) {
    int horariosCont = 0;
    for (unsigned int i = 0; i < horarios.length(); i++) {
        if (horarios[i] == ',') {
            horariosCont++;
        } else {
            horariosArray[horariosCont] += horarios[i];
        }
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    configTime(0, 0, "pool.ntp.org"); 
    wifi.init();
}

void loop() {
    while (SERVO_TEST) {
        Servo servo;
        servo.attach(SERVO_PIN);
        funcs.giraServo();
        Serial.println("Testando servo...");
    }
    int horas = timeClient.getHours();
    int minutos = timeClient.getMinutes();
    String horaAtual = String(horas) + ":" + (minutos < 10 ? ("0"+String(minutos)) : String(minutos));
    String horariosString = nvsMan.readString();
    int horariosNum = getNumHorarios(horariosString);
    if (horariosNum > 0) {
        String horariosArray[horariosNum];
        getHorarios(horariosArray, horariosString);
        for (int i = 0; i < horariosNum; i++) {
            Serial.println(horaAtual + " | " + horariosArray[i]);
            if (horaAtual == horariosArray[i]) {
                Serial.println("Ta no horario");
                if(!tbot.cancelNext) {
                    Serial.println("Era pra alimentar");
                    funcs.giraServo();
                    tbot.sendMessage("Pet alimentado com sucesso!");
                    delay(1 * 60 *1000);
                } else {
                    tbot.sendMessage("A refeição foi cancelada!");
                    delay(1 * 60 *1000);
                    tbot.cancelNext = false;
                }
            } 
        }
    }
    timeClient.update();
    tbot.respVerify();
}