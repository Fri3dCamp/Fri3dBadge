#include <Fri3dLegs.h>

Fri3dLegs legs;

void setup() {
    Serial.begin(115200);
    legs.attach();
    Serial.println("attached");
}

void loop() {
  readSerial();
//  Serial.println("straight");
//    legs.straight(8);
//    delay(3000);
//    Serial.println("leanToLeft");
//    legs.leanToLeft(8);
//    delay(3000);
//    Serial.println("straight");
//    legs.straight(8);
//    delay(3000);
//    Serial.println("leanToRight");
//    legs.leanToRight(8);
//    delay(3000);
    
}

void readSerial() {
  while (Serial.available() > 0) {
    String in = Serial.readStringUntil('\n');
      
    if (in.startsWith("LL")) {
      legs.leanToLeft(4);
    } else if (in.startsWith("LR")) {
      legs.leanToRight(4); 
    } else if (in.startsWith("LC")) {
      legs.straight(4);
    } else if (in.startsWith("F")) {
      legs.stepForward();
    } else if (in.startsWith("B")) {
      legs.stepBackward();  
    } else if (in.startsWith("TL")) {
      legs.turnLeft();
    } else if (in.startsWith("TR")) {
      legs.turnRight();  
    } else if (in.startsWith("HL")) {
      legs.helloLeft();
    } else if (in.startsWith("HR")) {
      legs.helloRight();
    } else if (in.startsWith("R")) {
      legs.reset(); 
    } else if (in.startsWith("D")) {
      legs.detach();
    } else {
      Serial.println("Unknown command");
    }
  }
}

