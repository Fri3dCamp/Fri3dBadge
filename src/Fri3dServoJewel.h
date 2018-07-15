// ensure this library description is only included once
#ifndef Fri3dServoJewel_h
#define Fri3dServoJewel_h

#define BUZZER_PIN 33

#include "Fri3dServo.h"

// library interface description
class Fri3dServoJewel {
private:
    Fri3dServo servos[4];
public:
  Fri3dServoJewel();
  ~Fri3dServoJewel();

  void attach();
  void detach();

  void center(int servoId);
  void angle(int servoId, float toAngle, int steps, int speed);
  void angle(int servoId1, int servoId2, float toAngle, int steps, int speed);
};

#endif