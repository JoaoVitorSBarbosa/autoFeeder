#include "../include/funcsAux.h"

Servo servo;

FuncsAux::FuncsAux() {
    servo.attach(SERVO_PIN);
}

void FuncsAux::initServo() {
    servo.attach(SERVO_PIN);
    int pos = 0;
    for (pos = 0; pos < SERVO_INIT_POS; pos++) {
        servo.write(pos); 
    }
}
void FuncsAux::giraServo() {
    servo.attach(SERVO_PIN);
    int pos = 180;
    for (pos = 180; pos > 0; pos--) {  
        servo.write(pos);                                       
    }
    delay(10);
    for (pos = 0; pos < 180; pos++) {
        servo.write(pos); 
    }
    delay(10);
    
}