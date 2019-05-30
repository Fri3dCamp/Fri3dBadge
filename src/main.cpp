#include <Fri3dServoJewel.h>
#include <Fri3dServo.h>

Fri3dServoJewel* jewel = Fri3dServoJewel::getInstance();

void setup() {
    Serial.begin(115200);
    jewel->attach();
//    jewel.center(0);
}

void loop() {
//    jewel.angle(0, 180, 180, 30);
//    delay(1000);
//    jewel.angle(0, 0, 180, 50);
    for (int i = 0; i < 4; i++) { 
        int range = jewel->max(i) - jewel->min(i);

        int nv = jewel->min(i) + (rand() % range);
        jewel->stateWrite(i, nv, 50);

        Serial.print("Setting Servo ");
        Serial.print(i, DEC);
        Serial.print(" to ");
        Serial.println(nv, DEC);
    }

    delay(5000);
}