#include <Fri3dServoJewel.h>
#include <Fri3dServo.h>

Fri3dServoJewel jewel;

void setup() {
    Serial.begin(115200);
    jewel.attach();
    jewel.center(0);
}

void loop() {
    jewel.angle(0, 180, 180, 30);
    delay(1000);
    jewel.angle(0, 0, 180, 50);
    delay(1000);
}
