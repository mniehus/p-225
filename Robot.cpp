#include "Robot.h"

Motor motorA(12, 13, 15);
Motor motorB(4, 14, 2);

Robot::Robot(String mac) {
  broadcastAddress = mac;
}

void Robot::setupRobot() {
  motorA.setupMotor();
  motorB.setupMotor();
}

void Robot::moveRobot(int dir) {
  directionState = dir;
  switch(dir) {
    case FRONTLEFT:
      motorA.controlMotor(LOW, LOW);
      motorB.controlMotor(LOW, HIGH);          
      delay(250);
      motorA.controlMotor(LOW, HIGH);
      motorB.controlMotor(LOW, HIGH);
      break;
    case FORWARD:
      motorA.controlMotor(LOW, HIGH);
      motorB.controlMotor(LOW, HIGH);
      break;
    case FRONTRIGHT:
      motorA.controlMotor(LOW, HIGH);
      motorB.controlMotor(LOW, LOW);          
      delay(250);
      motorA.controlMotor(LOW, HIGH);
      motorB.controlMotor(LOW, HIGH);
      break;
    case LEFT:
      motorA.controlMotor(LOW, LOW);
      motorB.controlMotor(LOW, HIGH);          
      break;
    case STOP:
      motorA.controlMotor(LOW, LOW);
      motorB.controlMotor(LOW, LOW);
      break;
    case RIGHT:
      motorA.controlMotor(LOW, HIGH);
      motorB.controlMotor(LOW, LOW);          
      break;
    case BACKLEFT:
      motorA.controlMotor(LOW, LOW);
      motorB.controlMotor(HIGH, LOW);          
      delay(250);
      motorA.controlMotor(HIGH, LOW);
      motorB.controlMotor(HIGH, LOW); 
      break;
    case BACKWARD:
      motorA.controlMotor(HIGH, LOW);
      motorB.controlMotor(HIGH, LOW);
      break;
    case BACKRIGHT:
      motorA.controlMotor(HIGH, LOW);
      motorB.controlMotor(LOW, LOW);          
      delay(250);
      motorA.controlMotor(HIGH, LOW);
      motorB.controlMotor(HIGH, LOW);    
      break;          
  }
}
