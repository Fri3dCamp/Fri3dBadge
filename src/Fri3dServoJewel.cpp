#include "Fri3dServoJewel.h"
#include "Arduino.h"
#include <Preferences.h>

portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

Fri3dServoJewel* Fri3dServoJewel::instance = 0;

void IRAM_ATTR onTimer() {
    portENTER_CRITICAL_ISR(&timerMux);
    
    //////////
    // increment the actual state "now" ==> slightly modify it towards the "wanted" state 
    //////////

    // debug
    // Serial.println("fired");

    Fri3dServoJewel * jewel = Fri3dServoJewel::getInstance();
    for (int i=0; i<4; i++) {
        int currentValue = jewel->stateNow(i);        
        int wantedValue = jewel->stateWanted(i);
        int step = jewel->stateSpeed(i);
        
        // enforce the state step
        int currentStep = wantedValue - currentValue;
        if (currentValue == 0) currentStep = 0;
        else if (abs(currentStep) > step) {
            currentStep = (currentStep > 0) ? step : -step;
        }

        int newValue = currentValue + currentStep;

        if (currentStep != 0) {
            jewel->writeNow(i, newValue);
        }

        // int currentStep = min(step, wantedValue - currentValue);
        // int newValue = currentValue + currentStep;

        
        
        // debug
        // Serial.print(i);
        // Serial.print(": ");
        // Serial.print(currentValue, DEC);
        // Serial.print(" + ");
        // Serial.print(currentStep, DEC);
        // Serial.print(" = ");
        // Serial.print(newValue, DEC);
        // Serial.print(" -> ");
        // Serial.print(wantedValue, DEC);
        // Serial.print("\n");
    }
    
    // debug
    // Serial.println("fire done");

    portEXIT_CRITICAL_ISR(&timerMux);
}

Fri3dServoJewel* Fri3dServoJewel::getInstance() {
    if (instance == 0) {
        instance = new Fri3dServoJewel();
    }

    return instance;
}

Fri3dServoJewel::Fri3dServoJewel() {
    
}

Fri3dServoJewel::~Fri3dServoJewel() {
    this->detach();
}

void Fri3dServoJewel::attach() {
    preferences.begin("servos", false);

    for (int i = 0; i < 4; i++) {
        int min = preferences.getUInt(SERVO_MIN[i], MIN_PULSE_WIDTH);
        int max = preferences.getUInt(SERVO_MAX[i], MAX_PULSE_WIDTH);
        int mid = (max - min) / 2;

        this->state[i].min = preferences.getUInt(SERVO_MIN[i], MIN_PULSE_WIDTH);
        this->state[i].max = preferences.getUInt(SERVO_MAX[i], MAX_PULSE_WIDTH);

        this->servos[i].attach(servo_pins[i], min, max);
        this->stateWrite(i, mid, 5);
        this->writeNow(i, mid);
        this->servos[i].write(mid);
        

        Serial.print("Servo ");
        Serial.print(i, DEC);
        Serial.print(" -> [");
        Serial.print(min, DEC);
        Serial.print(" -");
        Serial.print(max, DEC);
        Serial.println("]");
        delay(500);
    }

    preferences.end();

    this->timer = timerBegin(0, 80, true);
    timerAttachInterrupt(this->timer, &onTimer, true);

    // Set alarm to call onTimer function every second (value in microseconds).
    // Repeat the alarm (third parameter)
    timerAlarmWrite(this->timer, 1000, true);

    // Start an alarm
    timerAlarmEnable(this->timer);
}

void Fri3dServoJewel::detach() {
    for (int i = 0; i < 4; i++) {
        this->servos[i].detach();
    }
}

void Fri3dServoJewel::writeNow(int servoId, int value) {
    // Serial.print(servoId, DEC);
    // Serial.print(" -> ");
    // Serial.println(value, DEC);
    this->state[servoId].now = value;
    this->servos[servoId].writeMicroseconds(value * 1000);
}

void Fri3dServoJewel::stateWrite(int servoId, int value, int step) {
    this->state[servoId].wanted = value;
    this->state[servoId].step = step;
}
  
int Fri3dServoJewel::stateNow(int servoId) {
    return this->state[servoId].now;
}

int Fri3dServoJewel::stateWanted(int servoId) {
    return this->state[servoId].wanted;
}

int Fri3dServoJewel::stateSpeed(int servoId) {
    return this->state[servoId].step;
}

int Fri3dServoJewel::min(int servoId) {
    return this->state[servoId].min;
} 

int Fri3dServoJewel::max(int servoId) {
    return this->state[servoId].max;
}

// void Fri3dServoJewel::center(int servoId) {
//     this->angle(servoId, 90);
// }

// void Fri3dServoJewel::angle(int servoId, int toAngle) {
//     Serial.print("moving servo ");
//     Serial.print(servoId, DEC);
//     Serial.print(" to ");
//     Serial.print(toAngle, DEC);
//     Serial.println(" degrees");

//     this ->servos[servoId].write(toAngle);
// }

// void Fri3dServoJewel::angle(int servoId, int toAngle, int speed) {
//     Serial.print("moving servo ");
//     Serial.print(servoId, DEC);
//     Serial.print(" to ");
//     Serial.print(toAngle, DEC);
//     Serial.print(" degrees using ");
//     Serial.print(speed, DEC);
//     Serial.println("ms. delays");

//     int startPos = this->servos[servoId].read();

//     int range = abs(toAngle - startPos);

//     for (int i = 1; i <= range; i++) {
//         if (toAngle < startPos) {
//             this ->servos[servoId].write(startPos - i);
//         } else {
//             this ->servos[servoId].write(startPos + i);
//         }

//         delay(speed);
//     }
// }

// void Fri3dServoJewel::angle(int servoId1, int servoId2, int toAngle, int speed) {
//     Serial.print("moving servo ");
//     Serial.print(servoId1, DEC);
//     Serial.print(" and servo ");
//     Serial.print(servoId2, DEC);
//     Serial.print(" to ");
//     Serial.print(toAngle, DEC);
//     Serial.print(" degrees using ");
//     Serial.print(speed, DEC);
//     Serial.println("ms. delays");

//     int startPos1 = this->servos[servoId1].read();
//     int startPos2 = this->servos[servoId2].read();

//     int range1 = abs(toAngle - startPos1);
//     int range2 = abs(toAngle - startPos2);

//     Serial.print("max range: ");
//     Serial.println(max(range1, range2), DEC);

//     for (int i = 1; i <= max(range1, range2); i++) {
//         if (toAngle < startPos1) {
//             if (startPos1 - i > toAngle)
//                 this ->servos[servoId1].write(startPos1 - i);
//         } else {
//             if (startPos1 + i < toAngle)
//                 this ->servos[servoId1].write(startPos1 + i);
//         }

//         if (toAngle < startPos2) {
//             if (startPos2 - i > toAngle)
//                 this ->servos[servoId2].write(startPos2 - i);
//         } else {
//             if (startPos2 + i < toAngle)
//                 this ->servos[servoId2].write(startPos2 + i);
//         }

//         delay(speed);
//     }
// }