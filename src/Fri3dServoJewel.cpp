#include "Fri3dServoJewel.h"
#include "Arduino.h"
#include <Preferences.h>


Fri3dServoJewel::Fri3dServoJewel() {
    preferences.begin("servos", false);
}

Fri3dServoJewel::~Fri3dServoJewel() {
    this->detach();
}

void Fri3dServoJewel::attach() {
    for (int i = 0; i < 4; i++) {
        this->servos[i].attach(
            servo_pins[i], 
            preferences.getUInt(SERVO_MIN[i], MIN_PULSE_WIDTH), 
            preferences.getUInt(SERVO_MAX[i], MAX_PULSE_WIDTH));

        Serial.print("Servo ");
        Serial.print(i, DEC);
        Serial.print(" -> [");
        Serial.print(preferences.getUInt(SERVO_MIN[i], MIN_PULSE_WIDTH), DEC);
        Serial.print(" -");
        Serial.print(preferences.getUInt(SERVO_MAX[i], MAX_PULSE_WIDTH), DEC);
        Serial.println("]");

        this->angle(i, 90, 8);
        delay(500);
    }
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
            // Serial.print("servo ");
            // Serial.print(servoId, DEC);
            // Serial.print(": ");
            // Serial.println(startPos + i, DEC);
        } else {
            this ->servos[servoId].write(startPos + i);
            // Serial.print("servo ");
            // Serial.print(servoId, DEC);
            // Serial.print(": ");
            // Serial.println(startPos + i, DEC);
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