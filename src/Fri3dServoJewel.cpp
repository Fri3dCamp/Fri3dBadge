#include "Fri3dServoJewel.h"
#include "Arduino.h"



Fri3dServoJewel::Fri3dServoJewel() {
}

Fri3dServoJewel::~Fri3dServoJewel() {
    this->detach();
}

void Fri3dServoJewel::attach() {
    this->servos[0].attach(32);
    this->servos[1].attach(25);
    this->servos[2].attach(26);
    this->servos[3].attach(27);
}

void Fri3dServoJewel::detach() {
    for (int i = 0; i < 4; i++) {
        this->servos[i].detach();
    }
}

void Fri3dServoJewel::center(int servoId) {
    this->servos[servoId].write(90);
}

void Fri3dServoJewel::angle(int servoId, float toAngle, int steps, int speed) {
    int startPos = this->servos[servoId].read();

    for (int i = 0; i < steps; i++) {
        int val = startPos + (((toAngle - startPos) / steps) * i);
        this ->servos[servoId].write(val);

        delay(speed);
    }
}

void Fri3dServoJewel::angle(int servoId1, int servoId2, float toAngle, int steps, int speed) {
    int startPos1 = this->servos[servoId1].read();
    int startPos2 = this->servos[servoId2].read();

    for (int i = 0; i < steps; i++) {
        int val1 = startPos1 + (((toAngle - startPos1) / steps) * i);
        this ->servos[servoId1].write(val1);

        int val2 = startPos2 + (((toAngle - startPos2) / steps) * i);
        this ->servos[servoId2].write(val2);

        delay(speed);
    }
}