// ensure this library description is only included once
#ifndef Fri3dLegs_h
#define Fri3dLegs_h

#define LEFT_ANKLE 0
#define RIGHT_ANKLE 1
#define LEFT_HIP 2
#define RIGHT_HIP 3

#define HIP_MAX_ANGLE 120
#define HIP_MIN_ANGLE 60

#define ANKLE_MAX_ANGLE 120
#define ANKLE_MIN_ANGLE 60

#include "Fri3dServo.h"
#include "Fri3dServoJewel.h"
#include <Preferences.h>

class Fri3dLegs {
private:
    Fri3dServoJewel * jewel = Fri3dServoJewel::getInstance();

    Preferences preferences;

    int rangeLeft[4];
    int mid[4];
    int rangeRight[4];

    int servo_pins[4] = { 32, 25, 26, 27 };

    const char* SERVO_MIN[4] = {"s0_legs_min", "s1_legs_min", "s2_legs_min", "s3_legs_min"};
    const char* SERVO_MID[4] = {"s0_legs_mid", "s1_legs_mid", "s2_legs_mid", "s3_legs_mid"};
    const char* SERVO_MAX[4] = {"s0_legs_max", "s1_legs_max", "s2_legs_max", "s3_legs_max"};

public:
  static const int LEFT_LEG = -1;
  static const int RIGHT_LEG = 1;

  Fri3dLegs();
  ~Fri3dLegs();

  void attach();
  void detach();

  void reset();

// -- Simple Movements --------------------------------------------------------

  /**
   * rotate the hip of the given leg.
   *
   * @param leg   the leg to rotate
   * @param speed the delay in ms to wait between servo steps
   */
  void rotateHip(int leg, int pct, int speed);

  /**
   * tilt the ankle of the given leg.
   *
   * @param leg   the leg of which to tilt the ankle
   * @param speed the delay in ms to wait between servo steps
   */
  void tiltAnkle(int leg, int pct, int speed);

// // -- Complex Movements -------------------------------------------------------

//   /**
//    * lean to the left.
//    *
//    * @param speed the delay in ms to wait between servo steps
//    */
//   void leanToLeft(int speed);

//   /**
//    * stand up straight.
//    *
//    * @param speed the delay in ms to wait between servo steps
//    */
//   void straight(int speed);

//   /**
//    * lean to the right.
//    *
//    * @param speed the delay in ms to wait between servo steps
//    */
//   void leanToRight(int speed);


//   /**
//    * Say hello with the left foot.
//    *
//    * saying hello means leaning to one side and shaking with the foot on the 
//    * free leg.
//    */
//   void helloLeft();

//   /**
//    * Say hello with the right foot.
//    *
//    * saying hello means leaning to one side and shaking with the foot on the 
//    * free leg.
//    */
//   void helloRight();


//   /**
//    * make a single step forward.
//    */
//   void stepForward();

//   /**
//    * make a single step backward.
//    */
//   void stepBackward();

//   /**
//    * turn to the left.
//    */
//   void turnLeft();

//   /**
//    * turn to the right.
//    */
//   void turnRight();
};

#endif