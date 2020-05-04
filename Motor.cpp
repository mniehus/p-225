#include "Motor.h"

Motor::Motor(int pinEnNmbr, int pin1Nmbr, int pin2Nmbr) {
  pinEn = pinEnNmbr;
  pin1 = pin1Nmbr;
  pin2 = pin2Nmbr;
}

void Motor::setupMotor() {
  pinMode(pinEn, OUTPUT);
  pinMode(pin1, OUTPUT);  
  pinMode(pin2, OUTPUT);
}

void Motor::controlMotor(int pin1State, int pin2State) {
  digitalWrite(pin1, pin1State);
  digitalWrite(pin2, pin2State);
}
