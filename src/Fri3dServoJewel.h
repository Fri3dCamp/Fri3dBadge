// ensure this library description is only included once
#ifndef Fri3dServoJewel_h
#define Fri3dServoJewel_h

#include "Fri3dServo.h"
#include <Preferences.h>

struct ServoState
{
  int now;
  int wanted;
  int step;
  int min;
  int max;
};

// library interface description
class Fri3dServoJewel {
private:
    static Fri3dServoJewel* instance;
    Fri3dServoJewel();

    Fri3dServo servos[4];
    Preferences preferences;

    hw_timer_t * timer = NULL;
    
    ServoState state[4];

    int servo_pins[4] = { 32, 25, 26, 27 };
    const char* SERVO_MIN[4] = {"s0_min", "s1_min", "s2_min", "s3_min"};
    const char* SERVO_MAX[4] = {"s0_max", "s1_max", "s2_max", "s3_max"};
public:
  static Fri3dServoJewel* getInstance();
  ~Fri3dServoJewel();

  void attach();
  void detach();

  void stateWrite(int servoId, int value, int step);
  void writeNow(int servoId, int value);
  int stateNow(int servoId);
  int stateWanted(int servoId);
  int stateSpeed(int servoId);

  int min(int servoId);
  int max(int servoId);
};

#endif