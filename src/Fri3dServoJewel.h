// ensure this library description is only included once
#ifndef Fri3dServoJewel_h
#define Fri3dServoJewel_h

#define BUZZER_PIN 33

#include "Fri3dServo.h"
#include <Preferences.h>

// library interface description
class Fri3dServoJewel {
private:
    Fri3dServo servos[4];
    Preferences preferences;
    
    int servo_pins[4] = { 32, 25, 26, 27 };
    const char* SERVO_MIN[4] = {"s0_min", "s1_min", "s2_min", "s3_min"};
    const char* SERVO_MAX[4] = {"s0_max", "s1_max", "s2_max", "s3_max"};
public:
  Fri3dServoJewel();
  ~Fri3dServoJewel();

  void attach();
  void detach();

  void center(int servoId);
  void angle(int servoId, int toAngle);
  void angle(int servoId, int toAngle, int speed);
  void angle(int servoId1, int servoId2, int toAngle, int speed);
};

#endif