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

void Fri3dLegs::leanToLeft() {
    this->servoJewel.angle(RIGHT_ANKLE, ANKLE_MIN_ANGLE, 8);
    this->servoJewel.angle(LEFT_ANKLE, ANKLE_MIN_ANGLE, 8);
}

void Fri3dLegs::straight() {
    this->servoJewel.angle(RIGHT_ANKLE, 90, 8);
    this->servoJewel.angle(LEFT_ANKLE, 90, 8);
}

void Fri3dLegs::leanToRight() {
    this->servoJewel.angle(LEFT_ANKLE, ANKLE_MAX_ANGLE, 8);
    this->servoJewel.angle(RIGHT_ANKLE, ANKLE_MAX_ANGLE, 8);
}

// -- Stepping ----------------------------------------------------------------

void Fri3dLegs::stepForward() {

}

void Fri3dLegs::stepBackward() {
    
}