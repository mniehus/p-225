#include <Arduino.h>
#include <stdint.h>
#include "Motor.h"

#define FRONTLEFT   1
#define FORWARD     2
#define FRONTRIGHT  3
#define LEFT        4
#define STOP        5
#define RIGHT       6
#define BACKLEFT    7
#define BACKWARD    8
#define BACKRIGHT   9

class Robot {
  public:
    String broadcastAddress;
    int directionState;
    
    Robot(String mac);

    void setupRobot();

    void moveRobot(int dir);
};
