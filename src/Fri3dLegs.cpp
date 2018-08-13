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

void Fri3dLegs::rotateHipsToLeft(int speed) {
    this->servoJewel.angle(LEFT_HIP, RIGHT_HIP, HIP_MAX_ANGLE, speed);
}

void Fri3dLegs::rotateHipsToCenter(int speed) {
    this->servoJewel.angle(LEFT_HIP, RIGHT_HIP, 90, speed);
}

void Fri3dLegs::rotateHipsToRight(int speed) {
    this->servoJewel.angle(LEFT_HIP, RIGHT_HIP, HIP_MIN_ANGLE, speed);
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
    this->servoJewel.angle(LEFT_ANKLE, ANKLE_MIN_ANGLE);
    this->servoJewel.angle(RIGHT_ANKLE, ANKLE_MIN_ANGLE, speed);
}

void Fri3dLegs::straight(int speed) {
    this->servoJewel.angle(LEFT_ANKLE, 90, speed);
    this->servoJewel.angle(RIGHT_ANKLE, 90, speed);
}

void Fri3dLegs::leanToRight(int speed) {
    this->servoJewel.angle(RIGHT_ANKLE, ANKLE_MAX_ANGLE);
    this->servoJewel.angle(LEFT_ANKLE, ANKLE_MAX_ANGLE, speed);
}

// -- Stepping ----------------------------------------------------------------

void Fri3dLegs::stepForward() {
    this->leanToLeft(8);
    this->rotateHipsToLeft(4);
    this->leanToRight(8);
    this->rotateHipsToCenter(4);
    this->straight(8);
}

void Fri3dLegs::stepBackward() {
    this->leanToLeft(8);
    this->rotateHipsToRight(4);
    this->leanToRight(8);
    this->rotateHipsToCenter(4);
    this->straight(8);
}

// -- Turning -----------------------------------------------------------------

void Fri3dLegs::turnLeft() {
    this->leanToRight(8);
    this->rotateHipToLeft(LEFT_LEG, 4);
    this->straight(8);
    this->leanToLeft(8);
    this->rotateHipToCenter(LEFT_LEG, 4);
    this->straight(8);
}

void Fri3dLegs::turnRight() {
    this->leanToLeft(8);
    this->rotateHipToRight(RIGHT_LEG, 4);
    this->straight(8);
    this->leanToRight(8);
    this->rotateHipToCenter(RIGHT_LEG, 4);
    this->straight(8);
}

// -- Hello -------------------------------------------------------------------

void Fri3dLegs::helloLeft() {
    this->leanToRight(8);
    
    for (int i = 0; i < 4; i++) {
        this->servoJewel.angle(LEFT_ANKLE, ANKLE_MIN_ANGLE, 8);
        this->servoJewel.angle(LEFT_ANKLE, ANKLE_MAX_ANGLE, 8);
    }

    this->servoJewel.angle(LEFT_ANKLE, 90, 8);
    this->straight(8);
}

void Fri3dLegs::helloRight() {
    this->leanToLeft(8);
    
    for (int i = 0; i < 4; i++) {
        this->servoJewel.angle(RIGHT_ANKLE, ANKLE_MIN_ANGLE, 8);
        this->servoJewel.angle(RIGHT_ANKLE, ANKLE_MAX_ANGLE, 8);
    }

    this->servoJewel.angle(RIGHT_ANKLE, 90, 8);
    this->straight(8);
}