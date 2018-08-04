#include "Fri3dLegs.h"
#include "Arduino.h"



Fri3dLegs::Fri3dLegs() {
}

Fri3dLegs::~Fri3dLegs() {
    this->detach();
}

void Fri3dLegs::attach() {
    this->servoJewel.attach();
}

void Fri3dLegs::detach() {
    this->servoJewel.detach();
}

void Fri3dLegs::reset() {
    this->servoJewel.center(0);
    this->servoJewel.center(1);
    this->servoJewel.center(2);
    this->servoJewel.center(3);
}

// -- Hip Rotation ------------------------------------------------------------

void Fri3dLegs::rotateHipToLeft(int leg, int speed) {
    int servoId = (leg == Fri3dLegs::LEFT_LEG) ? LEFT_HIP : RIGHT_HIP;
    this->servoJewel.angle(servoId, HIP_MIN_ANGLE, speed);
}

void Fri3dLegs::rotateHipToCenter(int leg, int speed) {
    int servoId = (leg == Fri3dLegs::LEFT_LEG) ? LEFT_HIP : RIGHT_HIP;
    this->servoJewel.angle(servoId, 90, speed);
}

void Fri3dLegs::rotateHipToRight(int leg, int speed) {
    int servoId = (leg == Fri3dLegs::LEFT_LEG) ? LEFT_HIP : RIGHT_HIP;
    this->servoJewel.angle(servoId, HIP_MAX_ANGLE, speed);
}

// -- Ankle Tilting -----------------------------------------------------------

void Fri3dLegs::tiltAnkleToLeft(int leg, int speed) {
    int servoId = (leg == Fri3dLegs::LEFT_LEG) ? LEFT_ANKLE : RIGHT_ANKLE;
    this->servoJewel.angle(servoId, ANKLE_MIN_ANGLE, speed);
}

void Fri3dLegs::tiltAnkleToCenter(int leg, int speed) {
    int servoId = (leg == Fri3dLegs::LEFT_LEG) ? LEFT_ANKLE : RIGHT_ANKLE;
    this->servoJewel.angle(servoId, 90, speed);
}

void Fri3dLegs::tiltAnkleToRight(int leg, int speed) {
    int servoId = (leg == Fri3dLegs::LEFT_LEG) ? LEFT_ANKLE : RIGHT_ANKLE;
    this->servoJewel.angle(servoId, ANKLE_MAX_ANGLE, speed);
}

// -- Leaning -----------------------------------------------------------------

void Fri3dLegs::leanToLeft(int speed) {
    this->servoJewel.angle(RIGHT_ANKLE, ANKLE_MIN_ANGLE, speed);
    this->servoJewel.angle(LEFT_ANKLE, ANKLE_MIN_ANGLE, speed);
}

void Fri3dLegs::straight(int speed) {
    this->servoJewel.angle(RIGHT_ANKLE, 90, speed);
    this->servoJewel.angle(LEFT_ANKLE, 90, speed);
}

void Fri3dLegs::leanToRight(int speed) {
    this->servoJewel.angle(LEFT_ANKLE, ANKLE_MAX_ANGLE, speed);
    this->servoJewel.angle(RIGHT_ANKLE, ANKLE_MAX_ANGLE, speed);
}

// -- Stepping ----------------------------------------------------------------

void Fri3dLegs::stepForward() {
    this->leanToRight(8);
    this->rotateHipToLeft(Fri3dLegs::RIGHT_LEG, 5);
    this->rotateHipToLeft(Fri3dLegs::LEFT_LEG, 5);
    this->straight(12);

    this->leanToLeft(8);
    this->rotateHipToCenter(Fri3dLegs::RIGHT_LEG, 5);
    this->rotateHipToCenter(Fri3dLegs::LEFT_LEG, 5);
    this->straight(12);

    // leantoright();  
  
    // rightfront2center();
    // center2leftfront();
    
    // leanbackright();
    
    // checkproximity();

    // leantoleft();

    // leftfront2center();
    // center2rightfront();
    
    // leanbackleft();

    // checkproximity();

    // self.lean_to_right(speed)
    // self.twist_right(speed)
    // self.undo_lean_to_right(speed)

    // self.lean_to_left(speed)
    // self.twist_center(speed)
    // self.undo_lean_to_left(speed)
}

void Fri3dLegs::stepBackward() {
    // self.lean_to_right(speed)
    // self.twist_left(speed)
    // self.undo_lean_to_right(speed)

    // self.lean_to_left(speed)
    // self.twist_center(speed)
    // self.undo_lean_to_left(speed)
}