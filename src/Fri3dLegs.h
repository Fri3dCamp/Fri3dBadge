// ensure this library description is only included once
#ifndef Fri3dLegs_h
#define Fri3dLegs_h

#define LEFT_ANKLE 0
#define LEFT_HIP 1
#define RIGHT_HIP 2
#define RIGHT_ANKLE 3

#define HIP_MAX_ANGLE 110
#define HIP_MIN_ANGLE 70

#define ANKLE_MAX_ANGLE 110
#define ANKLE_MIN_ANGLE 70

#include "Fri3dServoJewel.h"

class Fri3dLegs {
private:
    Fri3dServoJewel servoJewel;

public:
  static const int LEFT_LEG = 0;
  static const int RIGHT_LEG = 1;

  Fri3dLegs();
  ~Fri3dLegs();

  void attach();
  void detach();

// -- Simple Movements --------------------------------------------------------

  void rotateHipToLeft(int leg, int speed);
  void rotateHipToCenter(int leg, int speed);
  void rotateHipToRight(int leg, int speed);

  void tiltAnkleToLeft(int leg, int speed);
  void tiltAnkleToCenter(int leg, int speed);
  void tiltAnkleToRight(int leg, int speed);

// -- Complex Movements -------------------------------------------------------

  void leanToLeft();
  void straight();
  void leanToRight();

  // void helloLeft();
  // void helloRight();

  // void shakeLeft();
  // void shakeRight();

  void stepForward();
  void stepBackward();

  // void turnLeft();
  // void turnRight();
};

#endif