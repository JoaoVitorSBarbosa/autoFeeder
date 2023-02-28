#include "../include/funcsAux.h"

Servo servo;

FuncsAux::FuncsAux() {
    servo.attach(SERVO_PIN);
}

void FuncsAux::giraServo() {
    int pos = 0;
    for (pos = 0; pos <= 180; pos += 1) {  // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        servo.write(pos);  // tell servo to go to position in variable 'pos'
        delay(10);         // waits 15ms for the servo to reach the position
    }
    delay(10);
    for (pos = 180; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
        servo.write(pos);                  // tell servo to go to position in variable 'pos'
        delay(10);                         // waits 15ms for the servo to reach the position
    }
}

void FuncsAux::getTime() {

}