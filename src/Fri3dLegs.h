// ensure this library description is only included once
#ifndef Fri3dLegs_h
#define Fri3dLegs_h

#define LEFT_ANKLE 0
#define RIGHT_ANKLE 1
#define LEFT_HIP 2
#define RIGHT_HIP 3

#define HIP_MAX_ANGLE 120
#define HIP_MIN_ANGLE 60

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

  void reset();

// -- Simple Movements --------------------------------------------------------

  /**
   * rotate the hip of the given leg to left.
   *
   * @param leg   the leg to rotate
   * @param speed the delay in ms to wait between servo steps
   */
  void rotateHipToLeft(int leg, int speed);

  /**
   * rotate the hip of the given leg to the center.
   *
   * @param leg   the leg to rotate
   * @param speed the delay in ms to wait between servo steps
   */
  void rotateHipToCenter(int leg, int speed);

  /**
   * rotate the hip of the given leg to right.
   *
   * @param leg   the leg to rotate
   * @param speed the delay in ms to wait between servo steps
   */
  void rotateHipToRight(int leg, int speed);


  /**
   * rotate both hips to left.
   *
   * @param speed the delay in ms to wait between servo steps
   */
  void rotateHipsToLeft(int speed);

  /**
   * rotate both hips to the center.
   *
   * @param speed the delay in ms to wait between servo steps
   */
  void rotateHipsToCenter(int speed);

  /**
   * rotate both hips to right.
   *
   * @param speed the delay in ms to wait between servo steps
   */
  void rotateHipsToRight(int speed);


  /**
   * tilt the ankle of the given leg to left.
   *
   * @param leg   the leg of which to tilt the ankle
   * @param speed the delay in ms to wait between servo steps
   */
  void tiltAnkleToLeft(int leg, int speed);

  /**
   * tilt the ankle of the given leg to the center.
   *
   * @param leg   the leg of which to tilt the ankle
   * @param speed the delay in ms to wait between servo steps
   */
  void tiltAnkleToCenter(int leg, int speed);

  /**
   * tilt the ankle of the given leg to right.
   *
   * @param leg   the leg of which to tilt the ankle
   * @param speed the delay in ms to wait between servo steps
   */
  void tiltAnkleToRight(int leg, int speed);

// -- Complex Movements -------------------------------------------------------

  /**
   * lean to the left.
   *
   * @param speed the delay in ms to wait between servo steps
   */
  void leanToLeft(int speed);

  /**
   * stand up straight.
   *
   * @param speed the delay in ms to wait between servo steps
   */
  void straight(int speed);

  /**
   * lean to the right.
   *
   * @param speed the delay in ms to wait between servo steps
   */
  void leanToRight(int speed);


  /**
   * Say hello with the left foot.
   *
   * saying hello means leaning to one side and shaking with the foot on the 
   * free leg.
   */
  void helloLeft();

  /**
   * Say hello with the right foot.
   *
   * saying hello means leaning to one side and shaking with the foot on the 
   * free leg.
   */
  void helloRight();


  /**
   * make a single step forward.
   */
  void stepForward();

  /**
   * make a single step backward.
   */
  void stepBackward();

  /**
   * turn to the left.
   */
  void turnLeft();

  /**
   * turn to the right.
   */
  void turnRight();
};

#endif