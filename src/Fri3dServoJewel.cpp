#include "Fri3dServoJewel.h"
#include "Arduino.h"
#include <Preferences.h>


Fri3dServoJewel::Fri3dServoJewel() {
    
}

Fri3dServoJewel::~Fri3dServoJewel() {
    this->detach();
}

void Fri3dServoJewel::attach() {
    preferences.begin("servos", false);

    for (int i = 0; i < 4; i++) {
        this->servos[i].attach(
            i, 
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

    preferences.end();
}

void Fri3dServoJewel::detach() {
    for (int i = 0; i < 4; i++) {
        this->servos[i].detach();
    }
}

void Fri3dServoJewel::center(int servoId) {
    this->angle(servoId, 90);
}

void Fri3dServoJewel::angle(int servoId, int toAngle) {
    Serial.print("moving servo ");
    Serial.print(servoId, DEC);
    Serial.print(" to ");
    Serial.print(toAngle, DEC);
    Serial.println(" degrees");

    this ->servos[servoId].write(toAngle);
}

void Fri3dServoJewel::angle(int servoId, int toAngle, int speed) {
    Serial.print("moving servo ");
    Serial.print(servoId, DEC);
    Serial.print(" to ");
    Serial.print(toAngle, DEC);
    Serial.print(" degrees using ");
    Serial.print(speed, DEC);
    Serial.println("ms. delays");

    int startPos = this->servos[servoId].read();

    int range = abs(toAngle - startPos);

    for (int i = 1; i <= range; i++) {
        if (toAngle < startPos) {
            this ->servos[servoId].write(startPos - i);
        } else {
            this ->servos[servoId].write(startPos + i);
        }

        delay(speed);
    }
}

void Fri3dServoJewel::angle(int servoId1, int servoId2, int toAngle, int speed) {
    Serial.print("moving servo ");
    Serial.print(servoId1, DEC);
    Serial.print(" and servo ");
    Serial.print(servoId2, DEC);
    Serial.print(" to ");
    Serial.print(toAngle, DEC);
    Serial.print(" degrees using ");
    Serial.print(speed, DEC);
    Serial.println("ms. delays");

    int startPos1 = this->servos[servoId1].read();
    int startPos2 = this->servos[servoId2].read();

    int range1 = abs(toAngle - startPos1);
    int range2 = abs(toAngle - startPos2);

    Serial.print("max range: ");
    Serial.println(max(range1, range2), DEC);

    for (int i = 1; i <= max(range1, range2); i++) {
        if (toAngle < startPos1) {
            if (startPos1 - i > toAngle)
                this ->servos[servoId1].write(startPos1 - i);
        } else {
            if (startPos1 + i < toAngle)
                this ->servos[servoId1].write(startPos1 + i);
        }

        if (toAngle < startPos2) {
            if (startPos2 - i > toAngle)
                this ->servos[servoId2].write(startPos2 - i);
        } else {
            if (startPos2 + i < toAngle)
                this ->servos[servoId2].write(startPos2 + i);
        }

        delay(speed);
    }
}