#include "Fri3dLegs.h"
#include "Arduino.h"



Fri3dLegs::Fri3dLegs() {
}

Fri3dLegs::~Fri3dLegs() {
    this->detach();
}

void Fri3dLegs::attach() {
    preferences.begin("legs", false);
    
    for (int i = 0; i < 4; i++) {
        int min = preferences.getUInt(SERVO_MIN[i], MIN_PULSE_WIDTH);
        this->mid[i] = preferences.getUInt(SERVO_MID[i], (MIN_PULSE_WIDTH + MAX_PULSE_WIDTH) / 2);
        int max = preferences.getUInt(SERVO_MAX[i], MAX_PULSE_WIDTH);

        this->rangeLeft[i] = this->mid[i] - min;
        this->rangeRight[i] = max - this->mid[i];

        // this->servos[i].attach(servo_pins[i], min, max);
        // this->servos[i].write(this->mid[i]);
    }

    preferences.end();
}

void Fri3dLegs::detach() {
    for (int i = 0; i < 4; i++) {
        // this->servos[i].detach();
    }
}

void Fri3dLegs::reset() {
    for (int i = 0; i < 4; i++) {
        // this->servos[i].write(this->mid[i]);
    }
}

// -- Hip Rotation ------------------------------------------------------------

void Fri3dLegs::rotateHip(int leg, int pct, int speed) {
    int servoId = (leg == Fri3dLegs::LEFT_LEG) ? LEFT_HIP : RIGHT_HIP;
    
    int val = 0;
    // -- center
    if (pct == 0) val = this->mid[servoId];
    // -- left
    else if (pct < 0) val = this->mid[servoId] - this->rangeLeft[servoId] * (pct / 100);
    // -- right
    else if (pct > 0) val = this->mid[servoId] + this->rangeRight[servoId] * (pct / 100);

    // this->servos[servoId].write(val);
}

// -- Ankle Tilting -----------------------------------------------------------

void Fri3dLegs::tiltAnkle(int leg, int pct, int speed) {
    int servoId = (leg == Fri3dLegs::LEFT_LEG) ? LEFT_ANKLE : RIGHT_ANKLE;

    int val = 0;
    // -- center
    if (pct == 0) val = this->mid[servoId];
    // -- left
    else if (pct < 0) val = this->mid[servoId] - this->rangeLeft[servoId] * (pct / 100);
    // -- right
    else if (pct > 0) val = this->mid[servoId] + this->rangeRight[servoId] * (pct / 100);

    // this->servos[servoId].write(val);
}

// // -- Leaning -----------------------------------------------------------------

// void Fri3dLegs::leanToLeft(int speed) {
//     this->servoJewel.angle(LEFT_ANKLE, ANKLE_MIN_ANGLE);
//     this->servoJewel.angle(RIGHT_ANKLE, ANKLE_MIN_ANGLE, speed);
// }

// void Fri3dLegs::straight(int speed) {
//     this->servoJewel.angle(LEFT_ANKLE, 90, speed);
//     this->servoJewel.angle(RIGHT_ANKLE, 90, speed);
// }

// void Fri3dLegs::leanToRight(int speed) {
//     this->servoJewel.angle(RIGHT_ANKLE, ANKLE_MAX_ANGLE);
//     this->servoJewel.angle(LEFT_ANKLE, ANKLE_MAX_ANGLE, speed);
// }

// // -- Stepping ----------------------------------------------------------------

// void Fri3dLegs::stepForward() {
//     this->leanToLeft(8);
//     this->rotateHipsToLeft(4);
//     this->leanToRight(8);
//     this->rotateHipsToCenter(4);
//     this->straight(8);
// }

// void Fri3dLegs::stepBackward() {
//     this->leanToLeft(8);
//     this->rotateHipsToRight(4);
//     this->leanToRight(8);
//     this->rotateHipsToCenter(4);
//     this->straight(8);
// }

// // -- Turning -----------------------------------------------------------------

// void Fri3dLegs::turnLeft() {
//     this->leanToRight(8);
//     this->rotateHipToLeft(LEFT_LEG, 4);
//     this->straight(8);
//     this->leanToLeft(8);
//     this->rotateHipToCenter(LEFT_LEG, 4);
//     this->straight(8);
// }

// void Fri3dLegs::turnRight() {
//     this->leanToLeft(8);
//     this->rotateHipToRight(RIGHT_LEG, 4);
//     this->straight(8);
//     this->leanToRight(8);
//     this->rotateHipToCenter(RIGHT_LEG, 4);
//     this->straight(8);
// }

// // -- Hello -------------------------------------------------------------------

// void Fri3dLegs::helloLeft() {
//     this->leanToRight(8);
    
//     for (int i = 0; i < 4; i++) {
//         this->servoJewel.angle(LEFT_ANKLE, ANKLE_MIN_ANGLE, 8);
//         this->servoJewel.angle(LEFT_ANKLE, ANKLE_MAX_ANGLE, 8);
//     }

//     this->servoJewel.angle(LEFT_ANKLE, 90, 8);
//     this->straight(8);
// }

// void Fri3dLegs::helloRight() {
//     this->leanToLeft(8);
    
//     for (int i = 0; i < 4; i++) {
//         this->servoJewel.angle(RIGHT_ANKLE, ANKLE_MIN_ANGLE, 8);
//         this->servoJewel.angle(RIGHT_ANKLE, ANKLE_MAX_ANGLE, 8);
//     }

//     this->servoJewel.angle(RIGHT_ANKLE, 90, 8);
//     this->straight(8);
// }