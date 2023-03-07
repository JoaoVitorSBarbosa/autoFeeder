#include "../include/funcsAux.h"

Servo servo;

FuncsAux::FuncsAux() {
    servo.attach(SERVO_PIN);
}

void FuncsAux::giraServo() {
    servo.attach(SERVO_PIN);
    int pos = 0;
    for (pos = 0; pos < 180; pos++) {
        servo.write(pos); 
        Serial.println(pos);
    }
    delay(10);
    for (pos = 180; pos > 0; pos--) {  
        servo.write(pos);                   
        Serial.println(pos);                       
    }
}