#include <Arduino.h>

class Motor {
  public:
    int pinEn;
    int pin1;
    int pin2;
    
    Motor(int pinEnNmbr, int pin1Nmbr, int pin2Nmbr);

    void setupMotor();
    
    void controlMotor(int pin1State, int pin2State);
};
