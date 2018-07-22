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

void Fri3dServoJewel::angle(int servoId, int toAngle, int speed) {
    int startPos = this->servos[servoId].read();

    int range = abs(toAngle - startPos);

    for (int i = 1; i <= range; i++) {
        if (toAngle < startPos) {
            this ->servos[servoId].write(startPos - i);
            Serial.print("servo ");
            Serial.print(servoId, DEC);
            Serial.print(": ");
            Serial.println(startPos + i, DEC);
        } else {
            this ->servos[servoId].write(startPos + i);
            Serial.print("servo ");
            Serial.print(servoId, DEC);
            Serial.print(": ");
            Serial.println(startPos + i, DEC);
        }

        delay(speed);
    }
}

void Fri3dServoJewel::angle(int servoId1, int servoId2, int toAngle, int speed) {
    int startPos1 = this->servos[servoId1].read();
    int startPos2 = this->servos[servoId2].read();

    int range1 = abs(toAngle - startPos1);
    int range2 = abs(toAngle - startPos2);

    for (int i = 1; i <= max(range1, range2); i++) {
        if (startPos1 + i <= toAngle) {
            if (toAngle < startPos1)
                this ->servos[servoId1].write(startPos1 - i);
            else
                this ->servos[servoId1].write(startPos1 + i);
        }
        
        if (startPos2 + i <= toAngle) {
            if (toAngle < startPos2)
                this ->servos[servoId2].write(startPos2 - i);
            else
                this ->servos[servoId2].write(startPos2 + i);
        }

        delay(speed);
    }
}